cmake_minimum_required(VERSION 3.17)
project(Digger2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)


set(SOURCE_FILES main.cpp)
add_executable(Digger main.cpp headers/Game.h src/game.cpp headers/TextureManager.h
        src/textureManager.cpp headers/Map.h src/map.cpp
        headers/Vector2D.h src/vector2D.cpp
        headers/ECS.h headers/SpriteComponent.h headers/TransformComponent.h
        headers/Components.h headers/Keyboard.h headers/CollisionComponent.h
        headers/Collision.h src/collision.cpp src/keyboard.cpp src/spriteComponent.cpp
        headers/TileComponent.h src/ECS.cpp
        headers/ChaseComponent.h src/chaseComponent.cpp headers/ENUMparameters.h
        src/collisionComponent.cpp src/transformComponent.cpp headers/DestroyBag.h src/destroyBag.cpp src/tileComponent.cpp headers/ProjectileComponent.h src/projectileComponent.cpp)
target_link_libraries(Digger -lmingw32 -lSDL2main -lSDL2 -lSDL2_image)

