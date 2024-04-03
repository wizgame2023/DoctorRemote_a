/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h" 

namespace basecross {
	class Enemy :public GameObject
	{
	public:
		Enemy(const shared_ptr<Stage>& StaegePtr);
		~Enemy() {}
		virtual void OnCreate() override;
		//void OnUpdate() override;
	};
}
//end namespace basecross
