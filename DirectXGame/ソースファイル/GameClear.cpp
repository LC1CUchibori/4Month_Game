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

	for (int i = 0; i < 10; i++) {
		sprite_[i]->Draw();
	}

	if (Medal > 99999) {
		Medal = 99999; //6桁以上にならないようにする
	}

	//メダル数を文字列に変換
	std::string countStr = std::to_string(Medal);
	size_t digitCount = countStr.length();

	// 基準となる描画開始位置
	float baseX = 1230.0f, y = 100.0f;
	float spacing = 50.0f; // 画像の間隔

	// 最小2桁はそのまま描画
	float x = baseX - (spacing * (digitCount - 1));

	//各桁を対応する画像で描画
	for (size_t i = 0; i < digitCount; i++) {
		int index = countStr[i] - '0'; // 0～9 のインデックス
		if (index >= 0 && index < 10) {
			sprite_[i]->SetTextureHandle(TextureHandle_[index]); // テクスチャを変更
			sprite_[i]->SetPosition({ x, y }); // 位置を更新
			sprite_[i]->Draw(); // 描画
		}
		x += spacing; // 画像の間隔
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


