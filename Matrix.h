#ifndef _MATRIX_H
#define _MATRIX_H

#include "Vector.h"

class Matrix;

/*
 * Vector transformation
 */
Vector& operator*=(Vector&, const Matrix&);
Vector operator*(const Matrix&, const Vector&);
Vector operator*(const Vector&, const Matrix&);

/*
 * Matrix operations
 */
Matrix operator+(const Matrix&);
Matrix operator-(const Matrix&);
Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, float);
Matrix operator*(float, const Matrix&);
Matrix operator/(const Matrix&, float);

/*
 * Special matrix operations
 */
Matrix rotate(const Matrix&, float, float, float, float);
Matrix rotate(const Matrix&, float, const Vector&);
Matrix rotateX(const Matrix&, float);
Matrix rotateY(const Matrix&, float);
Matrix rotateZ(const Matrix&, float);
Matrix translate(const Matrix&, float, float, float);
Matrix translate(const Matrix&, const Vector&);
Matrix scale(const Matrix&, float, float, float);
Matrix scale(const Matrix&, const Vector&);
Matrix transpose(const Matrix&);

/*
 * Special matrices
 */
Matrix rotationMatrix(float, float, float, float);
Matrix rotationMatrix(float, const Vector& v);
Matrix translationMatrix(float, float, float);
Matrix translationMatrix(const Vector&);
Matrix scalingMatrix(float, float, float);
Matrix scalingMatrix(const Vector&);
Matrix frustumMatrix(float, float, float, float, float, float);
Matrix perspectiveMatrix(float, float, float, float, float, float);

// Macros to access matrix elements
#define M11 m[0]
#define M21 m[1]
#define M31 m[2]
#define M41 m[3]
#define M12 m[4]
#define M22 m[5]
#define M32 m[6]
#define M42 m[7]
#define M13 m[8]
#define M23 m[9]
#define M33 m[10]
#define M43 m[11]
#define M14 m[12]
#define M24 m[13]
#define M34 m[14]
#define M44 m[15]

class Matrix {
private:

	/*
         * The elements are in column order in the memory!!!
         * Use the Mxx Macros to access the elements!
         */
	float m[16];

public:

	Matrix() {
		M11 = M22 = M33 = M44 = 1;
		M12 = M13 = M14 =
		M21 = M23 = M24 =
		M31 = M32 = M34 =
		M41 = M42 = M43 = 0;
	}

	Matrix(float m11, float m12, float m13, float m14,
               float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34,
               float m41, float m42, float m43, float m44) {
		M11 = m11; M12 = m12; M13 = m13; M14 = m14;
		M21 = m21; M22 = m22; M23 = m23; M24 = m24;
		M31 = m31; M32 = m32; M33 = m33; M34 = m34;
		M41 = m41; M42 = m42; M43 = m43; M44 = m44;
	}

	Matrix(const Matrix& M) {
		M11 = M.M11; M12 = M.M12; M13 = M.M13; M14 = M.M14;
		M21 = M.M21; M22 = M.M22; M23 = M.M23; M24 = M.M24;
		M31 = M.M31; M32 = M.M32; M33 = M.M33; M34 = M.M34;
		M41 = M.M41; M42 = M.M42; M43 = M.M43; M44 = M.M44;
	}

	Matrix& operator=(const Matrix& M) {
		M11 = M.M11; M12 = M.M12; M13 = M.M13; M14 = M.M14;
		M21 = M.M21; M22 = M.M22; M23 = M.M23; M24 = M.M24;
		M31 = M.M31; M32 = M.M32; M33 = M.M33; M34 = M.M34;
		M41 = M.M41; M42 = M.M42; M43 = M.M43; M44 = M.M44;
		return *this;
	}

	Matrix& operator+=(const Matrix& M) {
		M11 += M.M11; M12 += M.M12; M13 += M.M13; M14 += M.M14;
		M21 += M.M21; M22 += M.M22; M23 += M.M23; M24 += M.M24;
		M31 += M.M31; M32 += M.M32; M33 += M.M33; M34 += M.M34;
		M41 += M.M41; M42 += M.M42; M43 += M.M43; M44 += M.M44;
		return *this;
	}

	Matrix& operator-=(const Matrix& M) {
		M11 -= M.M11; M12 -= M.M12; M13 -= M.M13; M14 -= M.M14;
		M21 -= M.M21; M22 -= M.M22; M23 -= M.M23; M24 -= M.M24;
		M31 -= M.M31; M32 -= M.M32; M33 -= M.M33; M34 -= M.M34;
		M41 -= M.M41; M42 -= M.M42; M43 -= M.M43; M44 -= M.M44;
		return *this;
	}

