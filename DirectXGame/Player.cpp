#include "Player.h"
#include <cassert>

void Player::Initialize(const std::vector<Model*>& models) {
	BaseCharacter::Initialize(models);

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, -20.0f};

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

	worldTransformHammer_.Initialize();
	worldTransformHammer_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformHammer_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHammer_.translation_ = {0.0f, 1.0f, 0.0f};
}

void Player::Update() 
{ 
	if (behaviorRequest_) {
		// 振るまいを変更する
		behavior_ = behaviorRequest_.value();
		// 各振るまいごとの初期化を実行
		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootInitialize();
			break;
		case Behavior::kAttack:
			BehaviorAttackInitialize();
			break;
		}
		// ふるまいリクエストをリセット
		behaviorRequest_ = std::nullopt;
	}

	BaseCharacter::Update();

	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.parent_ = &worldTransform_;
	worldTransformL_arm_.parent_ = &worldTransform_;
	worldTransformR_arm_.parent_ = &worldTransform_;
	worldTransformHammer_.parent_ = &worldTransform_;

	switch (behavior_) {
		// 通常行動
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
		// 攻撃行動
	case Behavior::kAttack:
		BehaviorAttackUpdate();
		break;
	}

	UpdateFloatingGimmick();

	//行列の計算
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	worldTransformHammer_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	// 3Dモデル描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);
	if (isHammerDraw_ == true) {
		models_[4]->Draw(worldTransformHammer_, viewProjection);
	}
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
	const float floating = 0.25f;
	// 浮遊の座標を反映
	worldTransform_.translation_.y = std::sin(floatingParameter_) * floating;
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::RoopInitialize() { 
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, -20.0f};
	
}

void Player::BehaviorRootInitialize() { 
	isHammerDraw_ = false;
	worldTransformL_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
}

void Player::BehaviorRootUpdate() {

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ

		float speed = 0.3f;

		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			speed = 0.6f;
		}
		
		// 移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};
		// 移動量に速さを反映
		move = VectorMultiply(speed, Normalize(move));

		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		if (move.z != 0 || move.y != 0) {
			worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		}

		/*if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_X) {
			attackTime = 120.0f;
			behaviorRequest_ = Behavior::kAttack;
		}*/
	}

	
}

void Player::BehaviorAttackInitialize() { 
	isHammerDraw_ = true;

}

void Player::BehaviorAttackUpdate() {
	worldTransformL_arm_.rotation_.x = worldTransformHammer_.rotation_.x + 3.08f;
	worldTransformR_arm_.rotation_.x = worldTransformHammer_.rotation_.x + 3.08f;
	if (isHammerSet_ == false) {
		if (worldTransformHammer_.rotation_.x >= -0.4f) {
			worldTransformHammer_.rotation_.x -= 0.4f;
		}
		if (worldTransformHammer_.rotation_.x <= -0.4f) {
			worldTransformHammer_.rotation_.x = -0.4f;
			stanbyTime++;
			if (stanbyTime >= 12) {
				isHammerSet_ = true;
				stanbyTime = 0;
			}
		}
	} else if (isHammerSet_ == true) {
		if (worldTransformHammer_.rotation_.x <= 1.6f) {
			worldTransformHammer_.rotation_.x += 1.0f;
		}
		if (worldTransformHammer_.rotation_.x >= 1.6f) {
			worldTransformHammer_.rotation_.x = 1.6f;
			stanbyTime++;
			if (stanbyTime >= 12) {
				isHammerSet_ = false;
				behaviorRequest_ = Behavior::kRoot;
				stanbyTime = 0;
			}
		}
	}
}
