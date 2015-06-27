include(UnknownEngineModuleUtils)

set_module_name(Memory)
set_module_type(SHARED_LIB)

add_public_include(IRawAllocator.h)
add_public_include(TypedAllocator.h)
add_public_include(MemoryManager.h)
add_public_include(AlignedRawAllocator.h)
add_public_include(New.h)

add_private_include(SimpleMallocRawAllocator.h)

add_source_file(SimpleMallocRawAllocator.cpp)
add_source_file(MemoryManager.cpp)
add_source_file(New.cpp)

generate_target()
setup_installation()
set_folder_name(Core)

set_pch_include(stdafx.h)
enable_build_speedup()