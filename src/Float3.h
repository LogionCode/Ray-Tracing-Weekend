#pragma once

#include <math.h>
#include <iostream>

class Float3
{
public:
	Float3() : x_(0), y_(0), z_(0) {}
	Float3(float x, float y, float z) : x_(x), y_(y), z_(z) {}

	float length() const {
		return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
	}

public:
	float x() const { return x_; }
	float y() const { return y_; }
	float z() const { return z_; }

	// operators to float3

	Float3 operator + (const Float3 t) const {
		return Float3(x_ + t.x_, y_ + t.y_, z_ + t.z_);
	}

	void operator += (const Float3& t) {
		x_ += t.x_;
		y_ += t.y_;
		z_ += t.z_;
	}

	Float3 operator - (const Float3 t) const {
		return Float3(x_ - t.x_, y_ - t.y_, z_ - t.z_);
	}

	void operator -= (const Float3& t) {
		x_ -= t.x_;
		y_ -= t.y_;
		z_ -= t.z_;
	}

	//operators to float

	Float3 operator * (const float t) const {
		return Float3(x_ * t, y_ * t, z_ * t);
	}

	void operator *= (const float t) {
		x_ *= t;
		y_ *= t;
		z_ *= t;
	}

	Float3 operator / (const float t) const {
		return Float3(x_ / t, y_ / t, z_ / t);
	}

	void operator /= (const float t) {
		x_ /= t;
		y_ /= t;
		z_ /= t;
	}

private:
	float x_, y_, z_;
};

static Float3 normalize(const Float3 v) {
	return v / v.length();
}

static float dot(const Float3 v, const Float3 t) {
	return (v.x() * t.x() + v.y() * t.y() + v.z() * t.z());
}