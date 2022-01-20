#pragma once

#include "Float3.h"

class Ray {
public:
	Ray(const Float3& o, const Float3& d) : origin_(o), direction_(normalize(d)) {}

	const Float3& origin() const { return origin_; }
	const Float3& direction() const { return direction_; }

	Float3 point_at(float t) const {
		return origin_ + direction_ * t;
	}

private:
	Float3 origin_;
	Float3 direction_;
};
