#include "Framework.h"
#include "Math/Objects/BoundingFrustum.h"

#include "Math/Constants.h"
#include "Math/Objects/AxisAlignedBoundingBox.h"
#include "Math/Objects/BoundingSphere.h"
#include "Math/Objects/OrientedBoundingBox.h"
#include "Math/Objects/Vector3.h"

namespace Silent::Math
{
    bool BoundingFrustum::Intersects(const Vector3& point) const
    {
        auto localPoint = Vector3::Transform(point - Origin, Matrix::Inverse(Rotation.ToRotationMatrix()));

        // Check Z-depth, assuming +Z is forward.
        if (localPoint.z < Near || localPoint.z > Far)
        {
            return false;
        }

        // Check horizontal bounds.
        if (localPoint.x > (RightSlope * localPoint.z) ||
            localPoint.x < (LeftSlope  * localPoint.z))
        {
            return false;
        }

        // Check vertical bounds.
        if (localPoint.y > (TopSlope    * localPoint.z) ||
            localPoint.y < (BottomSlope * localPoint.z))
        {
            return false;
        }

        return true;
    }

    bool BoundingFrustum::Intersects(const BoundingSphere& sphere) const
    {
        // @todo
        return false;
    }

    bool BoundingFrustum::Intersects(const AxisAlignedBoundingBox& aabb) const
    {
        // @todo
        return false;
    }

    bool BoundingFrustum::Intersects(const OrientedBoundingBox& obb) const
    {
        // @todo
        return false;
    }

    ContainmentType BoundingFrustum::Contains(const Vector3& point) const
    {
        return Intersects(point) ? ContainmentType::Contains : ContainmentType::None;
    }

    ContainmentType BoundingFrustum::Contains(const BoundingSphere& sphere) const
    {
        // @todo
        return ContainmentType::None;
    }

    ContainmentType BoundingFrustum::Contains(const AxisAlignedBoundingBox& aabb) const
    {
        // @todo
        return ContainmentType::None;
    }

    ContainmentType BoundingFrustum::Contains(const OrientedBoundingBox& obb) const
    {
        // @todo
        return ContainmentType::None;
    }

    ContainmentType BoundingFrustum::Contains(const BoundingFrustum& frustum) const
    {
        // @todo
        return ContainmentType::None;
    }
}
