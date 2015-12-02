cmake_minimum_required(VERSION 3.3)
project(RTOSObjectOrientedArduino)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Thread.cpp Thread.h ArduinoRTOSMain.cpp ArduinoRTOSMain.h ThreadManager.cpp ThreadManager.h Semaphore.cpp Semaphore.h Task.cpp Task.h TimerEvent.cpp TimerEvent.h SemaphoreDataManager.cpp SemaphoreDataManager.h)

add_executable(RTOSObjectOrientedArduino ${SOURCE_FILES})