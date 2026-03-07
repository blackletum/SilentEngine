#pragma once

namespace Silent::Game
{
    void MainMenu_SelectedOptionIdxReset();

    void MainMenu_MainTextDraw();

    void MainMenu_DifficultyTextDraw(s32 idx);

    void MainMenu_BackgroundDraw();

    void func_8003B7BC();

    u32 func_8003B7FC(s32 idx);

    PACKET* MainMenu_FogPacketGet(GsOT* ot, PACKET* packet);

    void MainMenu_FogDraw();

    void MainMenu_FogRandomize();

    void MainMenu_FogScatter();

    void MainMenu_FogUpdate();

    /** Related to main menu fog. */
    void func_8003BCF4();
}
