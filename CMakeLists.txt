cmake_minimum_required(VERSION 3.3)
cmake_minimum_required(VERSION 3.1)
project(SDLRTS)
include_directories("/Library/Frameworks/SDL2.framework/Headers/")
include_directories("/Library/Frameworks/SDL2_image.framework/Headers/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Headers/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/TestClasses")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -F/Library/Frameworks/ -framework SDL2 -framework SDL2_image")
set(SOURCE_FILES
        Source/main.cpp
        Source/GameApp.cpp
        Source/Graphics.cpp
        TestClasses/TestGraphics.cpp
        TestClasses/TestGraphics.h
        TestClasses/TestGraphics.cpp
        TestClasses/TestGraphics.h
        Headers/GraphicsResources/IGraphicsResource.h
        Source/Resources.cpp Headers/Resources.h
        Headers/GraphicsResources/TriangleGraphicsResource.h
        Headers/GraphicsResources/RectGraphicsResource.h
        Headers/GraphicsResources/CircleFillGraphicsResource.h
        Headers/GraphicsResources/SpriteGraphicsResource.h
        Headers/ComponentType.h
        Headers/Transforms/PlayerMoveTransform.h
        Headers/ComponentSpec.h
        Source/ComponentSpec.cpp
        Headers/Utility.h
        Headers/GraphicsResources/CircleOutlineGraphicsResource.h
        Headers/Transforms/CollisionTransform.h
        Headers/Events/EventMap.h
        Headers/Events/EventType.h
        Headers/Events/EventInfo.h
        Headers/Events/Event.h
        Headers/Events/IEventHandler.h
        Headers/Events/SimpleButtonClickEventHandler.h
        Headers/Components/ClickableComponent.h
        TestClasses/TestEvents.h)

add_executable(SDLRTS ${SOURCE_FILES}

        TestClasses/TestGraphics.cpp
        TestClasses/TestGraphics.h
        Headers/GraphicsResources/IGraphicsResource.h
        Source/Resources.cpp
        Headers/Resources.h
        Headers/GraphicsResources/TriangleGraphicsResource.h
        Headers/GraphicsResources/RectGraphicsResource.h
        Headers/GraphicsResources/CircleFillGraphicsResource.h
        Headers/GraphicsResources/SpriteGraphicsResource.h
        Headers/ComponentType.h
        Headers/Transforms/PlayerMoveTransform.h
        Headers/ComponentSpec.h
        Headers/Utility.h
        Headers/GraphicsResources/CircleOutlineGraphicsResource.h
        Headers/Transforms/CollisionTransform.h
        Headers/Events/EventMap.h
        Headers/Events/EventType.h
        Headers/Events/EventInfo.h
        Headers/Events/Event.h
        Headers/Events/IEventHandler.h
        Headers/Events/SimpleButtonClickEventHandler.h
        Headers/Components/ClickableComponent.h
        TestClasses/TestEvents.h)
