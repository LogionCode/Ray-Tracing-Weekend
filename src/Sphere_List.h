#pragma once

#include <vector>

#include "Sphere.h"

class Sphere_List : Hittable {
public:
	template<class ...Args>
	Sphere_List(Args... args) : list_{ std::forward<Args>(args)... } {}

	bool hit_test(const Ray& r, float tmin, float tmax, Hit_Record& hit) const override {
		bool anyhit = false;
		float closest_hit = tmax;
		for (const sphere& s : list_) {
			bool has_hit = s.hit_test(r, 0.0f, closest_hit, hit);
			if (has_hit)
				closest_hit = hit.t;

			if (!anyhit)
				anyhit = has_hit;
		}
		return anyhit;
	}
private:
	std::vector<sphere> list_;
};
