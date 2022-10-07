#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>

using namespace std;

int main()
{
    int lcm = 1;
    vector<long long> primes;
    vector<bool> sieveVec;
    long long sqTarget = 20;
    sieveVec.resize(sqTarget,true);
    for(long long i=2; i<sqTarget; ++i) {
        if(!sieveVec[i]) {
            continue;
        }
        long long j = 2*i;
        while(j < sqTarget) {
            sieveVec[j]=false;
            j += i;
        }
    }
    for(long long i=2; i<sqTarget; ++i) {
        if(sieveVec[i]) {
            primes.push_back(i);
        }
    }
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
        int i=0;
        auto fs = factors.size();
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
    return 0;
}