	Matrix& operator*=(float s) {
		M11 *= s; M12 *= s; M13 *= s; M14 *= s;
		M21 *= s; M22 *= s; M23 *= s; M24 *= s;
		M31 *= s; M32 *= s; M33 *= s; M34 *= s;
		M41 *= s; M42 *= s; M43 *= s; M44 *= s;
		return *this;
	}

	Matrix& operator*=(const Matrix& M) {
                float m1 = M11, m2 = M12, m3 = M13;
		M11 = m1 * M.M11 + m2 * M.M21 + m3 * M.M31 + M14 * M.M41;
		M12 = m1 * M.M12 + m2 * M.M22 + m3 * M.M32 + M14 * M.M42;
		M13 = m1 * M.M13 + m2 * M.M23 + m3 * M.M33 + M14 * M.M43;
		M14 = m1 * M.M14 + m2 * M.M24 + m3 * M.M34 + M14 * M.M44;
		
		m1 = M21, m2 = M22, m3 = M23;
		M21 = m1 * M.M11 + m2 * M.M21 + m3 * M.M31 + M24 * M.M41;
		M22 = m1 * M.M12 + m2 * M.M22 + m3 * M.M32 + M24 * M.M42;
		M23 = m1 * M.M13 + m2 * M.M23 + m3 * M.M33 + M24 * M.M43;
		M24 = m1 * M.M14 + m2 * M.M24 + m3 * M.M34 + M24 * M.M44;

		m1 = M31, m2 = M32, m3 = M33;
		M31 = m1 * M.M11 + m2 * M.M21 + m3 * M.M31 + M34 * M.M41;
		M32 = m1 * M.M12 + m2 * M.M22 + m3 * M.M32 + M34 * M.M42;
		M33 = m1 * M.M13 + m2 * M.M23 + m3 * M.M33 + M34 * M.M43;
		M34 = m1 * M.M14 + m2 * M.M24 + m3 * M.M34 + M34 * M.M44;

		m1 = M41, m2 = M42, m3 = M43;
		M41 = m1 * M.M11 + m2 * M.M21 + m3 * M.M31 + M44 * M.M41;
		M42 = m1 * M.M12 + m2 * M.M22 + m3 * M.M32 + M44 * M.M42;
		M43 = m1 * M.M13 + m2 * M.M23 + m3 * M.M33 + M44 * M.M43;
		M44 = m1 * M.M14 + m2 * M.M24 + m3 * M.M34 + M44 * M.M44;
		return *this;
	}

	Matrix& operator/=(float s) {
		return (*this *= 1 / s);
	}

	float& operator()(int y, int x) {
		return m[y + (x << 2)];
	}

	const float& operator()(int y, int x) const {
		return m[y + (x << 2)];
	}

	operator float*() {
		return m;
	}

	operator const float*() const {
		return m;
	}

	Matrix& translate(float x, float y, float z) {
		M14 += x;
		M24 += y;
		M34 += z;
		return *this;
	}

	Matrix& translate(const Vector& v) {
		return translate(v[0], v[1], v[2]);
	}

	Matrix& scale(float x, float y, float z) {
		M11 *= x; M12 *= x; M13 *= x;
		M21 *= y; M22 *= y; M23 *= y;
		M31 *= z; M32 *= z; M33 *= z;
		return *this;
	}

	Matrix& scale(const Vector& v) {
		return scale(v[0], v[1], v[2]);
	}

	Matrix& rotate(float a, float x, float y, float z) {
		return *this *= rotationMatrix(a, x, y, z);
	}

	Matrix& rotate(float a, const Vector& v) {
		return rotate(a, v[0], v[1], v[2]);
	}

	Matrix& rotateX(float a) {
		float s = sin(a);
		float c = cos(a);

		float tmp = M12;
		M12 =  c * M12 + s * M13;
		M13 = -s * tmp + c * M13;

                tmp = M22;
		M22 =  c * M22 + s * M23;
		M23 = -s * tmp + c * M23;

                tmp = M32;
		M32 =  c * M32 + s * M33;
		M33 = -s * tmp + c * M33;

                tmp = M42;
		M42 =  c * M42 + s * M43;
		M43 = -s * tmp + c * M43;
		return *this;
	}

