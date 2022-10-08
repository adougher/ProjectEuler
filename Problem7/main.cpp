#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include "core/timer.h"

using namespace std;

int main()
{
    Timer timer;
    vector<long long> primes;
    vector<bool> sieveVec;
    vector<long long> factors;
    // x / ln(x) ~ 10001
    long long sieveLen = 120000;
    sieveVec.resize(sieveLen,true);
    for(long long i=2; i<sieveLen; ++i) {
        if(!sieveVec[i]) {
            continue;
        }
        long long j = 2*i;
        while(j < sieveLen) {
            sieveVec[j]=false;
            j += i;
        }
    }
    for(long long i=2; i<sieveLen; ++i) {
        if(sieveVec[i]) {
            primes.push_back(i);
        }
    }
    qDebug() << "prime 10001: " << primes[10000];
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
