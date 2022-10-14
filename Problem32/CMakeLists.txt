PROJECT(problem32)

set(source
    main.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${resources} ${headers} ${source})

target_link_libraries(${PROJECT_NAME} Qt5::Core core)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/core
    PUBLIC
    ${CMAKE_SOURCE_DIR}/core
    )
