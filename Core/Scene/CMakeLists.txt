include(UnknownEngineModuleUtils)

set_module_name(Scene)
set_module_type(SHARED_LIB)

add_public_include(IComponent.h)
add_public_include(ISceneObject.h)
add_public_include(SceneManager.h)
add_public_include(ComponentDesc.h)
add_public_include(ComponentType.h)

add_private_include(impl/SceneObject.h)

add_source_file(impl/SceneManager.cpp)
add_source_file(impl/SceneObject.cpp)

generate_target()
setup_installation()
set_folder_name(Core)

add_module_link_library(Memory)

enable_build_speedup()