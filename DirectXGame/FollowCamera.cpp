#include "FollowCamera.h"
#include "MatrixMath.h"

void FollowCamera::Initialize() { 

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	viewProjection_.rotation_.y = 0.0f;

}

void FollowCamera::Update() 
{
	//追従対象者がいなければ
	if (target_) {
		//追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		//オフセットの角度から回転行列を計算する
		offset = TransformNormal(offset, MakeRotateYMatrix(viewProjection_.rotation_.y));

		//座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		const float rotate = 0.05f;

		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * rotate;
	}

	//ビュー行列の更新と転送
	viewProjection_.UpdateMatrix();
}
