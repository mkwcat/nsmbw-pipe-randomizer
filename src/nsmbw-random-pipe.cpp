#include "SndSceneMgr.hpp"
#include "d_actor.hpp"
#include "d_cs_seq_mgr.hpp"
#include "d_fader.hpp"
#include "d_game_com.hpp"
#include "d_info.hpp"
#include "d_next.hpp"
#include "d_pl_base.hpp"
#include "d_save_mng.hpp"
#include "d_sc_crsin.hpp"
#include "d_sc_stage.hpp"
#include "d_sc_wmap.hpp"
#include "d_scene.hpp"
#include "dvd.h"
#include "lyt_base.hpp"
#include "pipe_entry_list.h"
#include <kamek.h>

enum RandBase {
    RAND_BASE_BOOT = 0, // Randomize on starting the game
    RAND_BASE_COURSE = 1, // Randomize on entering a course
    RAND_BASE_ALWAYS = 2, // Randomize on entering a pipe
    RAND_BASE_FILE = 3, // Use seed.txt
};

extern RandBase g_randBase;
u16 g_entryLookup[PipeEntryCount];
bool g_madeEntryTable = false;

// Redirect save file to piperng.sav
kmWrite32(0x802F148C, 0x70697065);
kmWrite32(0x802F1490, 0x726E672E);
kmWrite32(0x802F1494, 0x73617600);

class EntranceSorter
{
public:
    EntranceSorter(u16* lookupTable, u32 seed)
    {
        m_entryLookup = lookupTable;
        m_seed = seed;

        m_excEntIndex = 0;
        m_excEntCount = 0;
        m_curGroupEnd = 0;

        m_entCount = 0;
        m_ptrEntList = m_entList;

        // Add grouped entries to the list first
        bool inGroup = false;
        for (u32 i = 0; i < PipeEntryCount; i++) {
            u32 entry = i | ((PipeEntryList[i] & 0xF000) << 16);
            u8 flags = (entry >> 28);
            if (!inGroup && flags == 0x0) {
                continue;
            }

            // Write index and group flags
            m_entList[m_entCount++] = entry;

            if (flags & 0x2) {
                inGroup = false;
            } else if (flags & 0x1) {
                inGroup = true;
            } else if (flags & 0x3) {
                // If the entrance is by itself in a group then move it to
                // exclusive
                MoveToExclusive(m_entCount - 1);
            }

            m_entryLookup[i] = 0;
        }

        // Add non-grouped entries to the list
        inGroup = false;
        u32 lastGroupedEnt = m_entCount;
        for (u32 i = 0; i < PipeEntryCount; i++) {
            // Write index and copy group flags
            u32 entry = i | ((PipeEntryList[i] & 0xF000) << 16);
            u8 flags = (entry >> 28);
            if (inGroup || flags != 0x0) {
                if (flags & 0x2) {
                    inGroup = false;
                } else if (flags & 0x1) {
                    inGroup = true;
                }

                continue;
            }

            // Write index
            m_entList[m_entCount++] = entry;
        }

        // Reserve a random non-exclusive entrance for the last link
        u32 idx = lastGroupedEnt +
                  getRandomFromSeed(&m_seed, m_entCount - lastGroupedEnt);
        m_lastEntrance = m_entList[idx];
        Remove(idx);
    }

