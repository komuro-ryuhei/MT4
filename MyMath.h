#pragma once
#include "Matrix.h"
#include "Vector.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <assert.h>
#include <cmath>
#include <algorithm>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct Quaternion {
	float x, y, z, w;
};

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w}; }

Quaternion operator*(float scalar, const Quaternion& quaternion) { return {scalar * quaternion.x, scalar * quaternion.y, scalar * quaternion.z, scalar * quaternion.w}; }

// スカラー積 (Quaternion * float)
Quaternion operator*(const Quaternion& quaternion, float scalar) {
	return scalar * quaternion;
}

// 表示(Vector3)
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {

	Novice::ScreenPrintf(x, y, "%3.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%3.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%3.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// 表示(Matrix4x4)
void MatrixScreenPrintf(int x, int y, Matrix4x4 matrix) {
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.03f", matrix.m[row][column]);
		}
	}
}

// 表示(Quaternion)
void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label) {

	Novice::ScreenPrintf(x, y, "%3.2f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%3.2f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%3.2f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%3.2f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, "%s", label);
}

// 　加算(Vector3)
Vector3 Add(const Vector3& v1, const Vector3& v2) { return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }

// 　減算(Vector3)
Vector3 Subtract(const Vector3& v1, const Vector3& v2) { return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }

// 　スカラー倍(Vector3)
Vector3 Multiply(float scalar, const Vector3& v) { return Vector3(scalar * v.x, scalar * v.y, scalar * v.z); }

// 内積(Vector3)
float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

// 　長さ(ノルム)(Vector3)
float Length(const Vector3& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

// 正規化(Vector3)
Vector3 Normalize(const Vector3& v) {

	float length = Length(v);
	if (length != 0.0f) {
		float invLength = 1.0f / length;
		return Multiply(invLength, v);
	} else {
		return v;
	}
}

// 加算(Matrix4x4)
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

// 減算(Matrix4x4)
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

// 積(Matrix4x4)
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) { return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }

// 逆行列
Matrix4x4 Inverse4x4(Matrix4x4& matrix) {
	Matrix4x4 result = {};

	float a = matrix.m[0][0];
	float b = matrix.m[0][1];
	float c = matrix.m[0][2];
	float d = matrix.m[0][3];
	float e = matrix.m[1][0];
	float f = matrix.m[1][1];
	float g = matrix.m[1][2];
	float h = matrix.m[1][3];
	float i = matrix.m[2][0];
	float j = matrix.m[2][1];
	float k = matrix.m[2][2];
	float l = matrix.m[2][3];
	float m = matrix.m[3][0];
	float n = matrix.m[3][1];
	float o = matrix.m[3][2];
	float p = matrix.m[3][3];

	float det = a * (f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n)) - b * (e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m)) +
	            c * (e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m)) - d * (e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m));

	if (det == 0.0f) {
		return result;
	}

	float invDet = 1.0f / det;

	result.m[0][0] =
	    invDet * (matrix.m[1][1] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[1][2] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) +
	              matrix.m[1][3] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]));

	result.m[0][1] =
	    invDet * (-(matrix.m[0][1] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) +
	                matrix.m[0][3] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1])));

	result.m[0][2] =
	    invDet * (matrix.m[0][1] * (matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][1]) +
	              matrix.m[0][3] * (matrix.m[1][1] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][1]));

	result.m[0][3] =
	    invDet * (-(matrix.m[0][1] * (matrix.m[1][2] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][2]) - matrix.m[0][2] * (matrix.m[1][1] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][1]) +
	                matrix.m[0][3] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1])));

	result.m[1][0] =
	    invDet * (-(matrix.m[1][0] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[1][2] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
	                matrix.m[1][3] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0])));

	result.m[1][1] =
	    invDet * (matrix.m[0][0] * (matrix.m[2][2] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
	              matrix.m[0][3] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]));

	result.m[1][2] =
	    invDet * (-(matrix.m[0][0] * (matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][2]) - matrix.m[0][2] * (matrix.m[1][0] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][0]) +
	                matrix.m[0][3] * (matrix.m[1][0] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][0])));

	result.m[1][3] =
	    invDet * (matrix.m[0][0] * (matrix.m[1][2] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][2]) - matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][0]) +
	              matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]));

	result.m[2][0] =
	    invDet * (matrix.m[1][0] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) - matrix.m[1][1] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
	              matrix.m[1][3] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0]));

	result.m[2][1] =
	    invDet * (-(matrix.m[0][0] * (matrix.m[2][1] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][1]) - matrix.m[0][1] * (matrix.m[2][0] * matrix.m[3][3] - matrix.m[2][3] * matrix.m[3][0]) +
	                matrix.m[0][3] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0])));

	result.m[2][2] =
	    invDet * (matrix.m[0][0] * (matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][1]) - matrix.m[0][1] * (matrix.m[1][0] * matrix.m[3][3] - matrix.m[1][3] * matrix.m[3][0]) +
	              matrix.m[0][3] * (matrix.m[1][0] * matrix.m[3][1] - matrix.m[1][1] * matrix.m[3][0]));

	result.m[2][3] =
	    invDet * (-(matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][1]) - matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][3] - matrix.m[1][3] * matrix.m[2][0]) +
	                matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0])));

	result.m[3][0] =
	    invDet * (-(matrix.m[1][0] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]) - matrix.m[1][1] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]) +
	                matrix.m[1][2] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0])));

	result.m[3][1] =
	    invDet * (matrix.m[0][0] * (matrix.m[2][1] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][1]) - matrix.m[0][1] * (matrix.m[2][0] * matrix.m[3][2] - matrix.m[2][2] * matrix.m[3][0]) +
	              matrix.m[0][2] * (matrix.m[2][0] * matrix.m[3][1] - matrix.m[2][1] * matrix.m[3][0]));

	result.m[3][2] =
	    invDet * (-(matrix.m[0][0] * (matrix.m[1][1] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][1]) - matrix.m[0][1] * (matrix.m[1][0] * matrix.m[3][2] - matrix.m[1][2] * matrix.m[3][0]) +
	                matrix.m[0][2] * (matrix.m[1][0] * matrix.m[3][1] - matrix.m[1][1] * matrix.m[3][0])));

	result.m[3][3] =
	    invDet * (matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) - matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) +
	              matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]));

	return result;
}

