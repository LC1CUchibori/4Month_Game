#pragma once

#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Model.h>
#include <vector>
#include "MathUtilityForText.h"
#include <Input.h>


class LeftDoor {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Move();

private:
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ワールドトランスフォーム
	ViewProjection* viewProjection_;
	// キーボード入力
	Input* input_ = nullptr;

	bool isMoving_ = false; // ← 追加：移動中フラグ

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	float moveProgress_ = 0.0f;       // 進行度（0.0〜1.0）
	const float moveDuration_ = 2.0f; // 移動完了までの時間（秒）

};