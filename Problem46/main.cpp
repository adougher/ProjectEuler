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
    long long limit = 10000;
    auto primesVec = primes::primes(limit);
    std::set<long long> primes;
    for(const auto &p : primesVec) {
        primes.insert(p);
    }
    std::vector<long long> oddComposites;
    std::vector<long long> squares;
    for(long long i=1; i<limit; ++i) {
        auto odd = 2*i+1;
        if(primes.find(odd) == primes.end()) {
            oddComposites.push_back(odd);
        }
    }
    primesVec = primes::primes(oddComposites.back());
    primes.clear();
    for(const auto &p : primesVec) {
        primes.insert(p);
    }
    for(long long i=1; i<(long long)ceil(sqrt(oddComposites.back()/2)); ++i) {
        squares.push_back(i*i);
    }
    qDebug() << "oddComposites.back(): " << oddComposites.back();
    qDebug() << "primesVec.back(): " << primesVec.back();
    qDebug() << "squares.back(): " << squares.back();
    long long ps = (long long)oddComposites.size();
    long long odd = 0;
    for(long long i=0; i<ps; ++i) {
        auto oddPoss = oddComposites[i];
        bool valid = false;
        for(const auto &p : primesVec) {
            for(const auto &sq : squares) {
                if(oddPoss == (p + 2 * sq)) {
                    valid = true;
//                    qDebug() << oddPoss << " is " << p << " + 2 * " << sq;
                }
                if(valid) {
                    break;
                }
            }
            if(valid) {
                break;
            }
        }
        if(!valid) {
            odd = oddPoss;
            break;
        }
    }
    qDebug() << "the smalles example is " << odd;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
