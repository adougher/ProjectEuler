#include <iostream>

#include <QDebug>
#include "core/CudaDevice.h"

using namespace std;

extern double problem499_cuda(const uint64_t &fortune, const uint64_t &cost, const int &precision, const uint64_t &maxItrs,
                              int maxNumBlocks=1024, bool arnoldi=false);

int main(int argc, char* argv[])
{
    if(argc != 5 && argc != 6 && argc != 7) {
        qDebug() << "must specify [initial fortune] [cost per game] [desired digits of precision] [maximum power iterations] " <<
                    "[max block size (optional)] [verbose (optional)]";
        return 1;
    }
    auto cuda = CudaDevice::defaultInstance();
    cuda->init();
    uint64_t fortune = QString(argv[1]).toULongLong();
    uint64_t cost = QString(argv[2]).toULongLong();
    int precision = QString(argv[3]).toInt();
    uint64_t maxItrs = QString(argv[4]).toULongLong();
    int maxNumBlocks = argc > 5 ? QString(argv[5]).toInt() : 65535;
    printf("answer: %.8f\n",problem499_cuda(fortune,cost,precision,maxItrs,maxNumBlocks,argc==6));
    return 0;
}
