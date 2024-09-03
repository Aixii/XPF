add_executable(XPFLauncher main.cpp)

add_custom_command(TARGET XPFLauncher POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy 
	"$<TARGET_FILE:XPFLauncher>" 
	"${XPFBINDIR}/$<TARGET_FILE_NAME:XPFLauncher>")