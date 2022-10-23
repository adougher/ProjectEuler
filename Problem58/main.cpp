#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include <deque>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigInt.h"
#include "core/BigFloat.h"
#include "core/sets.h"

using namespace std;

int main()
{
    Timer timer;
    double ratio=1;
    long long start=1;
    long long count=0;
    long long p_count=0;
    long long stride=2;
    double target = 0.1;
    while(ratio >= 0.1) {
        start += stride;
        if(primes::isPrime(start)) {
            ++p_count;
        }
        ++count;
        if(count % 4 == 0) {
            ratio = 1.0 * p_count / (count+1);
            if(ratio < target) {
                break;
            }
            stride += 2;
        }
    }
    qDebug() << "the side length is " << stride + 1;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
