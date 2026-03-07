#pragma once

namespace Silent::Game
{
    /** Seeks for the English title screen background graphic. */
    void GameFs_TitleGfxSeek();

    /** Loads the English title screen background graphic. */
    void GameFs_TitleGfxLoad();

    /** Seeks for the stream overlay. */
    void GameFs_StreamBinSeek();

    /** Loads the stream overlay. */
    void GameFs_StreamBinLoad();

    /** Loads the options background graphic and overlay. */
    void GameFs_OptionBinLoad();

    /** Loads the save/load background graphic and overlay. */
    void GameFs_SaveLoadBinLoad();
}
