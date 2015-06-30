include(UnknownEngineModuleUtils)

set_module_name(State)
set_module_type(SHARED_LIB)

add_public_include(Synchronizable.h)
add_public_include(StateManager.h)
add_public_include(SynchronizationState.h)

add_source_file(StateManager.cpp)

generate_target()
setup_installation()
set_folder_name(Core)

enable_build_speedup()