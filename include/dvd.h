#pragma once

#include <kamek.h>

extern "C" {

typedef struct {
    u8 _00[0x0C - 0x00];
    s32 state;
    u8 _10[0x30 - 0x10];
} DVDCommandBlock;

static_assert(sizeof(DVDCommandBlock) == 0x30, "sizeof(DVDCommandBlock)");

typedef struct {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    void* callback;
} DVDFileInfo;

static_assert(sizeof(DVDFileInfo) == 0x3C, "sizeof(DVDFileInfo)");

s32 DVDConvertPathToEntrynum(const char* fileName);

bool DVDFastOpen(s32 entryNum, DVDFileInfo* fileInfo);

bool DVDClose(DVDFileInfo* fileInfo);

s32 DVDReadPrio(
    DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio
);

#define DVDRead(fileInfo, addr, length, offset)                                \
    DVDReadPrio((fileInfo), (addr), (length), (offset), 2)
}