#define NOMINMAX
#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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
	delete enemy1;
	delete enemy2;
	delete enemy3;
	delete enemy4;
	for (Coin* coin : coins_) {
		delete coin;
	}
	coins_.clear();

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
	Get = audio_->LoadWave("SE/Get.wav");
	Retry = audio_->LoadWave("SE/Retry.wav");
	DropCoinSE_ = audio_->LoadWave("SE/DropCoin.wav");

	// 背景
	BGtextureHandle_ = TextureManager::Load("BG.png");
	BGsprite_ = Sprite::Create(BGtextureHandle_, {0, 0});

	// スロット内の背景
	DanjonBGtextureHandle_ = TextureManager::Load("DanjonBG.png");
	DanjonBGSprite = Sprite::Create(DanjonBGtextureHandle_, { 140,-80 });

	// 説明
	RuleTextureHandle_ = TextureManager::Load("Rule.png");
	RuleSprite_ = Sprite::Create(RuleTextureHandle_, { 140,105 });

	// 操作説明
	OperationtextureHandle_ = TextureManager::Load("UI/Operation.png");
	OperationSprite_ = Sprite::Create(OperationtextureHandle_, { 0, 0 });

	// 退室
	OutRoomTextureHandle_ = TextureManager::Load("OutRoom.png");
	OutRoomSprite_ = Sprite::Create(OutRoomTextureHandle_, { 990,355 });

	// 退室
	OutRoomPickTextureHandle_ = TextureManager::Load("OutRoomPick.png");
	OutRoomPick2TextureHandle_ = TextureManager::Load("OutRoomPick2.png");
	OutRoomPick3TextureHandle_ = TextureManager::Load("OutRoomPick3.png");
	OutRoomPickSprite_ = Sprite::Create(OutRoomPickTextureHandle_, { 490,200 });
	OutRoomPickSprite2_ = Sprite::Create(OutRoomPick2TextureHandle_, { 490,200 });
	OutRoomPickSprite3_ = Sprite::Create(OutRoomPick3TextureHandle_, { 490,200 });

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
	lever_->Initialize(modelLever_, &viewProjection_,this);

	// モデル生成
	modelReel_ = Model::CreateFromOBJ("Reel", true);
	// スロットリールの生成
	reel1_ = new Reel();
	// スロットリールの初期化
	reel1_->Initialize(modelReel_, &viewProjection_, lever_);

	// モデル生成
	modelReel2_ = Model::CreateFromOBJ("Reel2", true);
	// スロットリール2の生成
	reel2_ = new Reel2();
	// スロットリール2の初期化
	reel2_->Initialize(modelReel2_, &viewProjection_, lever_);

	// モデル生成
	modelReel3_ = Model::CreateFromOBJ("Reel3", true);
	// スロットリール3の生成
	reel3_ = new Reel3();
	// スロットリー3の初期化
	reel3_->Initialize(modelReel3_, &viewProjection_, lever_);

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
	button1_->SetPosition({ -3.0f, 0.0f, 0.0f });

	// 真ん中のボタンの生成
	button2_ = new Button();
	// 真ん中のボタンの初期化
	button2_->Initialize(modelButton_, &viewProjection_);
	// 真ん中のボタンの位置
	button2_->SetPosition({ 0.5f, 0.0f, 0.0f });

	// 右側のボタン生成
	button3_ = new Button();
	// 右側のボタンの初期化
	button3_->Initialize(modelButton_, &viewProjection_);
	// 右側のボタンの位置
	button3_->SetPosition({ 4.0f, 0.0f, 0.0f });

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

	modelBONUS_ = Model::CreateFromOBJ("BONUS", true);
	BONUS_ = new BONUS();
	BONUS_->Initialize(modelBONUS_, &viewProjection_);

	modelTitile_Normal_ = Model::CreateFromOBJ("Title", true);
	//modelTitile_White_ = Model::CreateFromOBJ("TitleWhite", true);
	// タイトルの生成
	title_ = new Title();
	// 位置
	Vector3 position = { 0.5f, 12.0f, -5.0f };
	// タイトルの初期化
	title_->Initialize(modelTitile_Normal_, modelTitile_White_, &viewProjection_, position);

	// プレイヤーのインスタンス化
	player = new Player();
	// プレイヤー生成
	playerTextureHandle_ = TextureManager::Load("Yuusha.png");
	// プレイヤースプライト
	playerSprite_ = Sprite::Create(playerTextureHandle_, { 340,35 });


	// 敵のインスタンス化
	enemy1 = new Enemy();
	enemy2 = new Enemy();
	enemy3 = new Enemy();
	enemy4 = new Enemy();

	// 敵生成
	enemyTextureHandle_[0] = TextureManager::Load("Suraimu.png");
	enemyTextureHandle_[1] = TextureManager::Load("Mimikku.png");
	enemyTextureHandle_[2] = TextureManager::Load("Goremu.png");
	enemyTextureHandle_[3] = TextureManager::Load("Dragon.png");
	// 敵スプライト
	enemySprite_[0] = Sprite::Create(enemyTextureHandle_[0], {450,30 });
	enemySprite_[1] = Sprite::Create(enemyTextureHandle_[1], { 450,30 });
	enemySprite_[2] = Sprite::Create(enemyTextureHandle_[2], { 420,-15 });
	enemySprite_[3] = Sprite::Create(enemyTextureHandle_[3], { 435,-38 });
	
	// 0～9のテクスチャ読み込み
	for (int i = 0; i < 10; i++) {
		TextureHandle_[i] = TextureManager::Load("UI/" + std::to_string(i) + ".png");
	}

	// 短縮：sprite_、medalSprite_、EnemyGameSprite_ にまとめて生成
	for (int i = 0; i < 10; i++) {
		sprite_[i] = Sprite::Create(TextureHandle_[i], {0, 0});
		medalSprite_[i] = Sprite::Create(TextureHandle_[i], {0, 0});
		EnemyGameSprite_[i] = Sprite::Create(TextureHandle_[i], {0, 0});
		MoneySprite_[i] = Sprite::Create(TextureHandle_[i], { 0,0 });
	}

	// 矢印の生成
	Arrow_ = Sprite::Create(ArrowHandle_, { 480, 380 });

	// 音声再生
	//voiceHandle1_ = audio_->PlayWave(SLOT, true);

	//背景コインモデル生成
	modelCoin_ = Model::CreateFromOBJ("coin", true);

	std::vector<uint32_t> puchunTextures =
	{ TextureManager::Load("Puchun/Puchun1.png"), TextureManager::Load("Puchun/Puchun2.png"), TextureManager::Load("Puchun/Puchun3.png"), TextureManager::Load("Puchun/Puchun4.png"),
		TextureManager::Load("Puchun/Puchun5.png"), TextureManager::Load("Puchun/Puchun6.png"), TextureManager::Load("Puchun/Puchun7.png") };
	puchun_ = new Puchun();
	puchun_->Initialize(puchunTextures, audio_);

	prevMaxMoney_ = MaxMoney;
}

