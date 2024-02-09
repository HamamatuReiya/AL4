#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"

class Title {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Title();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Title();

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

	void RoopInitialize();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene(){return SceneType::kGamePlay;}

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t titleTexture = 0;
	Sprite* titleSprite_ = nullptr;
	Vector2 titleMove_ = {0.0f, -10.0f};
	float titleSpeed_ = 1.0f;

	bool isSceneEnd = false;

	uint32_t fadeTexture_ = 0;
	Sprite* fadeSprite_ = nullptr;
	Vector4 fadeColor_ = {1.0f, 1.0f, 1.0f, 0.0f};
	bool isFade_ = false;

	uint32_t backgroundTexture_ = 0;
	Sprite* backgroundSprite_ = nullptr;
	
};
