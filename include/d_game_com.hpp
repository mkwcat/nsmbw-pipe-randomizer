#pragma once

#include <kamek.h>

u32 getRandomFromSeed(u32* seed, u32 limit);

class dGameCom
{
public:
    static unsigned long getRandom(unsigned long limit);
};