void GameScene::Update() {

	// スロットリール1
	reel1_->Update();
	// スロットリール2
	reel2_->Update();
	// スロットリール3
	reel3_->Update();

	lever_->Update(Medal, GameCount, isFreePlay, canPullLever_);

	// ボタン1
	button1_->Update();
	// ボタン2
	button2_->Update();
	// ボタン3
	button3_->Update();

	pushButton_->Update();

	BONUS_->Update();

	puchun_->Update();

	player->Update();

	// タイトル更新
	title_->Update();

	UpdateMedal(0.02f);

	//背景コイン
	for (auto it = coins_.begin(); it != coins_.end();) {
		Coin* coin = *it;
		coin->Update();

		if (coin->IsDead()) {
			delete coin;
			it = coins_.erase(it); // リストから削除してイテレータ更新

			coinsDeletedCount_++; // カウント増やす！

			if (coinsDeletedCount_ % 10 == 0) {
				audio_->PlayWave(DropCoinSE_, false);
			}

		} else {
			++it;
		}
	}


	// 現在の状態を保存
	static int currentButtonIndex = 0;
	static int pressCount = 0; // 何回ボタンを押したかを数える変数

#pragma region メダルの処理
	//投入口にメダル入れる処理
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		//マウスの位置取得
		Vector2 v = Input::GetInstance()->GetMousePosition();

		//緑の投入口の判定処理
		if (v.x >= 900 && v.x <= 940 && v.y >= 370 && v.y <= 400&& MaxMoney >= 46) {
			MaxMoney -= 46;
			Medal += 46;
		}


		//メダルが3枚の時にレールを回す処理
		if (Medal >= 3&&MaxMoney>=46) {			
			Realflag = true;
		}
	}
