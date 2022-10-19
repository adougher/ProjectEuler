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
#include <QFile>

using namespace std;

int main()
{
    Timer timer;
    long long limit=1000000;
    long long thaNumber=0;
    for(int i=1; i<limit; ++i) {
        auto digits = BigInt::convertToDigitsVec(i);
        std::set<int> digitsSet;
        for(const auto &d : digits) {
            digitsSet.insert(d);
        }
        bool valid = true;
        for(int j=2; j<=6; ++j) {
            auto digits2 = BigInt::convertToDigitsVec(i*j);
            std::set<int> digitsSet2;
            for(const auto &d : digits2) {
                digitsSet2.insert(d);
            }
            if(digitsSet != digitsSet2) {
                valid=false;
                break;
            }
        }
        if(valid) {
            thaNumber=i;
            break;
        }
    }
    qDebug() << "That number is " << thaNumber;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
