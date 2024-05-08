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
		void CreateEnemyPiece();//敵のかけらの作成
		void CreateEnemy();//敵の作成
		void CreateRadar();//レーダーの作成
		void CreateEffect();//エフェクトの作成
	public:
		//構築と破棄
		SanpeiStage() :Stage() {}
		virtual ~SanpeiStage() {}

		virtual void OnCreate()override; //初期化
	};

}
//end basecross

