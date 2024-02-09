#include "Title.h"

Title::Title() {}

Title::~Title() {}

void Title::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	titleTexture = TextureManager::Load("title2.png");
	titleSprite_ = Sprite::Create(titleTexture, {0, 0});

	fadeTexture_ = TextureManager::Load("fade.png");
	fadeSprite_ = Sprite::Create(fadeTexture_, {0, 0}, {1.0f, 1.0f, 1.0f, 0.0f});
}

void Title::Update() { 

	if (isFade_ == true) {
		fadeColor_.w += 0.01f;
	}
	
	if (fadeColor_.w >= 1.0f) {
		isSceneEnd = true;
		fadeColor_.w = 0.0f;
		isFade_ = false;
	}
	fadeSprite_->SetColor(fadeColor_);

	//ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	//ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			isFade_ = true;
		}
	}
}

void Title::Draw() { 
	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	titleSprite_->Draw();

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
	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	fadeSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void Title::RoopInitialize() { isSceneEnd = false; }
