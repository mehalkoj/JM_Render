#pragma once

#include <iostream>




struct Vec2 {
	float x, y;

	// operations
	Vec2 operator+(const Vec2& other)const;

	Vec2 operator-(const Vec2& other) const;

	Vec2 operator*(const Vec2& other) const;

	Vec2 operator/(const Vec2& other) const;

	float dot(const Vec2& other) const;

};

struct Vec3 {
		float x, y, z;


		// operations
		Vec3 operator+(const Vec3& other) const;

		Vec3 operator-(const Vec3& other) const;

		Vec3 operator*(const Vec3& other) const;

		Vec3 operator/(const Vec3& other) const;

		float dot(const Vec3& other) const;

		Vec3 cross(const Vec3& other) const;

		float length() const;

		Vec3 normalized() const;

		float& operator[](int i);
		float operator[](int i) const;
};

struct Vec4 {
	float x, y, z, w;

	Vec4 operator+(const Vec4& other) const;

	Vec4 operator-(const Vec4& other) const;

	Vec4 operator*(const Vec4& other) const;

	Vec4 operator/(const Vec4& other) const;

	float cross2d(const Vec4& other) const;

	Vec4 p_divide() const;
};




};
struct Vertex {
	Vec3 pos;
	Vec3 color;
	Vec3 normal;
	Vec2 uv;
};