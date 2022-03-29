#ifndef SMART_HOME_API_STRUCTS_H
#define SMART_HOME_API_STRUCTS_H

#include <Arduino.h>

typedef String GUID;

struct Relay
{
    GUID Id;
    String Type;
    String Name;
};

#endif