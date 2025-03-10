#pragma once
class Button
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    void Press();

    void Push();

    const WorldTransform& GetWorldTransform() const { return worldTransform_; }

    void SetPosition(const Vector3& position);

    bool IsPressed() const { return isPressed_; }
 
    void Reset() { isPressed_ = false; } // 必要に応じてリセットも

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;
    // ボタンの初期位置
    Vector3 originalPosition_;

    // Pushボタンのモデル
    Model* modelPushButton_ = nullptr;

    // 押し込み状態フラグ
    bool isPressed_ = false;
    float pressTimer_ = 0.0f;
    // 押し込みの持続時間
    const float pressDuration_ = 0.2f;
    // 押し込みの深さ
    const float pressedOffset_ = 0.13f;
};

