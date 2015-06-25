include(UnknownEngineModuleUtils)

set_module_name(Tasks)
set_module_type(INCLUDES_ONLY)

add_public_include(ITask.h)

generate_target()
setup_installation()
set_folder_name(Core)