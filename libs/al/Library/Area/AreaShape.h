#pragma once

#include <al/Library/HostIO/HioNode.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace al {
class AreaShape : public al::HioNode {
    sead::Matrix34f* mBaseMtx; // 0x8
    sead::Vector3f mScale; // = sead::Vector3f::ones; // 0x10
public:
    AreaShape(void);

    virtual bool isInVolume(sead::Vector3f const& pos) const = 0;
    virtual bool isInVolumeOffset(sead::Vector3f const& pos, float offset) const = 0;
    virtual bool calcNearestEdgePoint(sead::Vector3f *result, sead::Vector3f const& pos) const = 0;
    virtual bool checkArrowCollision(sead::Vector3f *, sead::Vector3f *, sead::Vector3f const&, sead::Vector3f const&) const = 0;
    virtual bool calcLocalBoundingBox(sead::BoundBox3f *result) const = 0;

    void setBaseMtxPtr(sead::Matrix34f const*);
    void setScale(sead::Vector3f const&);
    void calcLocalPos(sead::Vector3f *,sead::Vector3f const&);
    void calcWorldPos(sead::Vector3f *,sead::Vector3f const&);
    void calcWorldDir(sead::Vector3f *,sead::Vector3f const&);
    void calcTrans(sead::Vector3f*);

};
}