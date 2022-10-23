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
#include "core/sets.h"

using namespace std;

int main()
{
    Timer timer;
    BigInt thaNumber;
    auto primesVec = primes::primes(10000);
    std::set<long long> primes;
    for(const auto &p : primesVec) {
        primes.insert(p);
    }
    for(long long i=1000; i<10000; ++i) {
        bool found = false;
        for(long long j=1; j<=4999; ++j) {
            std::vector<long long> candidates;
            for(long long k=0; k<3; ++k) {
                long long num = i+k*j;
                if(num >= 10000 || primes.find(num) == primes.end()) {
                    break;
                }
                candidates.push_back(num);
            }
            if(candidates.size() == 3 && i != 1487) {
                auto digVec = BigInt::convertToDigitsVec(i);
                std::vector<std::vector<int>> permutations;
                sets::permutations(digVec.size(),digVec,permutations);
                bool valid = true;
                for(long long k=1; k<3; ++k) {
                    auto digVec = BigInt::convertToDigitsVec(candidates[k]);
                    if(std::find(permutations.begin(),permutations.end(),digVec) == permutations.end()) {
                        valid=false;
                        break;
                    }
                }
                if(valid) {
                    std::vector<int> allNums;
                    for(long long k=0; k<3; ++k) {
                        auto digVec = BigInt::convertToDigitsVec(candidates[k]);
                        allNums.insert(allNums.begin(),digVec.begin(),digVec.end());
                    }
                    thaNumber = BigInt(allNums);
                    found=true;
                }
            }
            if(found) {
                break;
            }
        }
        if(found) {
            break;
        }
    }
    std::cout << "the magic number is " << thaNumber;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
