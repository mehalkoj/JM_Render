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

		Vec3 operator*(float s) const;
		Vec3 operator/(float s) const;

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

struct Mat4 {
	float mat[4][4];

	static Mat4 identity(); // identity matrix

	Mat4 operator*(const Mat4&) const;
};

struct Vertex {
	Vec3 pos;
	Vec3 color;
	Vec3 normal;
	Vec2 uv;
};