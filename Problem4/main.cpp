#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>

using namespace std;

int main()
{
    int largestP = 0;
    for(int i=100; i<1000; ++i) {
        for(int j=i+1; j<1000; ++j) {
            int mult = i * j;
            std::vector<int> digits;
            int ds = 3;
            int start = 100;
            while(start < mult) {
                start *= 10;
                ++ds;
            }
            --ds;
            int reduce = mult;
            auto ds_reduce = ds;
            while(ds_reduce > 0) {
                start /= 10;
                digits.push_back(reduce / start);
                reduce -= digits.back() * start;
                --ds_reduce;
            }
            int lim = ds/2;
            int k = 0;
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
    return 0;
}
