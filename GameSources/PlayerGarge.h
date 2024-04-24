/*!
@file PlayerGarge.h
@brief プレイヤーの体力ゲージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerGarge :public GameObject{
	private:
		float m_currentHp;
		float m_maxHp;
		float m_ratioHp;
		shared_ptr<Garge> m_garge;
		shared_ptr<Transform> m_trans;

		wstring m_meshResName;

		Vec3 m_screen;
	public:
		PlayerGarge(const shared_ptr<Stage>& stagePtr);
		virtual ~PlayerGarge(){} 
		
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		float GetHp();
		void SetHp(float hp);
	};
}
//end namespace basecross
