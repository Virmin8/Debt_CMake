cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  OFF)

project(Debt2)
file(GLOB dependencies_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
find_package(nlohmann_json CONFIG REQUIRED)

find_package(cpr CONFIG REQUIRED)

add_executable(Debt2 ${dependencies_SRC})

target_link_libraries(Debt2 PRIVATE nlohmann_json::nlohmann_json cpr::cpr)
