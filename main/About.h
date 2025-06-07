#ifndef ABOUT_H
#define ABOUT_H

#pragma once

#include "Arduino.h"

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATH  2

#define COMPANU     "Soliton 1 NTOA"

#define SERIAL_NUM    1

class About
{
public:
    About();
    ~About();

    String date();
    String time();

    uint32_t versionMajor();
    uint32_t versionMinor();
    uint32_t versionPathr();

    String versionStr();

    String companu();

    uint32_t serialNumber();

private:

};

extern About about;

#endif