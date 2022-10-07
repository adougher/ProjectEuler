#include <iostream>

#include <QDebug>
#include <QVector>
#include <vector>

using namespace std;

int main()
{
    int diff = 0;
    int nums = 100;
    for(int i=1; i<=nums; ++i) {
        for(int j=i+1; j<=nums; ++j) {
            diff += i*j;
        }
    }
    diff *= 2;
    qDebug() << "diff: " << diff;
    return 0;
}
