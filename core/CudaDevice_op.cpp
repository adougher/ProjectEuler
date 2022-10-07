#include "CudaDevice_op.h"

#include <cuda.h>
#include <cuda_runtime_api.h>

#include <QString>
#include <QDebug>

#include <ratio>

static int _ConvertSMVer2Cores(int major, int minor)
{
    // Defines for GPU Architecture types (using the SM version to determine
    // the # of cores per SM
    typedef struct {
        int SM;  // 0xMm (hexidecimal notation), M = SM Major version,
        // and m = SM minor version
        int Cores;
    } sSMtoCores;

    sSMtoCores nGpuArchCoresPerSM[] = {
        {0x30, 192},
        {0x32, 192},
        {0x35, 192},
        {0x37, 192},
        {0x50, 128},
        {0x52, 128},
        {0x53, 128},
        {0x60,  64},
        {0x61, 128},
        {0x62, 128},
        {0x70,  64},
        {0x72,  64},
        {0x75,  64},
        {0x80,  64},
        {-1, -1}
    };

    int index = 0;
    while (nGpuArchCoresPerSM[index].SM != -1) {
        if (nGpuArchCoresPerSM[index].SM == ((major << 4) + minor)) {
            return nGpuArchCoresPerSM[index].Cores;
        }
        index++;
    }
    return nGpuArchCoresPerSM[index - 1].Cores;
}

static QString
q_cuda_error()
{
    return QString{cudaGetErrorString(
            cudaGetLastError())};
}

std::unique_ptr<vmt::CudaDevice>
vmt::CudaDevice::New()
{
    return std::unique_ptr<CudaDevice>{new CudaDevice_op};
}

bool
vmt::CudaDevice_op::init_impl()
{
    if (cuInit(0) != CUDA_SUCCESS ||
        cudaDeviceSynchronize() != cudaSuccess) {
        qCritical() << "could not initialize cuda";
        return false;
    }
    return true;
}

void
vmt::CudaDevice_op::show_device_information_impl()
{
    int dc = 0;
    if (cuDeviceGetCount(&dc) != CUDA_SUCCESS) {
        qCritical() << "cuDeviceGetCount failed with message:"
            << q_cuda_error();
        return;
    }
    int device = {};
    if (cudaGetDevice(&device) != cudaSuccess) {
        qCritical() << "cudaGetDevice failed with message:"
            << q_cuda_error();
        return;
    }
    size_t av = {};
    size_t tl = {};
    if (cudaMemGetInfo(&av, &tl) != cudaSuccess) {
        qCritical() << "cudaMemGetInfo() failed with message:"
            << q_cuda_error();
        return;
    }
    qInfo() << "available cuda memory=" << av / std::mega::num << "MB";
    qInfo() << "total cuda memory=" << tl / std::mega::num << "MB";
    cudaDeviceProp properties = {};
    if (cudaGetDeviceProperties(&properties, device) != cudaSuccess) {
        qCritical() << "cudaGetDeviceProperties failed with message:"
            << q_cuda_error();
        return;
    }
    qInfo() << "card clock rate="
        << properties.clockRate / std::kilo::num << "kHz\n"
        << "computeMode=" << properties.computeMode << "\n"
        << "pciBusID=" << properties.pciBusID << "\n"
        << "maxThreadsPerBlock=" << properties.maxThreadsPerBlock << "\n"
        << "maxThreadsPerMP=" << properties.maxThreadsPerMultiProcessor;
}

bool
vmt::CudaDevice_op::populate_device_information_impl()
{
    int dc = 0;
    if(cuDeviceGetCount(&dc) != CUDA_SUCCESS) {
        qCritical() << "cuDeviceGetCount failed with message:"
            << q_cuda_error();
        return false;
    }
    int device = {};
    if(cudaGetDevice(&device) != cudaSuccess) {
        qCritical() << "cudaGetDevice failed with message:"
            << q_cuda_error();
        return false;
    }
    if (cudaMemGetInfo(&mAvailableCudaMemory, &mTotalCudaMemory) != cudaSuccess) {
        qCritical() << "cudaMemGetInfo() failed with message:"
            << q_cuda_error();
        return false;
    }
    mAvailableCudaMemory /= std::mega::num;
    mTotalCudaMemory /= std::mega::num;
    cudaDeviceProp properties = {};
    if (cudaGetDeviceProperties(&properties, device) != cudaSuccess) {
        qCritical() << "cudaGetDeviceProperties failed with message:"
            << q_cuda_error();
        return false;
    }
    mDeviceClockRate = properties.clockRate / std::kilo::num;
    mMaxThreadsPerBlock = properties.maxThreadsPerBlock;
    mMaxThreadsPerMP = properties.maxThreadsPerMultiProcessor;
    mSharedMemPerBlock = properties.sharedMemPerBlock / std::kilo::num;
    int coresPerMP = _ConvertSMVer2Cores(properties.major,properties.minor);
    mCudaCores = properties.multiProcessorCount * coresPerMP;

    return true;
}

void
vmt::CudaDevice_op::reset_impl()
{
    cudaDeviceReset();
}

