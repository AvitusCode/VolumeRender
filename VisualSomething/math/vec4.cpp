#include "vec4.h"


namespace jd
{
	using type = float;

	type vec4::base() const {
		return sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
	}

	vec4 vec4::normalize() const {
		type w = base();

		return vec3{ x_ / w, y_ / w, z_ / w };
	}
	
	vec4& vec4::correct()
	{
		if (x_ >= 1.0f){
			x_ = 1.0f;
		}
		if (y_ >= 1.0f){
			y_ = 1.0f;
		}
		if (z_ >= 1.0f){
			z_ = 1.0f;
		}
		if (w_ >= 1.0f){
			w_ = 1.0f;
		}
		
		return *this;
	}

}
