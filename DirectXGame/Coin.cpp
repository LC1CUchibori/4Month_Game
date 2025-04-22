#include "Coin.h"
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <random>
#include <corecrt_math_defines.h>


void Coin::Initialize(Model* model, ViewProjection* viewProjection) {

	// ワールド変換の初期化
	worldTransform_.Initialize();

	model_ = model;
	viewProjection_ = viewProjection;
	SetRandomBehavior();

}

void Coin::Update() {
	float time = static_cast<float>(std::clock()) / CLOCKS_PER_SEC;

	// 回転
	worldTransform_.rotation_.y += 0.05f;

	// スケールふわふわ（オプション）
	float scale = 1.0f + 0.05f * std::sinf(time * 3.0f + timeOffset_);
	worldTransform_.scale_ = {scale, scale, scale};

	// ===== 自由落下 & バウンド =====
	if (!grounded_) {
		velocity_.y += gravity_; // 重力を加える
		worldTransform_.translation_.y += velocity_.y;

		// 地面（Y=0）に当たったらバウンド処理
		if (worldTransform_.translation_.y < -25.0f) {
			worldTransform_.translation_.y = 0.0f;
			isDead_ = true; // 消えるフラグON
			// 🎵 ここで落下SEを鳴らす
			if (audio_ && DropCoinSE_ != 0) {
				voiceHandleCoin_ = audio_->PlayWave(DropCoinSE_, false);
			}
		}
	}

	worldTransform_.UpdateMatrix();
}

void Coin::Draw() {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}

void Coin::SetRandomRotation() {// 乱数生成器（毎回同じ乱数列にならないように）
	static std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> dist(0.0f, 360.0f); // 0〜360度

	worldTransform_.rotation_ = {
		dist(mt) * (float)M_PI / 180.0f, // X軸
		dist(mt) * (float)M_PI / 180.0f, // Y軸
		dist(mt) * (float)M_PI / 180.0f  // Z軸
	};
}

void Coin::SetRandomPosition() {
	// 乱数生成器
	static std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> distX(-35.0f, 35.0f); // X座標範囲
	std::uniform_real_distribution<float> distY(30.0f, 60.0f);    // Y座標範囲（少し上に浮いてる感じ）
	std::uniform_real_distribution<float> distZ(0.0f, 5.0f); // Z座標範囲

	worldTransform_.translation_ = {distX(mt), distY(mt), distZ(mt)};
}

void Coin::SetRandomBehavior() {
	SetRandomRotation();
	SetRandomPosition();

	// 浮遊の時間オフセットもランダムに
	static std::mt19937 mt(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> distTime(0.0f, 3.14f * 2.0f);
	timeOffset_ = distTime(mt);
}

void Coin::SetAudio(Audio* audio, uint32_t dropSE) {
	audio_ = audio;
	DropCoinSE_ = dropSE;
}

