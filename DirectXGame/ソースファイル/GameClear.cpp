#include <cassert>
#include "ヘッダーファイル/GameClear.h"
#include "TextureManager.h"

GameClear::~GameClear() { 
	for (int i = 0; i < 10; i++) {
		delete sprite_[i];
	}
}

void GameClear::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ワールド変数の初期化
	worldTransfrom_.Initialize();
	worldTransfrom_.scale_ = {2, 2, 2};

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("GameClear.png");

	//BGM・SE読み込み
	//Gameclear = audio_->LoadWave("SE/GameClear.wav");

	//スプライトの生成
	BGsprite_ = Sprite::Create(textureHandle_, {0, 0});

	//音声再生
	//voiceHandle_ = audio_->PlayWave(Gameclear, false);

	// 0～9のテクスチャ読み込み
	for (int i = 0; i < 10; i++) {
		TextureHandle_[i] = TextureManager::Load("UI/" + std::to_string(i) + ".png");
	}

	for (int i = 0; i < 10; i++) {
		sprite_[i] = Sprite::Create(TextureHandle_[i], { 0, 0 });
	}

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameClear::Update() {
	//行列を更新
	worldTransfrom_.UpdateMatrix();
}

void GameClear::Draw() {
	//コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	//背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	BGsprite_->Draw();

	//メダル数を最大5桁に制限
	if (medalCount_ > 99999) {
		medalCount_ = 99999;
	}

	//メダル数を文字列に変換
	std::string countStr = std::to_string(medalCount_);
	size_t digitCount = countStr.length();

	// 基準となる描画開始位置
	float baseX = 600.0f, y = 560.0f;
	float spacing = 90.0f;

	float x = baseX - (spacing * (digitCount - 1));

	//各桁を対応する画像で描画
	for (size_t i = 0; i < digitCount; i++) {
		int index = countStr[i] - '0';
		if (index >= 0 && index < 10) {
			sprite_[i]->SetTextureHandle(TextureHandle_[index]);
			sprite_[i]->SetPosition({ x, y });

			sprite_[i]->SetSize({ 72.0f, 96.0f });
			sprite_[i]->Draw();
		}
		x += spacing;
	}



	//スプライト描画後処理
	Sprite::PostDraw();
	//深度バッファクリア
	dxCommon_->ClearDepthBuffer();
}

void GameClear::SetMedalCount(int count)
{
	medalCount_ = count;
}


