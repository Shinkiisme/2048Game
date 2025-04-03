#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "2048Lib.h"

struct playerInfo {
    char* username = new char[MAXLEN];
    int character;
    int point = 0;
};

#endif
