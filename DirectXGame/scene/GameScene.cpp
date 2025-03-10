
#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_; 
	delete modelSlot_;
	delete modelReel_;
	delete modelReel2_;
	delete modelReel3_;
	delete modelPushButton_;
	delete modelLeverParts_;
	delete modelLever_;
	delete modelButton_;

	//音声停止
	audio_->StopWave(voiceHandle1_);
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// BGM・SE読み込み
	SLOT = audio_->LoadWave("BGM/Slot.wav");
	Click = audio_->LoadWave("SE/Decision.wav");

	// モデル生成
	modelSlot_ = Model::CreateFromOBJ("Slot", true);
	// スロットの生成
	slot_ = new Slot();
	// スロットの初期化
	slot_->Initialize(modelSlot_, &viewProjection_);

	// モデル生成
	modelLever_ = Model::CreateFromOBJ("Lever", true);
	// レバーの生成
	lever_ = new Lever();
	// レバーの初期化
	lever_->Initialize(modelLever_, &viewProjection_);

	// モデル生成
	modelReel_ = Model::CreateFromOBJ("Reel", true);
	// スロットリールの生成
	reel1_ = new Reel();
	// スロットリールの初期化
	reel1_->Initialize(modelReel_, &viewProjection_,lever_);

	// モデル生成
	modelReel2_ = Model::CreateFromOBJ("Reel2", true);
	// スロットリール2の生成
	reel2_ = new Reel2();
	// スロットリール2の初期化
	reel2_->Initialize(modelReel2_, &viewProjection_,lever_);

	// モデル生成
	modelReel3_ = Model::CreateFromOBJ("Reel3", true);
	// スロットリール3の生成
	reel3_ = new Reel3();
	// スロットリー3の初期化
	reel3_->Initialize(modelReel3_, &viewProjection_,lever_);

	// モデル生成
	modelLeverParts_ = Model::CreateFromOBJ("LeverParts", true);
	// レバーパーツの生成
	leverParts_ = new Slot();
	// レバーパーツの初期化
	leverParts_->Initialize(modelLeverParts_, &viewProjection_);

	// モデルの生成
	modelButton_ = Model::CreateFromOBJ("Botan", true);
	// 左側のボタン生成
	button1_ = new Button();
	// 左側のボタンの初期化
	button1_->Initialize(modelButton_, &viewProjection_);
	// 左側のボタンの位置
	button1_->SetPosition({-3.0f, 0.0f, 0.0f});

	// 真ん中のボタンの生成
	button2_ = new Button();
	// 真ん中のボタンの初期化
	button2_->Initialize(modelButton_, &viewProjection_);
	// 真ん中のボタンの位置
	button2_->SetPosition({0.5f, 0.0f, 0.0f});
	
	// 右側のボタン生成
	button3_ = new Button();
	// 右側のボタンの初期化
	button3_->Initialize(modelButton_, &viewProjection_);
	// 右側のボタンの位置
	button3_->SetPosition({4.0f, 0.0f, 0.0f});

	// モデルの生成
	modelPushButton_ = Model::CreateFromOBJ("Push", true);
	// Pushボタンの生成
	pushButton_ = new PushButton();
	// Pushボタンの初期化
	pushButton_->Initialize(modelPushButton_, &viewProjection_);

	// モデルの生成
	modelMedalCountButton_ = Model::CreateFromOBJ("MedalCountButton", true);
	// メダルカウントボタンの生成
	medalCountButton_ = new Slot();
	// メダルカウントボタンの初期化
	medalCountButton_->Initialize(modelMedalCountButton_, &viewProjection_);

	// モデルの生成
	modelMoneyBox_ = Model::CreateFromOBJ("MoneyBox", true);
	// 投入機の生成
	MoneyBox_ = new Slot();
	// 投入機の初期化
	MoneyBox_->Initialize(modelMoneyBox_, &viewProjection_);

	//画像生成
	TextureHandle_[0] = TextureManager::Load("0.png");
	TextureHandle_[1] = TextureManager::Load("1.png");
	TextureHandle_[2] = TextureManager::Load("2.png");
	TextureHandle_[3] = TextureManager::Load("3.png");
	TextureHandle_[4] = TextureManager::Load("4.png");
	TextureHandle_[5] = TextureManager::Load("5.png");
	TextureHandle_[6] = TextureManager::Load("6.png");
	TextureHandle_[7] = TextureManager::Load("7.png");
	TextureHandle_[8] = TextureManager::Load("8.png");
	TextureHandle_[9] = TextureManager::Load("9.png");

	//メダル用の数字生成
	sprite_[0] = Sprite::Create(TextureHandle_[0], { 0, 0 });
	sprite_[1] = Sprite::Create(TextureHandle_[1], { 0, 0 });
	sprite_[2] = Sprite::Create(TextureHandle_[2], { 0, 0 });
	sprite_[3] = Sprite::Create(TextureHandle_[3], { 0, 0 });
	sprite_[4] = Sprite::Create(TextureHandle_[4], { 0, 0 });
	sprite_[5] = Sprite::Create(TextureHandle_[5], { 0, 0 });
	sprite_[6] = Sprite::Create(TextureHandle_[6], { 0, 0 });
	sprite_[7] = Sprite::Create(TextureHandle_[7], { 0, 0 });
	sprite_[8] = Sprite::Create(TextureHandle_[8], { 0, 0 });
	sprite_[9] = Sprite::Create(TextureHandle_[9], { 0, 0 });

	//ゲームカウント用の数字生成
	medalSprite_[0] = Sprite::Create(TextureHandle_[0], { 0, 0 });
	medalSprite_[1] = Sprite::Create(TextureHandle_[1], { 0, 0 });
	medalSprite_[2] = Sprite::Create(TextureHandle_[2], { 0, 0 });
	medalSprite_[3] = Sprite::Create(TextureHandle_[3], { 0, 0 });
	medalSprite_[4] = Sprite::Create(TextureHandle_[4], { 0, 0 });
	medalSprite_[5] = Sprite::Create(TextureHandle_[5], { 0, 0 });
	medalSprite_[6] = Sprite::Create(TextureHandle_[6], { 0, 0 });
	medalSprite_[7] = Sprite::Create(TextureHandle_[7], { 0, 0 });
	medalSprite_[8] = Sprite::Create(TextureHandle_[8], { 0, 0 });
	medalSprite_[9] = Sprite::Create(TextureHandle_[9], { 0, 0 });

	// 音声再生
	voiceHandle1_ = audio_->PlayWave(SLOT, true);
}

