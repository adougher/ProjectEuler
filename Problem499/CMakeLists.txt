PROJECT(problem499)

set(source
    main.cpp
    problem499.cu)

CUDA_ADD_EXECUTABLE(${PROJECT_NAME} ${resources} ${headers} ${source})

set_target_properties( ${PROJECT_NAME}
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES} ${CUDA_CUDA_LIBRARY} Qt5::Core core)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/core
    PUBLIC
    ${CMAKE_SOURCE_DIR}/core
    )
