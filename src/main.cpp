#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <random>
#include <math.h>

#include "FrameBuffer.h"
#include "Hit_Record.h"
#include "Sphere_List.h"
#include "Camera.h"

Float3 color(const Ray& r) {
	Sphere_List scene{
		sphere(Float3(0.0f, 0.0f, -1.0f), 0.5f),
		sphere(Float3(0.0f, -100.5f, -1.0f), 100.0f)
	};

	Hit_Record hit;
	if (scene.hit_test(r, 0.0f, 1000.0f, hit))
		return hit.normal * 0.5f + Float3(0.5f, 0.5f, 0.5f);
	const float t = 0.5f * (r.direction().y() + 1.0f);
	return Float3(1.0f, 1.0f, 1.0f) * (1.0f - t) + Float3(0.5f, 0.7f, 1.0f) * t;
}

float randf() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> d{ 0.0f, 1.0f };
	return d(gen);
}

int main(int argc, char* argv[])
{
	FrameBuffer fb(600u, 300u);
	Camera cam(4.0f, 2.0f);

	for (size_t r = 0u; r < fb.height(); r++)
		for (size_t c = 0u; c < fb.width(); c++)
		{
			Float3 col{ 0.0f, 0.0f, 0.0f };
			constexpr size_t ns = 50u;
			for (size_t s = 0u; s < ns; s++)
			{
				const float u = ((float)c + randf()) / (float)fb.width();
				const float v = ((float)r + randf()) / (float)fb.height();

				col += color(cam.getRay(u, v));
			}
			col /= (float)ns;
			fb.setPixel(r, c, 255.99f * col.x(), 255.99f * col.y(), 255.99f * col.z());
		}

	fb.save("output/out.tga");
	return 0;
}