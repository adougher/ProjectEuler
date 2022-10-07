#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>
#include <string>

using namespace std;

int main()
{
    long long product = 0;
    for(int a=1; a<=998; ++a) {
        for(int b=a; b<=998; ++b) {
            int c = 1000 - a - b;
            if(c < 1) {
                continue;
            }
            if(a*a + b*b == c*c) {
                qDebug() << "a: " << a;
                qDebug() << "b: " << b;
                qDebug() << "c: " << c;
                qDebug() << "a*a + b*b: " << a*a + b*b;
                qDebug() << "c*c: " << c*c;
                qDebug() << "a+b+c: " << a+b+c;
                product=a*b*c;
            }
        }
    }
    qDebug() << "product: " << product;
    return 0;
}
