#ifndef _COLOR_H_
#define _COLOR_H_

#include <string>

// Only Effective for Linux / Unix

/** Reset all the Attributes */
inline constexpr std::string_view RESET = "\033[0m";

/** Set Font Color
 * Format: "\033[BackColor;FrontColorString\033[0m"
 */
inline constexpr std::string_view FRONT_BLACK = "\033[30m";
inline constexpr std::string_view FRONT_RED = "\033[31m";
inline constexpr std::string_view FRONT_GREEN = "\033[32m";
inline constexpr std::string_view FRONT_YELLOW = "\033[33m";
inline constexpr std::string_view FRONT_BLUE = "\033[34m";
inline constexpr std::string_view FRONT_PURPLR = "\033[35m";
inline constexpr std::string_view FRONT_DARKGREEN = "\033[36m";
inline constexpr std::string_view FRONT_WHITE = "\033[37m";

inline constexpr std::string_view BACK_BLACK = "\033[40m";
inline constexpr std::string_view BACK_RED = "\033[41m";
inline constexpr std::string_view BACK_GREEN = "\033[42m";
inline constexpr std::string_view BACK_YELLOW = "\033[43m";
inline constexpr std::string_view BACK_BLUE = "\033[44m";
inline constexpr std::string_view BACK_PURPLR = "\033[45m";
inline constexpr std::string_view BACK_DARKGREEN = "\033[46m";
inline constexpr std::string_view BACK_WHITE = "\033[47m";

/** Set Font Effect */
inline constexpr std::string_view BOLD = "\033[1m";
inline constexpr std::string_view UNDERLINE = "\033[4m";
inline constexpr std::string_view TWINKLING = "\033[5m";
inline constexpr std::string_view REVERSE = "\033[7m";
inline constexpr std::string_view HIDE = "\033[8m";

#endif
