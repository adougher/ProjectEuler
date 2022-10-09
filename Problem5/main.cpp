#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include "core/timer.h"
#include "core/primes.h"

using namespace std;

int main()
{
    Timer timer;
    int lcm = 1;
    long long sqTarget = 20;
    vector<long long> primes=primes::primes(sqTarget);
    std::map<int,std::vector<int>> numsToFactors;
    for(int target = 2; target<=20; ++target) {
        vector<long long> factors;
        long long i = 0;
        int tCopy = target;
        while(tCopy > 1) {
            while(tCopy % primes[i] == 0) {
                numsToFactors[target].push_back(primes[i]);
                tCopy /= primes[i];
            }
            ++i;
        }
    }
    std::map<int,int> factorsToMaxCounts;
    for(int target = 2; target<=20; ++target) {
        auto factors = numsToFactors[target];
        std::map<int,int> factorsToCounts;
        long long i=0;
        long long fs = factors.size();
        while(i < fs) {
            auto f = factors[i];
            factorsToCounts[f] = 1;
            while(++i<fs && factors[i] == f) {
                ++factorsToCounts[f];
            }
            if(factorsToMaxCounts.find(f) == factorsToMaxCounts.end() ||
               factorsToCounts[f] > factorsToMaxCounts[f]) {
                factorsToMaxCounts[f] = factorsToCounts[f];
            }
        }
    }
    for(auto f2mc : factorsToMaxCounts) {
        lcm *= pow(f2mc.first,f2mc.second);
    }
    qDebug() << "lcm: " << lcm;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
