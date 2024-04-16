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
		std::wstring m_meshResName;

	public:
		// 構築と破棄
		Block(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_meshResName(L"DEFAULT_CUBE")
		{
		}
		virtual ~Block()
		{
		}

		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
