# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(Vapor)


include_directories($ENV{PGR_FRAMEWORK_ROOT}include)
link_directories($ENV{PGR_FRAMEWORK_ROOT}lib)
# target_link_libraries(pgrd.lib)
# include_directories(include/)
# include_directories(include/assets/)
# include_directories(include/utils/)

set(SOURCE_FILES_
    # "src/assets/AssetHandler.cpp"
    "src/assets/Asset.cpp"
    "src/assets/MeshAsset.cpp"
    # "src/gl/Buffer.cpp"
    "src/hello.cpp"
    "src/assets/MaterialAsset.cpp"
    "src/assets/TextureAsset.cpp"
    "src/assets/ShaderAsset.cpp"
    "src/Util.cpp"
    "src/Types.cpp"
    "src/renderer/SceneRenderingInstance.cpp"
    
    "src/scene/ModelEntity.cpp"
    "src/scene/SceneEntity.cpp"
    "src/scene/SceneObject.cpp"
    "src/scene/SceneNode.cpp"
    "src/scene/SceneCamera.cpp"
    "src/scene/Scene.cpp"

    "src/input/UserInput.cpp"
    "src/input/GLUTUserInput.cpp"
    "src/input/GLUTCallbackRegistry.cpp"
    "src/input/GLUTKeyMapping.cpp"

    "src/renderer/SceneRenderer.cpp"

    "src/engine/Engine.cpp"

    "src/window/Window.cpp"
    "src/window/GLUTWindow.cpp"

    "src/action/UserCameraAction.cpp"
    "src/action/GLUTCaptureMouseSwitchAction.cpp"
    "src/action/EntityHovering.cpp"
)

set(HEADER_FILES
    "include/assets/AssetHandler.h"
    "include/assets/Asset.h"
    "include/assets/MeshAsset.h"
    "include/assets/MaterialAsset.h"
    "include/assets/TextureAsset.h"
    "include/assets/ShaderAsset.h"

    "include/gl/GLBuffer.h"
    "include/utils/Singleton.h"
    "include/hello.h"
    "include/nlohmann/json.hpp"
    "include/stb/stb_image.h"
    "include/Types.h"
    "include/gl/VecHash.h"
    "include/Util.h"

    "include/scene/SceneObject.h"
    "include/scene/SceneNode.h"
    "include/scene/SceneEntity.h"
    "include/scene/Scene.h"
    "include/scene/SceneCamera.h"
    "include/scene/ModelEntity.h"

    "include/input/UserInput.h"
    "include/input/GLUTUserInput.h"
    "include/input/GLUTInputsHandler.h"
    "include/input/GLUTCallbackRegistry.h"
    "include/input/GLUTKeyMapping.h"


    "include/renderer/SceneRenderer.h"
    "include/renderer/SceneRenderingInstance.h"

    "include/engine/Engine.h"

    "include/window/Window.h"
    "include/window/GLUTWindow.h"

    "include/action/IAction.h"
    "include/action/UserCameraAction.h"
    "include/action/EntityHovering.h"
    "include/action/GLUTCaptureMouseSwitchAction.h"
    )

# file(GLOB SOURCE "src/*.cpp" "include/*.h")
add_library(Vapor STATIC ${HEADER_FILES} ${SOURCE_FILES_})

# add_executable("src/main.cpp" $(SOURCE))

# target_link_libraries(Vapor)

# target_include_directories(Vapor PUBLIC ${PGR_FRAMEWORK_ROOTCMAKE_SOURCE_DIR}inc)

# target_include_directories(${PROJECT_NAME}
#     PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(Vapor PUBLIC cxx_std_20)