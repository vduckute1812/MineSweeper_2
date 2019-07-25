set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard
set (SOURCE_DIR ./)
include_directories( ${PROJECT_SOURCE_DIR} )
add_executable(game Cycle.cpp Rectangle.cpp Object.cpp Football_player.cpp Ball.cpp Player.cpp MainState.cpp Map.cpp DebugDraw.cpp Main.cpp)