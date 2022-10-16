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
#include <QFile>

using namespace std;

int main()
{
    Timer timer;
    std::vector<long long> pentNumVec;
    std::set<long long> pentNumSet;
    std::pair<long long, long long> minPair;
    for(long long i=1; i<10000; ++i) {
        auto pNum = i*(3*i-1)/2;
        pentNumSet.insert(pNum);
        pentNumVec.push_back(pNum);
    }
    long long ps = (long long)pentNumVec.size();
    long long minDiff = std::numeric_limits<long long>::max();
    for(long long i=0; i<ps; ++i) {
        for(long long j=i+1; j<ps; ++j) {
            auto sum = pentNumVec[i] + pentNumVec[j];
            auto absDiff = std::abs(pentNumVec[i] - pentNumVec[j]);
            if(pentNumSet.find(sum) != pentNumSet.end() &&
               pentNumSet.find(absDiff) != pentNumSet.end()) {
                minPair.first = pentNumVec[i];
                minPair.second = pentNumVec[j];
                if(absDiff < minDiff) {
                    minDiff = absDiff;
                }
            }
        }
    }
    qDebug() << "the min difference is " << minDiff << " and occurs for the pair {" << minPair.first << ", " << minPair.second << "}";
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
