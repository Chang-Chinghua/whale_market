#ifndef CLEAR_SCREEN_H
#define CLEAR_SCREEN_H


#include <iostream>
#include <cstdlib>


// clear_screen.cpp (源文件)
// 根据操作系统选择不同的实现
#ifdef _WIN32
    // 在 Windows 系统上，使用 system("cls")
    inline void clear_screen() {
        std::system("cls");
    }
#elif defined(__APPLE__) || defined(__linux__)
    // 在 macOS 和 Linux 系统上，使用 system("clear")
    inline void clear_screen() {
        std::system("clear");
    }
#else
    // 对于其他未知系统，使用打印换行符的通用方法
    inline void clear_screen() {
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    }
#endif