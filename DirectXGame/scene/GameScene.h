#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "DebugCamera.h"
#include <memory>
#include "Skydome.h"
#include "Ground.h"
#include "FollowCamera.h"

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//3Dモデル
	std::unique_ptr<Model> model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//3Dモデル
	std::unique_ptr<Model> modelPlayer_ = nullptr;
	//自キャラ
	std::unique_ptr<Player> player_;

	// 3Dモデル
	std::unique_ptr<Model> modelEnemy_ = nullptr;
	// 敵
	std::unique_ptr<Enemy> enemy_;

	//3Dモデル
	std::unique_ptr<Model> modelSkydome_ = nullptr;
	//天球
	std::unique_ptr<Skydome> skydome_;

	//3Dモデル
	std::unique_ptr<Model> modelGround_ = nullptr;
	//地面
	std::unique_ptr<Ground> ground_;

	//デバックカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	int isDebugCameraActive_;

	//追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	//3Dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyL_arm_;
	std::unique_ptr<Model> modelEnemyR_arm_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
