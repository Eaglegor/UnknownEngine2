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