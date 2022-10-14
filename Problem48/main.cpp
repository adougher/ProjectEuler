#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    BigInt sum({1});
    long long limit = 100;
    for(long long a=2; a<=limit; ++a) {
        sum = sum + (BigInt(a)^a);
    }
    std::cout << "sum: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
