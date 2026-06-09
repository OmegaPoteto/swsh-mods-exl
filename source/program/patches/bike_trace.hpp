#include "lib.hpp"
#include <lib/log/logger_mgr.hpp>
#include <lib/util/modules.hpp>

// Model trace: logs every model-by-hash load (hash + caller offset) plus a
// RideFunc marker. Mount the bike, then find the LoadModel lines right after
// the [BIKETRACE] RideFunc_d978a0 marker -- that hash/caller is the bike model.

HOOK_DEFINE_INLINE(Trace_RideFunc) {
    static void Callback(exl::hook::nx64::InlineCtx*) {
        ::Logging.Log("[BIKETRACE] RideFunc_d978a0 (MOUNT)\n");
    }
};

HOOK_DEFINE_INLINE(Trace_LoadModel) {
    static void Callback(exl::hook::nx64::InlineCtx* ctx) {
        ::Logging.Log("[BIKETRACE] LoadModel hash=%016lx caller=%lx\n",
            ctx->X[1],
            ctx->X[30] - exl::util::modules::GetTargetStart());
    }
};

void install_bike_trace_patch() {
    ::Logging.Log("[BIKETRACE] model trace loaded\n");
    Trace_RideFunc::InstallAtOffset(0xd978a0);
    Trace_LoadModel::InstallAtOffset(0x1411030);
}
