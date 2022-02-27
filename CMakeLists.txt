cmake_minimum_required(VERSION 3.21)
project(dbedu)

set(CMAKE_CXX_STANDARD 20)

add_executable(dbedu main.cpp Tables/cHeapTable.h Tables/cRecord.h Tables/cRecordTable.h Tables/cHashTableNode.h Tables/cHashTable.h Tables/cMemory.h)
