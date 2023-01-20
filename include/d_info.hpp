#pragma once

#include <kamek.h>

class dInfo_c
{
    static dInfo_c* m_instance;

public:
    static dInfo_c* instance()
    {
        return m_instance;
    }

    struct StartGameInfo_s {
        u32 unk_0;
        u8 replayType;
        u8 entrance; // 0xFF for default
        u8 area;
        u8 unk_7;
        u32 purpose;
        u8 world1;
        u8 level1;
        u8 world2;
        u8 level2;
    };

    static StartGameInfo_s m_startGameInfo;

    void startGame(const StartGameInfo_s&);
};
