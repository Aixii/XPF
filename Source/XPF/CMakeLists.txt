set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(XPFDIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${XPFDIR})

set(XPFDIR_INC ${XPFDIR}/Include)

include_directories(${XPFDIR_INC})

add_subdirectory(XPFCore)
add_subdirectory(XPFDbServicePlugin)
add_subdirectory(XPFTrayMenuPlugin)
add_subdirectory(XPFUi)
