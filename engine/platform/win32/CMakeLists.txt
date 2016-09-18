project(platform_win32)

set (SOURCE_FILES "")
find_source_files(SOURCE_FILES)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
