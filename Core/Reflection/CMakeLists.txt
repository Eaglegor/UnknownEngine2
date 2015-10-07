include(UnknownEngineModuleUtils)

set_module_name(Reflection)
set_module_type(SHARED_LIB)

add_public_include(IMetaType.h)
add_public_include(TypeSize.h)

add_source_file(main.cpp)

generate_target()
setup_installation()
set_folder_name(Core)