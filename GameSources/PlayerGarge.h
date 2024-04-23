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
	public:
		PlayerGarge(const shared_ptr<Stage>& stagePtr);
		virtual ~PlayerGarge(){} 
		
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end namespace basecross
