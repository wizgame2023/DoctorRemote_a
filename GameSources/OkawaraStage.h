/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class O_GameStage :public Stage
	{
		void CreateViewLight(); //ビューの作成
		void CreateBullet();//弾の作成
		void CreatePlayer();//プレイヤーの作成
		void CreateEnemyPiece();//敵のかけらの作成
		void CreateEnemy();//敵の作成
		void CreateRadar();//レーダーの作成
		void CreateWall();
		void CreateBreakWall();
		void CreateRecoveryWall();
		void CreateBlock();
		void CreateBlockSecond();
		void CreateMap();
	public:
		O_GameStage() :Stage(){}
		~O_GameStage() {}
		virtual void OnCreate()override;

	};
}
//end namespace basecross

