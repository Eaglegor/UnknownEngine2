include(UnknownEngineModuleUtils)

set_module_name(OS)
set_module_type(SHARED_LIB)

add_public_include(DLLUtils.h)

if(WIN32)
	add_source_file(DLLUtils.windows.cpp)
elseif(UNIX)
	add_source_file(DLLUtils.unix.cpp)
endif()

generate_target()
setup_installation()
set_folder_name(Core)

if(UNIX)
	find_package(DL REQUIRED)
	if(DL_FOUND)
		include_directories(${DL_INCLUDE_DIR})
		target_link_libraries(${TARGET_NAME} ${DL_LIBRARIES})
	endif(DL_FOUND)
endif()