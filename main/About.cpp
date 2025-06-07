#include "About.h"

About::About()
{

}

About::~About()
{

}

String About::date()
{
    const char *months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    char month[4];
    int day, year;
    
    // Парсим строку вида "Jun  7 2025" (пробелы могут быть)
    sscanf(__DATE__, "%3s %d %d", month, &day, &year);

    int month_num = 0;
    for (int i = 0; i < 12; i++) {
        if (strcmp(month, months[i]) == 0) {
            month_num = i + 1;
            break;
        }
    }

    char output[11];
    // Форматируем в "dd.mm.yyyy" с ведущими нулями
    sprintf(output, "%02d.%02d.%04d", day, month_num, year);


    return String(output);
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

String About::versionStr()
{
    return String(VERSION_MAJOR) + "." + String(VERSION_MINOR) + "." + String(VERSION_PATH);
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
