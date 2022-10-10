#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include "core/timer.h"
#include "core/primes.h"
using namespace std;

int main()
{
    Timer timer;
    long long target = 600851475143;
    auto factors = primes::primeFactors(target);
    qDebug() << "largest factor: " << factors.back().first;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
