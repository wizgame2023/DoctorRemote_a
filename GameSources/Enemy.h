/*!
@file GameStage.h
@brief ゲームステージ
担当　大河原
*/

#pragma once
#include "stdafx.h" 
#include "Bullet.h"
#include "TutorialManager.h"

namespace basecross {
	class Enemy :public GameObject
	{
		bool m_enemyflag;
		bool m_posX;
		float m_Hp;
		
		Vec3 m_pos;
		Vec3 m_posCur;
		Vec3 m_rot;
		Vec3 m_scale;

		wstring m_meshResName;

		weak_ptr<Bullet> m_bullet;
		shared_ptr<Transform> m_trans;

	public:
		Enemy(const shared_ptr<Stage>& StaegePtr);
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale);

		~Enemy() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void SetEnemy(bool enemy);
		bool GetEnemy();
	};
}
//end namespace basecross
