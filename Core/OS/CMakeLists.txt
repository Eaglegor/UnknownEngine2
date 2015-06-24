set(PUBLIC_INCLUDES
	DLLUtils.h
)
	
if(WIN32)
	set(COMPILATION_SCOPE
		DLLUtils.windows.cpp
	)
elseif(UNIX)
	set(COMPILATION_SCOPE
		DLLUtils.unix.cpp
	)
endif()