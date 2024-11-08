set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Xml REQUIRED)

file(GLOB_RECURSE MOD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE MOD_HED ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE MOD_UI  ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

message(STATUS ${MOD_SRC})

if(WIN32)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${MOD_SRC})
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${MOD_HED})
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "UI Files" FILES ${MOD_UI})
	source_group("zero" REGULAR_EXPRESSION "\\.h$|\\.cpp$|\\.stamp$|\\.rule$")
endif()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set(TARGET_NAME XPFUiPlugind)
else ()
set(TARGET_NAME XPFUiPlugin)
endif()

include_directories(${XPFDIR_INC})

add_library(${TARGET_NAME} SHARED ${MOD_SRC} ${MOD_HED} ${MOD_UI}) 

target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Xml)

add_custom_command (
	TARGET ${TARGET_NAME} 
	POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${TARGET_NAME}>" "${PROBINDIR}/XPFPlugins/$<TARGET_FILE_NAME:${TARGET_NAME}>"
	COMMAND ECHO Deploy ${TARGET_NAME}
	COMMAND CALL "${WINDEPLOYQT} --libdir ${PROBINDIR} --dir ${PROBINDIR} \"${PROBINDIR}/XPFPlugins/$<TARGET_FILE_NAME:${TARGET_NAME}>\"" > nul 2>&1
)