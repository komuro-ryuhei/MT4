#pragma once

#include "MyMath.h"

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