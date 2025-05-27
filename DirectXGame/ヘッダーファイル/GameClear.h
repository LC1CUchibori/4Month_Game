#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class GameClear {
public:
	~GameClear();

	void Initialize();

	void Update();

	void Draw();

	void SetMedalCount(int count); // メダル枚数を設定

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransfrom_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//ゲームクリアシーン
	GameClear* gameClear = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//スプライト
	Sprite* BGsprite_ = nullptr;

	//サウンドデータハンドル
	uint32_t Gameclear = 0;

	//音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	// 数字
	Sprite* sprite_[10];
	//テクスチャハンドル
	uint32_t TextureHandle_[10];

	int Medal = 0;

	int medalCount_ = 0; // メダル枚数
};
