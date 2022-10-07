#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>

using namespace std;

int main()
{
    vector<long long> primes;
    vector<bool> sieveVec;
    vector<long long> factors;
    long long target = 600851475143;
    long long sqTarget = (long long)sqrt(target);
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
    long long i = 0;
    while(target > 1) {
        while(target % primes[i] == 0) {
            factors.push_back(primes[i]);
            target /= primes[i];
        }
        ++i;
    }
    qDebug() << "largest factor: " << factors.back();
    return 0;
}
