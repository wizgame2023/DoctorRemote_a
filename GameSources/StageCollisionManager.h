/*!
@file StageCollisionManager.h
@brief ŠÔ‚Ì•\¦
’S“–FO•r—T‘¾
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageCollisionManager :public GameObject
	{
	private:
		bool m_CollisionSwhich;
	public:
		StageCollisionManager(shared_ptr<Stage>& stagePtr);
		~StageCollisionManager();

		void OnCreate()override;
		void OnUpdate()override;

	};
}