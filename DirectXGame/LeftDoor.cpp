#define NOMINMAX
#include <algorithm>

#include "LeftDoor.h"

// easeOutQuad 関数（C++ 版）
static float easeOutQuad(float x) { return 1 - (1 - x) * (1 - x); }

void LeftDoor::Initialize(Model* model, ViewProjection* viewProjection) {
	input_ = Input::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.scale_ = {
		2.5f,
		2.5f,
		2.5f,
	};
	worldTransform_.translation_ = {0.0f, -7.5f, 1.0f};
}

void LeftDoor::Update() {

	// スペースが押された「瞬間」に移動開始
	if (input_->TriggerKey(DIK_SPACE)) {
		isMoving_ = true;
	}

	// 移動処理
	if (isMoving_) {
		Move();

		// Z座標が -33.0f 以下になったら移動停止
		if (worldTransform_.translation_.z <= -33.0f) {
			isMoving_ = false;
		}
	}

	worldTransform_.UpdateMatrix();

}

void LeftDoor::Draw() {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}

void LeftDoor::Move() {
	if (moveProgress_ < 1.0f) {
		// 1フレーム = 1/60秒と仮定（固定フレームレートなら）
		moveProgress_ += 1.0f / (60.0f * moveDuration_);
		moveProgress_ = std::min(moveProgress_, 1.0f);

		float eased = easeOutQuad(moveProgress_);
		worldTransform_.translation_.x = 0.0f + (-12.0f) * eased;
	}
	worldTransform_.translation_ -= {0.0f, -0.03f, 0.2f};
}
