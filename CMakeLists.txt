cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(example-pnm CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    #set(CMAKE_BUILD_TYPE Debug) # keep assertion() on
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${INC_PATH}
)

include(FetchContent)
# you can also pick a particular commit es. FetchContent_Declare(opnm GIT_REPOSITORY https://github.com/Manu-sh/opnm.git GIT_TAG 41322ddef0feb4f7edec96c0adb86840723914bb)
FetchContent_Declare(opnm GIT_REPOSITORY https://github.com/Manu-sh/opnm.git) 
FetchContent_MakeAvailable(opnm)

# add & link pnm
target_link_libraries(${PROJECT_NAME} PRIVATE opnm)

target_compile_options(${PROJECT_NAME} PRIVATE
        -O3
        -pedantic
        -Wall -Wextra -Wno-unused-function -pipe
        -fstack-protector-all -fstack-protector-strong
	-ffast-math -funroll-loops -march=native -mtune=native
        -funswitch-loops -ftree-vectorize -fivopts -fmodulo-sched
)



