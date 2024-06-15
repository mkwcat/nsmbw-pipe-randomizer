#pragma once

#include <kamek.h>

class dCsSeqMng_c
{
public:
    static dCsSeqMng_c* ms_instance;

    void addScriptToQueue(int script, void* param_2, int param_3, int param_4);

    u8 _000[0x158 - 0x000];
    u32 m_cmdIndex;
    u8 _15C[0x1A8 - 0x15C];
    u32 m_script;
};
