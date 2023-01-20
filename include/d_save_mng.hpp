#pragma once

#include "d_mj2d_data.hpp"

class dSaveMng_c
{
    static dSaveMng_c* m_instance;

public:
    static dSaveMng_c* instance()
    {
        return m_instance;
    }

    dMj2dGame_c* getMj2dGame(int i);
};
