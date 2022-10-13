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
    std::set<BigInt> uniques;
    long long limit = 100;
    for(long long a=2; a<=limit; ++a) {
        for(long long b=2; b<=limit; ++b) {
            uniques.insert(BigInt(a)^b);
        }
    }
    qDebug() << "uniques: " << uniques.size();
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
