#pragma once

#include <al/Library/LiveActor/ActorInitInfo.h>
#include <al/Library/Yaml/ByamlIter.h>
#include <al/Library/Resource/Resource.h>

namespace al {

class LiveActor;
class ActorResource;
class ParameterIo;

bool isExistModelResource(LiveActor const*);
bool isExistAnimResource(LiveActor const*);
void tryGetAnimResource(LiveActor const*);
bool isExistModelResourceYaml(LiveActor const*,char const*,char const*);
Resource* getModelResource(LiveActor const*);
bool isExistAnimResourceYaml(LiveActor const*,char const*,char const*);
void getAnimResource(LiveActor const*);
bool isExistModelOrAnimResourceYaml(LiveActor const*,char const*,char const*);
u8* getModelResourceYaml(LiveActor const*,char const*,char const*);
u8* getAnimResourceYaml(LiveActor const*,char const*,char const*);
u8* getModelOrAnimResourceYaml(LiveActor const*,char const*,char const*);
u8* getMapPartsResourceYaml(ActorInitInfo const&,char const*);
u8* tryGetMapPartsResourceYaml(ActorInitInfo const&,char const*);
void tryMakeInitFileName(sead::BufferedSafeString *,Resource const*,char const*,char const*,char const*);
void tryGetSuffixIter(ByamlIter *,Resource const*,char const*,char const*);
void tryGetInitFileIterAndName(ByamlIter *,sead::BufferedSafeString *,Resource const*,char const*,char const*,char const*);
void tryGetActorInitFileIterAndName(ByamlIter *,sead::BufferedSafeString *,Resource const*,char const*,char const*);
bool tryGetActorInitFileIter(ByamlIter *,Resource const*,char const*,char const*);
bool tryGetActorInitFileIterAndName(ByamlIter *,sead::BufferedSafeString *,LiveActor const*,char const*,char const*);
bool tryGetActorInitFileIter(ByamlIter *,LiveActor const*,char const*,char const*);
bool tryGetActorInitFileName(sead::BufferedSafeString *,Resource const*,char const*,char const*);
bool tryGetActorInitFileName(sead::BufferedSafeString *,ActorResource const*,char const*,char const*);
bool tryGetActorInitFileName(sead::BufferedSafeString *,LiveActor const*,char const*,char const*);
bool tryGetActorInitFileSuffixName(sead::BufferedSafeString *,Resource const*,char const*,char const*);
bool tryGetActorInitFileSuffixName(sead::BufferedSafeString *,LiveActor const*,char const*,char const*);
const char* tryGetActorInitFileSuffixName(LiveActor const*,char const*,char const*);
const char* tryGetActorInitFileSuffixName(Resource const*,char const*,char const*);
void initParameterIoAsActorInfo(ParameterIo *,LiveActor const*,char const*,char const*);
void initParameterIoAndLoad(ParameterIo *,LiveActor const*,char const*,char const*);
}