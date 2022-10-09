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
    long long target = 600851475143;
    long long sqTarget = (long long)sqrt(target);
    vector<long long> primes = primes::primes(sqTarget);
    long long i = 0;
    while(target > 1) {
        while(target % primes[i] == 0) {
            factors.push_back(primes[i]);
            target /= primes[i];
        }
        ++i;
    }
    qDebug() << "largest factor: " << factors.back();
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