void GameScene::Update() {

	// スロットリール1
	reel1_->Update();
	// スロットリール2
	reel2_->Update();
	// スロットリール3
	reel3_->Update();

	// レバー
	lever_->Update(Medal,GameCount);

	// ボタン1
	button1_->Update();
	// ボタン2
	button2_->Update();
	// ボタン3
	button3_->Update();

	pushButton_->Update();

	// 現在の状態を保存
	static int currentButtonIndex = 0;
	static int pressCount = 0; // 何回ボタンを押したかを数える変数

#pragma region メダルの処理
	//投入口にメダル入れる処理
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		//マウスの位置取得
		Vector2 v = Input::GetInstance()->GetMousePosition();

		//緑の投入口の判定処理
		if (v.x >= 700 && v.x <= 780 && v.y >= 440 && v.y <= 455) {
			Medal += 1;
		}

		//メダルが3枚の時にレールを回す処理
		if (Medal >= 3) {			
			Realflag = true;
		}
	}
#pragma endregion

#pragma region レバーの処理
	// レバーが引かれていたらリール回転開始
	if (lever_->IsPulled())
	{
		reel1_->StartRotation();
		reel2_->StartRotation();
		reel3_->StartRotation();

			reel1IsStopped_ = false; // リール回転開始時に停止フラグをリセット
			reel2IsStopped_ = false;
			reel3IsStopped_ = false;

		// レバーを引いたらボタン押しの進行もリセットする
		currentButtonIndex = 0;
		pressCount = 0;
	}
#pragma endregion

