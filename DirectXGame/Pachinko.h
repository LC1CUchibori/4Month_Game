#pragma once

#include "MathUtilityForText.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Model.h>
#include <vector>
#include <Input.h>
#include <Sprite.h>
#include <Audio.h>
#include <TextureManager.h>
#include <DirectXCommon.h>


class Pachinko {
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
	DirectXCommon* dxCommon_ = nullptr;
	// キーボード入力
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// サウンドデータ
	uint32_t Falling = 0;

	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0u;


	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;


	bool isMoving_ = false; // ← 追加：移動中フラグ
};