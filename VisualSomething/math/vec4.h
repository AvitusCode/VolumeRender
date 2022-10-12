#pragma once
#include "vec3.h"

namespace jd
{
	using type = float;
	
	/// <summary>
	/// This structure have fourth position only for support estimates
	/// </summary>
	struct vec4
	{
		type x_, y_, z_, w_;

		vec4() noexcept : x_(0.0), y_(0.0), z_(0.0), w_(0.0) {}
		explicit vec4(type x, type y, type z, type w = 1.0) noexcept : x_(x), y_(y), z_(z), w_(w) {}
		vec4(vec3 vec, type w = 1.0) noexcept : x_(vec.x_), y_(vec.y_), z_(vec.z_), w_(w) {}

		type base() const; // base of first three components
		vec4 normalize() const; // normilize by first three components
		vec4& correct();

		operator vec3() const {
			return vec3{ x_, y_, z_ };
		}

		bool operator==(const vec4& rhs) const {
			return x_== rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_ && w_ == rhs.w_;
		}

		bool operator!=(const vec4& rhs) const {
			return !(rhs == *this);
		}

		vec4 operator+(const vec4& rhs) const {
			return vec4{ x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_, w_};
		}

		vec4& operator+=(const vec4& rhs) {
			x_ += rhs.x_;
			y_ += rhs.y_;
			z_ += rhs.z_;

			return *this;
		}

		vec4 operator-(const vec4& rhs) const {
			return vec4{ x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_, w_ };
		}

		vec4 operator*(type c) const {
			return vec4{ x_ * c, y_ * c, z_ * c, w_ };
		}

		vec4& operator*=(type c) {
			x_ *= c;
			y_ *= c;
			z_ *= c;
			return *this;
		}

		vec4 operator*(const vec4& rhs) const {
			return vec4{ x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_, w_};
		}

		vec4& operator*=(const vec4& rhs) {
			x_ *= rhs.x_;
			y_ *= rhs.y_;
			z_ *= rhs.z_;
			return *this;
		}
	};
}

