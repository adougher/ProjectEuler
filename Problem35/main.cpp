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
    auto primes=primes::primes(1000000);
    std::set<long long> pSet;
    for(const auto &p : primes) {
        pSet.insert(p);
    }
    long long count=0;
    for(const auto &p : primes) {
        auto digits=BigInt::convertToDigitsVec(p);
        std::deque<long long> dd;
        for(const auto &d : digits) {
            dd.push_back(d);
        }
        auto ds = digits.size();
        bool good=true;
        for(size_t i=0; i<ds; ++i) {
            long long num = 0;
            long long j = 0;
            for(const auto &d : dd) {
                num += d * pow(10,j);
                ++j;
            }
            if(pSet.find(num) == pSet.end()) {
                good=false;
                break;
            }
            auto b = dd.back();
            dd.pop_back();
            dd.push_front(b);
        }
        if(good) {
            ++count;
            qDebug() << "num is good: " << p;
        }
    }
    std::cout << "circular primes: " << count << std::endl;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
