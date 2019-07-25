#!/bin/bash
#Run this in terminal
#+ Command to compile c++ program. here i used common one

var=$(pwd)
CFLAG="-std=c++11 -I$var"

mkdir $var/_Build
cd $var/_Build

mkdir $var/_Build/Game
cd $var/_Build/Game

g++ $CFLAG -c $var/Game/Cycle.cpp
g++ $CFLAG -c $var/Game/Rectangle.cpp
g++ $CFLAG -c $var/Game/Object.cpp
g++ $CFLAG -c $var/Game/Football_player.cpp
g++ $CFLAG -c $var/Game/Ball.cpp
g++ $CFLAG -c $var/Game/Player.cpp
g++ $CFLAG -c $var/Game/MainState.cpp
g++ $CFLAG -c $var/Game/Map.cpp
g++ $CFLAG -c $var/Game/DebugDraw.cpp
g++ $CFLAG -c $var/Game/Main.cpp


mkdir $var/_Build/Box2d
cd $var/_Build/Box2d

mkdir $var/_Build/Box2d/Collision
cd $var/_Build/Box2d/Collision

g++ -std=c++11 -I$var -c $var/Box2D/Collision/b2BroadPhase.cpp
g++ $CFLAG -c $var/Box2D/Collision/b2CollideCircle.cpp
g++ $CFLAG -c $var/Box2D/Collision/b2CollideEdge.cpp
g++ $CFLAG -c $var/Box2D/Collision/b2CollidePolygon.cpp
g++ $CFLAG -c $var/Box2D/Collision/b2Collision.cpp
g++ $CFLAG -c $var/Box2D/Collision/b2Distance.cpp
g++ $CFLAG -c $var/Box2D/Collision/b2DynamicTree.cpp
g++ $CFLAG -c $var/Box2D/Collision/b2TimeOfImpact.cpp

mkdir $var/_Build/Box2d/Collision/Shapes
cd $var/_Build/Box2d/Collision/Shapes

g++ $CFLAG -c $var/Box2D/Collision/Shapes/b2ChainShape.cpp
g++ $CFLAG -c $var/Box2D/Collision/Shapes/b2CircleShape.cpp
g++ $CFLAG -c $var/Box2D/Collision/Shapes/b2EdgeShape.cpp
g++ $CFLAG -c $var/Box2D/Collision/Shapes/b2PolygonShape.cpp

mkdir $var/_Build/Box2d/Common
cd $var/_Build/Box2d/Common

g++ $CFLAG -c $var/Box2D/Common/b2BlockAllocator.cpp
g++ $CFLAG -c $var/Box2D/Common/b2Draw.cpp
g++ $CFLAG -c $var/Box2D/Common/b2Math.cpp
g++ $CFLAG -c $var/Box2D/Common/b2Settings.cpp
g++ $CFLAG -c $var/Box2D/Common/b2StackAllocator.cpp
g++ $CFLAG -c $var/Box2D/Common/b2Timer.cpp

mkdir $var/_Build/Box2d/Dynamics
cd $var/_Build/Box2d/Dynamics

g++ $CFLAG -c $var/Box2D/Dynamics/b2Body.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/b2ContactManager.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/b2Fixture.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/b2Island.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/b2World.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/b2WorldCallbacks.cpp

mkdir $var/_Build/Box2d/Dynamics/Contacts
cd $var/_Build/Box2d/Dynamics/Contacts

g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2CircleContact.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2Contact.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Contacts/b2PolygonContact.cpp

mkdir $var/_Build/Box2d/Dynamics/Joints
cd $var/_Build/Box2d/Dynamics/Joints

g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2GearJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2Joint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2MotorJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2MouseJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2RopeJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2WeldJoint.cpp
g++ $CFLAG -c $var/Box2D/Dynamics/Joints/b2WheelJoint.cpp

mkdir $var/_Build/Box2d/Rope
cd $var/_Build/Box2d/Rope

g++ -std=c++11 -I$var -c $var/Box2D/Rope/b2Rope.cpp

mkdir $var/_Build/glew
cd $var/_Build/glew

g++ -I$var -c $var/glew/glew.c

mkdir $var/_Build/glfw
cd $var/_Build/glfw

#g++ -I$var -c $var/glfw/context.c
#g++ -I$var -c $var/glfw/egl_context.c
#g++ -I$var -c $var/glfw/init.c
#g++ -I$var -c $var/glfw/input.c
#g++ -I$var -c $var/glfw/monitor.c
#g++ -I$var -c $var/glfw/vulkan.c
#g++ -I$var -c $var/glfw/wgl_context.c
#g++ -I$var -c $var/glfw/win32_init.c
#g++ -I$var -c $var/glfw/win32_joystick.c
#g++ -I$var -c $var/glfw/win32_monitor.c
#g++ -I$var -c $var/glfw/win32_time.c
#g++ -I$var -c $var/glfw/win32_tls.c
#g++ -I$var -c $var/glfw/win32_window.c
#g++ -I$var -c $var/glfw/window.c

mkdir $var/_Build/imgui
cd $var/_Build/imgui

g++ $CFLAG -c $var/imgui/imgui.cpp
g++ $CFLAG -c $var/imgui/imgui_demo.cpp
g++ $CFLAG -c $var/imgui/imgui_draw.cpp
g++ $CFLAG -c $var/imgui/imgui_impl_glfw_gl3.cpp


cd $var/_Build

g++ -o game $var/_Build/Game/Cycle.o $var/_Build/Game/Rectangle.o $var/_Build/Game/Object.o $var/_Build/Game/Football_player.o $var/_Build/Game/Ball.o $var/_Build/Game/Map.o $var/_Build/Game/DebugDraw.o $var/_Build/Game/MainState.o $var/_Build/Game/Main.o

cd $var
