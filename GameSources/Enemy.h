/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h" 

namespace basecross {
	class Enemy :public GameObject
	{
		float m_Hp;
	public:
		Enemy(const shared_ptr<Stage>& StaegePtr);
		~Enemy() {}
		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
	};
}
//end namespace basecross
