/*!
@file BreakWall.h
@brief •Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Wall : public GameObject
	{
	public:
		Wall(const shared_ptr<Stage>& StagePtr);
		~Wall() {}
		virtual void OnCreate() override; // ‰Šú‰»
		//virtual void OnUpdate() override; // XV
		//virtual void OnDraw() override; // •`‰æ

	};

}
//end namespace basecross

