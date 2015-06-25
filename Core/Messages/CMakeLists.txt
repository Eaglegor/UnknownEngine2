include(UnknownEngineModuleUtils)

set_module_name(Messages)
set_module_type(INCLUDES_ONLY)

add_public_include(IMessage.h)
add_public_include(IMessageQueue.h)
add_public_include(IMessageTypeMetaInfo.h)
add_public_include(MessageTypeMetaInfo.h)

generate_target()
setup_installation()
set_folder_name(Core)