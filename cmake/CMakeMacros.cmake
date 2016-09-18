
macro(set_source_groups pList)
	foreach(FilePath ${pList})
		get_filename_component(DirName ${FilePath} DIRECTORY)
		if( NOT "${DirName}" STREQUAL "" )
			string(REGEX REPLACE "[.][.][/]" "" GroupName "${DirName}")
			if( MSVC )
				string(REGEX REPLACE "/" "\\\\" GroupName "${GroupName}")
			endif()
			source_group("${GroupName}" FILES ${FilePath})
		else()
			source_group("" FILES ${FilePath})
		endif()
	endforeach()
endmacro()


macro(find_source_files pResult)
	set(FileList)
	# Retrive all source files recursively
	set(FileExtensions)
	list(APPEND FileExtensions "*.h" "*.c" "*.cpp" "*.inl")

	file(GLOB_RECURSE FileList RELATIVE ${PROJECT_SOURCE_DIR} ${FileExtensions})
	list(APPEND ${pResult} ${FileList})

	set_source_groups("${FileList}")
endmacro()

