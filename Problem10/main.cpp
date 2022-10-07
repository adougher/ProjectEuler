#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<long long> primes;
    vector<bool> sieveVec;
    vector<long long> factors;
    long long sieveLen = 2000000;
    sieveVec.resize(sieveLen,true);
    for(long long i=2; i<sieveLen; ++i) {
        if(!sieveVec[i]) {
            continue;
        }
        long long j = 2*i;
        while(j < sieveLen) {
            sieveVec[j]=false;
            j += i;
        }
    }
    for(long long i=2; i<sieveLen; ++i) {
        if(sieveVec[i]) {
            primes.push_back(i);
        }
    }
    long long sum=0;
    int ps = (int)primes.size();
    for(int i=0; i<ps; ++i) {
        sum += primes[i];
    }
    qDebug() << "sum: " << sum;
    return 0;
}
