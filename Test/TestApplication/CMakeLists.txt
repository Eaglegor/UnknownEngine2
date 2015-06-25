include(UnknownEngineModuleUtils)

set_module_name(TestApplication)
set_module_type(EXECUTABLE)

add_source_file(main.cpp)

generate_target()
setup_installation()
set_folder_name(Test)

add_module_link_library(Plugins)
add_module_link_library(Profiling)