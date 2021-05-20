#pragma once

namespace zikajak3 {

#include "./action/EntityHovering.h"
#include "./action/GLUTCaptureMouseSwitchAction.h"
#include "./action/IAction.h"
#include "./action/RotatingLight.h"
#include "./action/SelectableItems.h"
#include "./action/UserCameraAction.h"
#include "./action/UserKeyAction.h"
#include "./assets/Asset.h"
#include "./assets/AssetHandler.h"
#include "./assets/MaterialAsset.h"
#include "./assets/MeshAsset.h"
#include "./assets/ShaderAsset.h"
#include "./assets/TextureAsset.h"
#include "./engine/Engine.h"
#include "./engine/State.h"
#include "./gl/GLBuffer.h"
#include "./gl/LightsUBO.h"
#include "./gl/VecHash.h"
#include "./input/GLUTCallbackRegistry.h"
#include "./input/GLUTInputsHandler.h"
#include "./input/GLUTKeyMapping.h"
#include "./input/GLUTUserInput.h"
#include "./input/UserInput.h"
#include "./models/Pedestal.h"
#include "./models/UnitCube.h"
#include "./renderer/SceneRenderer.h"
#include "./renderer/SceneRenderingInstance.h"
#include "./scene/LightEntity.h"
#include "./scene/ModelEntity.h"
#include "./scene/Scene.h"
#include "./scene/SceneCamera.h"
#include "./scene/SceneEntity.h"
#include "./scene/SceneNode.h"
#include "./scene/SceneObject.h"
#include "./stb/stb_image.h"
#include "./utils/Singleton.h"
#include "./window/Window.h"
#include "./hello.h"
#include "./Types.h"
#include "./Util.h"

}