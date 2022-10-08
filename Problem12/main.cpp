#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "core/timer.h"

using namespace std;

static
vector<vector<long long>> powerSet(const vector<long long> &set)
{
    vector<vector<long long>> pSet;
    bitset<10> b;
    long long sz = set.size();
    long long order = pow(2,sz);
    for(int i=1; i<order; ++i) {
        vector<long long> oneSet;
        b = i;
        for(long long j=0; j<sz; ++j) {
            if(b[j]) {
                oneSet.push_back(set[j]);
            }
        }
        pSet.push_back(oneSet);
    }
    return pSet;
}


int main()
{
    Timer timer;
    long long triNum=1;
    vector<long long> primes;
    vector<bool> sieveVec;
    long long range = 100000;
    sieveVec.resize(range,true);
    for(long long i=2; i<range; ++i) {
        if(!sieveVec[i]) {
            continue;
        }
        long long j = 2*i;
        while(j < range) {
            sieveVec[j]=false;
            j += i;
        }
    }
    for(long long i=2; i<range; ++i) {
        if(sieveVec[i]) {
            primes.push_back(i);
        }
    }
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
        auto pSet = powerSet(counts);
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
