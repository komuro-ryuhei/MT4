#include "MyMath.h"
#include <Novice.h>

#include <algorithm>
#include <iostream>

const char kWindowTitle[] = "コムロ_リュウヘイ";

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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 from0 = Normalize(Vector3{1.0f, 0.7f, 0.5f});
	Vector3 to0 = -from0;
	Vector3 from1 = Normalize(Vector3{-0.6f, 0.9f, 0.2f});
	Vector3 to1 = Normalize(Vector3{0.4f, 0.7f, -0.5f});
	Matrix4x4 rotateMatrix0 = DirectionToDirection(Normalize(Vector3{1.0f, 0.0f, 0.0f}), Normalize(Vector3{-1.0f, 0.0f, 0.0f}));
	Matrix4x4 rotateMatrix1 = DirectionToDirection(from0, to0);
	Matrix4x4 rotateMatrix2 = DirectionToDirection(from1, to1);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, rotateMatrix0);
		MatrixScreenPrintf(0, 100, rotateMatrix1);
		MatrixScreenPrintf(0, 200, rotateMatrix2);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
