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

using namespace std;

static void
allPermutations(long long k, std::vector<long long> &vec, std::vector<std::vector<long long>> &permutations)
{
    if(k == 1) {
        permutations.push_back(vec);
    }
    else {
        for(long long i=0; i<k; ++i) {
            allPermutations(k - 1, vec, permutations);
            int swap = k % 2 == 0 ? i : 0;
            auto temp = vec[swap];
            vec[swap] = vec[k-1];
            vec[k-1] = temp;
        }
    }
}

int main()
{
    Timer timer;
    auto primes = primes::primes(100);
    long long sum = 0;
    std::vector<long long> digits = {0,1,2,3,4,5,6,7,8,9};
    std::vector<std::vector<long long>> permutaions;
    allPermutations((long long)10,digits,permutaions);
    for(auto digits : permutaions) {
        std::reverse(digits.begin(),digits.end());
        if(digits[0] == 0) {
            continue;
        }
        bool valid = true;
        for(int j=1; j<=7; ++j) {
            long long num = 0;
            long long p=0;
            for(int k=j+2; k>=j; --k) {
                num += digits[k] * pow(10,p);
                ++p;
            }
            if(num % primes[j-1] != 0) {
                valid = false;
                break;
            }
        }
        if(valid) {
            std::reverse(digits.begin(),digits.end());
            long long num = 0;
            for(int i=0; i<10; ++i) {
                num += digits[i] * pow(10,i);
            }
            sum += num;
        }
    }
    std::cout << "sum: " << sum << std::endl;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
