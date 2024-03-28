/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Bullet : public GameObject
	{
	private:
		Vec3 m_Position;
		Vec3 m_Scale;
	public:
		Bullet(
			   const shared_ptr<Stage>& StagePtr,
			   const Vec3& Position,
		       const Vec3& Scale
		       );
		~Bullet();
		void OnCreate()override;//初期化UnityでいうところのStart
		void OnUpdate()override;//アップデート
	};
}
//end namespace basecross