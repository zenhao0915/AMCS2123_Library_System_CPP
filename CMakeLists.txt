cmake_minimum_required(VERSION 4.2)
project(AMCS2123_Library_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(AMCS2123_Library_System main.cpp
        data.h
        member.cpp
        booking.cpp
        appointment.cpp
        billing.cpp
        report.cpp
        hotbooks.cpp
        blacklist.cpp
        fileManager.cpp
)