    void CreateLookupTable()
    {
        while (m_entCount > 0) {
            u32 ent1 = SelectEntrance1();
            u32 ent2 = SelectEntrance2() & 0x0FFFFFFF;

            bool exc = (ent1 >> 28) == 0x3;
            ent1 &= 0x0FFFFFFF;

            m_entryLookup[ent1] = ent2;
            m_entryLookup[ent2] = ent1;

#if 0
            if (exc) {
                dInfo_c::StartGameInfo_s sginfo;
                dInfo_c::StartGameInfo_s sginfo2;

                u32 entry = ent1;
                sginfo.world1 = (PipeEntryList[entry] >> 24) & 0xFF;
                sginfo.level1 = (PipeEntryList[entry] >> 16) & 0xFF;
                sginfo.entrance = PipeEntryList[entry] & 0xFF;
                sginfo.area = (PipeEntryList[entry] >> 8) & 0x0F;

                entry = ent2;
                sginfo2.world1 = (PipeEntryList[entry] >> 24) & 0xFF;
                sginfo2.level1 = (PipeEntryList[entry] >> 16) & 0xFF;
                sginfo2.entrance = PipeEntryList[entry] & 0xFF;
                sginfo2.area = (PipeEntryList[entry] >> 8) & 0x0F;

                OSReport(
                    "%d-%d area %d ent %d: %d-%d area %d ent %d\n",
                    sginfo.world1 + 1, sginfo.level1 + 1, sginfo.area + 1,
                    sginfo.entrance, sginfo2.world1 + 1, sginfo2.level1 + 1,
                    sginfo2.area + 1, sginfo2.entrance
                );
            }
#endif
        }
    }

private:
    u32 SelectEntrance1()
    {
        // Exclusive entrances always go first
        if (m_excEntCount != 0) {
            m_excEntCount--;
            return m_excEntList[m_excEntIndex++];
        }

        // Reset exclusive index
        m_excEntIndex = 0;

        if (m_curGroupEnd == 0) {
            // Not in a group
            u32 val = m_ptrEntList[0];
            if ((val >> 28) != 0x1) {
                RemoveEntrance(0);
                return val;
            }

            // Start of a group, let's find the end
            for (u32 i = 0; i < m_entCount; i++) {
                if ((m_ptrEntList[i] >> 28) == 0x2) {
                    m_curGroupEnd = i + 1;
                    break;
                }
            }

            // Then fall through to the group code
        }

        // Randomly select an entrance within the group. This will make sure
        // that which entry ends up exclusive will be evenly distributed.
        u32 i = getRandomFromSeed(&m_seed, m_curGroupEnd);
        u32 val = m_ptrEntList[i];
        RemoveEntrance(i);

        return val;
    }

    u32 SelectEntrance2()
    {
        // Entrance 2 cannot be an exclusive entrance
        u32 i = getRandomFromSeed(&m_seed, m_entCount);
        u32 val = m_ptrEntList[i];
        RemoveEntrance(i);

        return val;
    }

    void MoveToExclusive(u32 idx)
    {
        u32 val = m_ptrEntList[idx];
        Remove(idx);
        m_excEntList[m_excEntIndex + m_excEntCount] = val;
        m_excEntCount++;
    }

    void Remove(u32 idx)
    {
        if (idx < m_curGroupEnd) {
            m_curGroupEnd--;
        }

        if (idx == 0) {
            m_ptrEntList += 1;
            m_entCount -= 1;
            return;
        }

        if (idx == (m_entCount - 1)) {
            m_entCount -= 1;
            return;
        }

        memmove(
            m_ptrEntList + idx, m_ptrEntList + idx + 1,
            (m_entCount - idx - 1) * sizeof(u32)
        );
        m_entCount -= 1;
    }

    void RemoveEntrance(u32 idx)
    {
        u32 val = m_ptrEntList[idx];

        if ((val >> 28) == 0x1) {
            // Start of group
            m_ptrEntList[idx + 1] |= 0x1 << 28;
            if ((m_ptrEntList[idx + 1] >> 28) == 0x3) {
                MoveToExclusive(idx + 1);
            }
        }

        if ((val >> 28) == 0x2) {
            // End of group
            m_ptrEntList[idx - 1] |= 0x2 << 28;
            if ((m_ptrEntList[idx - 1] >> 28) == 0x3) {
                MoveToExclusive(idx - 1);
                idx--;
            }
        }

        Remove(idx);
    }

    u32 m_entList[PipeEntryCount];
    u32 m_entCount;
    u32* m_ptrEntList;

    u32 m_excEntList[PipeEntryCount];
    u32 m_excEntCount;
    u32 m_excEntIndex;

    u32 m_curGroupEnd;

    u32 m_lastEntrance;

    u16* m_entryLookup;
    u32 m_seed;
};

void MakeEntryTable(u32 seed)
{
    EntranceSorter sorter(g_entryLookup, seed);
    sorter.CreateLookupTable();
}

extern "C" {
s32 atoi(const char* str);
extern int errno;
}

