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
	Vec3 Vec3::operator+(const Vec3& other) const {
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

	Vec3 Vec3::operator*(float s) const { 
		return { x * s, y * s, z * s }; 
	}

	Vec3 Vec3::operator/(float s) const { 
		return { x / s, y / s, z / s }; 
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

	float& Vec3::operator[](int i) {
		return (&x)[i]; 
	}
	float Vec3::operator[](int i) const {
		return (&x)[i]; 
	}



	Vec4 Vec4::operator+(const Vec4& other) const {
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}

	Vec4 Vec4::operator-(const Vec4& other) const {
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}

	Vec4 Vec4::operator*(const Vec4& other) const {
		return { x * other.x, y * other.y, z * other.z, w * other.w };
	}

	Vec4 Vec4::operator/(const Vec4& other) const {
		return { x / other.x, y / other.y, z / other.z, w / other.w };
	}

	float Vec4::cross2d(const Vec4& other) const {
		return { x * other.y - y * other.x };
	}

	// perspevtive division
	Vec4 Vec4::p_divide() const {
		return { x / w, y/ w, z / w, 1.0f };
	}

	float& Vec4::operator[](int i) {
		return (&x)[i];
	}
	float Vec4::operator[](int i) const {
		return (&x)[i];
	}



	Mat4 Mat4::identity() {
		Mat4 r = {
			{
				{ 1, 0, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 0, 1 },
			}
		};

		return r;

	}



	Mat4 Mat4::operator*(const Mat4& other) const {

		float newmat[4][4] = {};
		Mat4 result = {};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					newmat[i][j] += mat[i][k] * other.mat[k][j];
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				result.mat[i][j] = newmat[i][j];
			}
		}

		return result;
	}

	Vec4 Mat4::operator*(const Vec4& other) const {

		Vec4 result = {0, 0, 0, 0};
		for (int i = 0; i < 4; i++) {
				for (int k = 0; k < 4; k++) {
					result[i] += mat[i][k] * other[k];

				}
			}

		return result;
	}

