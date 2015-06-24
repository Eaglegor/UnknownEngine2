include(UnknownEngineModuleUtils)

set_module_name(Utils_Common)
set_module_type(INCLUDES_ONLY)

add_public_include(Singleton.h)

generate_target()
setup_installation()