u16 LoadSeedTxt()
{
    s32 entryNum = DVDConvertPathToEntrynum("/seed.txt");
    if (entryNum == -1) {
        OSReport("seed.txt not found\n");
        return 0;
    }

    DVDFileInfo fileInfo;
    if (!DVDFastOpen(entryNum, &fileInfo)) {
        OSReport("Failed to open seed.txt\n");
        return 0;
    }

    if (fileInfo.length > 0x7DF) {
        OSReport("seed.txt is too big\n");
        DVDClose(&fileInfo);
        return 0;
    }

    static char seedDataSym[0x800];
    memset(seedDataSym, 0, sizeof(seedDataSym));
    // iirc Kamek doesn't care for symbol alignment
    char* seedData = (char*) (((u32) seedDataSym + 31) & ~31);

    DVDRead(&fileInfo, seedData, fileInfo.length, 0);
    DVDClose(&fileInfo);

    // Ignore whitespace characters and lines starting with #
    char* ptr = seedData;
    while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\r' ||
           *ptr == '#') {
        if (*ptr == '#') {
            while (*ptr != '\n' && *ptr != '\0') {
                ptr++;
            }
        }
        ptr++;
    }

    while (*ptr != '\0') {
        errno = 0;
        u32 value = u32(atoi(ptr));

        if (errno == 0) {
            return value;
        }

        ptr++;
    }

    return 0;
}

u32 g_playerStarTimer[4] = {0, 0, 0, 0};

void GoToNewStage(u32 index, dNext_c* next)
{
    dActor_c::mExecStopReq |= 0xF;

    // The fog is coming
    if (dScStage_c::m_gameMode == 4) {
        dFader_c::setFader(dFader_c::unk_fade_1);
    } else {
        dFader_c::setFader(next->fadeType);
    }

    dScCrsin_c::m_isDispOff = true;
    dScStage_c::m_exitMode = 4;

    // Save player star timer
    for (u32 i = 0; i < 4; i++) {
        g_playerStarTimer[i] = 0;

        daPlBase_c* ply = daPyMng_c::getPlayer(i);
        if (ply) {
            g_playerStarTimer[i] = ply->starTimer;
        }
    }

    u32 entry = 0;

    switch (g_randBase) {
    default: // Boot / Course
        // Not actually done on boot but it's indistinguishable
        if (!g_madeEntryTable) {
            MakeEntryTable(
                dGameCom::getRandom(0x10000) |
                (dGameCom::getRandom(0x10000) << 16)
            );
            g_madeEntryTable = true;
        }
        entry = g_entryLookup[index];
        break;

    case RAND_BASE_ALWAYS:
        entry = dGameCom::getRandom(PipeEntryCount);
        break;

    case RAND_BASE_FILE:
        if (!g_madeEntryTable) {
            MakeEntryTable(LoadSeedTxt());
            g_madeEntryTable = true;
        }
        entry = g_entryLookup[index];
        break;
    }

    u32 entData = PipeEntryList[entry];

    dInfo_c::StartGameInfo_s sginfo;
    sginfo.unk_0 = 0;
    sginfo.replayType = 0;
    sginfo.entrance = entData & 0xFF;
    sginfo.area = (entData >> 8) & 0x0F;
    sginfo.unk_7 = 0;
    sginfo.purpose = 0;
    sginfo.world1 = (entData >> 24) & 0xFF;
    sginfo.level1 = (entData >> 16) & 0xFF;
    sginfo.world2 = (entData >> 24) & 0xFF;
    sginfo.level2 = (entData >> 16) & 0xFF;

    dInfo_c::instance()->startGame(sginfo);
}

kmBranchDefCpp(0x800D03B8, 0, void, dNext_c* next)
{
    // TODO: binary search maybe?
    u32 world = dInfo_c::m_startGameInfo.world1;
    u32 stage = dInfo_c::m_startGameInfo.level1;
    u32 area = (dScene_c::mPara >> 8) & 0xFF;
    u32 entrance = next->entrance.entryId;

    u32 entData = (world << 24) | (stage << 16) | (area << 8) | entrance;
    for (u32 i = 0; i < PipeEntryCount; i++) {
        if ((PipeEntryList[i] & 0xFFFF0FFF) == entData) {
            // This is one of our entrances!
            GoToNewStage(i, next);
            return;
        }
    }

    next->changeScene();
}

