cmake_minimum_required(VERSION 3.5) 

project(XPF) 

set(CMAKE_BUILD_TYPE "Debug")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(XPFDIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

set(XPFBINDIR ${XPFDIR}/Bin)
set(XPFSRCDIR ${XPFDIR}/Source)
set(XPFINCDIR ${XPFSRCDIR}/include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${XPFINCDIR})

add_subdirectory(XPFLauncher)
add_subdirectory(XPFCore)
add_subdirectory(XPFUi)
add_subdirectory(XPFTrayMenu)
add_subdirectory(XPFLoginPlugin)

set(CONF_SRC_DIR "${XPFSRCDIR}/config")
set(CONF_DEST_DIR "${XPFBINDIR}/XPFConfig")

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
")
