include(UnknownEngineModuleUtils)

set_module_name(Subsystems)
set_module_type(INCLUDES_ONLY)

add_public_include(ISubsystem.h)

generate_target()
setup_installation()
set_folder_name(Core)