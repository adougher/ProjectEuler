PROJECT(problem60)

set(source
    main.cpp
    matrixMult.cu)

CUDA_ADD_EXECUTABLE(${PROJECT_NAME} ${resources} ${headers} ${source})

set_target_properties( ${PROJECT_NAME}
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(${PROJECT_NAME} Qt5::Core core)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/core
    PUBLIC
    ${CMAKE_SOURCE_DIR}/core
    )
