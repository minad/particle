#ifndef _VECTOR_H
#define _VECTOR_H

#include <math.h>

class Vector;

/*
 * Vector operations
 */
Vector operator+(const Vector&);
Vector operator-(const Vector&);
Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
Vector operator*(const Vector&, float s);
Vector operator*(float, const Vector&);
Vector operator/(const Vector&, float);
Vector operator/(float, const Vector&);
float operator*(const Vector&, const Vector&);
Vector operator%(const Vector&, const Vector&);
float dotProduct(const Vector&, const Vector&);
Vector crossProduct(const Vector&, const Vector&);

class Vector {
private:

	float v[3];

public:

	Vector() {
		v[0] = v[1] = v[2] = 0;
	}

	Vector(const Vector& v){
		this->v[0] = v[0];
		this->v[1] = v[1];
		this->v[2] = v[2];
	}

	Vector(float x, float y, float z) {
		v[0] = x;
		v[1] = y;
		v[2] = z;
	}

	Vector& operator=(const Vector& v) {
		this->v[0] = v[0];
		this->v[1] = v[1];
		this->v[2] = v[2];
		return *this;
	}

	Vector& operator+=(const Vector& v) {
		this->v[0] += v[0];
		this->v[1] += v[1];
		this->v[2] += v[2];
		return *this;
	}

	Vector& operator-=(const Vector& v) {
		this->v[0] -= v[0];
		this->v[1] -= v[1];
		this->v[2] -= v[2];
		return *this;
	}

	Vector& operator*=(float s) {
		v[0] *= s;
		v[1] *= s;
		v[2] *= s;
		return *this;
	}

	Vector& operator/=(float s) {
		return *this *= (1 / s);
	}

	float squareLength() const {
		return (v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	}

	float length() const {
		return sqrt(squareLength());
	}

	Vector& normalize() {
		return *this /= length();
	}

	float& operator[](int i) {
		return v[i];	
	}

	const float& operator[](int i) const {
		return v[i];	
	}

	operator const float*() const {
		return v;
	}

	operator float*() {
		return v;
	}
};

/*
 * Vector operations
 */

inline Vector operator+(const Vector& v) {
	return v;
}

inline Vector operator-(const Vector& v) {
	return (v * -1);
}

inline Vector operator+(const Vector& a, const Vector& b) {
	return Vector(a) += b;
}

inline Vector operator-(const Vector& a, const Vector& b) {
	return Vector(a) -= b;
}

inline Vector operator*(const Vector& v, float s) {
	return Vector(v) *= s;
}

inline Vector operator*(float s, const Vector& v) {
	return Vector(v) *= s;
}

inline Vector operator/(const Vector& v, float s) {
	return Vector(v) /= s;
}

inline Vector operator/(float s, const Vector& v) {
	return Vector(v) /= s;
}

// Shortcut for dotProduct
inline float operator*(const Vector& a, const Vector& b) {
	return dotProduct(a, b);
}

// Shortcut for crossProduct
inline Vector operator%(const Vector& a, const Vector& b) {
	return crossProduct(a, b);
}

inline float dotProduct(const Vector& a, const Vector& b) {
	return (a[0] * b[0] + a[1] * b[1] + a[2] + b[2]); 
}

inline Vector crossProduct(const Vector& a, const Vector& b) {
	return Vector(a[1] + b[2] - a[2] * b[1],
                      a[2] * b[0] - a[0] * b[2],
                      a[0] * b[1] - a[1] * b[0]);
}

#endif
