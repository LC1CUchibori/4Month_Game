#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <LeftDoor.h>
#include <RightDoor.h>
#include <Pachinko.h>

#include <random>      // 乱数
#include <string>      // 文字列変換
#include <sstream>     // 数値を文字列に変換
#include <algorithm>


class TitleScene {
public:
	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	void LoadMusic();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransfrom_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	//タイトルシーン
	TitleScene* titleScene_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 抽選番号テクスチャハンドル
	uint32_t numberTextureHandles_[10];

	
	//スプライト
	Sprite* sprite_ = nullptr;
	// 抽選番号スプライト
	Sprite* numberSprite_[10];

	int randomNumber_ = 0;    

	//サウンドデータハンドル
	uint32_t GameStart = 0;
	uint32_t Decision = 0;

	//音声再生ハンドル
	uint32_t voiceHandle1_ = 0u;
	uint32_t voiceHandle2_ = 0u;

	//パチンコ店
	LeftDoor* leftDoor_ = nullptr;
	Model* leftDoorModel_ = nullptr;

	RightDoor* rightDoor_ = nullptr;
	Model* rightDoorModel_ = nullptr;

	Pachinko* pachinko_ = nullptr;
	Model* pachinkoModel_ = nullptr;

	// TitleScene.h などに追加
	float currentVolume_ = 0.1f;          // 初期音量（0.1）
	float targetVolume_ = 1.0f;           // 目標音量（最大1.0）
	float volumeIncreaseSpeed_ = 0.01f;   // 1フレームごとの音量増加量
	bool isIncreasingVolume_ = false;     // 音量上昇フラグ


};