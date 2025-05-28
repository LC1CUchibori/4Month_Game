#define NOMINMAX
#include "RightDoor.h"
#include <algorithm> // std::min

static float easeOutQuad(float x) { return 1 - (1 - x) * (1 - x); }

void RightDoor::Initialize(Model* model, ViewProjection* viewProjection) {
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

void RightDoor::Update() {
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

void RightDoor::Draw() {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}

void RightDoor::Move() {
	if (moveProgress_ < 1.0f) {
		moveProgress_ += 1.0f / (60.0f * moveDuration_);
		moveProgress_ = std::min(moveProgress_, 1.0f);

		float eased = easeOutQuad(moveProgress_);
		worldTransform_.translation_.x = 0.0f + (12.0f - 0.0f) * eased;
	}

	worldTransform_.translation_ -= {0.0f, -0.03f, 0.2f};
}
