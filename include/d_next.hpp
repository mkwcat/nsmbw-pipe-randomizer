#pragma once

#include "d_fader.hpp"
#include <kamek.h>

class dNext_c
{
public:
    void changeScene();

    struct Entrance {
        u16 x;
        u16 y;
        u16 unk_4;
        u16 unk_6;
        u8 entryId;
        u8 destArea;
        u8 destEntrance;
        u8 type;
        u8 unk_C;
        u8 zoneId;
        u8 layerId;
        u8 pathId;
        u16 flags;
        u16 unk_12;
    };

    Entrance entrance;
    u8 fill[0x20 - 0x16];
    dFader_c::fader_type_e fadeType;
    // Not finished
};
