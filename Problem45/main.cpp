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
    std::vector<long long> triNumVec;
    std::set<long long> pentNumSet;
    std::set<long long> hexNumSet;
    long long triNum=0;
    for(long long i=1; i<1000000; ++i) {
        triNumVec.push_back(i*(i+1)/2);
        pentNumSet.insert(i*(3*i-1)/2);
        hexNumSet.insert(i*(2*i-1));
    }
    long long ps = (long long)triNumVec.size();
    for(long long i=0; i<ps; ++i) {
        triNum = triNumVec[i];
        if(pentNumSet.find(triNum) != pentNumSet.end() &&
           hexNumSet.find(triNum) != hexNumSet.end() && triNum > 40755) {
            break;
        }
    }
    qDebug() << "the magic triangle: " << triNum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
