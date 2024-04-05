/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class SanpeiStage : public Stage {
		
		void CreateViewLight(); //ビューの作成
		void CreateBullet();//弾の作成
		void CreatePlayer();//プレイヤーの作成
	public:
		//構築と破棄
		SanpeiStage() :Stage() {}
		virtual ~SanpeiStage() {}

		virtual void OnCreate()override; //初期化
	};

}
//end basecross

