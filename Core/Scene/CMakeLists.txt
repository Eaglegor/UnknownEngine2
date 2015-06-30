include(UnknownEngineModuleUtils)

set_module_name(Scene)
set_module_type(SHARED_LIB)

add_public_include(IComponent.h)
add_public_include(ISceneObject.h)
add_public_include(SceneManager.h)

add_source_file(SceneManager.cpp)

generate_target()
setup_installation()
set_folder_name(Core)


enable_build_speedup()