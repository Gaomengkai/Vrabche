cmake_minimum_required(VERSION 3.15)

project(Vrabche)
set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

# add antlr4
include_directories(/usr/local/include/antlr4-runtime)
link_directories(/usr/local/lib)
# multi-platform dependency
if (WIN32)
    include_directories("C:\\Program Files (x86)\\LIBANTLR4\\include\\antlr4-runtime")
    link_directories("C:\\Program Files (x86)\\LIBANTLR4\\bin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MT")
endif (WIN32)
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,4000000")
endif (WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# add source files like CBaseListener.cpp, CBaseVisitor.cpp, etc.
file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/MiddleIR/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/MiddleOpt/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/R5Emitter/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/IRGen/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/LLVMIRParser/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/R5Utils/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/R5Opt/*.cpp)
file(GLOB SRC_LIST ${SRC_LIST} ${PROJECT_SOURCE_DIR}/SYSYParser/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC /usr/local/include/antlr4-runtime)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/MiddleIR)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/MiddleOpt)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/R5Emitter)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/IRGen)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/LLVMIRParser)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/R5Utils)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/R5Opt)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/SYSYParser)
target_link_libraries(${PROJECT_NAME} antlr4-runtime)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "C:\\Program Files (x86)\\LIBANTLR4\\bin\\libantlr4-runtime.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying libantlr4-runtime.dll to executable directory"
            )
endif ()