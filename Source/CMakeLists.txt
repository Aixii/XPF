cmake_minimum_required(VERSION 3.15) 

project(XPF) 

set(CMAKE_BUILD_TYPE "Debug")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#file(REAL_PATH  ".." XPFDIR)
get_filename_component(XPFDIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set(XPFBINDIR ${XPFDIR}/Bin)
set(XPFSRCDIR ${XPFDIR}/Source)
set(XPFINCDIR ${XPFSRCDIR}/include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${XPFINCDIR})

file(GLOB_RECURSE CONFIG_FILES "config/*")

#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/config" PREFIX "Files" FILES ${CONFIG_FILES})

add_subdirectory(XPFLauncher)
add_subdirectory(XPFCore)
add_subdirectory(XPFUi)
add_subdirectory(XPFTrayMenu)

file(INSTALL DESTINATION "${XPFBINDIR}/XPFConfig" TYPE FILE FILES ${CONFIG_FILES})