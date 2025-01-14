#include "MyMath.h"
#include <Novice.h>

const char kWindowTitle[] = "コムロ_リュウヘイ";

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t) {
	// クォータニオンの内積を計算
	float dot = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;

	// 内積が負の場合、反対方向のクォータニオンを利用
	Quaternion q1Adjusted = q1;
	if (dot < 0.0f) {
		dot = -dot;
		q1Adjusted = {-q1.x, -q1.y, -q1.z, -q1.w};
	}

	// 補間用のスケール
	float scale0, scale1;

	// 極小値の閾値
	const float EPSILON = 0.0001f;

	// 内積が1に非常に近い場合、線形補間を使用
	if (1.0f - dot < EPSILON) {
		scale0 = 1.0f - t;
		scale1 = t;
	} else {
		// θを計算
		float theta = acosf(dot);
		float sinTheta = sinf(theta);

		// スケール係数を計算
		scale0 = sinf((1.0f - t) * theta) / sinTheta;
		scale1 = sinf(t * theta) / sinTheta;
	}

	// 補間結果を計算
	return {scale0 * q0.x + scale1 * q1Adjusted.x, scale0 * q0.y + scale1 * q1Adjusted.y, scale0 * q0.z + scale1 * q1Adjusted.z, scale0 * q0.w + scale1 * q1Adjusted.w};
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
		// クォータニオンの初期設定
		Quaternion rotation0 = MakeRotateAxisAngleQuaternion({0.71f, 0.71f, 0.0f}, 0.3f);
		Quaternion rotation1 = {-rotation0.x, -rotation0.y, -rotation0.z, -rotation0.w};

		Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0, 0, interpolate0, "interpolate0");
		QuaternionScreenPrintf(0, 20, interpolate1, "interpolate1");
		QuaternionScreenPrintf(0, 40, interpolate2, "interpolate2");
		QuaternionScreenPrintf(0, 60, interpolate3, "interpolate3");
		QuaternionScreenPrintf(0, 80, interpolate4, "interpolate4");

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
