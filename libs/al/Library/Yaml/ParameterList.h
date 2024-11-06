#pragma once

#include "ParameterBase.h"
#include "ParameterArray.h"

namespace al {
    class ParameterList {
    private:
        al::ParameterBase *mRootParamNode;
        al::ParameterObj *mRootObjNode;
        al::ParameterList *mRootListNode;
        al::ParameterArray *mRootArrayNode;
        al::ParameterList *mNext;
        sead::FixedSafeString<0x40> mNodeKey;
    public:
        ParameterList(void);

        void addArray(al::ParameterArray *, sead::SafeString const &);

        void addList(al::ParameterList *, sead::SafeString const &);

        void addObj(al::ParameterObj *, sead::SafeString const &);

        void addParam(al::ParameterBase *);

        void clearList(void);

        void clearObj(void);

        void isExistObj(al::ParameterObj *);

        void removeList(al::ParameterList *);

        void removeObj(al::ParameterObj *);

        void tryGetParam(al::ByamlIter const &);
    };

    class ParameterIo : public ParameterList {
    };
}