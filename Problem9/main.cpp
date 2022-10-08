#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>
#include "core/timer.h"

using namespace std;

int main()
{
    Timer timer;
    long long product = 0;
    for(int a=1; a<=998; ++a) {
        for(int b=a; b<=998; ++b) {
            int c = 1000 - a - b;
            if(c < 1) {
                continue;
            }
            if(a*a + b*b == c*c) {
                product=a*b*c;
            }
        }
    }
    qDebug() << "product: " << product;
    qDebug() << timer.ticks().count() / 1000.0 << "ms";
    return 0;
}
