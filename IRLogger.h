//
// Created by gao on 6/28/23.
//

#ifndef SYSYLEX_IRLOGGER_H
#define SYSYLEX_IRLOGGER_H


#include <iostream>
#include <fstream>

#ifndef _DEBUG
#    define _DEBUG
#endif

#ifndef SYSY_LOGGER

namespace IRCtrl
{
enum LOG_LEVEL {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
};
extern LOG_LEVEL g_log_level;
std::ostream&    sysyDebug(LOG_LEVEL level = LOG_LEVEL_DEBUG);
}   // namespace IRCtrl
#    define SYSY_LOGGER
#    define ANSI_COLOR_BLUE "\033[1;34m"
#    define ANSI_COLOR_ORANGE "\033[1;33m"
#    define ANSI_COLOR_YELLOW "\033[1;93m"
#    define ANSI_COLOR_RED "\033[1;31m"
#    define ANSI_COLOR_RESET "\033[0m"

#    define LOGD(message)                                                                       \
        do {                                                                                    \
            IRCtrl::sysyDebug(IRCtrl::LOG_LEVEL_DEBUG)                                              \
                << ANSI_COLOR_BLUE << "[D] File: " << __FILE__ << ANSI_COLOR_RESET              \
                << ANSI_COLOR_ORANGE << ":" << __LINE__ << ANSI_COLOR_RESET << ":\t" << message \
                << std::endl;                                                                   \
        } while (0)
#    define LOGW(message)                                                            \
        do {                                                                         \
            IRCtrl::sysyDebug(IRCtrl::LOG_LEVEL_WARNING)                                 \
                << ANSI_COLOR_YELLOW << "[W] File: " << __FILE__ << ANSI_COLOR_RESET \
                << ANSI_COLOR_ORANGE << ":" << __LINE__ << ANSI_COLOR_RESET << ":\t" \
                << ANSI_COLOR_YELLOW << message << ANSI_COLOR_RESET << std::endl;    \
        } while (0)

#    define LOGE(message)                                                            \
        do {                                                                         \
            IRCtrl::sysyDebug(IRCtrl::LOG_LEVEL_ERROR)                                   \
                << ANSI_COLOR_RED << "[E] File: " << __FILE__ << ANSI_COLOR_RESET    \
                << ANSI_COLOR_ORANGE << ":" << __LINE__ << ANSI_COLOR_RESET << ":\t" \
                << ANSI_COLOR_RED << message << ANSI_COLOR_RESET << std::endl;       \
        } while (0)

#    define RUNTIME_ERROR(message)                                                            \
        do {                                                                                  \
            LOGE(message);                                                                    \
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__)); \
        } while (0)

#    define IR_ASSERT(EXP_, MSG_)                 \
        do {                                      \
            if (!(EXP_)) { RUNTIME_ERROR(MSG_); } \
        } while (0)

#endif   // SYSY_LOGGER
#endif   // SYSYLEX_IRLOGGER_H
