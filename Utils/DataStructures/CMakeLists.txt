include(UnknownEngineModuleUtils)

set_module_name(Utils_DataStructures)
set_module_type(INCLUDES_ONLY)

add_public_include(UnsafeVector.h)
add_public_include(UnsafeUnorderedMap.h)

generate_target()
set_project_label(DataStructures)
setup_installation()



set_folder_name(Utils)