// Powerup persistance patches

kmCallDefCpp(0x80144D0C, u32, void)
{
    if (dScStage_c::m_exitMode == 4) {
        return 0;
    }

    return dScStage_c::m_exitMode;
}

kmBranchDefAsm(0x809251D8, 0)
{
    extern void RestorePlayerInfo();

    // clang-format off
    cmpwi r0, 4
    beqlr
    b RestorePlayerInfo
    // clang-format on
}

// Worldmap node select patches

bool g_exitedLevel = false;

bool IsW3Scene2Stage(int level)
{
    switch (level + 1) {
    case 4:
    case 5:
    case 24: // Castle
    case 28: // Star Toad House
    case 29: // Powerup Toad House 2
        return true;
    }

    return false;
}

kmCallDefCpp(0x80102580, void, int world, int r4, int r5)
{
    extern void GoToWorldMap(int, int, int);

    dScStage_c* stage = dScStage_c::instance();

    if (dScStage_c::m_exitMode == 0) {
        // Course Clear
        stage->enteredWorld = dInfo_c::m_startGameInfo.world2;
        stage->enteredLevel = dInfo_c::m_startGameInfo.level2;
        dScWMap_c::m_PrevWorldNo = stage->enteredWorld;
        dScWMap_c::m_PrevSceneNo = 0;

        // Second part of World 3
        if (stage->enteredWorld == 2 && IsW3Scene2Stage(stage->enteredLevel)) {
            dScWMap_c::m_PrevSceneNo = 1;
        }
    }

    g_exitedLevel = true;
    GoToWorldMap(dScWMap_c::m_PrevWorldNo, dScWMap_c::m_PrevSceneNo, r5);
}

bool SkipNodeOverride(int world, int level)
{
    // In particular, ambush stages should be skipped
    if (level == 32 || level == 33 || level == 34) {
        return true;
    }

    return false;
}

kmCallDefCpp(0x808DF33C, void, u32 wm)
{
    extern void WM_PathInit(u32 wm); // 0x808E13F0
    extern u32 WM_GetNodeIDFromName(
        u32, const char* name,
        int r5
    ); // 0x800F3380
    extern bool WM_GetNodeNameFromStage(
        int world, int level,
        char* out
    ); // 0x800F9480

    // Weird place to put this but it should work
    if (g_randBase == RAND_BASE_COURSE) {
        g_madeEntryTable = false;
    }

    if (g_exitedLevel &&
        !SkipNodeOverride(
            dInfo_c::m_startGameInfo.world2, dInfo_c::m_startGameInfo.level2
        )) {
        dScStage_c* stage = dScStage_c::instance();

        g_exitedLevel = false;
        if (stage->enteredWorld == 0xFF || stage->enteredLevel == 0xFF) {
            // This will happen when transferring to a different world
            stage->enteredWorld = dInfo_c::m_startGameInfo.world2;
            stage->enteredLevel = dInfo_c::m_startGameInfo.level2;

            dScWMap_c::m_WorldNo = stage->enteredWorld;
        }

        char name[8];
        WM_GetNodeNameFromStage(stage->enteredWorld, stage->enteredLevel, name);

        // Override the node chosen on entering the stage
        stage->wmNode = WM_GetNodeIDFromName(
            wm + *(int*) (wm + 0x338C) * 0x3F08 + 0x5C7F4, name, 13
        );
    }

    WM_PathInit(wm);
}

kmCallDefCpp(0x808FB584, void, dMj2dGame_c* save)
{
    // Unlock all worlds from the start
    save->onWorldDataFlag(0, 1);
    save->onWorldDataFlag(1, 1);
    save->onWorldDataFlag(2, 1);
    save->onWorldDataFlag(3, 1);
    save->onWorldDataFlag(4, 1);
    save->onWorldDataFlag(5, 1);
    save->onWorldDataFlag(6, 1);
    save->onWorldDataFlag(7, 1);
    save->onWorldDataFlag(8, 1);
}

