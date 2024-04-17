/*!
@file Block.h
@brief ブロックのオブジェクト
*/

#pragma once
#include "stdafx.h"


namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Block : public GameObject;
	//--------------------------------------------------------------------------------------
	class Block : public GameObject
	{

	public:
		Block(const shared_ptr<Stage>& StaegePtr);
		 ~Block(){}
		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
