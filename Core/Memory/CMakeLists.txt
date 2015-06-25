include(UnknownEngineModuleUtils)

set_module_name(Memory)
set_module_type(SHARED_LIB)

add_public_include(IRawAllocator.h)
add_public_include(TypedAllocator.h)

add_source_file(SimpleMallocRawAllocator.cpp)

generate_target()
setup_installation()

setup_precompiled_header(stdafx.h stdafx.cpp)