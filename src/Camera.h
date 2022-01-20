#pragma once

#include "Ray.h"

class Camera {
public:
	Camera(float aspect_h, float aspect_v) : aspect_h_(aspect_h), aspect_v_(aspect_v), origin_(0.0f, 0.0f, 0.0f) {}

	Ray getRay(float u, float v) {
		const Float3 lower_left{ -aspect_h_ / 2.0f, -aspect_v_ / 2.0f, -1.0f };

		return Ray(origin_, lower_left + Float3(u * aspect_h_, v * aspect_v_, 0.0f));
	}

private:
	float aspect_h_;
	float aspect_v_;
	Float3 origin_;
};