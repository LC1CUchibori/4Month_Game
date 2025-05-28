#include "ヘッダーファイル/TitleScene.h"
#include "TextureManager.h"
#include <cassert>

TitleScene::~TitleScene() { 
	delete sprite_;

	// 音源停止
	//audio_->StopWave(voiceHandle1_);
}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ワールド変数の初期化
	worldTransfrom_.Initialize();
	worldTransfrom_.scale_ = {2, 2, 2};

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Title4.png");

	//BGM・SE読み込み
	GameStart = audio_->LoadWave("BGM/GameStart.wav");
	Decision = audio_->LoadWave("SE/Decision.wav");

	//スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {0, 0});

	// 音声再生
	voiceHandle1_ = audio_->PlayWave(GameStart, true);

	// 最初の音量を小さくする（たとえば0.1）
	currentVolume_ = 0.3f;
	audio_->SetVolume(voiceHandle1_, currentVolume_);

	leftDoorModel_ = Model::CreateFromOBJ("LeftDoor", true);
	rightDoorModel_ = Model::CreateFromOBJ("RightDoor", true);


	leftDoor_ = new LeftDoor();
	leftDoor_->Initialize(leftDoorModel_, &viewProjection_);

	rightDoor_ = new RightDoor();
	rightDoor_->Initialize(rightDoorModel_, &viewProjection_);


	pachinkoModel_ = Model::CreateFromOBJ("Pachinko", true);

	pachinko_ = new Pachinko();
	pachinko_->Initialize(pachinkoModel_, &viewProjection_);

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void TitleScene::Update() {

	leftDoor_->Update();

	rightDoor_->Update();

	pachinko_->Update();

	// スペース押下で音量上昇開始
	if (input_->TriggerKey(DIK_SPACE)) {
		isIncreasingVolume_ = true;
	}

	// 音量を上げる処理
	if (isIncreasingVolume_) {
		currentVolume_ += volumeIncreaseSpeed_;
		if (currentVolume_ > targetVolume_) {
			currentVolume_ = targetVolume_;
			isIncreasingVolume_ = false; // 完了したら止める（必要なら）
		}
		audio_->SetVolume(voiceHandle1_, currentVolume_);
	}

	//行列を更新
	worldTransfrom_.UpdateMatrix();
}

void TitleScene::Draw() {
	//コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	//背景スプライト描画前処理
	Sprite::PreDraw(commandList);
	sprite_->Draw();
	//スプライト描画後処理
	Sprite::PostDraw();
	//深度バッファクリア
	dxCommon_->ClearDepthBuffer();

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 自キャラの描画
	// player_->Draw(viewProjection_);

	leftDoor_->Draw();
	rightDoor_->Draw();

	pachinko_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

}

void TitleScene::LoadMusic() { 
	//音声再生
	voiceHandle2_ = audio_->PlayWave(Decision, false);
}

