include(UnknownEngineModuleUtils)

set_module_name(Math)
set_module_type(INCLUDES_ONLY)

add_public_include(Scalar.h)

generate_target()
setup_installation()
set_folder_name(Core)
