set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Xml Sql REQUIRED)

file(GLOB_RECURSE PRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE PRO_HED ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#file(GLOB_RECURSE PRO_UI  ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

if(WIN32)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${PRO_SRC})
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${PRO_HED})
#	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "UI Files" FILES ${PRO_UI})
	source_group("zero" REGULAR_EXPRESSION "\\.h$|\\.cpp$|\\.stamp$|\\.rule$")
endif()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_definitions(-DXPFDB_EXPORTS)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set(TARGET_NAME XPFDbServicePlugind)
else ()
set(TARGET_NAME XPFDbServicePlugin)
endif()

add_library(${TARGET_NAME} SHARED ${PRO_SRC} ${PRO_HED} ${PRO_UI}) 

target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Xml)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

add_custom_command (
	TARGET ${TARGET_NAME} 
	POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${TARGET_NAME}>" "${PROBINDIR}/XPFPlugins/$<TARGET_FILE_NAME:${TARGET_NAME}>"
	COMMAND ECHO Deploy ${TARGET_NAME}
	COMMAND CALL "${WINDEPLOYQT} --libdir ${PROBINDIR} --dir ${PROBINDIR} \"${PROBINDIR}/XPFPlugins/$<TARGET_FILE_NAME:${TARGET_NAME}>\"" > nul 2>&1
)