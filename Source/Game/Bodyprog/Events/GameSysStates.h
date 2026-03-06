#pragma once

namespace Silent::Game
{
    void GameState_InGame_Update(void);

    void SysState_Gameplay_Update(void);

    void SysState_GamePaused_Update(void);

    void SysState_OptionsMenu_Update(void);

    void func_8003943C(void);

    void SysState_StatusMenu_Update(void);

    void GameState_LoadStatusScreen_Update(void);

    void SysState_MapScreen_Update(void);

    void GameState_LoadMapScreen_Update(void);

    void SysState_Fmv_Update(void);

    void SysState_LoadArea_Update(void);

    void AreaLoad_UpdatePlayerPosition(void);

    /** @brief Plays door sound when transitioning areas.
     * Reduntant code. `SysState_LoadArea_Update` also performs this same code
     * in the exact way this function is doing it.
     */
    void AreaLoad_TransitionSound(void);

    s8 func_80039F90(void);

    void SysState_ReadMessage_Update(void);

    /** @brief Updates the savegame buffer with the current player SysWork info (position, rotation, health, event index). */
    void SysWork_SavegameUpdatePlayer(void);

    void func_8003A16C(void);

    /** @brief Updates SysWork with player info from the savegame buffer (position, rotation, health). */
    void SysWork_SavegameReadPlayer(void);

    void SysState_SaveMenu_Update(void);

    void SysState_SaveMenu_Update(void);

    void SysState_EventCallFunc_Update(void);

    void SysState_EventSetFlag_Update(void);

    void SysState_EventPlaySound_Update(void);

    void SysState_GameOver_Update(void);

    void GameState_MapEvent_Update(void);
}
