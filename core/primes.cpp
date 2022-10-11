#include "primes.h"
#include "sets.h"

#include <QDebug>
#include <QVector>
#include <set>

using namespace std;

std::vector<long long>
primes::primes(const long long &limit)
{
    vector<long long> primes;
    vector<bool> sieveVec;
    sieveVec.resize(limit+1,true);
    for(long long i=2; i<=limit; ++i) {
        if(!sieveVec[i]) {
            continue;
        }
        long long j = 2*i;
        while(j <= limit) {
            sieveVec[j]=false;
            j += i;
        }
    }
    for(long long i=2; i<=limit; ++i) {
        if(sieveVec[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

std::vector<std::pair<long long,long long>>
primes::primeFactors(const long long &num)
{
    std::vector<std::pair<long long,long long>> primeFactors;
    long long sqTarget = (long long)floor(sqrt(num));
    vector<long long> primes = primes::primes(sqTarget);
    long long i = 0;
    auto numCp = num;
    while(i < (long long)primes.size() && numCp > 1) {
        int count = 0;
        while(numCp % primes[i] == 0) {
            numCp /= primes[i];
            ++count;
        }
        if(count > 0) {
            primeFactors.push_back({primes[i],count});
        }
        ++i;
    }
    if(numCp > 1) {
        primeFactors.push_back({numCp,1});
    }
    return primeFactors;
}

std::vector<long long>
primes::divisors(const long long &num)
{
    if(num == 1) {
        return {1};
    }
    auto pFactors = primeFactors(num);
    std::map<long long,std::vector<long long>> unrolled;
    for(const auto &pf : pFactors) {
        for(long long i=0; i<=pf.second; ++i) {
            unrolled[pf.first].push_back(i);
        }
    }
    std::vector<std::vector<long long>> divisorVecs;
    for(auto it=unrolled.begin(); it!=unrolled.end(); ++it) {
        auto num = (*it).first;
        auto pows = (*it).second;
        auto allPows = pows.size();
        if(divisorVecs.size()) {
            std::vector<std::vector<long long>> newDivisorVecs;
            for(size_t i=0; i<allPows; ++i) {
                auto dVecsCopy = divisorVecs;
                for(auto &dv : dVecsCopy) {
                    dv.push_back(pow(num,pows[i]));
                }
                newDivisorVecs.insert(newDivisorVecs.end(),dVecsCopy.begin(),dVecsCopy.end());
            }
            divisorVecs = newDivisorVecs;
        }
        else {
            for(size_t i=0; i<allPows; ++i) {
                divisorVecs.push_back({(long long)pow(num,pows[i])});
            }
        }
    }
    std::set<long long> factors;
    for(auto &dv : divisorVecs) {
        long long prod=1;
        for(const auto &d : dv) {
            prod *= d;
        }
        factors.insert(prod);
    }
    std::vector<long long> factorsVec;
    for(const auto &s : factors) {
        factorsVec.push_back(s);
    }
    return factorsVec;
}

std::vector<long long>
primes::properDivisors(const long long &num)
{
    auto div = divisors(num);
    div.pop_back();
    return div;
}
