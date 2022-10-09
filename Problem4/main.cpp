#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include "core/timer.h"
#include "core/BigInt.h"

using namespace std;

int main()
{
    Timer timer;
    int largestP = 0;
    for(int i=100; i<1000; ++i) {
        for(int j=i+1; j<1000; ++j) {
            int mult = i * j;
            std::vector<int> digits=BigInt::convertToDigitsVec(mult);
            auto ds = digits.size();
            long long lim = ds/2;
            long long k = 0;
            while(digits[k] == digits[ds-k-1] && k < lim) {
                ++k;
            }
            if(k == lim && mult > largestP) {
                largestP = mult;

                int k = 0;
                while(digits[k] == digits[ds-k-1] && k < lim) {
                    ++k;
                }
            }
        }
    }
    qDebug() << "largest palindrome: " << largestP;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