	Matrix& rotateY(float a) {
		float s = sin(a);
		float c = cos(a);

		float tmp = M11;
		M11 = c * M11 + -s * M13;
		M13 = s * tmp +  c * M13;

                tmp = M21;
		M21 = c * M21 + -s * M23;
		M23 = s * tmp +  c * M23;

                tmp = M31;
		M31 = c * M31 + -s * M33;
		M33 = s * tmp +  c * M33;

                tmp = M41;
		M41 = c * M41 + -s * M43;
		M43 = s * tmp +  c * M43;
		return *this;
	}

	Matrix& rotateZ(float a) {
		float s = sin(a);
		float c = cos(a);

		float tmp = M11;
		M11 = c * M11 + -s * M12;
		M12 = s * tmp +  c * M12;

                tmp = M21;
		M21 = c * M21 + -s * M22;
		M22 = s * tmp +  c * M22;

                tmp = M31;
		M31 = c * M31 + -s * M32;
		M32 = s * tmp +  c * M32;

                tmp = M41;
		M41 = c * M41 + -s * M42;
		M42 = s * tmp +  c * M42;
		return *this;
	}

	Matrix& transpose() {
		float t;
#define SWAP(x,y) t = x; x = y; y = t;
		SWAP(M12, M21);
		SWAP(M13, M31);
		SWAP(M14, M41);
		SWAP(M23, M32);
		SWAP(M24, M42);
		SWAP(M34, M43);
#undef SWAP
		return *this;
	}

	static const Matrix IDENTITY;
};

#undef M00
#undef M01
#undef M02
#undef M14
#undef M10
#undef M11
#undef M12
#undef M24
#undef M20
#undef M21
#undef M22
#undef M34
#undef M30
#undef M31
#undef M32
#undef M44

const Matrix Matrix::IDENTITY;

/*
 * Vector transformation
 */
inline Vector& operator*=(Vector& v, const Matrix& m) {
	float x = v[0], y = v[1];
	v[0] = x * m(0,0) + y * m(0,1) + v[2] * m(0,2) + m(0,3);
	v[1] = x * m(1,0) + y * m(1,1) + v[2] * m(1,2) + m(1,3);
	v[2] = x * m(2,0) + y * m(2,1) + v[2] * m(2,2) + m(2,3);
	return v;
}

inline Vector operator*(const Matrix& m, const Vector& v) {
	return Vector(v[0] * m(0,0) + v[1] * m(0,1) + v[2] * m(0,2) + m(0,3),
		      v[0] * m(1,0) + v[1] * m(1,1) + v[2] * m(1,2) + m(1,3),
	              v[0] * m(2,0) + v[1] * m(2,1) + v[2] * m(2,2) + m(2,3));
}

inline Vector operator*(const Vector& v, const Matrix& m) {
	return m * v;
}

/*
 * Matrix operations
 */

inline Matrix operator+(const Matrix& m) {
	return m;
}

inline Matrix operator-(const Matrix& m) {
	return (m * -1);
}

inline Matrix operator+(const Matrix& a, const Matrix& b) {
	return Matrix(a) += b;
}

inline Matrix operator-(const Matrix& a, const Matrix& b) {
	return Matrix(a) -= b;
}

inline Matrix operator*(const Matrix& a, const Matrix& b) {
	return Matrix(
	a(0,0) * b(0,0) + a(0,1) * b(1,0) + a(0,2) * b(2,0) + a(0,3) * b(3,0),
	a(0,0) * b(0,1) + a(0,1) * b(1,1) + a(0,2) * b(2,1) + a(0,3) * b(3,1),
	a(0,0) * b(0,2) + a(0,1) * b(1,2) + a(0,2) * b(2,2) + a(0,3) * b(3,2),
	a(0,0) * b(0,3) + a(0,1) * b(1,3) + a(0,2) * b(2,3) + a(0,3) * b(3,3),
	a(1,0) * b(0,0) + a(1,1) * b(1,0) + a(1,2) * b(2,0) + a(1,3) * b(3,0),
	a(1,0) * b(0,1) + a(1,1) * b(1,1) + a(1,2) * b(2,1) + a(1,3) * b(3,1),
	a(1,0) * b(0,2) + a(1,1) * b(1,2) + a(1,2) * b(2,2) + a(1,3) * b(3,2),
	a(1,0) * b(0,3) + a(1,1) * b(1,3) + a(1,2) * b(2,3) + a(1,3) * b(3,3),
	a(2,0) * b(0,0) + a(2,1) * b(1,0) + a(2,2) * b(2,0) + a(2,3) * b(3,0),
	a(2,0) * b(0,1) + a(2,1) * b(1,1) + a(2,2) * b(2,1) + a(2,3) * b(3,1),
	a(2,0) * b(0,2) + a(2,1) * b(1,2) + a(2,2) * b(2,2) + a(2,3) * b(3,2),
	a(2,0) * b(0,3) + a(2,1) * b(1,3) + a(2,2) * b(2,3) + a(2,3) * b(3,3),
	a(3,0) * b(0,0) + a(3,1) * b(1,0) + a(3,2) * b(2,0) + a(3,3) * b(3,0),
	a(3,0) * b(0,1) + a(3,1) * b(1,1) + a(3,2) * b(2,1) + a(3,3) * b(3,1),
	a(3,0) * b(0,2) + a(3,1) * b(1,2) + a(3,2) * b(2,2) + a(3,3) * b(3,2),
	a(3,0) * b(0,3) + a(3,1) * b(1,3) + a(3,2) * b(2,3) + a(3,3) * b(3,3));
}

