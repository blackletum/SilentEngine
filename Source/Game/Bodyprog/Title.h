#pragma once

namespace Silent::Game
{
    void MainMenu_SelectedOptionIdxReset(void);

    void MainMenu_MainTextDraw(void);

    void MainMenu_DifficultyTextDraw(s32 idx);

    void MainMenu_BackgroundDraw(void);

    void func_8003B7BC(void);

    u32 func_8003B7FC(s32 idx);

    PACKET* MainMenu_FogPacketGet(GsOT* ot, PACKET* packet);

    void MainMenu_FogDraw(void);

    void MainMenu_FogRandomize(void);

    void MainMenu_FogScatter(void);

    void MainMenu_FogUpdate(void);

    /** Related to main menu fog. */
    void func_8003BCF4(void);
}
