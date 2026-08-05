#pragma once

#include <iostream>


// takes rad
/*float cos(float angle);

//takes rad
float sin(float angle);*/

float rad(float degrees);


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

		Vec3 operator+=(const Vec3& other);
		Vec3 operator-=(const Vec3& other);

		friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);

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

	float& operator[](int i);
	float operator[](int i) const;
};

struct Mat4 {
	float mat[4][4];

	static Mat4 identity();
	static Mat4 translate(float tx, float ty, float tz);
	static Mat4 scale(float sx, float sy, float sz);
	static Mat4 rotateY(float radians);
	static Mat4 perspective(float fovY, float aspect, float near, float far);
	static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up);

	Mat4 operator*(const Mat4&) const;
	Vec4 operator*(const Vec4&) const;

};

struct Vertex {
	Vec3 pos;
	Vec3 color;
	Vec3 normal;
	Vec2 uv;
};