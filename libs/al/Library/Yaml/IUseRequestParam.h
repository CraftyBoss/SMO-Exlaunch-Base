#pragma once

#include "ParameterObj.h"

namespace al {
    class IUseRequestParam {
    public:
        virtual void getParamName() = 0;

        virtual al::ParameterObj *getParamObj() = 0;

        virtual al::ParameterObj *getParamObjConst() = 0;

        virtual bool isEqual(const al::IUseRequestParam *);

        virtual void copy(const al::IUseRequestParam *);

        virtual void copyInterp(const al::IUseRequestParam *, const al::IUseRequestParam *, float);
    };
}