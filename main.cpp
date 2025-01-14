#include "MT4.h"
#include "MyMath.h"
#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "コムロ_リュウヘイ";

struct Quaternion {
	float x, y, z, w;
};

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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion q1 = {2.0f, 3.0f, 4.0f, 1.0f};
	Quaternion q2 = {1.0f, 3.0f, 5.0f, 2.0f};

	Quaternion identity = IdentityQuaternion();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion normal = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);

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

		// 結果の表示
		Novice::ScreenPrintf(0, 0, "%.2f %.2f %.2f %.2f : Identity", identity.x, identity.y, identity.z, identity.w);
		Novice::ScreenPrintf(0, 20, "%.2f %.2f %.2f %.2f : Conjugate", conj.x, conj.y, conj.z, conj.w);
		Novice::ScreenPrintf(0, 40, "%.2f %.2f %.2f %.2f : Inverse", inv.x, inv.y, inv.z, inv.w);
		Novice::ScreenPrintf(0, 60, "%.2f %.2f %.2f %.2f : Normalize", normal.x, normal.y, normal.z, normal.w);
		Novice::ScreenPrintf(0, 80, "%.2f %.2f %.2f %.2f : Multiply(q1, q2)", mul1.x, mul1.y, mul1.z, mul1.w);
		Novice::ScreenPrintf(0, 100, "%.2f %.2f %.2f %.2f : Multiply(q2, q1)", mul2.x, mul2.y, mul2.z, mul2.w);
		Novice::ScreenPrintf(0, 120, "%.2f : Norm", norm);

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
