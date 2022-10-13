PROJECT(core)
set(CorePlatformDependentSrc
    ${CorePlatformDependentSrc}
    Api.h
    CudaDevice.h
    CudaDevice.cpp
    CudaDevice_op.h
    CudaDevice_op.cpp
    timer.h
    timer.cpp
    primes.h
    primes.cpp
    BigInt.h
    BigInt.cpp
    BigFloat.h
    BigFloat.cpp
    sets.h
    sets.cpp
)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${CorePlatformDependentSrc})
target_compile_definitions(${PROJECT_NAME}
    PRIVATE BUILDING_CORE
)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME}
    ${Linked_Libraries} ${CUDA_LIBRARIES} ${CUDA_CUDA_LIBRARY} Qt5::Core)
