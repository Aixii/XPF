cmake_minimum_required(VERSION 3.5) 

project(IR_Analysis) 

set(CMAKE_BUILD_TYPE "Release")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(PRODIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set(PROBINDIR ${PRODIR}/Bin/Debug)
else()
set(PROBINDIR ${PRODIR}/Bin/Release)
endif()

if(MSVC)
set(PROBINDIR ${PROBINDIR}/MSVC)
elseif(MINGW)
set(PROBINDIR ${PROBINDIR}/MINGW)
endif()

set(PROSRCDIR ${PRODIR}/Source)
set(PROINCDIR ${PROSRCDIR}/Include)
set(PROLIBDIR ${PRODIR}/Lib)

set(XPFDIR_INC ${PROSRCDIR}/XPF/Include)
set(XPFDIR_BIN ${PROBINDIR})

set(WINDEPLOYQT C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/bin/windeployqt.exe)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROINCDIR})
#include_directories(${PROINCDIR}/Define)
#include_directories(${PROINCDIR}/Service)

#add_subdirectory(PROLauncher)
#add_subdirectory(PROCore)
#add_subdirectory(PROUi)
#add_subdirectory(PROTrayMenuPlugin)
#add_subdirectory(PROConfigs)
add_subdirectory(QXlsx)
add_subdirectory(XPF)
add_subdirectory(Plugins)

set(CONF_SRC_DIR "${PROSRCDIR}/Config")
set(CONF_DEST_DIR "${PROBINDIR}/XPFConfig")

set(RESOURCE_SRC_DIR ${PROSRCDIR}/Resource)
set(RESOURCE_DEST_DIR ${PROBINDIR}/XPFResource)

set(STYLE_SRC_DIR ${PROSRCDIR}/Style)
set(STYLE_DEST_DIR ${PROBINDIR}/XPFStyle)

add_custom_target(COPYFILE ALL
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_BINARY_DIR}/copy_files.cmake"
    COMMENT "Copying files from ${CONF_SRC_DIR} to ${CONF_DEST_DIR}"
)
file(WRITE "${CMAKE_BINARY_DIR}/copy_files.cmake" "
    cmake_minimum_required(VERSION 3.5)
    function(copy_files src dest)
        file(GLOB_RECURSE ALL_FILES \"\${src}/*\")
        foreach(FILE \${ALL_FILES})
            file(RELATIVE_PATH REL_PATH \"\${src}\" \"\${FILE}\")
            set(DEST_PATH \${dest}/\${REL_PATH})
            get_filename_component(DEST_DIR_PATH \"\${DEST_PATH}\" DIRECTORY)
            file(MAKE_DIRECTORY \"\${DEST_DIR_PATH}\")
            file(COPY \"\${FILE}\" DESTINATION \"\${DEST_DIR_PATH}\")
            message(\"copied \${FILE} to \${DEST_PATH}.\")
        endforeach()
    endfunction()

    set(SRC_DIR \"${CONF_SRC_DIR}\")
    set(DEST_DIR \"${CONF_DEST_DIR}\")
    copy_files(\"\${SRC_DIR}\" \"\${DEST_DIR}\")

	set(SRC_DIR \"${RESOURCE_SRC_DIR}\")
	set(DEST_DIR \"${RESOURCE_DEST_DIR}\")
	copy_files(\"\${SRC_DIR}\" \"\${DEST_DIR}\")

	set(SRC_DIR \"${STYLE_SRC_DIR}\")
	set(DEST_DIR \"${STYLE_DEST_DIR}\")
	copy_files(\"\${SRC_DIR}\" \"\${DEST_DIR}\")
")