#pragma endregion

	// レバーのクールダウン処理
	if (!canPullLever_) {
		leverCooldownTimer_++;

		if (leverCooldownTimer_ >= kLeverCooldownMax) {
			canPullLever_ = true; // 2秒経過後にレバー操作解禁
		}
	}

	if (EnemyBONUSGameCount >= 1) {
		mode_ = 2;
	}
	else if (EnemyBONUSGameCount <= 0&&mode_==2) {
		mode_ = 0;
	}

#pragma region レバーの処理
	// レバーが引かれていたらリール回転開始
	if (canPullLever_ && lever_->IsPulled())
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

			if (mode_ == 1) {
				if (lever_->GetStorenum() == 97) {
					int randNum = rand() % 50;// 強チェリーを引いたときランダムでプチュン
					if (randNum == 0) {
						pushButton_->SetToggle(true); 
						isWaitingForPush = true;
					}
				}
				else if (lever_->GetStorenum() >= 91 && lever_->GetStorenum() <= 93) {
					int randNum = rand() % 40;// スイカを引いたときランダムでプチュン
					if (randNum == 0) {
						pushButton_->SetToggle(true); 
						isWaitingForPush = true;
					}
				}
				else if (lever_->GetStorenum() >= 94 && lever_->GetStorenum() <= 96) {
					int randNum = rand() % 30;// 弱チェリーを引いたときランダムでプチュン
					if (randNum == 0) {
						pushButton_->SetToggle(true); 
						isWaitingForPush = true;
					}
				}
			}

			if (mode_ == 2) {
				EnemyBONUSGameCount--; 
			}
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

			canPullLever_ = false;
			leverCooldownTimer_ = 0;


			// ベル
			if (lever_->GetStorenum() <= 30) {
				voiceHandle3_ = audio_->PlayWave(Get, false);
				targetMedal = Medal + 7;

				animating = true;
			}

			// リプレイ
			if (lever_->GetStorenum() >= 51 && lever_->GetStorenum() <= 90) {
				voiceHandle4_ = audio_->PlayWave(Retry, false);
				isFreePlay = true;
			}
			else
			{
				isFreePlay = false;
			}

			// 赤7
			if (lever_->GetStorenum() == 301) {
				targetMedal = Medal + 15;
				animating = true;
				BONUSMedal = 0;
			}

			// 青7
			if (lever_->GetStorenum() == 302) {
				targetMedal = Medal + 15;
				animating = true;
				BONUSMedal = 0;
			}

			// --------------------------------------------------- スイカ --------------------------------------
			if (lever_->GetStorenum() >= 91 && lever_->GetStorenum() <= 93) {
				voiceHandle3_ = audio_->PlayWave(Get, false);
				targetMedal = Medal + 5;
				animating = true;

				// 敵の初期化
				std::vector<Enemy*> enemies;  // 4体の敵を格納する配列
				enemies.push_back(enemy1);
				enemies.push_back(enemy2);
				enemies.push_back(enemy3);
				enemies.push_back(enemy4);

				// 敵1を倒す抽選 (スイカ)
				if (isEnemyActive == true && rand() % 100 < 100 && mode_ == 1 && enemies[0]) {  // 500%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[0]->SetIsActive(false);
					EnemyBONUSGameCount = 20;
				}
				// 敵2を倒す抽選 (スイカ)
				if (isEnemyActive == true && rand() % 100 < 100 && mode_ == 1 && enemies[1]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[1]->SetIsActive(false);
					EnemyBONUSGameCount = 30;
				}
				// 敵3を倒す抽選 (スイカ)
				if (isEnemyActive == true && rand() % 100 < 100 && mode_ == 1 && enemies[2]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[2]->SetIsActive(false);
					EnemyBONUSGameCount = 40;
				}
				// 敵4を倒す抽選 (スイカ)
				if (isEnemyActive == true && rand() % 100 < 100 && mode_ == 1 && enemies[3]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[3]->SetIsActive(false);
					EnemyBONUSGameCount = 50;
				}

				if (rand() % 100 < 50) {  // 50%の確率で敵を出現させる

					// 敵の出現確率
					std::vector<int> probabilities = { 60, 25, 10, 5 };

					enemyGameCount = 30;

					// ランダムで選ばれる敵のインデックスを決定
					int rand_value = rand() % 100;  // 0~99 のランダム値を生成
					int cumulative_prob = 0;
					int selected_enemy_index = -1;

					// 確率に基づいて選ばれる敵を決定
					for (int i = 0; i < probabilities.size(); ++i) {
						cumulative_prob += probabilities[i];
						if (rand_value < cumulative_prob) {
							selected_enemy_index = i;  // この敵が選ばれる
							break;
						}
					}

					// 選ばれた敵を描画
					if (selected_enemy_index != -1&& mode_ == 0) {
						enemies[selected_enemy_index]->Initialize();  // 敵を初期化
						enemies[selected_enemy_index]->SetIsActive(true);  // 敵をアクティブにする
						isEnemyActive = true;
					}
					if (mode_ == 0) {
						mode_ = 1;
					}
				}
			}

			// -------------------------------- 弱チェリー -------------------------------
			if (lever_->GetStorenum() >= 94 && lever_->GetStorenum() <= 96) {
				voiceHandle3_ = audio_->PlayWave(Get, false);
				targetMedal = Medal + 2;
				animating = true;

				// 敵の初期化
				std::vector<Enemy*> enemies;  // 4体の敵を格納する配列
				enemies.push_back(enemy1);
				enemies.push_back(enemy2);
				enemies.push_back(enemy3);
				enemies.push_back(enemy4);


				// 敵1を倒す抽選 (弱チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[0]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[0]->SetIsActive(false);
					EnemyBONUSGameCount = 20;
				}
				// 敵2を倒す抽選 (弱チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[1]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[1]->SetIsActive(false);
					EnemyBONUSGameCount = 30;
				}
				// 敵3を倒す抽選 (弱チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[2]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[2]->SetIsActive(false);
					EnemyBONUSGameCount = 40;
				}
				// 敵4を倒す抽選 (弱チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[3]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[3]->SetIsActive(false);
					EnemyBONUSGameCount = 50;
				}

				if (rand() % 100 < 30) {  // 30%の確率で敵を出現させる

					// 敵の出現確率
					std::vector<int> probabilities = { 60, 25, 10, 5 };

					enemyGameCount = 30;

					// ランダムで選ばれる敵のインデックスを決定
					int rand_value = rand() % 100;  // 0~99 のランダム値を生成
					int cumulative_prob = 0;
					int selected_enemy_index = -1;

					// 確率に基づいて選ばれる敵を決定
					for (int i = 0; i < probabilities.size(); ++i) {
						cumulative_prob += probabilities[i];
						if (rand_value < cumulative_prob) {
							selected_enemy_index = i;  // この敵が選ばれる
							break;
						}
					}

					// 選ばれた敵を描画
					if (selected_enemy_index != -1&& mode_ == 0) {
						enemies[selected_enemy_index]->Initialize();  // 敵を初期化
						enemies[selected_enemy_index]->SetIsActive(true);  // 敵をアクティブにする
						isEnemyActive = true;
					}
					if (mode_ == 0) {
						mode_ = 1;
					}
				}
			}

			// --------------------------------------- 強チェリー ------------------------------------
			if (lever_->GetStorenum() == 97) {
				voiceHandle3_ = audio_->PlayWave(Get, false);
				targetMedal = Medal + 2;
				animating = true;

				// 敵の初期化
				std::vector<Enemy*> enemies;  // 4体の敵を格納する配列
				enemies.push_back(enemy1);
				enemies.push_back(enemy2);
				enemies.push_back(enemy3);
				enemies.push_back(enemy4);

				
				// 敵1を倒す抽選 (強チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[0]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[0]->SetIsActive(false);
					EnemyBONUSGameCount = 20;
				}
				// 敵2を倒す抽選 (強チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[1]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[1]->SetIsActive(false);
					EnemyBONUSGameCount = 30;
				}
				// 敵3を倒す抽選 (強チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[2]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[2]->SetIsActive(false);
					EnemyBONUSGameCount = 40;
				}
				// 敵4を倒す抽選 (強チェリー)
				if (isEnemyActive && rand() % 100 < 100 && mode_ == 1 && enemies[3]) {  // 100%の確率で敵を倒せる
					isEnemyActive = false;
					enemies[3]->SetIsActive(false);
					EnemyBONUSGameCount = 50;
				}

				if (rand() % 100 < 80) {  // 80%の確率で敵を出現させる

					// 敵の出現確率
					std::vector<int> probabilities = { 60, 25, 10, 5 };

					enemyGameCount = 30;

					// ランダムで選ばれる敵のインデックスを決定
					int rand_value = rand() % 100;  // 0~99 のランダム値を生成
					int cumulative_prob = 0;
					int selected_enemy_index = -1;

					// 確率に基づいて選ばれる敵を決定	
					for (int i = 0; i < probabilities.size(); ++i) {
						cumulative_prob += probabilities[i];
						if (rand_value < cumulative_prob) {
							selected_enemy_index = i;  // この敵が選ばれる
							break;
						}
					}

					// 選ばれた敵を描画
					if (selected_enemy_index != -1 && mode_ == 0) {
						enemies[selected_enemy_index]->Initialize();  // 敵を初期化
						enemies[selected_enemy_index]->SetIsActive(true);  // 敵をアクティブにする
						isEnemyActive = true;
					}
					if (mode_ == 0) {
						mode_ = 1;
					}
				}
			}
		}

		// ゲームカウントを進める
		if (isEnemyActive && !enemyDefeated) {
			gameCount++;
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


	if (isWaitingForPush) {
		if (pushButton_->WasJustPressed()) {
			puchun_->Start();
			putyunMode = 1;
			pushButton_->SetToggle(false); 

		}
	}
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

	// 背景
	BGsprite_->Draw();

	// スロット内の背景
	DanjonBGSprite->Draw();


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

	//背景コイン
	for (Coin* coin : coins_) {
		coin->Draw();
	}

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

	if (mode_ == 2) {
		BONUS_->StartBonus();
		// BONUS図柄
		BONUS_->Draw();
	}

	// ボタン1
	button2_->Draw();
	// ボタン2
	button3_->Draw();
	// ボタン3
	button1_->Draw();

	// タイトル描画
	title_->Draw();

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

	// メダルの数を描画
	MedalDraw();

	// 残金描画
	MoneyDraw();

	// 矢印を描画
	Arrow_->Draw();

	playerSprite_->Draw();


	if (isEnemyActive == true) {
		 
		// 敵が出現している場合は描画
		if (enemy1->GetIsActive()) {
			enemySprite_[0]->Draw();
		}
		else if (enemy2->GetIsActive()) {
			enemySprite_[1]->Draw();
		}
		else if (enemy3->GetIsActive()) {
			enemySprite_[2]->Draw();
		}
		else if (enemy4->GetIsActive()) {
			enemySprite_[3]->Draw();
		}

		if (lever_->IsPulled() && !wasLeverPulledLastFrame) {
			enemyGameCount--;
		}

		/*if (lever_->GetStorenum() == 150 && putyunMode == 0) {
			puchun_->Start();
			putyunMode = 1;
		}*/



		if (putyunMode == 1) {
			// 必要であれば敵も非アクティブに
			enemy1->SetIsActive(false);
			enemy2->SetIsActive(false);
			enemy3->SetIsActive(false);
			enemy4->SetIsActive(false);
		}
		
		puchun_->Draw();

		// 今のレバー状態を保存（次フレームのために）
		wasLeverPulledLastFrame = lever_->IsPulled();

		if (enemyGameCount <= 0) {
			isEnemyActive = false;

			isEnemyGameFlag = false;

			enemyGameCount = 30;
			wasLeverPulledLastFrame = false;

			putyunMode = 0;

			// 必要であれば敵も非アクティブに
			enemy1->SetIsActive(false);
			enemy2->SetIsActive(false);
			enemy3->SetIsActive(false);
			enemy4->SetIsActive(false);
		}
	}



	if (input_->TriggerKey(DIK_E)) {
		// 音声再生
		voiceHandle5_ = audio_->PlayWave(Click, false);
		isRule = !isRule; // トグル（反転）
	}
	if (isRule) {
		RuleSprite_->Draw(); // 表示
	}

	// 操作説明描画
	OperationSprite_->Draw();

	// 退室
	OutRoomSprite_->Draw();

	// 退室選択
	// 退室選択
	if (input_->TriggerKey(DIK_TAB)) {
		isOutRoom = !isOutRoom;
	}
	if (input_->TriggerKey(DIK_LEFT)) {
		isOutRoom2 = !isOutRoom2;
		if (isOutRoom2) {
			isOutRoom3 = false; // 3を消す
		}
	}
	if (input_->TriggerKey(DIK_RIGHT)) {
		isOutRoom3 = true;
		isOutRoom2 = false; // 2を消す
	}

	// SPACEキーで右の退室表示を消す
	if (isOutRoom3 && input_->TriggerKey(DIK_SPACE)) {
		isOutRoom3 = false;
		isOutRoom = false;
	}

	// 描画処理
	if (isOutRoom) {
		OutRoomPickSprite_->Draw();
	}
	if (isOutRoom2 && !isOutRoom3) {
		OutRoomPickSprite2_->Draw();
	}
	if (isOutRoom3 && !isOutRoom2) {
		OutRoomPickSprite3_->Draw();
	}


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// メダルを徐々に増やす処理
void GameScene::UpdateMedal(float deltaTime) {
	if (animating) {
		timeElapsed += deltaTime;

		// 時間が経過したらメダル数を1増加させる
		if (timeElapsed >= medalIncrementTime) {
			timeElapsed = 0.0f; // 経過時間をリセット
			if (Medal < targetMedal) {
				Medal++; // メダルを1増加
				BONUSMedal++;

				if (lever_->GetStorenum() >= 301 && BONUSMedal <= 7) {
					Medal++;
				}

				// コインを1個ずつ出す
				SpawnCoins(1);
			}
			else {
				targetMedal = 0;
				animating = false; // メダル数が目標に達したらアニメーションを停止
			}
		}
	}
}

//ゲームカウントを描画
void GameScene::DrawGameCount() {
	//ゲームカウントを最大4桁に制限
	if (GameCount > 9999) {
		GameCount = 9999; //5桁以上にならないようにする
	}

	//メダル数を文字列に変換
	std::string countStr = std::to_string(GameCount);
	size_t digitCount = countStr.length();

	// 基準となる描画開始位置
	float x = 1230.0f, y = 8.0;
	float spacing = 50.0f; // 画像の間隔

	//各桁を対応する画像で描画
	for (size_t i = 0; i < digitCount; i++) {
		int index = countStr[digitCount - 1 - i] - '0'; // 0～9 のインデックス
		if (index >= 0 && index < 10) {
			medalSprite_[i]->SetTextureHandle(TextureHandle_[index]); // テクスチャを変更
			medalSprite_[i]->SetPosition({ x, y }); // 位置を更新
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
	float baseX = 1230.0f, y = 100.8f;
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
}

void GameScene::SpawnCoins(int count) {
	for (int i = 0; i < count; ++i) {
		Coin* coin = new Coin();
		coin->Initialize(modelCoin_, &viewProjection_);
		coin->SetRandomBehavior();
		coin->SetAudio(audio_, DropCoinSE_);
		coins_.push_back(coin);
	}
}


void GameScene::MoneyDraw() {
	// 所持金の上限設定（最大6桁 = 999999）
	if (money_ > 999999) {
		money_ = 999999;
	}

	// 所持金を文字列に変換
	std::string moneyStr = std::to_string(money_);
	size_t digitCount = moneyStr.length();

	// 描画開始位置（右寄せ）
	float baseX = 1230.0f, y = 200.0f; // メダルとはy座標を少しずらす
	float spacing = 50.0f;
	float x = baseX - (spacing * (digitCount - 1));

	// 数字ごとに対応する画像を描画
	for (size_t i = 0; i < digitCount; i++) {
		int index = moneyStr[i] - '0';
		if (index >= 0 && index < 10) {
			MoneySprite_[i]->SetTextureHandle(TextureHandle_[index]);
			MoneySprite_[i]->SetPosition({ x, y });
			MoneySprite_[i]->Draw();
		}
		x += spacing;
	}

	// MaxMoney が前フレームから46減っていたら、money_ を1000減らす
	if (prevMaxMoney_ - MaxMoney >= 46) {
		int numOf46s = (prevMaxMoney_ - MaxMoney) / 46;
		money_ -= 1000 * numOf46s;

		// 上限を下回らないように調整
		if (money_ < 0) {
			money_ = 0;
		}

		// prevMaxMoney_ を更新（1度に複数回分減っている場合も対応）
		prevMaxMoney_ = MaxMoney;
	}
}
