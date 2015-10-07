include(UnknownEngineModuleUtils)

set_module_name(Utils_Common)
set_module_type(INCLUDES_ONLY)

add_public_include(Singleton.h)
add_public_include(GUID.h)
add_public_include(String.h)

generate_target()
setup_installation()

set_project_label(Common)

set_folder_name(Utils)