// 転置行列
Matrix4x4 Transpose4x4(Matrix4x4& matrix) {
	Matrix4x4 result;

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			result.m[row][column] = matrix.m[column][row];
		}
	}
	return result;
}

// 単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 identity;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			identity.m[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
	return identity;
}

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 translateMatrix;

	translateMatrix.m[0][0] = 1.0f;
	translateMatrix.m[0][1] = 0.0f;
	translateMatrix.m[0][2] = 0.0f;
	translateMatrix.m[0][3] = 0.0f;

	translateMatrix.m[1][0] = 0.0f;
	translateMatrix.m[1][1] = 1.0f;
	translateMatrix.m[1][2] = 0.0f;
	translateMatrix.m[1][3] = 0.0f;

	translateMatrix.m[2][0] = 0.0f;
	translateMatrix.m[2][1] = 0.0f;
	translateMatrix.m[2][2] = 1.0f;
	translateMatrix.m[2][3] = 0.0f;

	translateMatrix.m[3][0] = translate.x;
	translateMatrix.m[3][1] = translate.y;
	translateMatrix.m[3][2] = translate.z;
	translateMatrix.m[3][3] = 1.0f;

	return translateMatrix;
}

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 scaleMatrix;

	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[0][1] = 0.0f;
	scaleMatrix.m[0][2] = 0.0f;
	scaleMatrix.m[0][3] = 0.0f;

	scaleMatrix.m[1][0] = 0.0f;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[1][2] = 0.0f;
	scaleMatrix.m[1][3] = 0.0f;

	scaleMatrix.m[2][0] = 0.0f;
	scaleMatrix.m[2][1] = 0.0f;
	scaleMatrix.m[2][2] = scale.z;
	scaleMatrix.m[2][3] = 0.0f;

	scaleMatrix.m[3][0] = 0.0f;
	scaleMatrix.m[3][1] = 0.0f;
	scaleMatrix.m[3][2] = 0.0f;
	scaleMatrix.m[3][3] = 1.0f;

	return scaleMatrix;
}

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = 1.0f;
	rotationMatrix.m[0][1] = 0.0f;
	rotationMatrix.m[0][2] = 0.0f;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = 0.0f;
	rotationMatrix.m[1][1] = std::cos(radian);
	rotationMatrix.m[1][2] = std::sin(radian);
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = 0.0f;
	rotationMatrix.m[2][1] = -std::sin(radian);
	rotationMatrix.m[2][2] = std::cos(radian);
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = std::cos(radian);
	rotationMatrix.m[0][1] = 0.0f;
	rotationMatrix.m[0][2] = -std::sin(radian);
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = 0.0f;
	rotationMatrix.m[1][1] = 1.0f;
	rotationMatrix.m[1][2] = 0.0f;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = std::sin(radian);
	rotationMatrix.m[2][1] = 0.0f;
	rotationMatrix.m[2][2] = std::cos(radian);
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = std::cos(radian);
	rotationMatrix.m[0][1] = std::sin(radian);
	rotationMatrix.m[0][2] = 0.0f;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = -std::sin(radian);
	rotationMatrix.m[1][1] = std::cos(radian);
	rotationMatrix.m[1][2] = 0.0f;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = 0.0f;
	rotationMatrix.m[2][1] = 0.0f;
	rotationMatrix.m[2][2] = 1.0f;
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate) {
	Matrix4x4 affineMatrix;

	// 各変換行列を作成
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	// 各変換行列を合成してアフィン変換行列を作成
	affineMatrix = Multiply(scaleMatrix, Multiply(rotateXYZMatrix, translateMatrix));

	return affineMatrix;
}

// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {

	Matrix4x4 perspectiveFoVMatrix;

	perspectiveFoVMatrix.m[0][0] = 1.0f / (aspectRatio * std::tan(fovY / 2));
	;
	perspectiveFoVMatrix.m[0][1] = 0.0f;
	perspectiveFoVMatrix.m[0][2] = 0.0f;
	perspectiveFoVMatrix.m[0][3] = 0.0f;

	perspectiveFoVMatrix.m[1][0] = 0.0f;
	perspectiveFoVMatrix.m[1][1] = 1.0f / (std::tan(fovY / 2));
	perspectiveFoVMatrix.m[1][2] = 0.0f;
	perspectiveFoVMatrix.m[1][3] = 0.0f;

	perspectiveFoVMatrix.m[2][0] = 0.0f;
	perspectiveFoVMatrix.m[2][1] = 0.0f;
	perspectiveFoVMatrix.m[2][2] = farClip / (farClip - nearClip);
	perspectiveFoVMatrix.m[2][3] = 1.0f;

	perspectiveFoVMatrix.m[3][0] = 0.0f;
	perspectiveFoVMatrix.m[3][1] = 0.0f;
	perspectiveFoVMatrix.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	perspectiveFoVMatrix.m[3][3] = 0.0f;

	return perspectiveFoVMatrix;
}

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {

	Matrix4x4 orthographicMatrix;

	orthographicMatrix.m[0][0] = 2.0f / (right - left);
	orthographicMatrix.m[0][1] = 0.0f;
	orthographicMatrix.m[0][2] = 0.0f;
	orthographicMatrix.m[0][3] = 0.0f;

	orthographicMatrix.m[1][0] = 0.0f;
	orthographicMatrix.m[1][1] = 2.0f / (top - bottom);
	orthographicMatrix.m[1][2] = 0.0f;
	orthographicMatrix.m[1][3] = 0.0f;

	orthographicMatrix.m[2][0] = 0.0f;
	orthographicMatrix.m[2][1] = 0.0f;
	orthographicMatrix.m[2][2] = 1.0f / (farClip - nearClip);
	orthographicMatrix.m[2][3] = 0.0f;

	orthographicMatrix.m[3][0] = (left + right) / (left - right);
	orthographicMatrix.m[3][1] = (top + bottom) / (bottom - top);
	orthographicMatrix.m[3][2] = nearClip / (nearClip - farClip);
	orthographicMatrix.m[3][3] = 1.0f;

	return orthographicMatrix;
}

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {

	Matrix4x4 viewportMatrix;

	viewportMatrix.m[0][0] = width / 2.0f;
	viewportMatrix.m[0][1] = 0.0f;
	viewportMatrix.m[0][2] = 0.0f;
	viewportMatrix.m[0][3] = 0.0f;

	viewportMatrix.m[1][0] = 0.0f;
	viewportMatrix.m[1][1] = -height / 2.0f;
	viewportMatrix.m[1][2] = 0.0f;
	viewportMatrix.m[1][3] = 0.0f;

	viewportMatrix.m[2][0] = 0.0f;
	viewportMatrix.m[2][1] = 0.0f;
	viewportMatrix.m[2][2] = maxDepth - minDepth;
	viewportMatrix.m[2][3] = 0.0f;

	viewportMatrix.m[3][0] = left + width / 2.0f;
	viewportMatrix.m[3][1] = top + height / 2.0f;
	viewportMatrix.m[3][2] = minDepth;
	viewportMatrix.m[3][3] = 1.0f;

	return viewportMatrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// MT4からの新しい関数

/////////////////////////////////////////////////////////////////////////////////////////////////////////


Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {
	// 回転軸を正規化
	Vector3 normalizedAxis = Normalize(axis);

	// 必要な値を計算
	float x = normalizedAxis.x;
	float y = normalizedAxis.y;
	float z = normalizedAxis.z;
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);

	// 回転行列を構築
	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = cosTheta + x * x * (1.0f - cosTheta);
	rotationMatrix.m[0][1] = x * y * (1.0f - cosTheta) + z * sinTheta;
	rotationMatrix.m[0][2] = x * z * (1.0f - cosTheta) - y * sinTheta;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = y * x * (1.0f - cosTheta) - z * sinTheta;
	rotationMatrix.m[1][1] = cosTheta + y * y * (1.0f - cosTheta);
	rotationMatrix.m[1][2] = y * z * (1.0f - cosTheta) + x * sinTheta;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = z * x * (1.0f - cosTheta) + y * sinTheta;
	rotationMatrix.m[2][1] = z * y * (1.0f - cosTheta) - x * sinTheta;
	rotationMatrix.m[2][2] = cosTheta + z * z * (1.0f - cosTheta);
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}

