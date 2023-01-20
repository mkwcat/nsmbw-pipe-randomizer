#pragma once

#include <kamek.h>

class SndSceneMgr
{
    static SndSceneMgr* sInstance;

public:
    static SndSceneMgr* instance()
    {
        return sInstance;
    }

    void stopBgmFlag(u32 flag);
};
