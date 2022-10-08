#include <iostream>

#include <QDebug>
#include <vector>
#include "core/timer.h"

using namespace std;

int main()
{
    Timer timer;
    vector<int> fibs;
    int sum = 0;
    fibs.push_back(0);
    fibs.push_back(1);
    int index = 1;
    while(fibs.back() < 4000000) {
        auto newFib = fibs[index] + fibs[index-1];
        if(newFib % 2 == 0) {
            sum += newFib;
        }
        fibs.push_back(newFib);
        ++index;
    }
    qDebug() << "sum: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
