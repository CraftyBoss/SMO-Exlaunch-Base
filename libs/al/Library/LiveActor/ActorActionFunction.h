#pragma once

#include <basis/seadTypes.h>

namespace al {
class LiveActor;
class Nerve;

void startAction(al::LiveActor* actor, const char* actionName);
void startActionAtRandomFrame(al::LiveActor* actor, const char* actionName);
bool tryStartAction(al::LiveActor* actor, const char* actionName);
bool tryStartActionIfNotPlaying(al::LiveActor* actor, const char* actionName);
bool tryStartActionIfActionEnd(al::LiveActor* actor, const char* actionName);

bool isActionPlaying(const al::LiveActor* actor, const char* actionName);
bool isActionEnd(const al::LiveActor* actor);
bool isExistAction(const al::LiveActor* actor);
bool isExistAction(const al::LiveActor* actor, const char* actionName);
bool isActionOneTime(const al::LiveActor* actor);
bool isActionOneTime(const al::LiveActor* actor, const char* actionName);

const char* getActionName(const al::LiveActor* actor);
f32 getActionFrame(const al::LiveActor* actor);
f32 getActionFrameMax(const al::LiveActor* actor);
f32 getActionFrameMax(const al::LiveActor* actor, const char* actionName);
f32 getActionFrameRate(const al::LiveActor* actor);

void setActionFrame(al::LiveActor* actor, f32 frame);
void setActionFrameRate(al::LiveActor* actor, f32 rate);

void stopAction(al::LiveActor* actor);
void restartAction(al::LiveActor* actor);
void copyAction(al::LiveActor* actor, const al::LiveActor* sourceActor);

void startNerveAction(al::LiveActor* actor, const char* actionName);
void setNerveAtActionEnd(al::LiveActor* actor, const al::Nerve* nerve);
void resetNerveActionForInit(al::LiveActor* actor);
}  // namespace al
