//
// Created by Chris Henk on 3/8/17.
//

#ifndef SORTING_COMPETITION_LOWLEVELUTILS_H
#define SORTING_COMPETITION_LOWLEVELUTILS_H

#include <fstream>
#include <cstring>

#ifdef SORT_COMP_SIMD
    #include "asmlib.h"
#endif

// String object for holding file
struct file {
    size_t length;
    char* data;
};

// String object for marking strings within the file
struct string {
    uint8_t length; // Strings are limited to ~80 bytes, use smallest data type to represent length
    char* data;

    inline bool operator<(const string & rhs) {
#ifndef SORT_COMP_SIMD
        return length < rhs.length || (length == rhs.length && std::strcmp(data, rhs.data) < 0);
#else
        return length < rhs.length || (length == rhs.length && A_strcmp(data, rhs.data) < 0);
#endif
    }
};

inline file getFileContents(const char* filename) {
    std::ifstream input(filename, std::ios::in | std::ios::binary);

    file contents;

    // Determine file length
    input.seekg(0, std::ios::end);
#ifndef SORT_COMP_SIMD
    contents.length = (size_t)input.tellg();
#else
    contents.length = (size_t)input.tellg() + 15;
#endif
    contents.data = new char[contents.length];

    // Reset file pointer and load file
    input.seekg(0, std::ios::beg);
    input.read(contents.data, contents.length);

    input.close();

    return contents;
}


inline string getLine(char* & ptr, int & index) {
    int originalIdx = index;

    while(ptr[index] != '\n') index++;

    string temp;
    temp.length = (uint8_t)(index - originalIdx);
    temp.data = ptr + originalIdx;

    ptr[index++] = '\0';

    return temp;
}

//inline int strcmpSSE42(char* ptr1, char* ptr2) {
//    __asm__ volatile (
//            "pusha \n"
//            "mov eax, %0 \n"
//            "inc eax \n"
//            "mov ecx, %1 \n"
//            "xor ecx, %1 \n"
//            "mov %1, ecx \n"
//            "mov eax, %1 \n"
//            "popa \n"
//    : // no output
//    : "m" (temp), "m" (usernb) ); // input
//}

#endif //SORTING_COMPETITION_LOWLEVELUTILS_H
