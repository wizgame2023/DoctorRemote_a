/*!
@file PlayerGarge.h
@brief プレイヤーの体力ゲージ
担当：逸見
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
