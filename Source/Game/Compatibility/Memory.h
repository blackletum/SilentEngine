#pragma once

namespace Silent::Game
{
    /** @brief Gets a pointer to an address in the virtual PSX scratchpad.
     *
     * @param addr Physical PSX address.
     * @return Pointer to virtual memory corresponding to the address.
     */
    void* GetScratchpadPtr(uint32 addr);

    /** @brief Gets a pointer to an address in the virtual PSX RAM.
     *
     * @param addr Physical PSX address.
     * @return Pointer to virtual memory corresponding to the address.
     */
    void* GetRamPtr(uint32 addr);
}
