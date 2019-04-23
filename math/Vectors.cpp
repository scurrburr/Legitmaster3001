#pragma once
#include "../windows/pch.h"

#include "Vectors.h"

float vector2f::Angle(vector2f rightVec) {
	vector2f tempVec = Normalized();
	float temp = tempVec.Dot(rightVec.Normalized());
	return float(acos(temp));
}

void vector2f::Vec3ToVec2(vector3f rightVec) {
	x = rightVec.x;
	y = rightVec.y;
}

vector2f vector2f::operator+(vector2f rightVec)const {
	return vector2f(*this) += rightVec;
}

vector2f vector2f::operator-(vector2f rightVec) const {
	return vector2f(*this) -= rightVec;
}

vector2f vector2f::operator*(float scalar) const {
	return vector2f(*this) *= scalar;
}

vector2f vector2f::operator/(float scalar) const {
	return vector2f(*this) /= scalar;
}

vector2f& vector2f::operator+=(vector2f rightVec) {
	x += rightVec.x;
	y += rightVec.y;
	return *this;
}

vector2f& vector2f::operator-=(vector2f rightVec) {
	x -= rightVec.x;
	y -= rightVec.y;
	return *this;
}

vector2f& vector2f::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

vector2f& vector2f::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

vector2f& vector2f::operator=(vector2f rightVec) {
	x = rightVec.x;
	y = rightVec.y;
	return *this;
}

bool vector2f::operator==(const vector2f& rightVec) const {
	return (x == rightVec.x && y == rightVec.y);
}

bool vector2f::operator!=(const vector2f & rightVec) const {
	return !operator==(rightVec);
}

vector3f vector3f::Cross(vector3f rightVec) {
	return vector3f((y * rightVec.z) - (z * rightVec.y),
		(z * rightVec.x) - (x * rightVec.z),
		(x * rightVec.y) - (y * rightVec.x));
}

float vector3f::Angle(vector3f rightVec) {
	vector3f tempVec = Normalized();
	float temp = tempVec.Dot(rightVec.Normalized());
	return float(acos(temp));
}

vector3f vector3f::operator+(vector3f rightVec)const {
	return vector3f(*this) += rightVec;
}

vector3f vector3f::operator-(vector3f rightVec) const {
	return vector3f(*this) -= rightVec;
}

vector3f vector3f::operator*(float scalar) const {
	return vector3f(*this) *= scalar;
}

vector3f vector3f::operator/(float scalar) const {
	return vector3f(*this) /= scalar;
}

vector3f& vector3f::operator+=(vector3f rightVec) {
	x += rightVec.x;
	y += rightVec.y;
	z += rightVec.z;
	return *this;
}

vector3f& vector3f::operator-=(vector3f rightVec) {
	x -= rightVec.x;
	y -= rightVec.y;
	z -= rightVec.z;
	return *this;
}

vector3f& vector3f::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

vector3f& vector3f::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

vector3f& vector3f::operator=(vector3f rightVec) {
	x = rightVec.x;
	y = rightVec.y;
	z = rightVec.z;
	return *this;
}

bool vector3f::operator==(const vector3f & rightVec) const {
	return (x == rightVec.x &&
		y == rightVec.y &&
		z == rightVec.z);
}

bool vector3f::operator!=(const vector3f & rightVec) const {
	return !operator==(rightVec);
}