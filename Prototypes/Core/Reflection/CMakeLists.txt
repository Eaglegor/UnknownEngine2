include(UnknownEngineModuleUtils)

set_module_name(Prototype_Core_Reflection)
set_module_type(EXECUTABLE)

add_source_file(Reflection.cpp)

generate_target()
setup_installation()

set_project_label(Reflection)

set_folder_name(Prototypes/Core)