#include "Framework.h"
#include "Game/Compatibility/Memory.h"

namespace Silent::Game
{
    constexpr uint32 SCRATCHPAD_SIZE       = 1024;             /** 1KB. */
    constexpr uint32 RAM_SIZE              = 2 * SQUARE(1024); /** 2MB. */
    constexpr uint32 SCRATCHPAD_START_ADDR = 0x1F800000;       /** CPU data cache. */
    constexpr uint32 RAM_START_ADDR        = 0x80000000;       /** Main ram in KSEG0 region. */

    static auto VirtualScratchpad = std::array<byte, SCRATCHPAD_SIZE>{};
    static auto VirtualRam        = std::array<byte, RAM_SIZE>{};

    void* GetScratchpadPtr(uint32 addr)
    {
        uint32 offset = addr - SCRATCHPAD_START_ADDR;
        return &VirtualScratchpad + offset;
    }

    void* GetRamPtr(uint32 addr)
    {
        uint32 offset = addr & 0x00FFFFFF; 
        return &VirtualRam[offset];
    }
}
