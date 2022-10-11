#include "vec3.h"

namespace jd
{
	using type = float;

	type vec3::base() const {
		return sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
	}

	vec3 vec3::normalize() const {
		type w = base();

		return vec3{ x_ / w, y_ / w, z_ / w };
	}

	type Distance(const vec3& lhs, const vec3& rhs)
	{
		type x = lhs.x_ - rhs.y_;
		type y = lhs.y_ - rhs.y_;
		type z = lhs.z_ - rhs.z_;

		return sqrtf(x * x + y * y + z * z);
	}
}
