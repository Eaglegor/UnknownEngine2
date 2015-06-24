include(UnknownEngineModuleUtils)

set_module_name(Plugins)
set_module_type(SHARED_LIB)

add_public_include(IPlugin.h)
add_public_include(PluginsManager.h)

add_source_file(PluginsManager.cpp)

generate_target()
setup_installation()

setup_precompiled_header(stdafx.h stdafx.cpp)

add_module_link_library(OS)
add_module_link_library(Profiling)