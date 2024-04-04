/*!
@file GameStage.h
@brief 弾
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Bullet : public GameObject
	{
	private:
		Vec3 m_Position;
		Vec3 m_Scale;
		float m_Speed;
	public:
		Bullet(
			   const shared_ptr<Stage>& StagePtr,
			   const Vec3& Position,
		       const Vec3& Scale,
			   float Speed
		       );
		~Bullet();
		void OnCreate()override;//初期化UnityでいうところのStart
		void OnUpdate()override;//アップデート
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時
	};
}
//end namespace basecross