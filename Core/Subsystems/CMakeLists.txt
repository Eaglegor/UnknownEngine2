include(UnknownEngineModuleUtils)

set_module_name(Subsystems)
set_module_type(SHARED_LIB)

add_public_include(ISubsystem.h)
add_public_include(SubsystemsManager.h)

add_source_file(SubsystemsManager.cpp)

generate_target()
setup_installation()
set_folder_name(Core)

set_pch_include(stdafx.h)
enable_build_speedup()