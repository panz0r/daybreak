
project(main_x64)

set (SOURCE_FILES "")
find_source_files(SOURCE_FILES)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} core)
