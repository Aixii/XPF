set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Xml REQUIRED)

file(GLOB_RECURSE PRO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE PRO_HED ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB PRO_CNF ${XPFSRCDIR}/config/*.xml)

message(STATUS ${PRO_CNF})

if(WIN32)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${PRO_SRC})
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Header Files" FILES ${PRO_HED})
	source_group(TREE ${XPFSRCDIR}/config PREFIX "Config Files" FILES ${PRO_CNF})
	source_group("zero" REGULAR_EXPRESSION "\\.h$|\\.cpp$|\\.stamp$|\\.rule$")
endif()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(TARGET_NAME XPF)

add_executable(${TARGET_NAME} ${PRO_SRC} ${PRO_HED} ${PRO_CNF})

target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(${TARGET_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Xml)

add_custom_command(
	TARGET ${TARGET_NAME} 
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${TARGET_NAME}>" "${XPFBINDIR}/$<TARGET_FILE_NAME:${TARGET_NAME}>"
	COMMENT "Copying $<TARGET_FILE:${TARGET_NAME}> to ${XPFBINDIR}/$<TARGET_FILE_NAME:${TARGET_NAME}>"
)
