#include "primes.h"

using namespace std;

std::vector<long long>
primes::primes(const long long &limit)
{
    vector<long long> primes;
    vector<bool> sieveVec;
    sieveVec.resize(limit,true);
    for(long long i=2; i<limit; ++i) {
        if(!sieveVec[i]) {
            continue;
        }
        long long j = 2*i;
        while(j < limit) {
            sieveVec[j]=false;
            j += i;
        }
    }
    for(long long i=2; i<limit; ++i) {
        if(sieveVec[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}
