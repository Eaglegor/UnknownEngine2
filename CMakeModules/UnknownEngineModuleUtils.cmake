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

macro(setup_precompiled_header include_file source_file)
	include(PCHSupport)
	
	if(COMPILER_SUPPORTS_PCH)
		add_precompiled_header(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${include_file} ${CMAKE_CURRENT_SOURCE_DIR}/${source_file})
	endif(COMPILER_SUPPORTS_PCH)
endmacro()

macro(add_source_file filename)
	list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
endmacro()

macro(add_public_include filename)
	list(APPEND PUBLIC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
endmacro()

macro(add_private_include filename)
	list(APPEND PRIVATE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/${filename})
endmacro()
	
macro(set_pch_include pch_include)
	set(pch_include_file ${pch_include})
endmacro()
	
macro(enable_build_speedup)
	include(Cotire)
	
	if(pch_include_file)
		set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_UNIT ${CMAKE_CURRENT_SOURCE_DIR}/${pch_include_file})
	endif()

	set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_ENABLE_PRECOMPILED_HEADER TRUE)
	set_target_properties(${TARGET_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
	
	cotire(${TARGET_NAME})
endmacro()
	
macro(generate_target)
	if(NOT TARGET_NAME)
		message(FATAL_ERROR "Target name is not set. Please set it using set_module_name()")
	endif()
	
	if(NOT MODULE_TYPE)
		message(FATAL_ERROR "Target type is not set. Please set it using set_module_type()")
	endif()
	
	set(PREPARED_TARGET_SOURCES ${SOURCE_FILES} ${PUBLIC_INCLUDES} ${PRIVATE_INCLUDES})
	
	include_directories(${UNKNOWN_ENGINE_BINARY_DIR}/SharedLibrariesExportHeaders/)
	
	if(MODULE_TYPE STREQUAL SHARED_LIB)
		add_library(${TARGET_NAME} SHARED ${PREPARED_TARGET_SOURCES})
		
		include(GenerateExportHeader)
		GENERATE_EXPORT_HEADER(${TARGET_NAME} EXPORT_FILE_NAME ${UNKNOWN_ENGINE_BINARY_DIR}/SharedLibrariesExportHeaders/${TARGET_NAME}_export.h)
	elseif(MODULE_TYPE STREQUAL STATIC_LIB)
		add_library(${TARGET_NAME} STATIC ${PREPARED_TARGET_SOURCES})
		
		include(GenerateExportHeader)
		GENERATE_EXPORT_HEADER(${TARGET_NAME} EXPORT_FILE_NAME ${UNKNOWN_ENGINE_BINARY_DIR}/SharedLibrariesExportHeaders/${TARGET_NAME}_export.h)
	elseif(MODULE_TYPE STREQUAL PLUGIN)
		add_library(${TARGET_NAME} MODULE ${PREPARED_TARGET_SOURCES})
	elseif(MODULE_TYPE STREQUAL INCLUDES_ONLY)
		add_custom_target(${TARGET_NAME} SOURCES ${PREPARED_TARGET_SOURCES})
	elseif(MODULE_TYPE STREQUAL EXECUTABLE)
		add_executable(${TARGET_NAME} ${PREPARED_TARGET_SOURCES})
	else()
		message(FATAL_ERROR "Unknown module type")
	endif()
endmacro()

macro(get_stripped_directory full_filename destination_var)
	file(RELATIVE_PATH REL_DIR ${UNKNOWN_ENGINE_SOURCE_DIR} ${full_filename})
	get_filename_component(${destination_var} ${REL_DIR} DIRECTORY)
endmacro()

macro(setup_installation)
	
	if(NOT MODULE_TYPE)
		message(FATAL_ERROR "Target type is not set. Please set it using set_module_type()")
	endif()
	
	if(MODULE_TYPE STREQUAL SHARED_LIB)
		install(TARGETS ${TARGET_NAME} DESTINATION bin)
	elseif(MODULE_TYPE STREQUAL PLUGIN)
		install(TARGETS ${TARGET_NAME} DESTINATION bin/plugins)
	elseif(MODULE_TYPE STREQUAL STATIC_LIB)
		install(TARGETS ${TARGET_NAME} ARCHIVE DESTINATION lib)
	elseif(MODULE_TYPE STREQUAL EXECUTABLE)
		install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)
	endif()
	
	if(DEPLOY_INCLUDES)
		foreach(public_include ${PUBLIC_INCLUDES})
			get_stripped_directory(${public_include} stripped_include_dir)
			install(FILES ${public_include} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${stripped_include_dir})
		endforeach()
	endif()
endmacro()

macro(set_folder_name name)
	set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${name})
endmacro()

macro(set_project_label label)
	set_property(TARGET ${TARGET_NAME} PROPERTY PROJECT_LABEL Common)
endmacro()

if(MSVC)
	include(GenerateMSVCFilters)
	MSVC_generate_filters()
endif(MSVC)
