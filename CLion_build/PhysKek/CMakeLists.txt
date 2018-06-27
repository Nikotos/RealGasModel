cmake_minimum_required(VERSION 3.9)
project(PhysKek)

set(CMAKE_CXX_STANDARD 11)
add_executable(PhysKek main.cpp Collector/Collector.h Collector/Collector.hpp
                Collector/objects/Heroes.h Collector/objects/Heroes.hpp
                Collector/OakEngine/OakEngine.h Collector/OakEngine/OakEngine.hpp)

set(SFML_DIR "/home/noak/Desktop/Programms/CLion/MyLib/SFML-2.4.2/share/SFML/cmake/Modules")
set(CMAKE_MODULE_PATH "/home/noak/Desktop/Programms/CLion/MyLib/SFML-2.4.2/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(PhysKek ${SFML_LIBRARIES})
endif()







