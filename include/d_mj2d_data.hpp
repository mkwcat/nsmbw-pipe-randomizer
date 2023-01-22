#pragma once

#include "kamek.h"

class dMj2dGame_c
{
public:
    void setCollectCoin(int world, int level, u8 coins);
    void onWorldDataFlag(int world, u8 flag);

    u8 mVersion[2];
    u8 mGameCompletion;
};
