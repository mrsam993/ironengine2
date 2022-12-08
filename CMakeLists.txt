cmake_minimum_required(VERSION 3.0)
project(IRONENGINE)

if(WIN32)
  include_directories(
    src
    contrib/windows-cl-amd64/include
  )

  link_directories(
    ${PROJECT_SOURCE_DIR}/contrib/windows-cl-amd64/lib
  )
  set(LIBOPENAL openal32)
  set(LIBOPENGL opengl32)
  set(LIBGLEW glew32)
  set(LIBSDL2 SDL2 SDL2main)
  set(LIBWINSOCK ws2_32)
else()
  include_directories(
    src
    contrib/emcc-emscripten-wasm/include
  )

  link_directories(
    contrib/emcc-emscripten-wasm/lib
  )
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file ${CMAKE_SOURCE_DIR}/resources@resources")
  set(LIBOPENAL openal)
  set(LIBOPENGL GL)
  set(LIBGLEW GLEW)
  set(LIBSDL2 SDL2)
  set(LIBWINSOCK socket)
endif()

add_library(rend
    src/rend/rend.h
    src/rend/Animation.h
    src/rend/Animation.cpp
    src/rend/Buffer.h
    src/rend/Buffer.cpp
    src/rend/Mesh.h
    src/rend/mesh.cpp
    src/rend/Model.h
    src/rend/Model.cpp
    src/rend/ModelRenderer.h
    src/rend/ModelRenderer.cpp
    src/rend/Renderer.h
    src/rend/Renderer.cpp
    src/rend/RenderTexture.h
    src/rend/RenderTexture.cpp
    src/rend/rendmath.h
    src/rend/rendmath.cpp
    src/rend/Shader.h
    src/rend/Shader.cpp
    src/rend/stb_image.h
    src/rend/Texture.h
    src/rend/Texture.cpp
    src/rend/sys/Atomic.h
    src/rend/sys/config.h
    src/rend/sys/Exception.h
    src/rend/sys/File.h
    src/rend/sys/List.h
    src/rend/sys/Lock.h
    src/rend/sys/Mutex.h
    src/rend/sys/panic.h
    src/rend/sys/Pipe.h
    src/rend/sys/Private.h
    src/rend/sys/Ptr.h
    src/rend/sys/String.h
    src/rend/sys/ThreadPool.h
    src/rend/sys/Unique.h
    src/rend/sys/Vector.h
    src/rend/sys/Weak.h
    src/rend/sys/Zero.h
)

target_link_libraries(rend ${LIBGLEW} ${LIBOPENGL})

add_library(ironengine
    src/ironengine/ironengine.h

    src/ironengine/Core.h
    src/ironengine/Core.cpp

    src/ironengine/Entity.h
    src/ironengine/Entity.cpp

    src/ironengine/Component.h
    src/ironengine/Component.cpp

    src/ironengine/TriangleRenderer.h
    src/ironengine/TriangleRenderer.cpp

    src/ironengine/Transform.h
    src/ironengine/Transform.cpp

    src/ironengine/SoundSource.h
    src/ironengine/SoundSource.cpp

    src/ironengine/Keyboard.h
    src/ironengine/Keyboard.cpp

    src/ironengine/Camera.h
    src/ironengine/Camera.cpp

    src/ironengine/BoxCollider.h
    src/ironengine/BoxCollider.cpp

    src/ironengine/RigidBody.h
    src/ironengine/RigidBody.cpp

    src/ironengine/IrcComponent.h
    src/ironengine/IrcComponent.cpp
)

target_link_libraries(ironengine rend ${LIBSDL2} ${LIBOPENAL} ${LIBWINSOCK})

add_executable(game
    src/game/main.cpp
)
target_link_libraries(game ironengine)