#pragma once

#include <prim/seadSafeString.h>
#include <prim/seadEnum.h>
#include <math/seadVector.h>
#include <gfx/seadColor.h>
#include "ByamlIter.h"

#define PARAM_TYPE_DEF(Name, Type) \
class Parameter##Name : public Parameter<Type> { \
public: \
    const char *getParamTypeStr() override { return al::YamlParamType::text(al::YamlParamType:: Name); } \
    al::YamlParamType::ValueType getParamType() override { return al::YamlParamType:: Name; } \
};

namespace al {
    class ParameterObj;

    class ParameterList;

    SEAD_ENUM(YamlParamType,
              Invalid,
              Bool,
              F32,
              S32,
              U32,
              V2f,
              V2s32, // unused
              V3f,
              V4f,
              Q4f, // unused
              C4f,
              StringRef,
              String32,
              String64,
              String128,
              String256,
              String512,
              String1024,
              String2048,
              String4096
    )

    class ParameterBase {
    private:
        ParameterBase *mNext = nullptr;
        sead::FixedSafeString<0x40> mParamName;
        int mParamHash;
    public:
        ParameterBase(const sead::SafeString &key, const sead::SafeString &label, const sead::SafeString &hint,
                      ParameterObj *,
                      bool unused);

        ParameterBase(const sead::SafeString &name, const sead::SafeString &, const sead::SafeString &, ParameterList *,
                      bool unused);

        virtual const char *getParamTypeStr() = 0;

        virtual al::YamlParamType::ValueType getParamType() = 0;

        virtual const void *ptr() const = 0;

        virtual void *ptr() = 0;

        virtual void afterGetParam() {}

        virtual void size() = 0;

        virtual bool isEqual(const al::ParameterBase *other);

        virtual void copy(const al::ParameterBase *other);

        virtual void copyLerp(const al::ParameterBase *from, const al::ParameterBase *to, float a4);

        void initializeListNode(sead::SafeString const &, sead::SafeString const &, sead::SafeString const &,
                                al::ParameterObj *, bool);

        void initializeListNode(sead::SafeString const &, sead::SafeString const &, sead::SafeString const &,
                                al::ParameterList *, bool);

        void initialize(sead::SafeString const &, sead::SafeString const &, sead::SafeString const &, bool);

        uint calcHash(sead::SafeString const &);

        void tryGetParam(al::ByamlIter const &);

        template<typename T>
        bool isEqual_(al::ParameterBase const &) const;

        template<typename T>
        void copyLerp_(al::ParameterBase const &, al::ParameterBase const &, float);

    };

    template<class T>
    class Parameter : public ParameterBase {
    private:
        T mParam;
    public:
        Parameter(const T &defValue, const sead::SafeString &key, const sead::SafeString &label,
                  const sead::SafeString &hint,
                  ParameterObj *paramObj, bool unused) : ParameterBase(key, label, hint, paramObj,
                                                                       unused) { mParam = defValue; }

        const char *getParamTypeStr() override { return al::YamlParamType::text(al::YamlParamType::Invalid); }

        al::YamlParamType::ValueType getParamType() override { return al::YamlParamType::Invalid; }

        const void *ptr() const override { return (void *) mParam; }

        void *ptr() override { return (void *) mParam; }

        inline T &ref() { return mParam; }
    };

    PARAM_TYPE_DEF(Bool, bool)

    PARAM_TYPE_DEF(F32, f32)

    PARAM_TYPE_DEF(S32, s32)

    PARAM_TYPE_DEF(U32, u32)

    PARAM_TYPE_DEF(V2f, sead::Vector2f)

    PARAM_TYPE_DEF(V3f, sead::Vector3f)

    PARAM_TYPE_DEF(V4f, sead::Vector4f)

    PARAM_TYPE_DEF(C4f, sead::Color4f)

    PARAM_TYPE_DEF(StringRef, const char*)

    PARAM_TYPE_DEF(String32, sead::FixedSafeString<0x20>)

    PARAM_TYPE_DEF(String64, sead::FixedSafeString<0x40>)

    PARAM_TYPE_DEF(String128, sead::FixedSafeString<0x80>)

    PARAM_TYPE_DEF(String256, sead::FixedSafeString<0x100>)

    PARAM_TYPE_DEF(String512, sead::FixedSafeString<0x200>)

    PARAM_TYPE_DEF(String1024, sead::FixedSafeString<0x400>)

    PARAM_TYPE_DEF(String2048, sead::FixedSafeString<0x800>)

    PARAM_TYPE_DEF(String4096, sead::FixedSafeString<0x1000>)

}