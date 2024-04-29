/*!
@file Sprite.h
@brief スプライト
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite :public GameObject {

	public:
		Sprite(const shared_ptr<Stage>& stagePtr);
		virtual ~Sprite(){}

	};

}
//end namespace basecross