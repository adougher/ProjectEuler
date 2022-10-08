#include <iostream>

#include <QDebug>
#include "core/timer.h"

using namespace std;

int main()
{
    Timer timer;
    int sum = 0;
    for(int i=1; i<1000; ++i) {
        if(i%3 == 0 || i%5 == 0) {
            sum += i;
        }
    }
    qDebug() << "sum: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
