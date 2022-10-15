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
    long long sum=0;
    for(const auto &p : primes) {
        auto digits=BigInt::convertToDigitsVec(p);
        auto ds = digits.size();
        if(ds == 1) {
            continue;
        }
        std::deque<long long> dd;
        for(const auto &d : digits) {
            dd.push_back(d);
        }
        bool good=true;
        for(auto k : {0,1}) {
            auto ddCp = dd;
            bool broken = false;
            for(size_t i=0; i<ds; ++i) {
                long long num = 0;
                long long j = 0;
                for(const auto &d : ddCp) {
                    num += d * pow(10,j);
                    ++j;
                }
                if(pSet.find(num) == pSet.end()) {
                    good=false;
                    broken = true;
                    break;
                }
                if(k==0) {
                    ddCp.pop_back();
                }
                else {
                    ddCp.pop_front();
                }
            }
            if(broken) {
                break;
            }
        }
        if(good) {
            sum += p;
            qDebug() << "num is good: " << p;
        }
    }
    std::cout << "bi-truncatable primes sum: " << sum << std::endl;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
