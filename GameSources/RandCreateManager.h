/*!
@file RandCreateManager.h
@brief ƒ‰ƒ“ƒ_ƒ€‚È‚©‚¯‚ç‚Ì”z’u
’S“–FO•r—T‘¾
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandCreateManager :public GameObject
	{
	private:

	public:
		RandCreateManager(shared_ptr<Stage>& stagePtr);
		~RandCreateManager()override;
		void OnCreate() override;
	};
}
