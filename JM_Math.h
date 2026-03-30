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
	};


struct Vertex {
	Vec2 pos;
	Vec3 color;
};