inline Matrix operator*(const Matrix& m, float s) {
	return Matrix(m) *= s;
}

inline Matrix operator*(float s, const Matrix& m) {
	return m * s;
}

inline Matrix operator/(const Matrix& m, float s) {
	return Matrix(m) /= s;
}

/*
 * Special matrix operations
 */

inline Matrix rotate(const Matrix& m, float a, const Vector& v) {
	return Matrix(m).rotate(a, v);
}

inline Matrix rotate(const Matrix& m, float a, float x, float y, float z) {
	return Matrix(m).rotate(a, x, y, z);
}

inline Matrix rotateX(const Matrix& m, float a) {
	return Matrix(m).rotateX(a);
}

inline Matrix rotateY(const Matrix& m, float a) {
	return Matrix(m).rotateY(a);
}

inline Matrix rotateZ(const Matrix& m, float a) {
	return Matrix(m).rotateZ(a);
}

inline Matrix translate(const Matrix& m, float x, float y, float z) {
	return Matrix(m).translate(x, y, z);
}

inline Matrix translate(const Matrix& m, const Vector& v) {
	return Matrix(m).translate(v);
}

inline Matrix scale(const Matrix& m, const Vector& v) {
	return Matrix(m).scale(v);
}

inline Matrix transpose(const Matrix& m) {
	return Matrix(m).transpose();
}

/*
 * Special matrices
 */

inline Matrix rotationMatrix(float a, float x, float y, float z) {
	float s = sin(a);
	float c = cos(a);
	float ic = 1 - c;
	float len = x*x + y*y + z*z;
	if (len != 1) {
		len = 1 / sqrt(len);
		x *= len;
		y *= len;
		z *= len;
	}
	return Matrix(c+ic*x*x,   ic*x*y-s*z, ic*x*z+s*y, 0,
                      ic*x*y+s*z, c+ic*y*y,   ic*y*z-s*x, 0, 
		      ic*x*z-s*y, ic*y*z+s*x, c+ic*z*z,   0,
                      0,          0,          0,          1);
}

inline Matrix rotationMatrix(float a, const Vector& v) {
	return rotationMatrix(a, v[0], v[1], v[2]);
}

inline Matrix translationMatrix(float x, float y, float z) {
	return Matrix(1, 0, 0, x,
                      0, 1, 0, y,
                      0, 0, 1, z,
                      0, 0, 0, 1);
}

inline Matrix translationMatrix(const Vector& v) {
	return translationMatrix(v[0], v[1], v[2]);
}

inline Matrix scalingMatrix(float x, float y, float z) {
	return Matrix(x, 0, 0, 0,
                      0, y, 0, 0,
                      0, 0, z, 0,
                      0, 0, 0, 1);
}

inline Matrix scalingMatrix(const Vector& v) {
	return scalingMatrix(v[0], v[1], v[2]);
}

inline Matrix frustumMatrix(float l, float r, float b, float t, float n, float f) {
	return Matrix(2*n/(r-l), 0,         (r+l)/(r-l), 0,
                      0,         2*n/(t-b), (t+b)/(t-n), 0, 
		      0,         0,         (f+n)/(n-f), 2*f*n/(n-f),
                      0,         0,         -1,          0);
}

inline Matrix perspectiveMatrix(float fovy, float aspect, float n, float f) {
	float t = 1 / tan(fovy / 2);
	return Matrix(t/aspect, 0,   0,           0,
                      0,        t,   0,           0,
                      0,        0,   (f+n)/(n-f), 2*f*n/(n-f),
                      0,        0,   -1,          0);
}

#endif
