#ifndef vmt_CudaDevice_op_file_h_included
#define vmt_CudaDevice_op_file_h_included

#include "core/CudaDevice.h"

namespace vmt {

    class CudaDevice_op : public CudaDevice
    {
        public:
            virtual ~CudaDevice_op() = default;
        protected:
            bool init_impl() override;
            void show_device_information_impl() override;
            bool populate_device_information_impl() override;
            void reset_impl() override;
    };

}

#endif

