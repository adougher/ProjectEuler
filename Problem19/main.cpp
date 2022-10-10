#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"
#include "core/BigInt.h"

using namespace std;

static int
monthToDays(int month, bool leap) {
    if(month == 9 || month == 4 ||
       month == 6 || month == 11) {
        return 30;
    }
    if(month == 2) {
        return leap ? 29 : 28;
    }
    return 31;
}

static int
dayOfMonth(int day)
{
    day -= 365;
    day = day % (3*365 + 366);
    bool leapYear = day >= 3*365;
    if(leapYear) {
        day -= 3*365;
    }
    else {
        day = day % 365;
    }
    int month = 1;
    while(day > monthToDays(month,leapYear) - 1) {
        day -= monthToDays(month,leapYear);
        ++month;
    }
    return day % monthToDays(month,leapYear);
}

int main()
{
    Timer timer;
    int total = 0;
    int leapYears = 100/4 - 1;
    int totalDays = leapYears * 366 + (101 - leapYears) * 365;
    for(int i=0; i<totalDays; ++i) {
        if(i >= 365 && i % 7 == 6 && dayOfMonth(i) == 0) {
            ++total;
        }
    }
    qDebug() << "Sundays on first of the month in the 21st century: " << total;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
