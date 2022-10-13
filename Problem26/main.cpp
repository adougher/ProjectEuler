#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include <set>
#include <bitset>
#include "core/timer.h"
#include "core/primes.h"
#include "core/BigFloat.h"

using namespace std;

int main()
{
    Timer timer;
//    for(int i=0; i<10; ++i) {
//        auto num1 = 10.0 * rand() / RAND_MAX;
//        auto num2 = 10.0 * rand() / RAND_MAX;
//        auto bnum1 = BigFloat(num1);
//        auto bnum2 = BigFloat(num2);
//        std::cout << "num1: " << num1 << std::endl;
//        std::cout << "num2: " << num2 << std::endl;
//        std::cout << "num1+num2: " << num1+num2 << std::endl;
//        std::cout << "num1-num2: " << num1-num2 << std::endl;
//        std::cout << "num2-num2: " << num2-num1 << std::endl;
//        std::cout << "num1*num2: " << num1*num2 << std::endl;
//        std::cout << "num1^num2: " << pow(num1,num2) << std::endl;
//        std::cout << "num2^num2: " << pow(num2,num2) << std::endl;
//        std::cout << "e^num1: " << exp(num1) << std::endl;
//        std::cout << "log(num2): " << log(num2) << std::endl;
//        std::cout << "bnum1: " << bnum1.truncated(50);
//        std::cout << "bnum2: " << bnum2.truncated(50);
//        std::cout << "bnum1+bnum2: " << (bnum1+bnum2).truncated(50);
//        std::cout << "bnum1-bnum2: " << (bnum1-bnum2).truncated(50);
//        std::cout << "bnum2-bnum2: " << (bnum2-bnum1).truncated(50);
//        std::cout << "bnum1*bnum2: " << (bnum1*bnum2).truncated(50);
//        std::cout << "bnum1/bnum2: " << (bnum1/bnum2).truncated(50);
//        std::cout << "bnum2/bnum2: " << (bnum2/bnum1).truncated(50);
//        std::cout << "e^bnum1: " << BigFloat::exp(bnum1).truncated(50);
//        std::cout << "log(bnum2): " << BigFloat::log(bnum2).truncated(50);

////        std::cout << "num1/num2: " << num1/num2 << std::endl;
////        std::cout << "num2/num2: " << num2/num1 << std::endl;
////        std::cout << "bnum1^bnum2: " << (bnum1^bnum2);
////        std::cout << "bnum2^bnum2: " << (bnum2^bnum2);
//    }
    auto primes = primes::primes(1000);
    size_t maxCycleLen = 0;
    size_t maxCycleNum = 1;
    for(const auto &p : primes) {
        int ten=10 % p;
        std::set<int> els;
        while(els.find(ten) == els.end()) {
            els.insert(ten);
            ten=(ten*10) % p;
        }
        size_t cylen = els.size();
        if(maxCycleLen < cylen) {
            maxCycleLen = cylen;
            maxCycleNum = p;
        }
    }
    qDebug() << "number with max cycle length: 1 /" << maxCycleNum << ", cycle length: " << maxCycleLen;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
