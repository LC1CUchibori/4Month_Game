#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "ヘッダーファイル/Button.h"
#include <Input.h>

void Button::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Button::Update()
{
    // 押し込み状態のとき、時間をカウントして一定時間経ったらリセット
    if (isPressed_)
    {
        const float deltaTime = 1.0f / 60.0f;
        pressTimer_ += deltaTime;
        if (pressTimer_ >= pressDuration_)
        {
            // 押し込み状態を解除し、元の位置に戻す
            worldTransform_.translation_.z = originalPosition_.z;
            isPressed_ = false;
        }
    }

    // ワールドトランスフォームの更新
    worldTransform_.UpdateMatrix();
}

void Button::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

void Button::Press()
{
    // ボタンを押したときの深さ
    worldTransform_.translation_.z = originalPosition_.z + pressedOffset_;
    isPressed_ = true;
    pressTimer_ = 0.0f;
}

void Button::Push()
{
}

void Button::SetPosition(const Vector3& position)
{
	// ワールドトランスフォーム内の位置を更新
	worldTransform_.translation_ = position;
	// 初期位置も記録
	originalPosition_ = position;
}
