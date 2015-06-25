include(UnknownEngineModuleUtils)

set_module_name(Reflection)
set_module_type(SHARED_LIB)

add_public_include(IPropertiesMap.h)
add_public_include(IProperty.h)
add_public_include(IPropertyTypeMetaInfo.h)
add_public_include(PropertyTypeMetaInfo.h)

add_source_file(ReflectionManager.cpp)

generate_target()
setup_installation()
set_folder_name(Core)