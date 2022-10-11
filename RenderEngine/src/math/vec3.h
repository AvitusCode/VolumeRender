#pragma once
#include <math.h>

namespace jd
{
	using type = float;

	struct vec3
	{
	public:
		type x_, y_, z_;
		vec3() noexcept : x_(0.0), y_(0.0), z_(0.0) {}
		explicit vec3(type x, type y, type z) noexcept : x_(x), y_(y), z_(z) {}

		type base() const;
		vec3 normalize() const;

		bool operator==(const vec3& rhs) const {
			return x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_;
		}

		bool operator!=(const vec3& rhs) const {
			return !(rhs == *this);
		}

		vec3 operator+(const vec3& rhs) const {
			return vec3{ x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_ };
		}

		vec3& operator+=(const vec3& rhs) {
			x_ += rhs.x_;
			y_ += rhs.y_;
			z_ += rhs.z_;

			return *this;
		}

		vec3 operator-(const vec3& rhs) const {
			return vec3{ x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_ };
		}

		vec3 operator*(type c) const {
			return vec3{ x_ * c, y_ * c, z_ * c };
		}

		vec3& operator*=(type c) {
			x_ *= c;
			y_ *= c;
			z_ *= c;
			return *this;
		}

		vec3 operator*(const vec3& rhs) const {
			return vec3{ x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_ };
		}

		vec3& operator*=(const vec3& rhs) {
			x_ *= rhs.x_;
			y_ *= rhs.y_;
			z_ *= rhs.z_;
			return *this;
		}
	};

	const vec3 zeroVec3(0.0, 0.0, 0.0);

	type Distance(const vec3& lhs, const vec3& rhs);
}
