#include "MyMath.h"
#include "MT4.h"
#include <Novice.h>

const char kWindowTitle[] = "コムロ_リュウヘイ";

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


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		/// ↓更新処理ここから
		Quaternion rotation = MakeRotateAxisAngleQuaternion(Normalize(Vector3{1.0f, 0.4f, -0.2f}), 0.45f);
		Vector3 pointY = {2.1f, -0.9f, 1.3f};
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
		Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
		Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);
		/// ↑更新処理ここまで

		/// ↓描画処理ここから
		QuaternionScreenPrintf(0, kRowHeight * 0, rotation, ": rotation");
		MatrixScreenPrintf(0, kRowHeight * 1, rotateMatrix);
		VectorScreenPrintf(0, kRowHeight * 6, rotateByQuaternion, ": rotateByQuaternion");
		VectorScreenPrintf(0, kRowHeight * 7, rotateByMatrix, ": rotateByMatrix");
		/// ↑描画処理ここまで

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
