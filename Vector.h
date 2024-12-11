#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;
};

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	// + 演算子のオーバーロード
	Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }

	// - 演算子のオーバーロード
	Vector3 operator-(const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }

	// + オペレーターのオーバーロード
	Vector3& operator+(const float& other) {
		x = x + other;
		y = y + other;
		z = z + other;
		return *this;
	}

	// + オペレーターのオーバーロード
	Vector3& operator+=(const float& other) {
		x = x += other;
		y = y += other;
		z = z += other;
		return *this;
	}

	// += オペレーターのオーバーロード
	Vector3& operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	// *= オペレーターのオーバーロード (スカラ倍)
	Vector3& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector3 と float の掛け算のオペレーター
	Vector3 operator*(float scalar) { return Vector3{x * scalar, y * scalar, z * scalar}; }
};

/// <summary>
/// 4次元ベクトル
/// </summary>
struct Vector4 final {
	float x;
	float y;
	float z;
	float w;
};