include(UnknownEngineModuleUtils)

set_module_name(Serialization)
set_module_type(INCLUDES_ONLY)

add_public_include(IArchive.h)
add_public_include(Serializable.h)

generate_target()
setup_installation()
set_folder_name(Core)