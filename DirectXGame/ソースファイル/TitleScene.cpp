#include "ヘッダーファイル/TitleScene.h"
#include "TextureManager.h"
#include <cassert>

TitleScene::~TitleScene() { 
	delete sprite_;
	for (auto& sprite : numberSprite_) {
		delete sprite;
	}
	

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
	textureHandle_ = TextureManager::Load("TitleBG.png");

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

	// 0～9のテクスチャ読み込み
	for (int i = 0; i < 10; i++) {
		numberTextureHandles_[i] = TextureManager::Load("UI/" + std::to_string(i) + ".png");
	}

	for (int i = 0; i < 10; i++) {
		numberSprite_[i] = Sprite::Create(numberTextureHandles_[i], { 0, 0 });
	}

	// 最初のランダム数生成
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 999); // 0〜999の範囲
	randomNumber_ = dist(mt);

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

	// 背景
	sprite_->Draw();
	int number = (randomNumber_ < 99999) ? randomNumber_ : 99999;
	std::string numStr = std::to_string(number);
	size_t digitCount = numStr.length();

	float baseX = 850.0f; // 画面中心基準に変更（仮に1280x720なら中央は640）
	float y = 540.0f;
	float spacing = 52.0f;

	// 中央に寄せるために、表示の開始X座標を調整
	float totalWidth = spacing * digitCount;
	float x = baseX - (totalWidth / 2.0f) + (spacing / 2.0f);

	for (size_t i = 0; i < digitCount; ++i) {
		int digit = numStr[i] - '0';
		if (digit >= 0 && digit < 10 && i < 10) {
			numberSprite_[i]->SetTextureHandle(numberTextureHandles_[digit]);
			numberSprite_[i]->SetPosition({x, y});
			numberSprite_[i]->SetSize({ 48.0f, 64.0f });
			numberSprite_[i]->Draw();
		}
		x += spacing;
	}


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

