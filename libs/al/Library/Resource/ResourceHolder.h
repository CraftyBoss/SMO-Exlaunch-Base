#pragma once

#include <prim/seadSafeString.h>

// this probably isnt a good spot
namespace al {

    class Resource;
    class SeadAudioPlayer;
    class ActorResourceHolder;
    class ActorResource;

    void addResourceCategory(sead::SafeStringBase<char> const&,int,sead::Heap *);
    bool isEmptyCategoryResource(sead::SafeStringBase<char> const&);
    void createCategoryResourceAll(sead::SafeStringBase<char> const&);
    void removeResourceCategory(sead::SafeStringBase<char> const&);
    const char* getResourceName(al::Resource const*);
    const char* getResourcePath(al::Resource const*);
    bool isExistResGraphicsFile(al::Resource const*);
    Resource* findResource(sead::SafeStringBase<char> const&);
    Resource* findOrCreateResource(sead::SafeString const& path, char const* ext);
    Resource* findOrCreateResourceCategory(sead::SafeString const& path, sead::SafeString const& category, char const* ext);
    Resource* findOrCreateResourceEventData(char const*,char const*);
    Resource* findOrCreateResourceSystemData(char const*,char const*);
    ActorResource* findOrCreateActorResource(al::ActorResourceHolder *,char const*,char const*);
    ActorResource* findOrCreateActorResourceWithAnimResource(al::ActorResourceHolder *,char const*,char const*,char const*,bool);
    void isExistResourceYaml(al::Resource const*,char const*,char const*);
    void isExistResourceYaml(al::ActorResource const*,char const*,char const*);
    void findResourceYaml(al::Resource const*,char const*,char const*);
    void findResourceYaml(al::ActorResource const*,char const*,char const*);
    void tryFindStageParameterFileDesign(sead::SafeStringBase<char> const&,sead::SafeStringBase<char> const&,int);
    void loadCategoryArchiveAll(sead::SafeStringBase<char> const&);
    void setCurrentCategoryName(char const*);
    void resetCurrentCategoryName(void);
    void setCurrentCategoryNameDefault(void);
    bool getBymlFromObjectResource(sead::SafeString const&,sead::SafeString const&);
    bool tryGetBymlFromObjectResource(sead::SafeString const&,sead::SafeString const&);
    bool getBymlFromLayoutResource(sead::SafeString const&,sead::SafeString const&);
    bool tryGetBymlFromLayoutResource(sead::SafeString const&,sead::SafeString const&);
    u8 *tryGetBymlFromArcName(sead::SafeString const&,sead::SafeString const&);
    u8 *getBymlFromArcName(sead::SafeString const&,sead::SafeString const&);
    u8 *getByml(Resource const*,sead::SafeString const&);
    u8 *tryGetByml(Resource const*,sead::SafeString const&);
    bool setAudioPlayerToResourceSystem(SeadAudioPlayer *,SeadAudioPlayer *);

}