#pragma region ボタンの処理
	// キー入力
	Input* input = Input::GetInstance();

	// スペースキーを押したら、左から順にボタンを押す
	if (input->TriggerKey(DIK_SPACE))
	{
		 // リールが停止していない場合のみボタンを押す
        if (!reel1IsStopped_ && currentButtonIndex == 0)
        {
			voiceHandle2_ = audio_->PlayWave(Click, false);
            button1_->Press();
            reel1_->StopRotation();
            reel1IsStopped_ = true; // リール1を停止状態に設定
        }
        else if (!reel2IsStopped_ && currentButtonIndex == 1)
        {
			voiceHandle2_ = audio_->PlayWave(Click, false);
            button2_->Press();
            reel2_->StopRotation();
            reel2IsStopped_ = true; // リール2を停止状態に設定
        }
        else if (!reel3IsStopped_ && currentButtonIndex == 2)
        {
			voiceHandle2_ = audio_->PlayWave(Click, false);
            button3_->Press();
            reel3_->StopRotation();
            reel3IsStopped_ = true; // リール3を停止状態に設定
			if (lever_->GetStorenum() <= 50) {
				Medal += 8;  
			}
        }

		// 次のボタンへ
		currentButtonIndex++;
		pressCount++;

		// 3回押したらリセットする
		if (pressCount >= 3)
		{
			currentButtonIndex = 0; // 左に戻る
			pressCount = 0;         // カウントもリセット
		}
	}
#pragma endregion

#pragma region 勝つ・負ける条件の処理

	//メダルの数が一定数超えたらクリア
	if (Medal >= 100) {
		cleared_ = true;
	}

#pragma endregion
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// スロット鏡台
	slot_->Draw();

	// スロットリール1
	reel1_->Draw();
	// スロットリール2
	reel2_->Draw();
	// スロットリール3
	reel3_->Draw();

	// レバー
	lever_->Draw();

	// レバーパーツ
	leverParts_->Draw();

	// メダルカウントボタン
	medalCountButton_->Draw();

	// 投入機
	MoneyBox_->Draw();

	// ボタン1
	button2_->Draw();
	// ボタン2
	button3_->Draw();
	// ボタン3
	button1_->Draw();

	// Pushボタン
	pushButton_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// ゲーム数のスプライト描画
	DrawGameCount();

	MedalDraw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::DrawGameCount() {
	//ゲームカウントを最大4桁に制限
	if (GameCount > 9999) {
		GameCount = 9999; //5桁以上にならないようにする
	}

	//メダル数を文字列に変換
	std::string countStr = std::to_string(GameCount);
	size_t digitCount = countStr.length();

	// 基準となる描画開始位置
	float x = 1200.0f;
	float spacing = 65.0f; // 画像の間隔

	//各桁を対応する画像で描画
	for (size_t i = 0; i < digitCount; i++) {
		int index = countStr[digitCount - 1 - i] - '0'; // 0～9 のインデックス
		if (index >= 0 && index < 10) {
			medalSprite_[i]->SetTextureHandle(TextureHandle_[index]); // テクスチャを変更
			medalSprite_[i]->SetPosition({ x, 0 }); // 位置を更新
			medalSprite_[i]->Draw(); // 描画
		}
		x -= spacing; // 画像の間隔
	}
}

//メダルの数を描画
void GameScene::MedalDraw() {
	//メダル数を最大5桁に制限
	if (Medal > 99999) {
		Medal = 99999; //6桁以上にならないようにする
	}

	//メダル数を文字列に変換
	std::string countStr = std::to_string(Medal);
	size_t digitCount = countStr.length();

	// 基準となる描画開始位置
	float baseX = 1200.0f, y = 120.0f;
	float spacing = 65.0f; // 画像の間隔

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
}

void GameScene::DrawMedalCount()
{
	// 4桁の各桁の数字を取得
	int MedalNum = Medal;
	int MedalDigits[2] = { 0, 0  };

	for (int j = 1; j >= 0; j--) {
		MedalDigits[j] = MedalNum % 10;  // 下位の桁から取得
		MedalNum /= 10;
	}

	// 各桁をスプライトとして描画
	float startMedalX = 1000.0f;  // 右端のX座標
	float MedalY = 50.0f;       // Y座標
	float Medalspacing = 50.0f;  // 各桁の間隔

	for (int j = 0; j < 2; j++) {
		medalSprite_[j]->SetPosition({ startMedalX + j * Medalspacing, MedalY });
		medalSprite_[j]->Draw();
		medalSprite_[j]->SetTextureHandle(TextureHandle_[MedalDigits[j]]);
	}
}
