cmake_minimum_required(VERSION 3.2)
project(SimpleComponentsProj)

include(ExternalProject)



# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SimpleComponentsProj_SOURCE_DIR}/Build)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# https://crascit.com/2015/07/25/cmake-gtest/
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)
 
# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include"
                      "${gmock_SOURCE_DIR}/include")
endif()



# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

set(GTEST_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
set(GTEST_LIBRARY gtest)

# add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)

set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARY_PATH} )
add_dependencies(${GTEST_LIBRARY} googletest)

set(SOURCE_FILES
        Headers/Actions/IAction.h
        Headers/Actions/SimpleButtonAction.h
        Headers/Demos/CameraTest/CameraTestApp.h
        Headers/Demos/CameraTest/CameraTestStage.h
        Headers/Components/Repository/ComponentCollection.h
        Headers/Components/Repository/ComponentCollectionRepository.h
        Headers/Components/Repository/CComponentCollection.h
        Headers/Components/AISimpleGoalComponent.h
        Headers/Components/BaseComponent.h
        Headers/Components/CollisionComponent.h
        Headers/Components/GraphicsComponent.h
        Headers/Components/IntersectionComponent.h
        Headers/Components/PhysicsComponent.h
        Headers/Components/SimpleButtonComponent.h
        Headers/Components/SimpleStateComponent.h
        Headers/Components/TransformComponent.h
        Headers/Components/Repository/VectorContainer.h
        Headers/Components/VelocityComponent.h
        Headers/Components/Component.h
        Headers/Events/ButtonEventArgs.h
        Headers/Events/CollisionEventArgs.h
        Headers/Events/EventObserveable.h
        Headers/Events/ExitBoundsEventArgs.h
        Headers/Events/IComponentProcess.h
        Headers/Events/IEventArgs.h
        Headers/Events/IntersectionEventArgs.h
        Headers/Events/ITaskEvent.h
        Headers/Events/MouseButtonEventArgs.h
        Headers/Events/MouseMotionEventArgs.h
        Headers/Events/QuitApplicationEventArgs.h
        Headers/Events/SDLEventCollector.h
        Headers/Events/TaskEvent.h
        Headers/Game/IGameApp.h
        Headers/Game/IStage.h
        Headers/Graphics/BubbleGraphicsResources.h
        Headers/Graphics/Camera.h
        Headers/Graphics/CircleFIllGraphicsResource.h
        Headers/Graphics/CircleOutlineGraphicsResource.h
        Headers/Graphics/Color.h
        Headers/Graphics/EnemyTriangleGraphicsResource.h
        Headers/Graphics/Graphics.h
        Headers/Graphics/GraphicsUtility.h
        Headers/Graphics/GridGraphicsResource.h
        Headers/Graphics/IGraphicsResource.h
        Headers/Graphics/ITransform.h
        Headers/Graphics/MouseCameraTransform.h
        Headers/Graphics/ProceduralAsteroidGraphicsResource.h
        Headers/Graphics/RectGraphicsResource.h
        Headers/Graphics/SpriteGraphicsResource.h
        Headers/Graphics/StarGraphicsResource.h
        Headers/Graphics/TextGraphicsResource.h
        Headers/Graphics/TriangleGraphicsResource.h
        Headers/Physics/CollisionPhysicsTask.h
        Headers/Physics/ExitBoundsTask.h
        Headers/Physics/IntersectionTask.h
        Headers/Physics/IPhysicsTask.h
        Headers/Physics/Physics.h
        Headers/Physics/VelocityTask.h
        Headers/Demos/SnakeGame/FoodAction.h
        Headers/Demos/SnakeGame/SnakeAction.h
        Headers/Demos/SnakeGame/SnakeEatFoodTask.h
        Headers/Demos/SnakeGame/SnakeEatSelfTask.h
        Headers/Demos/SnakeGame/SnakeGameApp.h
        Headers/Demos/SnakeGame/SnakeGameMenuStage.h
        Headers/Demos/SnakeGame/SnakeGameStage.h
        Headers/Demos/SpaceGame/AsteroidAction.h
        Headers/Demos/SpaceGame/BackgroundStarsAction.h
        Headers/Demos/SpaceGame/PlayerSpaceshipAction.h
        Headers/Demos/SpaceGame/SpaceGameAction.h
        Headers/Demos/SpaceGame/SpaceGameApp.h
        Headers/Demos/SpaceGame/SpaceGameEntityConstructor.h
        Headers/Demos/SpaceGame/SpaceGameMenuStage.h
        Headers/Demos/SpaceGame/SpaceGameStage.h
        Headers/Utility/DebugUtility.h
        Headers/Utility/LogUtility.h
        Headers/Utility/MathUtility.h
        Headers/Utility/Vector.h
        Source/Graphics/BubbleGraphicsResource.cpp
        Source/Graphics/RectGraphicsResource.cpp
        Source/SnakeGame/SnakeGameApp.cpp
        Source/SnakeGame/SnakeGameMenuStage.cpp
        Source/SnakeGame/SnakeGameStage.cpp
        Source/SpaceGame/PlayerSpaceshipAction.cpp
        Source/SpaceGame/SpaceGameMenuStage.cpp
        Source/Components/ComponentCollection.cpp
        Source/Graphics.cpp
        Source/main.cpp
        Source/Physics.cpp
        Source/SDLEventCollector.cpp
        Source/SnakeAction.cpp
        Source/SpaceGameApp.cpp
        Source/Graphics/Camera.cpp
        Headers/Utility/ProcessUtility.h)

