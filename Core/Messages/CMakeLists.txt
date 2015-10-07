include(UnknownEngineModuleUtils)

set_module_name(Messages)
set_module_type(SHARED_LIB)

add_public_include(IMessage.h)
add_public_include(IMessageQueue.h)
add_public_include(IMessageType.h)
add_public_include(MessageType.h)

add_source_file(MessageDispatcher.cpp)

generate_target()
setup_installation()
set_folder_name(Core)