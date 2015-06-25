include(UnknownEngineModuleUtils)

set_module_name(Profiling)
set_module_type(SHARED_LIB)

add_public_include(IProfilerInstance.h)
add_public_include(ProfileMacros.h)
add_public_include(ProfileManager.h)
add_public_include(FunctionSignatureMacros.h)
add_public_include(RAIIFunctionProfiler.h)

add_source_file(ProfileManager.cpp)
add_source_file(RAIIFunctionProfiler.cpp)

generate_target()
setup_installation()
set_folder_name(Core)

set_pch_include(stdafx.h)
enable_build_speedup()