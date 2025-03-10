#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Slot.h"

void Slot::Initialize(Model *model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;

	modelLeverParts_ = model;

    modelMedalCountButton_ = model;

    modelMoneyBox_ = model;
}

void Slot::Update()
{
}

void Slot::Draw()
{
	// 本体
	model_->Draw(worldTransform_, *viewProjection_);
	// レバーのパーツ
	modelLeverParts_->Draw(worldTransform_, *viewProjection_);
    // メダルカウントボタン
    modelMedalCountButton_->Draw(worldTransform_, *viewProjection_);
    // 投入機
    modelMoneyBox_->Draw(worldTransform_, *viewProjection_);
}

bool Slot::CheckHorizontal()
{
    {
        // 各リールのシンボルを取得
        Reel::Symbol symbol1 = reel1_->GetResultSymbol();
        Reel::Symbol symbol2 = reel2_->GetResultSymbol();
        Reel::Symbol symbol3 = reel3_->GetResultSymbol();

        bool Ret = false;

        if (symbol1== symbol2&& symbol2 == symbol3) {
            true;
        }
        return Ret;
    }
}

bool Slot::CheckVertical()
{
    // 縦の役を成立させるために、各リールのシンボルを取得
    std::vector<Reel::Symbol> reel1Symbols = reel1_->GetSymbols();
    std::vector<Reel::Symbol> reel2Symbols = reel2_->GetSymbols();
    std::vector<Reel::Symbol> reel3Symbols = reel3_->GetSymbols();

    // 3リール全体で縦の組み合わせが一致しているかを確認
    for (int i = 0; i < reel1Symbols.size(); i++)
    {
        if (reel1Symbols[i] == reel2Symbols[i] && reel2Symbols[i] == reel3Symbols[i])
        {
            return true; // 縦が揃った場合
        }
    }

    return false; // 縦が揃わなければ役成立しない
}

