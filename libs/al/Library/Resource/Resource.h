#pragma once

#include <filedevice/seadArchiveFileDevice.h>
#include <nn/g3d/ResFile.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>
#include <resource/seadResource.h>

namespace al {
class ActorInitResourceData;

class Resource {
private:
    sead::ArchiveRes* mArchive;
    sead::ArchiveFileDevice* mDevice;
    sead::FixedSafeString<0x80> mName;
    sead::Heap* mHeap;
    al::ActorInitResourceData* mData;
    nn::g3d::ResFile* mResFile;

public:
    Resource(const sead::SafeString& path);
    Resource(const sead::SafeString& path, sead::ArchiveRes* archive);
    bool isExistFile(const sead::SafeString& name) const;
    bool isExistByml(char const*) const;
    u32 getSize(void) const;
    u32 getEntryNum(const sead::SafeString&) const;
    const char* getEntryName(const sead::BufferedSafeString* outName, const sead::SafeString&,
                             u32) const;
    u32 getFileSize(const sead::SafeString& name) const;
    const u8* getByml(const sead::SafeString& name) const;
    void* getFile(const sead::SafeString& name) const;
    const u8* tryGetByml(const sead::SafeString& name) const;
    void getKcl(const sead::SafeString& name) const;
    void tryGetKcl(const sead::SafeString& name) const;
    void getPa(const sead::SafeString& name) const;
    void tryGetPa(const sead::SafeString& name) const;
    void getOtherFile(const sead::SafeString& name) const;
    const char* getArchiveName() const;
    void tryCreateResGraphicsFile(const sead::SafeString& name, nn::g3d::ResFile* resFile);
    void cleanupResGraphicsFile();
};

class AnimInfoTable { char size[0x18]; };
class ActionAnimCtrlInfo { char size[0x60]; };

struct InitResourceDataAnim {
    al::AnimInfoTable *mInfoTable; // 0x0
    al::AnimInfoTable *mFclAnim; // 0x8
    al::AnimInfoTable *mFtsAnim; // 0x10
    al::AnimInfoTable *mFtpAnim; // 0x18
    al::AnimInfoTable *mInfoTable2; // 0x18
};

class InitResourceDataActionAnim {
private:
    int mLength = 0;
    ActionAnimCtrlInfo **mInfos; // ActionAnimCtrlInfo*[mLength];
public:
    InitResourceDataActionAnim(al::Resource *,al::InitResourceDataAnim const*,char const* resourceYml);
    void sortCtrlInfo(void);

    static InitResourceDataActionAnim* tryCreate(al::Resource *,al::InitResourceDataAnim const*,char const*);
};

struct InitResourceDataAction {
    al::InitResourceDataActionAnim *dataActionAnim;
};

class ActorResource {
private:
    sead::FixedSafeString<0x80> unkStr;  // 0x8
    al::Resource *mResourceModel; // 0xA0
    al::Resource *mResourceAnim;  // 0xA8
    bool mHasAnimData;            // 0xB0
    al::InitResourceDataAnim *mAnimResData; // 0xB8
    al::InitResourceDataAction *mActionResData; // 0xC0
public:
    ActorResource(sead::SafeString const&, al::Resource*, al::Resource*);
    virtual ~ActorResource();

    void initResourceData(char const*, bool);
};
}  // namespace al
