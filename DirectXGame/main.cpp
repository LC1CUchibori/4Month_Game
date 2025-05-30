#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "ヘッダーファイル/TitleScene.h"
#include "ヘッダーファイル/GameClear.h"
#include "ヘッダーファイル/GameOver.h"

GameScene *gameScene = nullptr;
TitleScene *titleScene = nullptr;
GameClear *gameClear = nullptr;

// シーン
enum class Scene {

	kUnknown = 0,

	kTitle,
	kGame,
	kGameCler,
};

//現在シーン
Scene scene = Scene::kUnknown;

//シーン切り替え処理
void ChangeScene();

//シーンの更新
void UpdateScene();

//シーンの描画
void DrawScene();

bool isTabPressed = false;
bool isLeftSelected = false;

bool isChangeToGameRequested = false;
float changeToGameTimer = 0.0f;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"3161_スマスロ:クエスト");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// 最初のシーンの初期化
	scene = Scene::kTitle;
	titleScene = new TitleScene;
	titleScene->Initialize();

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		//シーン切り替え
		ChangeScene();
		//現在のシーン
		UpdateScene();
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		//現在のシーンの描画
		DrawScene();
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	SafeDelete(gameScene);
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();
	delete titleScene;

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		// Enterキーで遷移リクエスト
		if (Input::GetInstance()->TriggerKey(DIK_SPACE) && !isChangeToGameRequested) {
			isChangeToGameRequested = true;
			changeToGameTimer = 0.0f;
		}

		// 遷移リクエスト中
		if (isChangeToGameRequested) {
			changeToGameTimer += 1.0f / 60.0f; // フレームレート60FPS想定

			if (changeToGameTimer >= 3.0f) {
				// シーンの変更
				scene = Scene::kGame;
				// 旧シーンの解放
				delete titleScene;
				titleScene = nullptr;
				// 新シーンの生成と初期化
				gameScene = new GameScene();
				gameScene->Initialize();

				// リセット
				isChangeToGameRequested = false;
				changeToGameTimer = 0.0f;
			}
		}
		break;
	case Scene::kGame:
		// TAB押下で状態変更
		if (Input::GetInstance()->TriggerKey(DIK_TAB)) {
			isTabPressed = true;
			isLeftSelected = false;
		}

		// TAB状態中にLEFT押下で選択
		if (isTabPressed && Input::GetInstance()->TriggerKey(DIK_LEFT)) {
			isLeftSelected = true;
		}

		// TAB状態中にRIGHT押下で選択解除
		if (isTabPressed && Input::GetInstance()->TriggerKey(DIK_RIGHT)) {
			isLeftSelected = false;
		}

		//　ゴールした時
		if (isTabPressed && isLeftSelected && Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			// シーンの変更
			scene = Scene::kGameCler;
			// 旧シーンの解放
			delete gameScene;
			int currentMedals = gameScene->GetMedalCount();
			gameScene = nullptr;
			// 新シーンの生成と初期化
			gameClear = new GameClear();
			gameClear->Initialize();
			gameClear->SetMedalCount(currentMedals);

			isTabPressed = false;
			isLeftSelected = false;
		}
		break;
	case Scene::kGameCler:
		if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
			// シーンの変更
			scene = Scene::kTitle;
			// 旧シーンの解放
			delete gameClear;
			gameClear = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene();
			titleScene->Initialize();
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kGameCler:
		gameClear->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kGameCler:
		gameClear->Draw();
		break;
	}
}