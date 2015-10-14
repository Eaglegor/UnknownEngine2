include(UnknownEngineModuleUtils)

set_module_name(SamplePlugin)
set_module_type(PLUGIN)

add_private_include(SampleComponent.h)
add_private_include(SampleSubsystem.h)

add_source_file(SamplePlugin.cpp)

generate_target()
setup_installation()

set_folder_name(Plugins)

add_module_link_library(Plugins)
add_module_link_library(Memory)

enable_build_speedup()