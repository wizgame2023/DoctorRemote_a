/*!
@file PlayerGarge.h
@brief プレイヤーの体力ゲージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerGarge :public GameObject {
	public:
		PlayerGarge(const shared_ptr<Stage>& stagePtr);
		virtual ~PlayerGarge(){} 
		
	};
}
//end namespace basecross
