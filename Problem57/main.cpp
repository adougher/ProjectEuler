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

static void
continuedFrac(BigInt &numer,
              BigInt &denom,
              const int &itrs,
              std::vector<std::pair<BigInt,BigInt>> &storedResults)
{
    int currentItr=std::max(itrs-2,1);
    while(currentItr<=itrs) {
        if(currentItr == itrs) {
            numer = denom + numer;
        }
        else {
            if(itrs > 2) {
                auto stored = storedResults[itrs - 2];
                numer = stored.first;
                denom = stored.second;
            }
            numer = denom * 2 + numer;
        }
        auto gcd = primes::gcd(numer,denom);
        numer = numer / gcd;
        denom = denom / gcd;
        if(currentItr == itrs) {
            break;
        }
        auto temp = numer;
        numer = denom;
        denom = temp;
        if(currentItr == itrs - 1) {
            storedResults[itrs - 1] = {numer,denom};
        }
        ++currentItr;
    }
}

int main()
{
    Timer timer;
    int count=0;
    int itrs = 1000;
    std::vector<std::pair<BigInt,BigInt>> storedResults(itrs);
    for(int i=1; i<=itrs; ++i) {
        BigInt numer=1;
        BigInt denom=2;
        continuedFrac(numer,denom,i,storedResults);
        if(numer.digitsVec().size() > denom.digitsVec().size()) {
            ++count;
        }
    }
    qDebug() << "numerartor is greater than the denominator " << count << " times";
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
