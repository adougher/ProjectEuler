#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    int sum=0;
    std::set<long long> prodSet;
    for(long long i=1; i<10000; ++i) {
        for(long long j=i+1; j<10000; ++j) {
            std::set<long long> digitsSet;
            std::vector<long long> digitsVec;
            auto digVec1 = BigInt::convertToDigitsVec(i);
            auto digVec2 = BigInt::convertToDigitsVec(j);
            if(digVec1.size() + digVec2.size() > 5) {
                continue;
            }
            long long prod = i * j;
            auto digVec3 = BigInt::convertToDigitsVec(prod);
            for(const auto &d : digVec1) {
                digitsSet.insert(d);
            }
            for(const auto &d : digVec2) {
                digitsSet.insert(d);
            }
            for(const auto &d : digVec3) {
                digitsSet.insert(d);
            }
            digitsVec.insert(digitsVec.end(),digVec1.begin(),digVec1.end());
            digitsVec.insert(digitsVec.end(),digVec2.begin(),digVec2.end());
            digitsVec.insert(digitsVec.end(),digVec3.begin(),digVec3.end());
            if(digitsSet.size() == 9 && digitsVec.size() == 9 &&
               digitsSet.find(0) == digitsSet.end()) {
                prodSet.insert(prod);
                qDebug() << "pan dig: " << i << "*" << j << ": " << prod;
            }
        }
    }
    for(const auto &d : prodSet) {
        qDebug() << "THA D: " << d;
        sum += d;
    }
    qDebug() << "sum: " << sum;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
