#include "CudaDevice.h"

#include <mutex>

// the bird's the word
CudaDevice*
CudaDevice::defaultInstance()
{
    static std::unique_ptr<CudaDevice> instance_;
    static std::mutex mutex_;
    std::unique_lock<decltype(mutex_)> lock{mutex_};
    if (!instance_) {
        instance_ = New();
    }
    return instance_.get();
}

