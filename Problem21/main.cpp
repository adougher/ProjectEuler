#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    int sum = 0;
    int range = 10000;
    std::vector<bool> found(range+1,false);
    for(int i=2; i<=range; ++i) {
        if(found[i]) {
            continue;
        }
        found[i] = true;
        auto properDiv = primes::properDivisors(i);
        int sum1 = 0;
        for(const auto &p : properDiv) {
            sum1 += p;
        }
        if(found[sum1]) {
            continue;
        }
        properDiv = primes::properDivisors(sum1);
        int sum2 = 0;
        for(const auto &p : properDiv) {
            sum2 += p;
        }
        if(sum2 == i) {
            sum += i;
            sum += sum1;
            qDebug() << i << " and " << sum1 << " are amicable";
            found[sum1] = true;
        }
    }

    qDebug() << "sum of amicable numbers" << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
