#include "Player.h"
#include <cassert>



void Player::Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm) 
{
	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.Initialize();
	worldTransformBody_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBody_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.Initialize();
	worldTransformHead_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformHead_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 1.5f, 0.0f};
	worldTransformL_arm_.Initialize();
	worldTransformL_arm_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_arm_.translation_ = {-0.5f, 1.25f, 0.0f};
	worldTransformR_arm_.Initialize();
	worldTransformR_arm_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm_.translation_ = {0.5f, 1.25f, 0.0f};
}

void Player::Update() 
{ 
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		//速さ
		const float speed = 0.3f;

		worldTransformBody_.parent_ = &worldTransform_;
		worldTransformHead_.parent_ = &worldTransform_;
		worldTransformL_arm_.parent_ = &worldTransform_;
		worldTransformR_arm_.parent_ = &worldTransform_;


		//移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 
			0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};
		//移動量に速さを反映
		move = VectorMultiply(speed, Normalize(move));

		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));

		//移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		if (move.z != 0 || move.y != 0) {
			worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		}
	}

	UpdateFloatingGimmick();

	//行列の計算
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {

	modelFighterBody_->Draw(worldTransformBody_, viewProjection);
	modelFighterHead_->Draw(worldTransformHead_, viewProjection);
	modelFighterL_arm_->Draw(worldTransformL_arm_, viewProjection);
	modelFighterR_arm_->Draw(worldTransformR_arm_, viewProjection);

}

void Player::InitializeFloatGimmick() 
{ floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() 
{
	//浮遊移動のサイクル<frame>
	const uint16_t period = uint32_t(90.0f);
	//1フレームでのパラメータ加算値
	const float step = 2.0f * (float)M_PI / (float)period;

	// パラメータを1ステップ分加算
	floatingParameter_ += step;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * (float)M_PI);

	// 浮遊の幅<m>
	const float floating = 0.125f;
	// 浮遊の座標を反映
	worldTransform_.translation_.y = std::sin(floatingParameter_) * floating;
}
