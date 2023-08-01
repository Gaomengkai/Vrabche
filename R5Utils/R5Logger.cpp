//
// Created by gaome on 2023/7/13.
//

#include "R5Logger.h"

namespace MiddleIR
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
}   // namespace MiddleIR