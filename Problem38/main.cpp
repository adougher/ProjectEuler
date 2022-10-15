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
    BigInt best;
    for(long long i=1; i<=100000; ++i) {
        for(long long n=2; n<10; ++n) {
            std::vector<int> allDigits;
            for(long long k=1; k<=n; ++k) {
                long long prod = k*i;
                auto digits = BigInt::convertToDigitsVec(prod);
                allDigits.insert(allDigits.begin(),digits.begin(),digits.end());
            }
            std::set<int> allDigitsSet;
            for(const auto &d:allDigits) {
                allDigitsSet.insert(d);
            }
            if(allDigits.size() == 9 && allDigitsSet.size() == 9 &&
               allDigitsSet.find(0) == allDigitsSet.end()) {
                BigInt contender(allDigits);
                if(best < contender) {
                    best = contender;
                }
            }
        }
    }
    std::cout << "largest panny: " << best;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
