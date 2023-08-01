//
// Created by gaome on 2023/7/13.
//

#ifndef IRBACKENDR5_R5LOGGER_H
#define IRBACKENDR5_R5LOGGER_H
#ifndef SYSY_LOGGER
#    define SYSY_LOGGER

#    include <iostream>

namespace MiddleIR
{
enum LOG_LEVEL {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
};
extern LOG_LEVEL g_log_level;
std::ostream&    sysyDebug(LOG_LEVEL level = LOG_LEVEL_DEBUG);
}   // namespace MiddleIR

#    define ANSI_COLOR_BLUE "\033[1;34m"
#    define ANSI_COLOR_ORANGE "\033[1;33m"
#    define ANSI_COLOR_YELLOW "\033[1;93m"
#    define ANSI_COLOR_RED "\033[1;31m"
#    define ANSI_COLOR_RESET "\033[0m"

#    define LOGD(message)                                                                       \
        do {                                                                                    \
            MiddleIR::sysyDebug(MiddleIR::LOG_LEVEL_DEBUG)                                              \
                << ANSI_COLOR_BLUE << "[D] File: " << __FILE__ << ANSI_COLOR_RESET              \
                << ANSI_COLOR_ORANGE << ":" << __LINE__ << ANSI_COLOR_RESET << ":\t" << message \
                << std::endl;                                                                   \
        } while (0)
#    define LOGW(message)                                                            \
        do {                                                                         \
            MiddleIR::sysyDebug(MiddleIR::LOG_LEVEL_WARNING)                                 \
                << ANSI_COLOR_YELLOW << "[W] File: " << __FILE__ << ANSI_COLOR_RESET \
                << ANSI_COLOR_ORANGE << ":" << __LINE__ << ANSI_COLOR_RESET << ":\t" \
                << ANSI_COLOR_YELLOW << message << ANSI_COLOR_RESET << std::endl;    \
        } while (0)

#    define LOGE(message)                                                            \
        do {                                                                         \
            MiddleIR::sysyDebug(MiddleIR::LOG_LEVEL_ERROR)                                   \
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



#endif
#endif   // IRBACKENDR5_R5LOGGER_H
