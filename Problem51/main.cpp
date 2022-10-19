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
    auto primes = primes::primes(limit);
    std::set<long long> primesSet;
    for(const auto &p : primes) {
        primesSet.insert(p);
    }
    long long thaNumber=0;
    long long target=8;
    std::vector<long long> boPancy;
    for(const auto &p : primes) {
        if(p < 10000) {
            continue;
        }
        auto digVec = BigInt::convertToDigitsVec(p);
        bool broken = false;
        auto pairs = sets::nChoose2Indices(digVec);
        for(const auto &pair : pairs) {
            int count = 0;
            boPancy.clear();
            for(int i=0; i<10; ++i) {
                auto dvCp = digVec;
                dvCp[pair[0]] = i;
                dvCp[pair[1]] = i;
                auto num = BigInt::digitsVecToLong(dvCp);
                auto digVec2 = BigInt::convertToDigitsVec(num);
                if(digVec2.size() == digVec.size() &&
                   primesSet.find(num) != primesSet.end()) {
                    boPancy.push_back(num);
                    ++count;
                }
            }
            if(count == target) {
                broken=true;
                break;
            }
        }
        if(broken) {
            thaNumber=p;
            break;
        }
        auto triples = sets::nChoose3Indices(digVec);
        for(const auto &triple : triples) {
            int count = 0;
            boPancy.clear();
            for(int i=0; i<10; ++i) {
                auto dvCp = digVec;
                dvCp[triple[0]] = i;
                dvCp[triple[1]] = i;
                dvCp[triple[2]] = i;
                auto num = BigInt::digitsVecToLong(dvCp);
                auto digVec2 = BigInt::convertToDigitsVec(num);
                if(digVec2.size() == digVec.size() &&
                   primesSet.find(num) != primesSet.end()) {
                    boPancy.push_back(num);
                    ++count;
                }
            }
            if(count == target) {
                broken=true;
                break;
            }
        }
        if(broken) {
            thaNumber=p;
            break;
        }
        auto quaddies = sets::nChoose4Indices(digVec);
        for(const auto &quaddie : quaddies) {
            int count = 0;
            boPancy.clear();
            for(int i=0; i<10; ++i) {
                auto dvCp = digVec;
                dvCp[quaddie[0]] = i;
                dvCp[quaddie[1]] = i;
                dvCp[quaddie[2]] = i;
                dvCp[quaddie[3]] = i;
                auto num = BigInt::digitsVecToLong(dvCp);
                auto digVec2 = BigInt::convertToDigitsVec(num);
                if(digVec2.size() == digVec.size() &&
                   primesSet.find(num) != primesSet.end()) {
                    boPancy.push_back(num);
                    ++count;
                }
            }
            if(count == target) {
                broken=true;
                break;
            }
        }
        if(broken) {
            thaNumber=p;
            break;
        }
    }
    qDebug() << thaNumber << " is the first " << target << " bo'pancy with bo'pancy numbers: " << QVector<long long>::fromStdVector(boPancy);
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
