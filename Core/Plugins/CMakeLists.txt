include(UnknownEngineModuleUtils)

set_module_name(Plugins)
set_module_type(SHARED_LIB)

add_public_include(IPlugin.h)
add_public_include(PluginsManager.h)

add_source_file(PluginsManager.cpp)

generate_target()
setup_installation()
set_folder_name(Core)

add_module_link_library(OS)
add_module_link_library(Profiling)

set_pch_include(stdafx.h)
enable_build_speedup()