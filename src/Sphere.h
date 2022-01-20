#pragma once

#include "Hittable.h"

class sphere : public Hittable {
public:
	sphere(const Float3& center, float radius) : center_(center), radius_(radius) {}

	bool hit_test(const Ray& r, float tmin, float tmax, Hit_Record& hit) const override {
		const Float3 oc = r.origin() - center_;
		const float a = dot(r.direction(), r.direction());
		const float b = dot(oc, r.direction()) * 2.0f;
		const float c = dot(oc, oc) - radius_ * radius_;
		const float d = b * b - 4.0f * a * c;
		if (d > 0.0f)
		{
			const float t1 = (-b - sqrt(d)) / (2.0f * a);
			const float t2 = (-b + sqrt(d)) / (2.0f * a);
			if (t1 > tmin && t1 < tmax)
				hit.t = t1;
			else if (t2 > tmin && t2 < tmax)
				hit.t = t2;
			else
				return false;
			const Float3 p = r.point_at(hit.t);
			hit.normal = normalize(p - center_);
		}

		return d > 0.0f;
	}
	const Float3 center() { return center_; }
	const float radius() { return radius_; }
private:
	Float3 center_;
	float radius_;
};