set(TEST_SOURCE_FILES
        ${gtest_SOURCE_DIR}/src/gtest_main.cc
        Source/Graphics/BubbleGraphicsResource.cpp
        Source/Graphics/RectGraphicsResource.cpp
        Source/SnakeGame/SnakeGameApp.cpp
        Source/SnakeGame/SnakeGameMenuStage.cpp
        Source/SnakeGame/SnakeGameStage.cpp
        Source/SpaceGame/PlayerSpaceshipAction.cpp
        Source/SpaceGame/SpaceGameMenuStage.cpp
        Source/Components/ComponentCollection.cpp
        Source/Components/ComponentRepository.cpp
        Source/Components/ComponentContainerFactory.cpp
        Source/Graphics.cpp
        Source/Graphics/Camera.cpp
        Source/Physics.cpp
        Source/SDLEventCollector.cpp
        Source/SnakeAction.cpp
        Source/SpaceGameApp.cpp
        GoogleTestComponents/ComponentCollectionRepositoryTests.cpp
        GoogleTestComponents/ComponentContainerTests.cpp
        GoogleTestComponents/ComponentCollectionTests.cpp
        GoogleTestComponents/ComponentCollectionIteratorTests.cpp
        GoogleTestComponents/ComponentRepositoryTests.cpp
        GoogleTestComponents/EventTests.cpp
        GoogleTestComponents/GraphicsTests.cpp
        GoogleTestComponents/MathUtilTests.cpp
        GoogleTestComponents/PhysicsTest.cpp
        GoogleTestComponents/SDLEventTests.cpp
        GoogleTestComponents/VectorTests.cpp
        GoogleTestComponents/SerializationTests.cpp
        GoogleTestComponents/PerformanceTests.cpp)

include_directories(${GTEST_INCLUDE_DIR} ${SimpleComponentsProj_SOURCE_DIR}/Headers)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

add_executable(SimpleComponentsProj ${SOURCE_FILES})
add_executable(SimpleComponentsTest ${TEST_SOURCE_FILES})

target_link_libraries(SimpleComponentsProj ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(SimpleComponentsTest ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${GTEST_LIBRARY})

# Copy the resources to the build folder
set(RESOURCE_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Resources")

add_custom_target(build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RESOURCE_DIR})

add_custom_command(TARGET SimpleComponentsProj POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Resources ${RESOURCE_DIR})

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()