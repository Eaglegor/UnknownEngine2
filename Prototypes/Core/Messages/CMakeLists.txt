include(UnknownEngineModuleUtils)

set_module_name(Prototype_Core_Messages)
set_module_type(EXECUTABLE)

add_source_file(Messages.cpp)

generate_target()
setup_installation()

set_project_label(Messages)

set_folder_name(Prototypes/Core)