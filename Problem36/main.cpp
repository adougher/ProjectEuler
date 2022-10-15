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

using namespace std;

int main()
{
    Timer timer;
    long long sum=0;
    for(long long i=1; i<=1000000; ++i) {
        auto digits = BigInt::convertToDigitsVec(i);
        auto ds = digits.size();
        bool p=true;
        for(size_t i=0; i<ds/2; ++i) {
            if(digits[i] != digits[ds-i-1]) {
                p=false;
                break;
            }
        }
        auto base2 = BigInt::base2(i);
        auto digVec = base2.digitsVec();
        ds = digVec.size();
        for(size_t i=0; i<ds/2; ++i) {
            if(digVec[i] != digVec[ds-i-1]) {
                p=false;
                break;
            }
        }
        if(p) {
            sum += i;
        }
    }
    std::cout << "sum: " << sum << std::endl;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
