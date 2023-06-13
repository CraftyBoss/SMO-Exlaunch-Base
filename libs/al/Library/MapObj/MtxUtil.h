#pragma once

#include <math/seadMatrix.h>

namespace nn::util::neon {
    class MatrixColumnMajor4x3fType;
    class MatrixColumnMajor4x4fType;
}

namespace al {

template <typename T>
class Matrix43;

class MtxPtrHolder {
private:
public:
    MtxPtrHolder(void);
    void init(int);
    void setMtxPtrAndName(int,char const*,sead::Matrix34<float> const*);
    void setMtxPtr(char const*,sead::Matrix34<float> const*);
    void findIndex(char const*) const;
    void findMtxPtr(char const*) const;
    void tryFindMtxPtr(char const*) const;
    void tryFindIndex(char const*) const;
};

void makeBayerMatrix(int *,int);
void f32ToF16(float);
void f16ToF32(unsigned short);

void makeMtxRotateTrans(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxFromTwoAxis(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&,int,int);
void makeMtxFrontUp(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxFrontSide(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxUpFront(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxUpSide(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxSideUp(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxSideFront(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxFrontNoSupport(sead::Matrix34<float> *,sead::Vector3<float> const&);
void makeMtxFrontNoSupportPos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxUpNoSupport(sead::Matrix34<float> *,sead::Vector3<float> const&);
void makeMtxUpNoSupportPos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxSideNoSupport(sead::Matrix34<float> *,sead::Vector3<float> const&);
void makeMtxSideNoSupportPos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxQuatPos(sead::Matrix34<float> *,sead::Quat<float> const&,sead::Vector3<float> const&);
void makeMtxQuatScalePos(sead::Matrix34<float> *,sead::Quat<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxQuatScalePos(sead::Matrix44<float> *,sead::Quat<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxFrontUpPos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxFrontSidePos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxUpFrontPos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxUpSidePos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxSideUpPos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxSideFrontPos(sead::Matrix34<float> *,sead::Vector3<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxFollowTarget(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxProj(sead::Matrix44<float> *,sead::Vector2<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&);
void makeMtxProjFromQuatPoseUp(sead::Matrix44<float> *,sead::Quat<float> const&,sead::Vector2<float> const&,sead::Vector3<float> const&);
void makeMtxProjFromQuatPoseFront(sead::Matrix44<float> *,sead::Quat<float> const&,sead::Vector2<float> const&,sead::Vector3<float> const&);
void makeMtxProjFromQuatPoseSide(sead::Matrix44<float> *,sead::Quat<float> const&,sead::Vector2<float> const&,sead::Vector3<float> const&);
void makeMtxProjFromUp(sead::Matrix44<float> *,sead::Vector2<float> const&,sead::Vector3<float> const&);
void rotateMtxXDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,float);
void rotateMtxYDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,float);
void rotateMtxZDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,float);
void rotateMtxCenterPosXDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,float);
void rotateMtxCenterPosAxisDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,sead::Vector3<float> const&,float);
void rotateMtxCenterPosYDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,float);
void rotateMtxCenterPosZDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,float);
void rotateMtxCenterPosQuat(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,sead::Quat<float> const&);
void turnMtxXDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,float);
void turnMtxYDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,float);
void turnMtxZDirDegree(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&,float);
void calcCameraPosFromViewMtx(sead::Vector3<float> *,sead::Matrix34<float> const&);
void calcMtxMul(sead::Vector3<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&);
void calcMtxMul(sead::Vector3<float> *,al::Matrix43<float> const&,sead::Vector3<float> const&);
void calcMtxScale(sead::Vector3<float> *,sead::Matrix34<float> const&);
void calcMtxScale(sead::Vector3<float> *,al::Matrix43<float> const&);
void normalizeMtxScale(sead::Matrix34<float> *,sead::Matrix34<float> const&);
void tryNormalizeMtxScaleOrIdentity(sead::Matrix34<float> *,sead::Matrix34<float> const&);
void calcMtxLocalTrans(sead::Vector3<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&);
void calcTransLocalOffsetByMtx(sead::Vector3<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&);
void preScaleMtx(sead::Matrix34<float> *,sead::Vector3<float> const&);
void addTransMtxLocalOffset(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Vector3<float> const&);
void blendMtx(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Matrix34<float> const&,float);
void blendMtxRotate(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Matrix34<float> const&,float);
void blendMtxTrans(sead::Matrix34<float> *,sead::Matrix34<float> const&,sead::Matrix34<float> const&,float);
void calcMtxLocalDirAngleOnPlaneToTarget(sead::Matrix34<float> const*,sead::Vector3<float> const&,int,int);
void calcMtxLocalDirAngleOnPlaneToDir(sead::Matrix34<float> const*,sead::Vector3<float> const&,int,int);
void calcRotAxisOrZero(sead::Vector3<float> *,sead::Matrix34<float> const&);
void calcMxtInvertOrtho(sead::Matrix34<float> *,sead::Matrix34<float> const&);
void calcNearFarByInvProjection(float *,float *,sead::Matrix44<float> const&);
void calcMovedInertiaTensor(sead::Matrix33<float> *,sead::Matrix33<float> const&,sead::Vector3<float> const&,float);
void calcInertiaTensorByMovedTensorAndCenter(sead::Matrix33<float> *,sead::Matrix33<float> const&,sead::Vector3<float> const&,float);
void calcInertiaTensorSphere(sead::Matrix33<float> *,float,float);
void calcInertiaTensorBox(sead::Matrix33<float> *,sead::Vector3<float> const&,float);
void makeMtx34f(sead::Matrix34<float> *,nn::util::neon::MatrixColumnMajor4x3fType const&);
void makeMtx44f(sead::Matrix44<float> *,nn::util::neon::MatrixColumnMajor4x4fType const&);
}