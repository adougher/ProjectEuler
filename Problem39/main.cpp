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
    long long maxSolutions=0;
    long long maxP=0;
    for(long long p=3; p<=1000; ++p) {
        long long solutions=0;
        for(long long i=1; i<p-1; ++i) {
            for(long long j=i; j<p-1; ++j) {
                long long k = p - i - j;
                if(k < 1) {
                    continue;
                }
                if(pow(i,2)+pow(j,2) == pow(k,2)) {
                    ++solutions;
                }
            }
        }
        if(solutions > maxSolutions) {
            maxSolutions = solutions;
            maxP = p;
        }
    }
    qDebug() << maxP << " has " << maxSolutions << " solutions";
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
