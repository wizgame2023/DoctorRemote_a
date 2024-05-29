/*!
@file BreakWall.h
@brief 壊れる壁
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class BreakWall : public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotate;
		int m_Hp;
		weak_ptr<Bullet> m_bullet;
		shared_ptr<CollisionObb> m_ptrCollider;
		shared_ptr<Transform> m_Trans;

		Vec3 m_StartPosition;

	public:
		BreakWall(const shared_ptr<Stage>& StagePtr,		
						Vec3 m_Position,
						Vec3 m_Scale,
						Vec3 m_Rotate
			     );
		~BreakWall();
		void OnCreate()override;//初期化UnityでいうところのStart
		void OnUpdate()override;//アップデート
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時
		void OnCollisionExit(shared_ptr<GameObject>& Other) override;//コリジョンが抜けたとき

	};
}
//end namespace basecross
