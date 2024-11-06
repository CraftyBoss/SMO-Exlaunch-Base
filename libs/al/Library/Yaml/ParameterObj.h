#pragma once

#include "ParameterBase.h"

namespace al {
    class ParameterArray;

    class ParameterObj {
    private:
        al::ParameterBase *mFirstParam;
        al::ParameterBase *mLastParam;
        al::ParameterObj *mNext;
        al::ParameterArray *mParamArray;
        sead::FixedSafeString<0x40> mParamObjKey;
    public:
        ParameterObj(void);

        void addArray(al::ParameterArray *, sead::SafeString const &);

        void copy(al::ParameterObj const &);

        void copyLerp(al::ParameterObj const &, al::ParameterObj const &, float);

        void findParameter(char const *);

        bool isEqual(al::ParameterObj const &) const;

        void pushBackListNode(al::ParameterBase *);

        void tryGetParam(al::ByamlIter const &);
    };
}