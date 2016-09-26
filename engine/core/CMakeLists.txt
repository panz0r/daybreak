project(core)

set (SOURCE_FILES "")
find_source_files(SOURCE_FILES)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} platform_windows)
