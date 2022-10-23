#include "primes.h"
#include "sets.h"

#include <QDebug>
#include <QVector>
#include <set>
#include <random>

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
primes::expand(const std::vector<std::pair<long long,long long>> &pfac)
{
    std::vector<long long> expanded;
    for(const auto & pf : pfac) {
        for(int i=0; i<pf.second; ++i) {
            expanded.push_back(pf.first);
        }
    }
    return expanded;
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

long long
primes::lcm(const long long &num1,
            const long long &num2)
{
    auto p1 = primeFactors(num1);
    auto p2 = primeFactors(num2);
    long long prod = 1;
    for(const auto &p : p1) {
        bool found=false;
        for(const auto &q : p2) {
            if(p.first == q.first) {
                prod *= pow(p.first,std::max(p.second,q.second));
                found = true;
                break;
            }
        }
        if(!found) {
            prod *= pow(p.first,p.second);
        }
    }
    for(const auto &p : p2) {
        bool found=false;
        for(const auto &q : p1) {
            if(p.first == q.first) {
                found = true;
                break;
            }
        }
        if(!found) {
            prod *= pow(p.first,p.second);
        }
    }
    return prod;
}

long long
primes::gcd(const long long &num1,
            const long long &num2)
{
    bool num1Less = num1 < num2;
    long long min=num1Less ? num1 : num2;
    long long max=num1Less ? num2 : num1;
    while(min > 0) {
        auto temp = min;
        min = max % min;
        max = temp;
    }
    return max;
}

BigInt
primes::gcd(const BigInt &num1,
            const BigInt &num2)
{
    bool num1Less = num1 < num2;
    BigInt min=num1Less ? num1 : num2;
    BigInt max=num1Less ? num2 : num1;
    while(BigInt({}) < min) {
        auto temp = min;
        min = max % min;
        max = temp;
    }
    return max;
}

static long long
powMod(const long long &a,
       const long long &x,
       const long long &n)
{
    if(x == 0) {
        return 1;
    }
    long long result=a;
    if(x == 1) {
        return result % n;
    }
    long long pows = (long long)floor(log2(x));
    long long twoPow = 1;
    while(twoPow <= pows) {
        result = (result * result) % n;
        ++twoPow;
    }
    twoPow = (long long)pow(2,twoPow - 1);
    result = (result * powMod(a,x-twoPow,n)) % n;
    return result;
}

static bool init=false;
static std::random_device rd;
static std::mt19937 mt;
static std::uniform_int_distribution<long long> dist;
bool
primes::isPrime(const long long &n)
{
    if(n == 3 || n == 2) {
        return true;
    }
    long long d = n - 1;
    long long s = 0;
    while((d & 0x00000001) == 0) {
        d = d >> 1;
        ++s;
    }
    long long trials = 10;
    if(!init) {
        mt = std::mt19937(rd());
        dist = std::uniform_int_distribution<long long>(2,n-2);
        init=true;
    }
    for(long long k=0; k<trials; ++k) {
        long long a = dist(mt);
        long long x = powMod(a,d,n);
        if(x == 1 || x == n-1) {
            continue;
        }
        bool broken = false;
        for(int i=0; i < s - 1; ++i) {
            x = (x*x) % n;
            if(x == n-1) {
                broken = true;
                break;
            }
        }
        if(!broken) {
            return false;
        }
    }
    return true;
}
