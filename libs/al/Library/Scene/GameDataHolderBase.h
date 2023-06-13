#pragma once

#include <al/Library/Scene/ISceneObj.h>
#include <al/Library/HostIO/HioNode.h>
#include <al/Library/Message/IUseMessageSystem.h>

namespace al {
class GameDataHolderBase : public ISceneObj, HioNode, IUseMessageSystem {

};
}
