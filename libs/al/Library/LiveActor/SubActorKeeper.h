#pragma once

#include <basis/seadTypes.h>
#include <al/Library/LiveActor/ActorInitInfo.h>

// TODO: bring this up to sanae
// temp solution to figure out a solution to bitflag enums (stole this right from nvn headers)
#define AL_BITS(CLASS)                                                                            \
private:                                                                                           \
    int m_value;                                                                                   \
                                                                                                   \
public:                                                                                            \
    CLASS() : m_value(-1) {}                                                                       \
    CLASS(const CLASS& c) : m_value(c.m_value) {}                                                  \
    CLASS(int i) : m_value(i) {}                                                                   \
    CLASS(Enum e) : m_value(e) {}                                                                  \
    operator int() const {                                                                         \
        return m_value;                                                                            \
    }                                                                                              \
    bool operator==(const CLASS& c) const {                                                        \
        return m_value == c.m_value;                                                               \
    }                                                                                              \
    bool operator==(const Enum& e) const {                                                         \
        return m_value == e;                                                                       \
    }                                                                                              \
    bool operator!=(const CLASS& c) const {                                                        \
        return m_value != c.m_value;                                                               \
    }                                                                                              \
    bool operator!=(const Enum& e) const {                                                         \
        return m_value != e;                                                                       \
    }                                                                                              \
    CLASS operator|(const CLASS& c) const {                                                        \
        return CLASS(m_value | c.m_value);                                                         \
    }                                                                                              \
    CLASS operator|(const Enum& e) const {                                                         \
        return CLASS(m_value | e);                                                                 \
    }                                                                                              \
    CLASS operator&(const CLASS& c) const {                                                        \
        return CLASS(m_value & c.m_value);                                                         \
    }                                                                                              \
    CLASS operator&(const Enum& e) const {                                                         \
        return CLASS(m_value & e);                                                                 \
    }                                                                                              \
    CLASS operator^(const CLASS& c) const {                                                        \
        return CLASS(m_value ^ c.m_value);                                                         \
    }                                                                                              \
    CLASS operator^(const Enum& e) const {                                                         \
        return CLASS(m_value ^ e);                                                                 \
    }                                                                                              \
    CLASS& operator|=(const CLASS& c) {                                                            \
        m_value |= c.m_value;                                                                      \
        return *this;                                                                              \
    }                                                                                              \
    CLASS& operator|=(const Enum& e) {                                                             \
        m_value |= e;                                                                              \
        return *this;                                                                              \
    }                                                                                              \
    CLASS& operator&=(const CLASS& c) {                                                            \
        m_value &= c.m_value;                                                                      \
        return *this;                                                                              \
    }                                                                                              \
    CLASS& operator&=(const Enum& e) {                                                             \
        m_value &= e;                                                                              \
        return *this;                                                                              \
    }                                                                                              \
    CLASS& operator^=(const CLASS& c) {                                                            \
        m_value ^= c.m_value;                                                                      \
        return *this;                                                                              \
    }                                                                                              \
    CLASS& operator^=(const Enum& e) {                                                             \
        m_value ^= e;                                                                              \
        return *this;                                                                              \
    }

namespace al {

    class LiveActor;

    struct SubActorSync {
        enum Enum {
            cNone = 0, // 0
            cAppear = 1 << 0, // 1
            cClipping = 1 << 1, // 2
            cHide = 1 << 2, // 4
            cAlphaMask = 1 << 3, // 8
            cAll = cAppear | cClipping | cHide | cAlphaMask // 15
        };
        AL_BITS(SubActorSync);
    };

    struct SubActorInfo
    {
        SubActorInfo() = default;
        inline SubActorInfo(al::LiveActor *actor, SubActorSync syncType) : mSubActor(actor), mSyncType(syncType) {};
        al::LiveActor* mSubActor = nullptr;
        void* field_8 = nullptr;
        SubActorSync mSyncType = SubActorSync::cNone;
    };

