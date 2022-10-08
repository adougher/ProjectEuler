#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include "core/timer.h"

using namespace std;

int main()
{
    Timer timer;
    int diff = 0;
    int nums = 100;
    for(int i=1; i<=nums; ++i) {
        for(int j=i+1; j<=nums; ++j) {
            diff += i*j;
        }
    }
    diff *= 2;
    qDebug() << "diff: " << diff;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
