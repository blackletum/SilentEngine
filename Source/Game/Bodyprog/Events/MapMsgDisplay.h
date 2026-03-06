#pragma once

namespace Silent::Game
{
    extern u8 g_MapMsg_AudioLoadBlock;

    s32 Gfx_MapMsg_Draw(s32 mapMsgIdx);

    s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1);

    void func_8003708C(s16* ptr0, u16* ptr1);

    void func_80037124(void);
}
