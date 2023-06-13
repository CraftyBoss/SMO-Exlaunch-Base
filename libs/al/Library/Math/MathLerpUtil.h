#pragma once

#include <math/seadVector.h>
#include <gfx/seadColor.h>

namespace al {
    void easeIn(float);
    void easeOut(float);
    void easeInOut(float);
    void squareIn(float);
    void squareOut(float);
    void powerIn(float,float);
    void powerOut(float,float);
    void logarithmIn(float,float);
    void logarithmOut(float,float);
    void exponentIn(float,float);
    void exponentOut(float,float);
    void hermiteRate(float,float,float);
    void calcFourthOrderRate(float,float);
    void calcTriangleWave01(float,float);
    void calcTriangleWave(float,float,float,float);
    void lerpValue(float,float,float);
    void calcRate01(float,float,float);
    void easeByType(float,int);
    void lerpValue(float,float,float,float,float);
    void lerpDegree(float,float,float);
    void lerpRadian(float,float,float);
    void lerpVec(sead::Vector2f *,sead::Vector2f const&,sead::Vector2f const&,float);
    void lerpVec(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,float);
    void lerpVecHV(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&,float,float);
    void separateVectorHV(sead::Vector3f *,sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&);
    void lerpColor(sead::Color4f *,sead::Color4f const&,sead::Color4f const&,float);
    void lerpLogValueEaseIn(float,float,float,float);
    void lerpLogValueEaseOut(float,float,float,float);
    void lerpLogVecEaseIn(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,float,float);
    void lerpLogVecEaseOut(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,float,float);
    void lerpExponentValueEaseIn(float,float,float,float);
    void lerpExponentValueEaseOut(float,float,float,float);
    void lerpExponentVecEaseIn(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,float,float);
    void lerpExponentVecEaseOut(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,float,float);
    void clampLeapMinAbs(float,float,float,float);
    void hermite(float,float,float,float,float);
    void hermite(float,float,float,float,float,float);
    void hermiteVec(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&,float);
    void converge(int,int,int);
    void converge(float,float,float);
    void convergeDegree(float,float,float);
    void convergeRadian(float,float,float);
    void convergeVec(sead::Vector2f *,sead::Vector2f const&,sead::Vector2f const&,float);
    void convergeVec(sead::Vector3f *,sead::Vector3f const&,sead::Vector3f const&,float);
    void diffNearAngleDegree(float,float);
    void isInRangeAngleDegree(float,float,float);
    void calcEyesAnimAngleInRange(float *,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&,sead::Vector3f const&,float,float,float,float);
    void isSameSign(float,float);
    void reverseBit8(unsigned char);
    void reverseBit16(unsigned short);
    void reverseBit32(unsigned int);
    void calcVanDerCorput(unsigned int);
    void calcHammersleyPoint(sead::Vector2f *,unsigned int,unsigned int);
    void findMaxFromArray(int const*,int);
    void separateMinMax(sead::Vector3f *,sead::Vector3f *,sead::Vector3f const&);
    void findMinFromArray(int const*,int);
}