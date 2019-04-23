#pragma once

#include <cmath>
class vector3f;

class vector2f {
	public:
		float x, y;
		vector2f() : x(0), y(0) {};
		vector2f(float X, float Y) : x(X), y(Y) {}

		float GetLength() const { return sqrt(pow(x, 2) + pow(y, 2)); }
		void Normalize() { *this /= GetLength(); }
		vector2f Normalized() { return *this /= GetLength(); }
		float Dot(vector2f rightVec) const { return (x * rightVec.x) + (y * rightVec.y); }
		float Angle(vector2f);
		float GreaterAngle(vector2f rightVec) { return float((2 * M_PI) - Angle(rightVec)); }
		void Vec3ToVec2(vector3f);

		vector2f operator+ (vector2f) const;
		vector2f operator- (vector2f) const;
		vector2f operator* (float) const;
		vector2f operator/ (float) const;
		vector2f& operator+= (vector2f);
		vector2f& operator-= (vector2f);
		vector2f& operator*= (float);
		vector2f& operator/= (float);
		vector2f& operator= (vector2f);
		bool operator== (const vector2f&) const;
		bool operator!= (const vector2f&) const;
};

class vector3f {
	public:
		float x, y, z;
		vector3f() : x(0), y(0), z(0) {};
		vector3f(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

		float GetLength() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
		void Normalize() { *this /= GetLength(); }
		vector3f Normalized() { return *this /= GetLength(); }
		float Dot(vector3f rightVec) const { return (x * rightVec.x) + (y * rightVec.y) + (z * rightVec.z); }
		vector3f Cross(vector3f);
		float Angle(vector3f);
		float GreaterAngle(vector3f rightVec) { return float((2 * M_PI) - Angle(rightVec)); }
		void Vec2ToVec3(vector2f rightVec) { x = rightVec.x, y = rightVec.y, z = 0; }

		vector3f operator+ (vector3f) const;
		vector3f operator- (vector3f) const;
		vector3f operator* (float) const;
		vector3f operator/ (float) const;
		vector3f& operator+= (vector3f);
		vector3f& operator-= (vector3f);
		vector3f& operator*= (float);
		vector3f& operator/= (float);
		vector3f& operator= (vector3f);
		bool operator== (const vector3f&) const;
		bool operator!= (const vector3f&) const;
};