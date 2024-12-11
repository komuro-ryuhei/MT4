#pragma once

struct Matrix2x2 final {
	float m[2][2];
};

struct Matrix3x3 final {
	float m[3][3];
};

struct Matrix4x4 final {
	float m[4][4];

	// *= 演算子の定義
	Matrix4x4& operator*=(const Matrix4x4& other) {
		Matrix4x4 result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.m[i][j] = 0;
				for (int k = 0; k < 4; ++k) {
					result.m[i][j] += m[i][k] * other.m[k][j];
				}
			}
		}
		*this = result;
		return *this;
	}
};