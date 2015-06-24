macro(set_module_name name)
	set(TARGET_NAME ${name})
endmacro()

macro(set_module_type type)
	set(MODULE_TYPE ${type})
endmacro()

macro(add_module_link_library module_name)
	target_link_libraries(${TARGET_NAME} ${module_name})
endmacro()

macro(add_module_dependency module_name)
	add_dependencies(${TARGET_NAME} ${module_name})
endmacro()

macro(add_precompiled_header include_file source_file)
	include(${UNKNOWN_ENGINE_SOURCE_DIR}/CMakeModules/PCHSupport)

	if(COMPILER_SUPPORTS_PCH)
		add_precompiled_header(${TARGET_NAME} ${include_file} ${source_file})
	endif(COMPILER_SUPPORTS_PCH)
endmacro()

macro(add_source_file filename)
	list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
endmacro()

macro(add_public_include filename)
	list(APPEND PUBLIC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
endmacro()
	
macro(generate_target)
	if(NOT TARGET_NAME)
		message(FATAL_ERROR "Target name is not set. Please set it using set_module_name()")
	endif()
	
	if(NOT MODULE_TYPE)
		message(FATAL_ERROR "Target type is not set. Please set it using set_module_type()")
	endif()
	
	if(MODULE_TYPE STREQUAL SHARED_LIB)
		add_library(${TARGET_NAME} SHARED ${SOURCE_FILES})
		
		include(GenerateExportHeader)
		GENERATE_EXPORT_HEADER(${TARGET_NAME} EXPORT_FILE_NAME ${UNKNOWN_ENGINE_BINARY_DIR}/SharedLibrariesExportHeaders/${TARGET_NAME}_export.h)
		include_directories(${UNKNOWN_ENGINE_BINARY_DIR}/SharedLibrariesExportHeaders/)
	elseif(MODULE_TYPE STREQUAL STATIC_LIB)
		add_library(${TARGET_NAME} STATIC ${SOURCE_FILES})
		
		include(GenerateExportHeader)
		GENERATE_EXPORT_HEADER(${TARGET_NAME} EXPORT_FILE_NAME ${UNKNOWN_ENGINE_BINARY_DIR}/SharedLibrariesExportHeaders/${TARGET_NAME}_export.h)
		include_directories(${UNKNOWN_ENGINE_BINARY_DIR}/SharedLibrariesExportHeaders/)
	elseif(MODULE_TYPE STREQUAL INCLUDES_ONLY)
		message(STATUS ${TARGET_NAME})
		add_custom_target(${TARGET_NAME})
	else()
		message(FATAL_ERROR "Unknown module type")
	endif()
endmacro()

macro(get_stripped_directory full_filename destination_var)
	string(REPLACE ${UNKNOWN_ENGINE_SOURCE_DIR}/ "" STRIPPED_FIRST ${CMAKE_CURRENT_SOURCE_DIR})
	string(REGEX REPLACE "(.*)/.*\.h" "\\1" ${destination_var} ${STRIPPED_FIRST})
endmacro()

macro(setup_installation)
	
	if(NOT MODULE_TYPE)
		message(FATAL_ERROR "Target type is not set. Please set it using set_module_type()")
	endif()
	
	if(MODULE_TYPE STREQUAL SHARED_LIB)
		install(TARGETS ${TARGET_NAME} DESTINATION bin)
	elseif(MODULE_TYPE STREQUAL STATIC_LIB)
		install(TARGETS ${TARGET_NAME} ARCHIVE DESTINATION lib)
	endif()
	
	if(DEPLOY_INCLUDES)
		foreach(public_include ${PUBLIC_INCLUDES})
			get_stripped_directory(${public_include} stripped_include_dir)
			message(STATUS include/${stripped_include_dir})
			install(FILES ${public_include} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${stripped_include_dir})
		endforeach()
	endif()
endmacro()

if(MSVC)
	include(GenerateMSVCFilters)
	MSVC_generate_filters()
endif(MSVC)
