cmake_minimum_required(VERSION 3.14)
project(challenging)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled7 main.cpp GarbageCollection.cpp GarbageCollection.h VirtualMachine.cpp VirtualMachine.h Object_.h Frame.cpp Frame.h Structures/instruction.h Converter.cpp Converter.h Structures/object.h Structures/frame.h Structures/class.h Structures/test.cpp Structures/value.h)