include(UnknownEngineModuleUtils)

set_module_name(SamplePlugin)
set_module_type(PLUGIN)

add_source_file(SamplePlugin.cpp)

generate_target()
setup_installation()

set_folder_name(Plugins)

add_module_link_library(Plugins)

enable_build_speedup()