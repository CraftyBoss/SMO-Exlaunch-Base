#pragma once

#include "ParameterObj.h"

namespace al {
    class ParameterArray {
    private:
        al::ParameterObj *mFirstParam;
        al::ParameterArray *mNext;
        sead::FixedSafeString<0x40> mParamObjKey;
        int mKeyHash;
    public:
        ParameterArray(void);

        void addObj(al::ParameterObj *);

        void clearObj(void);

        void copy(al::ParameterArray const &);

        void copyLerp(al::ParameterArray const &, al::ParameterArray const &, float);

        void isEqual(al::ParameterArray const &);

        void isExistObj(al::ParameterObj *);

        void removeObj(al::ParameterObj *);

        void tryGetParam(al::ByamlIter const &);
    };
}