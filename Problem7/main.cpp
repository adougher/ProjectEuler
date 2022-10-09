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
    vector<long long> factors;
    // x / ln(x) ~ 10001
    long long sieveLen = 120000;
    vector<long long> primes=primes::primes(sieveLen);
    qDebug() << "prime 10001: " << primes[10000];
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
