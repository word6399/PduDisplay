#include "About.h"

About::About()
{

}

About::~About()
{

}

String About::date()
{
    return __DATE__;
}

String About::time()
{
    return __TIME__;
}

uint32_t About::versionMajor()
{
    return VERSION_MAJOR;
}

uint32_t About::versionMinor()
{
    return VERSION_MINOR;
}

uint32_t About::versionPathr()
{
    return VERSION_PATH;
}

String About::companu()
{
    return COMPANU;
}

uint32_t About::serialNumber()
{
    return SERIAL_NUM;
}

About about;