#include "d_actor.hpp"
#include "d_fader.hpp"
#include "d_game_com.hpp"
#include "d_info.hpp"
#include "d_next.hpp"
#include "d_save_mng.hpp"
#include "d_sc_crsin.hpp"
#include "d_sc_stage.hpp"
#include "d_sc_wmap.hpp"
#include "d_scene.hpp"
#include "pipe_entry_list.h"
#include <kamek.h>

#if 0
kmBranchDefCpp(0x800D026C, 0x800D0340, void, void)
#endif

enum RandBase {
    RAND_BASE_SAVE, // Randomize on creating a file
    RAND_BASE_COURSE, // Randomize on entering a course
    RAND_BASE_ALWAYS, // Randomize on entering a pipe
};

RandBase g_randBase = RAND_BASE_SAVE;
u16 g_entryLookup[PipeEntryCount];

bool g_madeEntryTable = false;

void MakeEntryTable(u32 seed)
{
    u16 openEntries[PipeEntryCount];

    for (u32 i = 0; i < PipeEntryCount; i++) {
        openEntries[i] = i;
        g_entryLookup[i] = 0;
    }

    u16* ptrOpenEntries = openEntries;

    for (s32 openEntryCount = PipeEntryCount; openEntryCount > 0;
         openEntryCount -= 2) {
        u32 j = getRandomFromSeed(&seed, openEntryCount - 1) + 1;

        g_entryLookup[ptrOpenEntries[0]] = ptrOpenEntries[j];
        g_entryLookup[ptrOpenEntries[j]] = ptrOpenEntries[0];

        // Remove the entry from the list
        memmove(ptrOpenEntries + j, ptrOpenEntries + j + 1,
                (openEntryCount - j - 1) * 2);

        ptrOpenEntries += 1;
    }
}

void GoToNewStage(u32 index, dNext_c* next)
{
    dActor_c::mExecStopReq |= 0xF;

    // The fog is coming
    if (dScStage_c::m_gameMode == 4) {
        dFader_c::setFader(dFader_c::unk_fade_1);
    } else {
        dFader_c::setFader(next->fadeType);
    }

    u32 entry = 0;

    switch (g_randBase) {
    case RAND_BASE_SAVE:
    case RAND_BASE_COURSE:
        // Temporary
        if (!g_madeEntryTable) {
            MakeEntryTable(dGameCom::getRandom(1024));
            g_madeEntryTable = true;
        }
        entry = g_entryLookup[index];
        break;

    case RAND_BASE_ALWAYS:
        entry = dGameCom::getRandom(PipeEntryCount);
        break;
    }

    dInfo_c::StartGameInfo_s sginfo;
    sginfo.unk_0 = 0;
    sginfo.replayType = 0;
    sginfo.entrance = PipeEntryList[entry] & 0xFF;
    sginfo.area = (PipeEntryList[entry] >> 8) & 0xFF;
    sginfo.unk_7 = 0;
    sginfo.purpose = 0;
    sginfo.world1 = (PipeEntryList[entry] >> 24) & 0xFF;
    sginfo.level1 = (PipeEntryList[entry] >> 16) & 0xFF;
    sginfo.world2 = (PipeEntryList[entry] >> 24) & 0xFF;
    sginfo.level2 = (PipeEntryList[entry] >> 16) & 0xFF;

    dScCrsin_c::m_isDispOff = true;
    dScStage_c::m_exitMode = 4;

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
        if (PipeEntryList[i] == entData) {
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
    if (dScStage_c::m_exitMode == 4)
        return 0;

    return dScStage_c::m_exitMode;
}

kmBranchDefAsm(0x809251D8, 0)
{
    // clang-format off
    extern void RestorePlayerInfo();

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
    if (level == 32 || level == 33 || level == 34)
        return true;

    return false;
}

kmCallDefCpp(0x808DF33C, void, u32 wm)
{
    extern void WM_PathInit(u32 wm); // 808E13F0
    extern u32 WM_GetNodeIDFromName(u32, const char* name,
                                    int r5); // 0x800F3380
    extern bool WM_GetNodeNameFromStage(int world, int level,
                                        char* out); // 0x800F9480

    if (g_exitedLevel && !SkipNodeOverride(dInfo_c::m_startGameInfo.world2,
                                           dInfo_c::m_startGameInfo.level2)) {
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
          wm + *(int*) (wm + 0x338C) * 0x3F08 + 0x5C7F4, name, 13);
    }

    WM_PathInit(wm);
}

// This will disable the airship cutscene when you enter a new world
kmCallDefCpp(0x80914924, bool, int world)
{
    extern bool WM_CheckIfWorldOpen(int world); // 0x800FB3E0

    if (world == 0) {
        return WM_CheckIfWorldOpen(world);
    }

    return true;
}

// Star Coin stuff!

kmCallDefCpp(0x80AAA364, void, int coin, int state)
{
    dScStage_c::setStarCoinState(coin, state);

    if (dInfo_c::m_startGameInfo.purpose != 0)
        return;

    if (state == 4)
        return;

    dSaveMng_c::instance()->getMj2dGame(-1)->setCollectCoin(
      dInfo_c::m_startGameInfo.world2, dInfo_c::m_startGameInfo.level2,
      1 << coin);
}
