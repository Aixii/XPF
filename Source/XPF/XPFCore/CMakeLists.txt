set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Xml REQUIRED)

file(GLOB_RECURSE MOD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE MOD_HED ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

if(WIN32)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${MOD_SRC})
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${MOD_HED})
	source_group("zero" REGULAR_EXPRESSION "\\.h$|\\.cpp$|\\.stamp$|\\.rule$")
endif()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(TARGET_NAME XPF)

add_executable(${TARGET_NAME} WIN32 ${MOD_SRC} ${MOD_HED})

target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Xml)

add_custom_command(
	TARGET ${TARGET_NAME} 
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${TARGET_NAME}>" "${PROBINDIR}/$<TARGET_FILE_NAME:${TARGET_NAME}>"
	COMMENT "Copying $<TARGET_FILE:${TARGET_NAME}> to ${PROBINDIR}/$<TARGET_FILE_NAME:${TARGET_NAME}>"
	COMMAND ECHO Deploy ${TARGET_NAME}
	COMMAND CALL "${WINDEPLOYQT} --libdir ${PROBINDIR} --dir ${PROBINDIR} \"${PROBINDIR}/$<TARGET_FILE_NAME:${TARGET_NAME}>\"" > nul 2>&1
)
