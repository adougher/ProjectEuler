#ifndef CudaDevice_file_h_included
#define CudaDevice_file_h_included

#include "Api.h"

#include <memory>
class COREAPI CudaDevice
{
    public:
        virtual ~CudaDevice() = default;

        static CudaDevice* defaultInstance();

        /* implemented in os impl files */
        static std::unique_ptr<CudaDevice> New();

        bool init() {
            return init_impl();
        }
        void show_device_information() {
            show_device_information_impl();
        }
        bool populate_device_information() {
            return populate_device_information_impl();
        }

        void reset() {
            reset_impl();
        }

        size_t availableCudaMemory() {return mAvailableCudaMemory;}
        size_t totalCudaMemory() {return mTotalCudaMemory;}
        size_t deviceClockRate() {return mDeviceClockRate;}
        size_t maxThreadsPerBlock() {return mMaxThreadsPerBlock;}
        size_t maxThreadsPerMultiProcessor() {return mMaxThreadsPerMP;}
        size_t sharedMemoryPerBlock() {return mSharedMemPerBlock;}
        size_t cudaCores() {return mCudaCores;}

    protected:
        virtual bool init_impl()=0;
        virtual void show_device_information_impl()=0;
        virtual bool populate_device_information_impl()=0;
        virtual void reset_impl()=0;

        size_t mAvailableCudaMemory;
        size_t mTotalCudaMemory;
        size_t mDeviceClockRate;
        size_t mMaxThreadsPerBlock;
        size_t mMaxThreadsPerMP;
        size_t mSharedMemPerBlock;
        size_t mCudaCores;
};

#endif

