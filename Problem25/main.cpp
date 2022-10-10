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

int main()
{
    Timer timer;
    BigInt fib1(1);
    BigInt fib2(1);
    BigInt fib(1);
    long long index = 2;
    while(fib.digits() < 1000) {
        fib = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib;
        ++index;
    }
    qDebug() << "index: " << index;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
