cmake_minimum_required(VERSION 3.1)

project(UNKNOWN_ENGINE)

if(WIN32)
	set(Boost_USE_STATIC_LIBS ON)
endif(WIN32)

set(DEPLOY_INCLUDES TRUE)

add_definitions(-DUNKNOWN_ENGINE_ENABLE_PROFILING)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/FindModules)

include(DetectCompiler)
include(CompilerFlags/${CMAKE_CXX_COMPILER_ID})

include_directories(${UNKNOWN_ENGINE_SOURCE_DIR})

add_subdirectory(Core)
add_subdirectory(Plugins)
add_subdirectory(Utils)
add_subdirectory(Assets)
add_subdirectory(SceneLoaders)
add_subdirectory(CMakeModules)