// Show all worlds on Star Coin screen
kmWrite32(0x807749A8, 0x38600001);

// Always show airship on Star Coin screen
kmWrite32(0x80776B00, 0x38600001);

// Always show final castle in World 8 on Star Coin screen
kmWrite32(0x80776B3C, 0x38600001);

// If the course is clear then it must be open

extern "C" {
extern bool IsCourseClear__6dWmLibFii(int world, int stage);
}

// clang-format off
kmBranchDefAsm(0x800FA4A4, 0x800FA4A8)
{
    ble-    L_End

    mr      r3, r28
    mr      r4, r20
    bl      IsCourseClear__6dWmLibFii
    cmpwi   r3, 0
    beq-    L_NotClear

    // Branch will not be taken
    cmpw    r0, r0
    b       L_End

L_NotClear:
    // Branch will be taken
    li      r0, 1
    cmpwi   r0, 0

L_End:
    li      r26, 0
    blr
}

// clang-format on

extern bool IsWorldCollectionCoinComplete(int world);

// isSpecialWorldCourseOpen__6dWmLibFi
kmBranchDefCpp(0x800FC580, 0, bool, int stage)
{
    if (IsCourseClear__6dWmLibFii(8, stage)) {
        return true;
    }

    if (IsWorldCollectionCoinComplete(stage)) {
        return true;
    }

    return false;
}

// Always go to the next world when the castle level is completed
kmWrite32(0x808CC968, 0x41820050);
kmWrite32(0x808CC970, 0x41820048);
kmWrite32(0x808CC9E0, 0x38600001);

// Kick the player out of Peach's Castle

static u32 smc_demo_castle_in_fail[][2] = {
    {128, 0}, // lock_hud_visibility
    {114, 0}, // ?
    {136, 0}, // ?
    {0, 10}, // wait 10 frames
    {51, 0}, // set direction to up
    {19, 0}, // open castle doors
    {10, 0}, // trigger walking into castle animation
    {52, 0}, // set direction to down
    {0, 30}, // wait 30 frames
    {11, 1}, // trigger castle fail animation
    {20, 0}, // close castle doors
    {130, 0}, // ?
    {115, 0}, // ?
    {129, 0}, // unlock_hud_visibility
    {5, 0}, // end script
};
// Inject in script 35
kmWritePointer(0x8031DC58, smc_demo_castle_in_fail);

// Change the script used for entering Peach's Castle
kmWrite32(0x80904538, 0x38800023);

#if 0
kmCallDefCpp(0x8090CB10, int, void* obj, int world, int stage)
{
    extern int WM_StartStage(void* obj, int world, int stage);

    if (world == 0 && stage == 40) {
        // dCsSeqMng_c::ms_instance->addScriptToQueue(10, 0, 0, 128);

        // smc_demo_castle_fail
        dCsSeqMng_c::ms_instance->m_cmdIndex = 0;
        dCsSeqMng_c::ms_instance->m_script = 10;
        return 0;
    }

    return WM_StartStage(obj, world, stage);
}
#endif

#ifdef WORLDMAP_DEBUG
kmBranchDefCpp(0x800FA9D0, 0, int, int world, int stage)
{
    OSReport("GetClearStatus(): Check %02d-%02d\n", world + 1, stage + 1);
    return 1;
}
#endif

// Always can save patches

kmWrite32(0x8077AA7C, 0x60000000); // message
kmWrite32(0x8092FD00, 0x38000002); // button behavior

// Save Star Coin stuff!
kmCallDefCpp(0x80AAA364, void, int coin, int state)
{
    dScStage_c::setStarCoinState(coin, state);

    if (dInfo_c::m_startGameInfo.purpose != 0) {
        return;
    }

    if (state == 4) {
        return;
    }

    dSaveMng_c::instance()->getMj2dGame(-1)->setCollectCoin(
        dInfo_c::m_startGameInfo.world2, dInfo_c::m_startGameInfo.level2,
        1 << coin
    );
}

