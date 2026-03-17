#pragma once

#include "f_base.hpp"

class dScCrsin_c : public fBase_c
{
public:
    void executeState_DispEndCheck();

    static bool m_isDispOff;
};
