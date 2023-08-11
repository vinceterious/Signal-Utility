cmake_minimum_required(VERSION 3.14)
project(SignalUtility)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################
# Dataset example
################################

file(COPY "dataset/XC629629-Common-Wood-Pigeon-Columba-palumbus.wav" DESTINATION "${CMAKE_BINARY_DIR}")

################################
# Exec
################################
set(SRC
  main.cpp
  Signal.cpp
  SignalUtils.cpp
  FftUtils.cpp
)
add_executable(signalExample ${SRC} )