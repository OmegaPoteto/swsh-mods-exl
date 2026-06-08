#include "lib.hpp"
#include "external.hpp"
#include "symbols.hpp"
#include "config.hpp"

// Sword 1.3.2 site where s0 holds the raw spawn radius, just before the
// engine squares (2*radius) for the player-proximity test.
const u64 SpawnRadiusUse_offset = 0xce0400;

HOOK_DEFINE_INLINE(ScaleSpawnRadius) {
    static void Callback(exl::hook::nx64::InlineFloatCtx* ctx) {
        EXL_ASSERT(global_config.initialized);
        if (global_config.spawn_distance.active) {
            ctx->S[0] *= global_config.spawn_distance.multiplier;
        }
    }
};

void install_spawn_distance_patch() {
    ScaleSpawnRadius::InstallAtOffset(SpawnRadiusUse_offset);
}