// ベクトルの長さを計算
Vector3 Perpendicular(const Vector3& v) {
	// 垂直なベクトルを生成するための基準ベクトル
	Vector3 reference = (std::fabs(v.x) > std::fabs(v.z)) ? Vector3(0, 0, 1) : Vector3(1, 0, 0);

	// 外積を計算して垂直なベクトルを取得
	return Cross(v, reference);
}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {
	// 入力ベクトルを正規化
	Vector3 fromNormalized = Normalize(from);
	Vector3 toNormalized = Normalize(to);

	// 回転軸を計算
	Vector3 axis = Cross(fromNormalized, toNormalized);
	float axisLength = Length(axis);

	// 方向が逆（180度回転）の場合
	if (axisLength == 0.0f) {
		if (Dot(fromNormalized, toNormalized) < 0.0f) {
			// 180度回転の場合、適当な垂直軸を選ぶ
			axis = Normalize(Perpendicular(fromNormalized));
		} else {
			// 同じ方向の場合、単位行列を返す
			return MakeIdentity4x4();
		}
	}

	// 回転軸を正規化
	axis = Normalize(axis);

	// ベクトル間の角度を計算
	float angle = acosf(std::clamp(Dot(fromNormalized, toNormalized), -1.0f, 1.0f));

	// 回転行列を生成
	return MakeRotateAxisAngle(axis, angle);
}

// クォータニオンの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {
	return {
	    lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y, lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x, lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w,
	    lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z};
}

// 単位クォータニオン
Quaternion IdentityQuaternion() { return {0.0f, 0.0f, 0.0f, 1.0f}; }

// 共役
Quaternion Conjugate(const Quaternion& quaternion) { return {-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w}; }

// ノルム
float Norm(const Quaternion& quaternion) { return sqrtf(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w); }

// 正規化
Quaternion Normalize(const Quaternion& quaternion) {
	float norm = Norm(quaternion);
	if (norm == 0.0f)
		return quaternion;
	return {quaternion.x / norm, quaternion.y / norm, quaternion.z / norm, quaternion.w / norm};
}

// 逆
Quaternion Inverse(const Quaternion& quaternion) {
	float normSq = Norm(quaternion) * Norm(quaternion);
	if (normSq == 0.0f)
		return quaternion;
	Quaternion conjugate = Conjugate(quaternion);
	return {conjugate.x / normSq, conjugate.y / normSq, conjugate.z / normSq, conjugate.w / normSq};
}

// 任意軸回転を表すQuaternionを生成
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {
	Vector3 normalizedAxis = Normalize(axis);
	float sinHalfAngle = sinf(angle / 2.0f);
	float cosHalfAngle = cosf(angle / 2.0f);

	return {normalizedAxis.x * sinHalfAngle, normalizedAxis.y * sinHalfAngle, normalizedAxis.z * sinHalfAngle, cosHalfAngle};
}

// クォータニオンを使ってベクトルを回転
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {
	Quaternion vectorQuat = {vector.x, vector.y, vector.z, 0.0f};
	Quaternion conjugate = Conjugate(quaternion);
	Quaternion rotatedQuat = Multiply(Multiply(quaternion, vectorQuat), conjugate);
	return {rotatedQuat.x, rotatedQuat.y, rotatedQuat.z};
}

// クォータニオンから回転行列を作成
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {
	Quaternion normalized = Normalize(quaternion);
	float x = normalized.x;
	float y = normalized.y;
	float z = normalized.z;
	float w = normalized.w;

	Matrix4x4 rotationMatrix = {};

	rotationMatrix.m[0][0] = 1.0f - 2.0f * (y * y + z * z);
	rotationMatrix.m[0][1] = 2.0f * (x * y + z * w);
	rotationMatrix.m[0][2] = 2.0f * (x * z - y * w);
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = 2.0f * (x * y - z * w);
	rotationMatrix.m[1][1] = 1.0f - 2.0f * (x * x + z * z);
	rotationMatrix.m[1][2] = 2.0f * (y * z + x * w);
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = 2.0f * (x * z + y * w);
	rotationMatrix.m[2][1] = 2.0f * (y * z - x * w);
	rotationMatrix.m[2][2] = 1.0f - 2.0f * (x * x + y * y);
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	return rotationMatrix;
}
