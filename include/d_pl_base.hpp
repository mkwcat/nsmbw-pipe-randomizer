#pragma once

#include <kamek.h>

class daPlBase_c
{
public:
    u8 fill[0x60];

    // massive vtable
    virtual void vt_000() = 0;
    virtual void vt_004() = 0;
    virtual void vt_008() = 0;
    virtual void vt_00C() = 0;
    virtual void vt_010() = 0;
    virtual void vt_014() = 0;
    virtual void vt_018() = 0;
    virtual void vt_01C() = 0;
    virtual void vt_020() = 0;
    virtual void vt_024() = 0;
    virtual void vt_028() = 0;
    virtual void vt_02C() = 0;
    virtual void vt_030() = 0;
    virtual void vt_034() = 0;
    virtual void vt_038() = 0;
    virtual void vt_03C() = 0;
    virtual void vt_040() = 0;
    virtual void vt_044() = 0;
    virtual void vt_048() = 0;
    virtual void vt_04C() = 0;
    virtual void vt_050() = 0;
    virtual void vt_054() = 0;
    virtual void vt_058() = 0;
    virtual void vt_05C() = 0;
    virtual void vt_060() = 0;
    virtual void vt_064() = 0;
    virtual void vt_068() = 0;
    virtual void vt_06C() = 0;
    virtual void vt_070() = 0;
    virtual void vt_074() = 0;
    virtual void vt_078() = 0;
    virtual void vt_07C() = 0;
    virtual void vt_080() = 0;
    virtual void vt_084() = 0;
    virtual void vt_088() = 0;
    virtual void vt_08C() = 0;
    virtual void vt_090() = 0;
    virtual void vt_094() = 0;
    virtual void vt_098() = 0;
    virtual void vt_09C() = 0;
    virtual void vt_0A0() = 0;
    virtual void vt_0A4() = 0;
    virtual void vt_0A8() = 0;
    virtual void vt_0AC() = 0;
    virtual void vt_0B0() = 0;
    virtual void vt_0B4() = 0;
    virtual void vt_0B8() = 0;
    virtual void vt_0BC() = 0;
    virtual void vt_0C0() = 0;
    virtual void vt_0C4() = 0;
    virtual void vt_0C8() = 0;
    virtual void vt_0CC() = 0;
    virtual void vt_0D0() = 0;
    virtual void vt_0D4() = 0;
    virtual void vt_0D8() = 0;
    virtual void vt_0DC() = 0;
    virtual void vt_0E0() = 0;
    virtual void vt_0E4() = 0;
    virtual void vt_0E8() = 0;
    virtual void vt_0EC() = 0;
    virtual void vt_0F0() = 0;
    virtual void vt_0F4() = 0;
    virtual void vt_0F8() = 0;
    virtual void vt_0FC() = 0;
    virtual void vt_100() = 0;
    virtual void vt_104() = 0;
    virtual void vt_108() = 0;
    virtual void vt_10C() = 0;
    virtual void vt_110() = 0;
    virtual void vt_114() = 0;
    virtual void vt_118() = 0;
    virtual void vt_11C() = 0;
    virtual void vt_120() = 0;
    virtual void vt_124() = 0;
    virtual void vt_128() = 0;
    virtual void vt_12C() = 0;
    virtual void vt_130() = 0;
    virtual void vt_134() = 0;
    virtual void vt_138() = 0;
    virtual void vt_13C() = 0;
    virtual void vt_140() = 0;
    virtual void vt_144() = 0;
    virtual void vt_148() = 0;
    virtual void vt_14C() = 0;
    virtual void vt_150() = 0;
    virtual void vt_154() = 0;
    virtual void vt_158() = 0;
    virtual void vt_15C() = 0;
    virtual void vt_160() = 0;
    virtual void vt_164() = 0;
    virtual void vt_168() = 0;
    virtual void vt_16C() = 0;
    virtual void vt_170() = 0;
    virtual void vt_174() = 0;
    virtual void vt_178() = 0;
    virtual void vt_17C() = 0;
    virtual void vt_180() = 0;
    virtual void vt_184() = 0;
    virtual void vt_188() = 0;
    virtual void vt_18C() = 0;
    virtual void vt_190() = 0;
    virtual void vt_194() = 0;
    virtual void vt_198() = 0;
    virtual void vt_19C() = 0;
    virtual void vt_1A0() = 0;
    virtual void vt_1A4() = 0;
    virtual void vt_1A8() = 0;
    virtual void vt_1AC() = 0;
    virtual void vt_1B0() = 0;
    virtual void vt_1B4() = 0;
    virtual void vt_1B8() = 0;
    virtual void vt_1BC() = 0;
    virtual void vt_1C0() = 0;
    virtual void vt_1C4() = 0;
    virtual void vt_1C8() = 0;
    virtual void vt_1CC() = 0;
    virtual void vt_1D0() = 0;
    virtual void vt_1D4() = 0;
    virtual void vt_1D8() = 0;
    virtual void vt_1DC() = 0;
    virtual void vt_1E0() = 0;
    virtual void vt_1E4() = 0;
    virtual void vt_1E8() = 0;
    virtual void vt_1EC() = 0;
    virtual void vt_1F0() = 0;
    virtual void vt_1F4() = 0;
    virtual void vt_1F8() = 0;
    virtual void vt_1FC() = 0;
    virtual void vt_200() = 0;
    virtual void vt_204() = 0;
    virtual void vt_208() = 0;
    virtual void vt_20C() = 0;
    virtual void vt_210() = 0;
    virtual void vt_214() = 0;
    virtual void vt_218() = 0;
    virtual void vt_21C() = 0;
    virtual void vt_220() = 0;
    virtual void vt_224() = 0;
    virtual void vt_228() = 0;
    virtual void vt_22C() = 0;
    virtual void vt_230() = 0;
    virtual void vt_234() = 0;
    virtual void vt_238() = 0;
    virtual void vt_23C() = 0;
    virtual void vt_240() = 0;
    virtual void vt_244() = 0;
    virtual void vt_248() = 0;
    virtual void vt_24C() = 0;
    virtual void vt_250() = 0;
    virtual void vt_254() = 0;
    virtual void vt_258() = 0;
    virtual void vt_25C() = 0;
    virtual void vt_260() = 0;
    virtual void vt_264() = 0;
    virtual void vt_268() = 0;
    virtual void vt_26C() = 0;
    virtual void vt_270() = 0;
    virtual void vt_274() = 0;
    virtual void vt_278() = 0;
    virtual void vt_27C() = 0;
    virtual void vt_280() = 0;
    virtual void vt_284() = 0;
    virtual void vt_288() = 0;
    virtual void vt_28C() = 0;
    virtual void vt_290() = 0;
    virtual void vt_294() = 0;
    virtual void vt_298() = 0;
    virtual void vt_29C() = 0;
    virtual void vt_2A0() = 0;
    virtual void vt_2A4() = 0;
    virtual void vt_2A8() = 0;
    virtual void vt_2AC() = 0;
    virtual void vt_2B0() = 0;
    virtual void vt_2B4() = 0;
    virtual void vt_2B8() = 0;
    virtual void vt_2BC() = 0;
    virtual void vt_2C0() = 0;
    virtual void vt_2C4() = 0;
    virtual void vt_2C8() = 0;
    virtual void vt_2CC() = 0;
    virtual void vt_2D0() = 0;
    virtual void vt_2D4() = 0;
    virtual void vt_2D8() = 0;
    virtual void vt_2DC() = 0;
    virtual void vt_2E0() = 0;
    virtual void vt_2E4() = 0;
    virtual void vt_2E8() = 0;
    virtual void vt_2EC() = 0;
    virtual void vt_2F0() = 0;
    virtual void vt_2F4() = 0;
    virtual void vt_2F8() = 0;
    virtual void vt_2FC() = 0;
    virtual void vt_300() = 0;
    virtual void vt_304() = 0;
    virtual void vt_308() = 0;
    virtual void vt_30C() = 0;
    virtual void vt_310() = 0;
    virtual void vt_314() = 0;
    virtual void vt_318() = 0;
    virtual void vt_31C() = 0;
    virtual void vt_320() = 0;
    virtual void vt_324() = 0;
    virtual void vt_328() = 0;
    virtual void vt_32C() = 0;
    virtual void vt_330() = 0;
    virtual void vt_334() = 0;
    virtual void vt_338() = 0;
    virtual void vt_33C() = 0;
    virtual void vt_340() = 0;
    virtual void vt_344() = 0;
    virtual void vt_348() = 0;
    virtual void vt_34C() = 0;
    virtual void vt_350() = 0;
    virtual void vt_354() = 0;
    virtual void vt_358() = 0;
    virtual void vt_35C() = 0;
    virtual void vt_360() = 0;
    virtual void vt_364() = 0;
    virtual void vt_368() = 0;
    virtual void vt_36C() = 0;
    virtual void vt_370() = 0;
    virtual void vt_374() = 0;
    virtual void vt_378() = 0;
    virtual void vt_37C() = 0;
    virtual void vt_380() = 0;
    virtual void vt_384() = 0;
    virtual void vt_388() = 0;
    virtual void vt_38C() = 0;
    virtual void vt_390() = 0;
    virtual void vt_394() = 0;
    virtual void vt_398() = 0;
    virtual void vt_39C() = 0;
    virtual void vt_3A0() = 0;
    virtual void vt_3A4() = 0;
    virtual void vt_3A8() = 0;
    virtual void vt_3AC() = 0;
    virtual void vt_3B0() = 0;
    virtual void vt_3B4() = 0;
    virtual void vt_3B8() = 0;
    virtual void vt_3BC() = 0;
    virtual void vt_3C0() = 0;
    virtual void vt_3C4() = 0;
    virtual void vt_3C8() = 0;
    virtual void vt_3CC() = 0;
    virtual void beginStar(int r4, u32 timer) = 0;

    u8 fill2[0x1070 - 0x64];
    u32 starTimer;
};

class dAcPy_c : public daPlBase_c
{
};

class daPyMng_c
{
public:
    static dAcPy_c* getPlayer(int id);
    static void setPlayer(int id, dAcPy_c* object);
};
