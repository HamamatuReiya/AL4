#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読む
	textureHandle_ = TextureManager::Load("Steve.jpg");
	//3Dモデルの生成
	model_.reset(Model::Create());
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//デバックカメラの生成
	debugCamera_ = std::make_unique<DebugCamera>(1280,720);

	//追従カメラの生成
	followCamera_ = std::make_unique<FollowCamera>();
	//追従カメラの初期化
	followCamera_->Initialize();

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//自キャラの生成
	player_ = std::make_unique<Player>();
	//3Dモデルの生成
	modelPlayer_.reset(Model::CreateFromOBJ("player", true));
	//自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	//自キャラの初期化
	player_->Initialize(modelPlayer_.get());

	//天球の生成
	skydome_ = std::make_unique<Skydome>();
	//3Dモデルの生成
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	//天球の初期化
	skydome_->Initialize(modelSkydome_.get());

	//地面の生成
	ground_ = std::make_unique<Ground>();
	//3Dモデルの生成
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	//地面の初期化
	ground_->Initialize(modelGround_.get());


}

void GameScene::Update() {
	player_->Update();
	debugCamera_->Update();
	followCamera_->Update();

	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.matView = followCamera_->GetViewProjection().matView;

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C)) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_B)) {
		isDebugCameraActive_ = false;
	}
#endif
	if (isDebugCameraActive_) {
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.TransferMatrix();
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
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
