cmake_minimum_required(VERSION 3.0.0)
project(football_ai VERSION 0.1.0)

include(CTest)
enable_testing()

# Set icon for the application
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/icons/application.rc")

add_executable(
	football_ai 
	WIN32 #prevent of appearing console when running application
	win32_platform.cpp
	game_objects.hpp
	game_play.hpp
	physics.hpp
	platform_commands.hpp
	renderer.hpp
	typenames.hpp
	utilities.hpp
	${APP_ICON_RESOURCE_WINDOWS}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
