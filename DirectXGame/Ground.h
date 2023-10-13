#pragma once
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 地面
/// </summary>
class Ground {
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};
