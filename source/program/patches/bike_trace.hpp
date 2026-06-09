#include "lib.hpp"
#include <lib/log/logger_mgr.hpp>

// Trace build: logs [BIKETRACE] lines so we can see what the bike-mount triggers.
// Startup line proves logging works; RequestPlayerRideBicycle proves hooks fire.

#define BIKE_TRACE(NAME, LABEL)                                          \
    HOOK_DEFINE_INLINE(NAME) {                                           \
        static void Callback(exl::hook::nx64::InlineCtx*) {              \
            exl::log::Logging.Log("[BIKETRACE] " LABEL "\n");            \
        }                                                                \
    };

BIKE_TRACE(Trace_RequestRideBicycle,    "RequestPlayerRideBicycle")
BIKE_TRACE(Trace_RideFunc,              "RideFunc_d978a0")
BIKE_TRACE(Trace_GetDressupParts,       "GetPlayerDressupParts")
BIKE_TRACE(Trace_SetDressupParts,       "SetPlayerDressupParts")
BIKE_TRACE(Trace_SetDressupPartsPreset, "SetPlayerDressupPartsByPreset")
BIKE_TRACE(Trace_SetNoDressupParts,     "SetPlayerNoDressupParts")
BIKE_TRACE(Trace_AddDressupItemPreset,  "PlayerAddDressupItemByPreset")
BIKE_TRACE(Trace_ChangeBicycle,         "ChangeBicycle")
BIKE_TRACE(Trace_ModelHandler,          "ModelHandler_de02d0")

void install_bike_trace_patch() {
    exl::log::Logging.Log("[BIKETRACE] trace mod loaded\n");
    Trace_RequestRideBicycle::InstallAtOffset(0x148b960);
    Trace_RideFunc::InstallAtOffset(0xd978a0);
    Trace_GetDressupParts::InstallAtOffset(0x1472580);
    Trace_SetDressupParts::InstallAtOffset(0x1472680);
    Trace_SetDressupPartsPreset::InstallAtOffset(0x1472830);
    Trace_SetNoDressupParts::InstallAtOffset(0x14727a0);
    Trace_AddDressupItemPreset::InstallAtOffset(0x14adde0);
    Trace_ChangeBicycle::InstallAtOffset(0x1472a60);
    Trace_ModelHandler::InstallAtOffset(0xde02d0);
}
