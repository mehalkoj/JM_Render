#include "JM_Math.h"






	// operations
	Vec2 Vec2::operator+(const Vec2& other) const {
		return { x + other.x, y + other.y };
	}

	Vec2 Vec2::operator-(const Vec2& other) const {
		return { x - other.x, y - other.y };
	}

	Vec2 Vec2::operator*(const Vec2& other) const {
		return { x * other.x, y * other.y };
	}

	Vec2 Vec2::operator/(const Vec2& other) const {
		return { x / other.x, y / other.y };
	}

	float Vec2::dot(const Vec2& other) const {
		return { x * other.x + y * other.y };
	}






	// operations
	Vec3 Vec3::operator+(const Vec3 & other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	Vec3 Vec3::operator-(const Vec3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	Vec3 Vec3::operator*(const Vec3& other) const {
		return { x * other.x, y * other.y, z * other.z };
	}

	Vec3 Vec3::operator/(const Vec3& other) const {
		return { x / other.x, y / other.y, z / other.z };
	}

	float Vec3::dot(const Vec3& other) const {
		return { x * other.x + y * other.y + z * other.z };
	}

	Vec3 Vec3::cross(const Vec3& other) const {
		return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}

	float Vec3::length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	Vec3 Vec3::normalized() const {
		float len = length();
		return { x / len, y / len, z / len };
	}



