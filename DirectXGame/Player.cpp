#include "Player.h"
#include <cassert>
void Player::Initialize(Model* model) 
{
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Player::Update() 
{ 
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		//速さ
		const float speed = 0.3f;

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

	//行列の計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
