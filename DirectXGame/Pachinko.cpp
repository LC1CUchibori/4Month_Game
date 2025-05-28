#include "Pachinko.h"

void Pachinko::Initialize(Model* model, ViewProjection* viewProjection) {
	audio_ = Audio::GetInstance();
	input_ = Input::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	worldTransform_.Initialize();

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.scale_ = {2.5f, 2.5f, 2.5f};
	worldTransform_.translation_ = {0.0f, -6.0f, 0.0f};
}


void Pachinko::Update() {
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

void Pachinko::Draw() {

	model_->Draw(worldTransform_, *viewProjection_);
}

void Pachinko::Move() {
	// 移動量の調整
	worldTransform_.translation_ += {0.0f, 0.03f, -0.2f};
}