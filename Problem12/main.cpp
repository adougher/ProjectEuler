#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/sets.h"

using namespace std;


int main()
{
    Timer timer;
    long long triNum=1;
    long long range = 100000;
    vector<long long> primes=primes::primes(range);
    long long i=2;
    long long minFactors = 501;
    long long factors = 1;
    while(factors < minFactors) {
        factors = 1;
        triNum = (i * (i+1)) >> 1;
        long long j = 0;
        auto triNumCp = triNum;
        vector<long long> counts;
        while(triNumCp > 1) {
            long long count=0;
            while(triNumCp % primes[j] == 0) {
                triNumCp /= primes[j];
                ++count;
            }
            if(count > 0) {
                counts.push_back(count);
            }
            ++j;
        }
        auto pSet = sets::powerSet(counts);
        for(const auto &s : pSet) {
            long long prod = 1;
            for(const auto &ss : s) {
                prod *= ss;
            }
            factors += prod;
        }
        ++i;
    }
    qDebug() << "triangle number " << i << ": " << triNum << " has " << factors << " factors";
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
