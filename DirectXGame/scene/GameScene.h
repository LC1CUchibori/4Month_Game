#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "ヘッダーファイル/Slot.h"
#include "ヘッダーファイル/Reel.h"
#include "ヘッダーファイル/Reel2.h"
#include "ヘッダーファイル/Reel3.h"
#include "ヘッダーファイル/Lever.h"
#include "ヘッダーファイル/Button.h"
#include "ヘッダーファイル/PushButton.h"
#include "Puchun.h"
#include "Enemy.h"
#include "Player.h"
#include <Coin.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//メダルを徐々に増やす処理
	void UpdateMedal(float deltaTime);

	//回転数を描画
	void DrawGameCount();

	//メダルの数を描画
	void MedalDraw();

	//クリアフラグのgetter
	bool IsCleared() const { return cleared_; }

	//デスフラグのgetter
	bool IsDead() const { return finished_; }

	void SpawnCoins(int count);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// スロット
	Slot* slot_ = nullptr;
	Model* modelSlot_ = nullptr;

	// スロットリール1
	Reel* reel1_ = nullptr;
	Model* modelReel_ = nullptr;
	// スロットリール2
	Reel2* reel2_ = nullptr;
	Model* modelReel2_ = nullptr;
	// スロットリール3
	Reel3* reel3_ = nullptr;
	Model* modelReel3_ = nullptr;

	// レバー
	Lever* lever_ = nullptr;
	Model* modelLever_ = nullptr;

	// レバーパーツ
	Slot* leverParts_ = nullptr;
	Model* modelLeverParts_ = nullptr;

	// ボタン1
	Button* button2_ = nullptr;
	// ボタン2
	Button* button3_ = nullptr;
	// ボタン3
	Button* button1_ = nullptr;
	Model* modelButton_ = nullptr;

	// Pushボタン
	PushButton* pushButton_ = nullptr;
	Model* modelPushButton_ = nullptr;

	// メダルカウントボタン
	Slot* medalCountButton_ = nullptr;
	Model* modelMedalCountButton_ = nullptr;

	// 投入機
	Slot* MoneyBox_ = nullptr;
	Model* modelMoneyBox_ = nullptr;

	//背景メダルモデル
	Model* modelCoin_ = nullptr;
	std::list<Coin*> coins_;
	//背景メダルSE
	uint32_t medalFinishSE_ = 0;

	// プレイヤー
	Player* player = nullptr;

	Enemy* enemy1 = nullptr;  // 敵1
	Enemy* enemy2 = nullptr;  // 敵2
	Enemy* enemy3 = nullptr;  // 敵3
	Enemy* enemy4 = nullptr;  // 敵4


	Puchun* puchun_ = nullptr;

	bool reel1IsStopped_ = false;
	bool reel2IsStopped_ = false;
	bool reel3IsStopped_ = false;

	//メダル
	int Medal = 46;
	//目標メダル
	int targetMedal = 0;
	//メダル増加にかかる時間
	float medalIncrementTime = 0.2f;
	//経過時間
	float timeElapsed = 0.0f;
	//アニメーション
	bool animating = false;

	//ゲーム数
	int GameCount = 0;

	// ゲーム数
	int gameCount_ = 0;

	// プレイヤー
	Sprite* playerSprite_ = nullptr;
	uint32_t playerTextureHandle_ = 0;

	// 敵
	Sprite* enemySprite_[4];
	uint32_t enemyTextureHandle_[4];

	// 数字
	Sprite* sprite_[10];
	// メダルカウント用のスプライト
	Sprite* medalSprite_[10];
	//テクスチャハンドル
	uint32_t TextureHandle_[10];

	// 矢印
	Sprite *Arrow_ = 0;
	// テクスチャハンドル
	uint32_t ArrowHandle_ = 0;

	// 背景テクスチャハンドル
	uint32_t BGtextureHandle_ = 0;
	// 背景スプライト
	Sprite* BGsprite_ = nullptr;

	// スロット内の背景スプライト
	Sprite* DanjonBGSprite = nullptr;
	// スロット内の背景テクスチャハンドル
	uint32_t DanjonBGtextureHandle_ = 0;

	//サウンドデータハンドル
	uint32_t SLOT = 0;
	uint32_t Click = 0;
	uint32_t Get = 0;
	uint32_t Retry = 0;
	uint32_t DropCoinSE_ = 0;

	//音声再生ハンドル
	uint32_t voiceHandle1_ = 0u;
	uint32_t voiceHandle2_ = 0u;
	uint32_t voiceHandle3_ = 0u;
	uint32_t voiceHandle4_ = 0u;
	uint32_t voiceHandleCoin_ = 0;

	// 説明
	uint32_t RuleTextureHandle_ = 0;
	Sprite* RuleSprite_ = nullptr;

	// 説明2
	uint32_t Rule2TextureHandle_ = 0;
	Sprite* Rule2Sprite_ = nullptr;

	bool isRule = false; // 最初は非表示

	//リールを動かせなくするフラグ
	bool Realflag = false;

	//終了フラグ
	bool cleared_ = false;
	bool finished_ = false;

	bool isFreePlay = false;

	int gameCount = 0;
	bool isEnemyActive = false;  // 敵が出現したかどうか
	Enemy* activeEnemy = nullptr;  // 現在アクティブな敵
	bool enemyDefeated = false;   // 敵が倒されたかどうか

	int coinsDeletedCount_ = 0; // 消えたコインの数をカウント
};
