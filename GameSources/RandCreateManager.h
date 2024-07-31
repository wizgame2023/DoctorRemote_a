/*!
@file RandCreateManager.h
@brief ランダムオブジェクトの配置
担当：三瓶
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RandCreateManager :public GameObject
	{
	private:
		wstring m_ObjMapDataName;//データの名前を保存する変数
		int m_MapSize;//マップの大きさを保存する変数
		int m_Num;//どのくらいのオブジェクト生成するかの変数
	public:
		RandCreateManager(shared_ptr<Stage>& stagePtr,wstring objMapDataName,int mapSize,int Num);
		~RandCreateManager()override;
		void OnCreate() override;
	};
}
