#include "JM_Math.h"
#include <cmath>



float rad(float degrees) {
	return degrees * (3.14159265358979f / 180.0);
}


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
		return { x / w, y / w, z / w, 1.0f };
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

	Mat4 Mat4::translate(float tx, float ty, float tz) {
		Mat4 r = {
			{
				{1, 0, 0, tx },
				{0, 1, 0, ty },
				{0, 0, 1, tz },
				{0, 0, 0, 1 },
			}
		};
		return r;
	}


	Mat4 Mat4::scale(float sx, float sy, float sz) {
		Mat4 r = {
			{
				{sx, 0, 0, 0 },
				{0,sy, 0, 0 },
				{0, 0, sz, 0 },
				{0, 0, 0, 1 },
			}
		};
		return r;
	}


	Mat4 Mat4::rotateY(float y) {
		Mat4 r = {
			{
				{std::cos(rad(y)), 0, -std::sin(rad(y)), 0},
				{0,1, 0, 0 },
				{std::sin(rad(y)), 0, std::cos(rad(y)), 0},
				{0, 0, 0, 1 },
			}
		};
		return r;
	}



	Mat4 Mat4::perspective(float fovY, float aspect, float near, float far) {


		Mat4 r = {
			{
				{1 / (aspect * std::tan(rad(fovY / 2))), 0, 0, 0},
				{0, 1 / std::tan(rad(fovY / 2)), 0, 0 },
				{0, 0, -far / (far - near), -far * near / (far - near)},
				{0, 0, -1, 0 },
			}
		};
		return r;
	}


	/*Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
		Mat4 r = {
			{
				{, 0, , 0},
				{0,1, 0, 0 },
				{, 0, , 0},
				{0, 0, 0, 1 },
			}
		};
		return r;
	}*/



	/* Remember Mat4 * Mat4 will need to traverse the left side mat on row and the right size mat on columns.
		They also will need to multiply everything, so index 0,1 is multipled against all of them in the row
		in the other mat as demonstrated below with the 3 for loops.
	*/

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

		// required for projection matrices
		if (result[3] != 1) {
			 return result = result.p_divide();
		}

		return result;
	}

