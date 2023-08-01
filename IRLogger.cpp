//
// Created by gao on 6/28/23.
//
#include "IRLogger.h"

namespace IRCtrl
{
static auto   debug_null_out = std::ostream(nullptr);
LOG_LEVEL     g_log_level    = LOG_LEVEL_DEBUG;
std::ostream& sysyDebug(LOG_LEVEL level)
{
    if (level >= g_log_level) {
        return std::cout;
    } else {
        return debug_null_out;
    }
}
}   // namespace IRCtrl
