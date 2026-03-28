cmake_minimum_required(VERSION 3.10)
project(CppSpeedReader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SILKIT_ROOT
    "C:/Users/MohamedMooo/Downloads/SilKit-5.0.3-Win-x86-VS2019/SilKit-5.0.3-Win-x86-VS2019/SilKit"
)

if(EXISTS "${SILKIT_ROOT}")
    list(APPEND CMAKE_PREFIX_PATH "${SILKIT_ROOT}")
else()
    message(FATAL_ERROR "SIL Kit path not found: ${SILKIT_ROOT}")
endif()

find_package(SilKit REQUIRED)

add_executable(CppSpeedReader
    main.cpp
    RTE_Generation/Rte_WarningStatus.c
    RTE_Generation/Algorithm_SWC.c
    RTE_Generation/Rte_SA_Speed_SWC.c
)

target_include_directories(CppSpeedReader PRIVATE
    ${CMAKE_SOURCE_DIR}/RTE_Generation
)

target_link_libraries(CppSpeedReader SilKit::SilKit)