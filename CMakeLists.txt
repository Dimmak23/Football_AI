cmake_minimum_required(VERSION 3.0.0)
project(football_ai VERSION 0.1.0)

include(CTest)
enable_testing()

# Set icon for the application
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/icons/application.rc")

add_executable(
	football_ai
	win32_platform.cpp
	game_objects.h
	game_play.h
	physics.h
	platform_commands.h
	renderer.h
	typenames.h
	utilities.h
	${APP_ICON_RESOURCE_WINDOWS}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
