cmake_minimum_required(VERSION 3.25)
project(TimetableBot)

set(CMAKE_CXX_STANDARD 23)
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL REQUIRED)
find_package(cpr REQUIRED)
find_package(RapidJSON REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(TimetableBot
        src/main.cpp
        src/Types/Lesson.cpp
        src/Types/Lesson.h
        src/API/ScheduleAPI.cpp
        src/API/ScheduleAPI.h
        src/Types/ScheduleDay.cpp
        src/Types/ScheduleDay.h
)

target_link_libraries(TimetableBot D:/dev/vcpkg/installed/x64-windows/lib/TgBot.lib cpr::cpr rapidjson ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})

