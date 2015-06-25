include(UnknownEngineModuleUtils)

set_module_name(State)
set_module_type(INCLUDES_ONLY)

add_public_include(Synchronizable.h)

generate_target()
setup_installation()
set_folder_name(Core)