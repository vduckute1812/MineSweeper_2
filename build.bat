cls
@echo off

set var=%cd%
if not exist "%var%\_Build" mkdir %var%\_Build
cd %var%\_Build

if not exist "%var%\_Build\Game" mkdir %var%\_Build\Game
cd %var%\_Build\Game

g++ -std=c++11 -I%var% -c %var%/Game/Cycle.cpp
g++ -std=c++11 -I%var% -c %var%/Game/Rectangle.cpp
g++ -std=c++11 -I%var% -c %var%/Game/Object.cpp
g++ -std=c++11 -I%var% -c %var%/Game/Football_player.cpp
g++ -std=c++11 -I%var% -c %var%/Game/Ball.cpp
g++ -std=c++11 -I%var% -c %var%/Game/Player.cpp
g++ -std=c++11 -I%var% -c %var%/Game/MainState.cpp
g++ -std=c++11 -I%var% -c %var%/Game/Map.cpp
g++ -std=c++11 -I%var% -c %var%/Game/Main.cpp
g++ -std=c++11 -I%var% -c %var%/Game/DebugDraw.cpp

if not exist "%var%\_Build\Box2d" mkdir %var%\_Build\Box2d
cd %var%\_Build\Box2d

if not exist "%var%\_Build\Box2d\Collision" mkdir %var%\_Build\Box2d\Collision
cd %var%\_Build\Box2d\Collision

g++ -I%var% -c %var%/Box2D/Collision/b2BroadPhase.cpp
g++ -I%var% -c %var%/Box2D/Collision/b2CollideCircle.cpp
g++ -I%var% -c %var%/Box2D/Collision/b2CollideEdge.cpp
g++ -I%var% -c %var%/Box2D/Collision/b2CollidePolygon.cpp
g++ -I%var% -c %var%/Box2D/Collision/b2Collision.cpp
g++ -I%var% -c %var%/Box2D/Collision/b2Distance.cpp
g++ -I%var% -c %var%/Box2D/Collision/b2DynamicTree.cpp
g++ -I%var% -c %var%/Box2D/Collision/b2TimeOfImpact.cpp

if not exist "%var%\_Build\Box2d\Collision\Shapes" mkdir %var%\_Build\Box2d\Collision\Shapes
cd %var%\_Build\Box2d\Collision\Shapes

g++ -I%var% -c %var%/Box2D/Collision/Shapes/b2ChainShape.cpp
g++ -I%var% -c %var%/Box2D/Collision/Shapes/b2CircleShape.cpp
g++ -I%var% -c %var%/Box2D/Collision/Shapes/b2EdgeShape.cpp
g++ -I%var% -c %var%/Box2D/Collision/Shapes/b2PolygonShape.cpp

if not exist "%var%\_Build\Box2d\Common" mkdir %var%\_Build\Box2d\Common
cd %var%\_Build\Box2d\Common

g++ -I%var% -c %var%/Box2D/Common/b2BlockAllocator.cpp
g++ -I%var% -c %var%/Box2D/Common/b2Draw.cpp
g++ -I%var% -c %var%/Box2D/Common/b2Math.cpp
g++ -I%var% -c %var%/Box2D/Common/b2Settings.cpp
g++ -I%var% -c %var%/Box2D/Common/b2StackAllocator.cpp
g++ -I%var% -c %var%/Box2D/Common/b2Timer.cpp

if not exist "%var%\_Build\Box2d\Dynamics" mkdir %var%\_Build\Box2d\Dynamics
cd %var%\_Build\Box2d\Dynamics

g++ -I%var% -c %var%/Box2D/Dynamics/b2Body.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/b2ContactManager.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/b2Fixture.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/b2Island.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/b2World.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/b2WorldCallbacks.cpp

if not exist "%var%\_Build\Box2d\Dynamics\Contacts" mkdir %var%\_Build\Box2d\Dynamics\Contacts
cd %var%\_Build\Box2d\Dynamics\Contacts

g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2CircleContact.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2Contact.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Contacts/b2PolygonContact.cpp

if not exist "%var%\_Build\Box2d\Dynamics\Joints" mkdir %var%\_Build\Box2d\Dynamics\Joints
cd %var%\_Build\Box2d\Dynamics\Joints

g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2GearJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2Joint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2MotorJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2MouseJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2RopeJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2WeldJoint.cpp
g++ -I%var% -c %var%/Box2D/Dynamics/Joints/b2WheelJoint.cpp

if not exist "%var%\_Build\Box2d\Rope" mkdir %var%\_Build\Box2d\Rope
cd %var%\_Build\Box2d\Rope

g++ -I%var% -c %var%/Box2D/Rope/b2Rope.cpp

if not exist "%var%\_Build\glew" mkdir %var%\_Build\glew
cd %var%\_Build\glew

g++ -I%var% -c %var%/glew/glew.c

if not exist "%var%\_Build\glfw" mkdir %var%\_Build\glfw
cd %var%\_Build\glfw

rem g++ -I%var% -c %var%/glfw/context.c
rem g++ -I%var% -c %var%/glfw/egl_context.c
rem g++ -I%var% -c %var%/glfw/init.c
rem g++ -I%var% -c %var%/glfw/input.c
rem g++ -I%var% -c %var%/glfw/monitor.c
rem g++ -I%var% -c %var%/glfw/vulkan.c
rem g++ -I%var% -c %var%/glfw/wgl_context.c
rem g++ -I%var% -c %var%/glfw/win32_init.c
rem g++ -I%var% -c %var%/glfw/win32_joystick.c
rem g++ -I%var% -c %var%/glfw/win32_monitor.c
rem g++ -I%var% -c %var%/glfw/win32_time.c
rem g++ -I%var% -c %var%/glfw/win32_tls.c
rem g++ -I%var% -c %var%/glfw/win32_window.c
rem g++ -I%var% -c %var%/glfw/window.c

if not exist "%var%\_Build\imgui" mkdir %var%\_Build\imgui
cd %var%\_Build\imgui

g++ -I%var% -c %var%/imgui/imgui.cpp
g++ -I%var% -c %var%/imgui/imgui_demo.cpp
g++ -I%var% -c %var%/imgui/imgui_draw.cpp
g++ -I%var% -c %var%/imgui/imgui_impl_glfw_gl3.cpp


cd %var%\_Build

g++ -o game.exe ^
		%var%\_Build\Game\Cycle.o ^
		%var%\_Build\Game\Rectangle.o ^
		%var%\_Build\Game\Object.o ^
		%var%\_Build\Game\Football_player.o ^
		%var%\_Build\Game\Ball.o ^
		%var%\_Build\Game\Map.o ^
		%var%\_Build\Game\DebugDraw.o ^
		%var%\_Build\Game\MainState.o ^
		%var%\_Build\Game\Main.o

cd %var%