kmBranchDefCpp(0x8005F4CC, 0, void, void)
{
    // Restore player star timer
    for (u32 i = 0; i < 4; i++) {
        if (g_playerStarTimer[i] == 0)
            continue;

        daPlBase_c* ply = daPyMng_c::getPlayer(i);
        if (ply) {
            ply->beginStar(1, g_playerStarTimer[i]);
        }

        g_playerStarTimer[i] = 0;
    }

    // Stop P-Switch music
    SndSceneMgr::instance()->stopBgmFlag(8);
}

// Don't hide Star Coins on Coin Battle stages
kmCallDefCpp(0x80157EB8, void, u8* layout)
{
    if (dInfo_c::m_startGameInfo.level2 == 19) {
        return;
    }

    layout[0xBB] &= ~1;
}

// Show Coin Battle stages properly on pause menu
extern u32 m_startGameInfo__7dInfo_c;

kmCallDefAsm(0x8015ACC4)
{
    // clang-format off
    nofralloc
    rlwinm. r0, r0, 0x0, 0x19, 0x19
    bne L_out

    lis r8, (m_startGameInfo__7dInfo_c + 0xF)@ha
    lbzu r5, (m_startGameInfo__7dInfo_c + 0xF)@l(r8)
    cmpwi r5, 19
    bne L_out

    ori r0, r0, 0x40
    lbz r4, -1(r8)

L_out:
    rlwinm. r0, r0, 0x0, 0x19, 0x19
    blr
    // clang-format on
}

// Hide timer
// kmWrite32(0x80157E24, 0x60000000);

// Set time display to ---
kmBranchDefCpp(0x800E3A20, 0, void, void)
{
    u32* gameDisplay = dScStage_c::getGameDisplay();
    LytTextBox_c* timerLyt = (LytTextBox_c*) gameDisplay[0x4E0 / 4];

    timerLyt->setText(L"---", 0);
}

// Set time to 0
kmBranchDefCpp(0x800E3A00, 0, void, u8* obj, u32 time)
{
    *(u16*) (obj + 0x8) = 0;
    *(u32*) (obj + 0x4) = 0;
}

// Stub dGameDisplay_c::executeState_ProcGoalSettleUp to remove the time ->
// score sound
kmBranchDefCpp(0x801590B0, 0, void, u8* obj)
{
    // TODO: Wait for boss stages so the fanfare doesn't cut off?

    *(u32*) (obj + 0x400) = 0;

    extern u32 StateID_ProcGoalEnd__14dGameDisplay_c;

    (*(void (*)(u8*, u32*)) * (u32*) (*(u32*) (obj + 0x390) + 0x18))(
        obj + 0x390, &StateID_ProcGoalEnd__14dGameDisplay_c
    );
}

// Remove checkpoint flag
kmWrite32(0x807E215C, 0x60000000);

// Remove Select World layout

// clang-format off
kmCallDefAsm(0x8001038C)
{
    lwz     r5, 0x3A4(r31) // N_guideViewC_00
    lbz     r4, 0xBB(r5) // is visible flags thing
    rlwinm  r4, r4, 0, 24, 30
    stb     r4, 0xBB(r5)

    li      r0, 0x2
    blr
}

// clang-format on

kmWrite32(0x80012580, 0x60000000);

#ifndef WORLDMAP_DEBUG
// Disable pressing minus to select world
kmWrite32(0x809042C8, 0x48000024);

// Skip loading World Select assets
kmWrite32(0x8091CDB0, 0x4E800020);
kmWrite32(0x80926CE4, 0x48000050);

// Remove creating world select managers
kmWrite32(0x80926E68, 0x38600000);
kmWrite32(0x80926E80, 0x38600000);
kmWrite32(0x80926E98, 0x60000000);

// Remove load world select wait
kmWrite32(0x809270F4, 0x38000001);

// Remove load world select guide wait
kmWrite32(0x80927100, 0x38000001);

// Skip loading world select islands
kmWrite32(0x809272DC, 0x48000034);
#endif

// Skip opening cutscene
kmWrite32(0x809191C4, 0x48000018);

// Skip title screen movies
kmWrite32(0x80781FB8, 0x60000000);
kmWrite32(0x80781FBC, 0x38600000);

// Always allow exiting a level
kmBranchDefCpp(0x800B4E30, 0, bool, void)
{
    return true;
}
