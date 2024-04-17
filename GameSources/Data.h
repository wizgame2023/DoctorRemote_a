/*!
@file Player.h
@brief プレイヤー
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Data :public GameObject {
	public:
		Data(shared_ptr<Stage>& StagePtr);
		virtual ~Data(){}

		virtual void OnCreate() override;

	};
}