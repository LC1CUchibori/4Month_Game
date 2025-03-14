#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Reel2.h"
#include "ヘッダーファイル/Reel.h"
#include "ヘッダーファイル/Lever.h"

void Reel2::Initialize(Model* model, ViewProjection* viewProjection ,Lever* lever)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
	lever_ = lever;

	// リール上のシンボルをセットアップ
	symbols_ = {
		Symbol::Bell,
		Symbol::Watermelon,
		Symbol::blueSeven,
		Symbol::Cherry,
		Symbol::RePlay,
		Symbol::Bell,
		Symbol::Bar,
		Symbol::Cherry,
		Symbol::Bar,
		Symbol::RedSeven,
	};
}

void Reel2::Update()
{
	// リールの位置を少し下に
	worldTransform_.translation_.y = -1.5f;

	if (isRotating_)
	{
		// Y軸周りに回転
		worldTransform_.rotation_.x += 0.5f;
	}
	else if (isStopping_)
	{
		// 一定速度で目標に向かう
		float& rotationX = worldTransform_.rotation_.x;
		float diff = stopTargetAngle_ - rotationX;

		// 目標角度に向かって進む
		if (fabs(diff) > 0.01f)
		{
			// 1フレームの回転量
			float step = (diff > 0 ? 0.1f : -0.1f);
			if (fabs(diff) < fabs(step))
			{
				step = diff;
			}
			rotationX += step;
		}
		else
		{
			// 差分が小さくなったら即停止
			rotationX = stopTargetAngle_;
			isStopping_ = false; // 停止
		}
	}

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void Reel2::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

void Reel2::StopRotation()
{
	isRotating_ = false;

	const float symbolAngleRad = 36.0f * (3.14159265f / 180.0f);
	float& rotationX = worldTransform_.rotation_.x;

	// ベルが揃う
	if (lever_->GetStorenum() <= 50) {
		rotationX = 137.0f;
	}
	//if(reel1->GetResultSymbol() == Bell){}

	// 0～2πの範囲に正規化
	rotationX = fmod(rotationX, 2.0f * 3.14159265f);



	float offsetAngle = symbolAngleRad * 0.4f; // 0.6個分 ちょっと進ませる
	float nextSymbolAngle = ceil(rotationX / symbolAngleRad) * symbolAngleRad + offsetAngle;

	// 目標角度に向けて一定速度で進むようにする
	stopTargetAngle_ = nextSymbolAngle;
	// 滑らかに止まる
	isStopping_ = true; 
}

Reel2::Symbol Reel2::GetResultSymbol()
{
	const float symbolAngleRad = 36.0f * (3.14159265f / 180.0f);
	// 回転角からシンボルインデックスを求める
	float rotationX = fmod(worldTransform_.rotation_.x, 2.0f * 3.14159265f);


	if (lever_->GetStorenum() <= 50) {
		rotationX = 180.0f;
	}

	rotationX = fmod(worldTransform_.rotation_.x, 2.0f * 3.14159265f);
	if (rotationX < 0) rotationX += 2.0f * 3.14159265f; // マイナス対策

	int symbolIndex = static_cast<int>(round(rotationX / symbolAngleRad)) % symbols_.size();
	return symbols_[symbolIndex];
}

std::vector<Reel2::Symbol> Reel2::GetSymbols() const
{
	return symbols_;
}


