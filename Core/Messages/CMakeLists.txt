include(UnknownEngineModuleUtils)

set_module_name(Messages)
set_module_type(SHARED_LIB)

add_public_include(IMessage.h)
add_public_include(IMessageQueue.h)
add_public_include(IMessageTypeMetaInfo.h)
add_public_include(MessageTypeInfo.h)

#generate_target()
#setup_installation()
