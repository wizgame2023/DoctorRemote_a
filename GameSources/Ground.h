/*!
@file Ground.h
@brief ’n–Ê
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Ground : public GameObject;
	//--------------------------------------------------------------------------------------
	class Ground : public GameObject
	{
	public:
		// \’z‚Æ”jŠü
		Ground(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Ground()
		{
		}

		virtual void OnCreate() override; // ‰Šú‰»
		//virtual void OnUpdate() override; // XV
		//virtual void OnDraw() override; // •`‰æ
	};

}
//end basecross
