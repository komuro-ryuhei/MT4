#include "MyMath.h"
#include <Novice.h>

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

		///
		/// ↓更新処理ここから
		///

		Vector3 axis = Normalize({1.0f, 1.0f, 1.0f});
		float angle = 0.44f;
		Matrix4x4 rotateMatrix = MakeRotateAxisAngle(axis, angle);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, rotateMatrix);

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
