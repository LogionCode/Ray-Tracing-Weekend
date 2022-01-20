#pragma once

#include "Ray.h"
#include "Hit_Record.h"

class Hittable {
public:
	virtual bool hit_test(const Ray& r, float tmin, float tmax, Hit_Record& hit) const = 0;
};
