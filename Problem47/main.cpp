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
    long long limit = 1000000;
    long long chainLen = 4;
    long long thaNumber=0;
    for(long long i=2; i<limit-chainLen; ++i) {
        bool valid=true;
        for(long long j=i; j<i+chainLen; ++j) {
            auto divs=primes::primeFactors(j);
            if((long long)divs.size() != chainLen) {
                valid=false;
                break;
            }
        }
        if(valid) {
            thaNumber = i;
            break;
        }
    }
    qDebug() << "the magic number is " << thaNumber;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