    class SubActorKeeper {
        friend class alSubActorFunction;
    private:
        al::LiveActor *mRootActor;
        int mMaxActorCount = 0;
        int mCurActorCount = 0;
        al::SubActorInfo **mBuffer = nullptr;
    public:
        SubActorKeeper(al::LiveActor *);
        void registerSubActor(al::LiveActor *, u32);
        void init(al::ActorInitInfo const&,char const*,int);

        static SubActorKeeper* create(al::LiveActor *);
        static SubActorKeeper* tryCreate(al::LiveActor *,char const*,int);
    };

    class alSubActorFunction {
    public:
        static void trySyncAlive(al::SubActorKeeper *);
        static void trySyncDead(al::SubActorKeeper *);
        static void trySyncClippingStart(al::SubActorKeeper *);
        static void trySyncClippingEnd(al::SubActorKeeper *);
        static void trySyncShowModel(al::SubActorKeeper *);
        static void trySyncHideModel(al::SubActorKeeper *);
        static void trySyncModelAlphaMask(al::SubActorKeeper *,float);
        static void findSubActor(al::SubActorKeeper const*,char const*);
    };

    bool isExistSubActorKeeper(al::LiveActor const*);
    al::LiveActor* getSubActor(al::LiveActor const*,char const*);
    al::LiveActor* tryGetSubActor(al::LiveActor const*,char const*);
    al::LiveActor* getSubActor(al::LiveActor const*,int);
    int getSubActorNum(al::LiveActor const*);
    void offSyncClippingSubActor(al::LiveActor *,al::LiveActor const*);
    void offSyncClippingSubActor(al::LiveActor *,char const*);
    void offSyncClippingSubActorAll(al::LiveActor *);
    void onSyncClippingSubActor(al::LiveActor *,al::LiveActor const*);
    void onSyncClippingSubActor(al::LiveActor *,char const*);
    void onSyncClippingSubActorAll(al::LiveActor *);
    void offSyncAppearSubActor(al::LiveActor *,al::LiveActor const*);
    void offSyncAppearSubActor(al::LiveActor *,char const*);
    void offSyncAppearSubActorAll(al::LiveActor *);
    void onSyncAppearSubActor(al::LiveActor *,al::LiveActor const*);
    void onSyncAppearSubActor(al::LiveActor *,char const*);
    void onSyncAppearSubActorAll(al::LiveActor *);
    void offSyncHideSubActor(al::LiveActor *,al::LiveActor const*);
    void offSyncHideSubActor(al::LiveActor *,char const*);
    void offSyncHideSubActorAll(al::LiveActor *);
    void onSyncHideSubActor(al::LiveActor *,al::LiveActor const*);
    void onSyncHideSubActor(al::LiveActor *,char const*);
    void onSyncHideSubActorAll(al::LiveActor *);
    void isSyncHideSubActor(al::LiveActor const*,al::LiveActor const*);
    void offSyncAlphaMaskSubActor(al::LiveActor *,al::LiveActor const*);
    void offSyncAlphaMaskSubActor(al::LiveActor *,char const*);
    void offSyncAlphaMaskSubActorAll(al::LiveActor *);
    void onSyncAlphaMaskSubActor(al::LiveActor *,al::LiveActor const*);
    void onSyncAlphaMaskSubActor(al::LiveActor *,char const*);
    void onSyncAlphaMaskSubActorAll(al::LiveActor *);
    void isSyncAlphaMaskSubActor(al::LiveActor const*,al::LiveActor const*);
    void startActionSubActor(al::LiveActor const*,char const*,char const*);
    void isActionEndSubActor(al::LiveActor const*,char const*);
    void isActionPlayingSubActor(al::LiveActor const*,char const*,char const*);
    void isActionOneTimeSubActor(al::LiveActor const*,char const*);
    void isActionOneTimeSubActor(al::LiveActor const*,char const*,char const*);
    void tryStartActionSubActorAll(al::LiveActor const*,char const*);
    void makeActorDeadSubActorAll(al::LiveActor const*);
    void tryValidateCollisionPartsSubActorAll(al::LiveActor *);
    void tryInvalidateCollisionPartsSubActorAll(al::LiveActor *);
}