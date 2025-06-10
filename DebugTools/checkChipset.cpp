//
// Created by Alex Sutherland on 2025-05-19.
//
#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int checkChipset() {

#if defined(__x86_64__) || defined(_M_X64)
    std::cout << "Running on x86_64 (Intel/AMD 64-bit)" << std::endl;
#elif defined(__i386__) || defined(_M_IX86)
    std::cout << "Running on x86 (32-bit)" << std::endl;
#elif defined(__aarch64__)
    std::cout << "Running on ARM64 (Apple Silicon / ARMv8)" << std::endl;
#elif defined(__arm__) || defined(_M_ARM)
    std::cout << "Running on ARM (32-bit)" << std::endl;
#else
    std::cout << "Unknown architecture" << std::endl;
#endif

    return 0;
}
