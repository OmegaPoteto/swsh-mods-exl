#include "lib.hpp"
#include <lib/log/logger_mgr.hpp>

// Logs whenever a candidate outfit/model function runs, so we can see which
// one the bike-mount script triggers. Look for [BIKETRACE] lines in the log.

#define BIKE_TRACE(NAME, LABEL)                                          \
    HOOK_DEFINE_INLINE(NAME) {                                           \
        static void Callback(exl::hook::nx64::InlineCtx*) {              \
            exl::log::Logging.Log("[BIKETRACE] " LABEL "\n");            \
        }                                                                \
    };

BIKE_TRACE(Trace_SetDressupParts,       "SetPlayerDressupParts")
BIKE_TRACE(Trace_SetDressupPartsPreset, "SetPlayerDressupPartsByPreset")
BIKE_TRACE(Trace_AddDressupItemPreset,  "PlayerAddDressupItemByPreset")
BIKE_TRACE(Trace_ChangeBicycle,         "ChangeBicycle_")
BIKE_TRACE(Trace_ModelHandler,          "ModelHandler@de02d0")

void install_bike_trace_patch() {
    Trace_SetDressupParts::InstallAtOffset(0x1472680);
    Trace_SetDressupPartsPreset::InstallAtOffset(0x1472830);
    Trace_AddDressupItemPreset::InstallAtOffset(0x14adde0);
    Trace_ChangeBicycle::InstallAtOffset(0x1472a60);
    Trace_ModelHandler::InstallAtOffset(0xde02d0);
}
