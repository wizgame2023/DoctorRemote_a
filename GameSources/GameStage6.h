/*!
@file GameStage6.h
@brief ゲームステージ6
担当：三瓶
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameStage6 :public Stage
	{
		bool m_PieceFlag;//ピースゲージがマックスになったら発動するフラグ
		shared_ptr<SoundItem> m_BGM;
		int m_CareerFlag;//ステージ全体のフラグ
		int m_BigPieceLength;//BigPieceの合計の数

		void CreateViewLight(); //ビューの作成
		void CreatePlayer();//プレイヤーの作成
		void CreateEnemyPiece();//敵のかけらの作成
		void CreateEnemyPiece2();//敵のかけらの作成（集まっているかけら何個出るか決める）
		void CerateBreakEnemyPiece();//壊れる壁の後ろに生成するかけら
		void CreateEnemy();//敵の作成
		void CreateRadar();//レーダーの作成
		void CreateMap();//マップの生成
		void CreateMiniMap();//ミニマップの生成
		void CreateEffect();//エフェクトの作成
		void RandamPiecePosition(Vec3 originPosition);//ランダムに
		void CollisionActive(bool On);//コリジョンの判定のきりかえ
		shared_ptr<SingleView> m_View;//ビューの変数

	public:
		//構築と破棄
		GameStage6() :Stage() {}
		virtual ~GameStage6() {}

		virtual void OnCreate()override; //初期化
		void OnUpdate()override;//更新

		void BaseBGM();
		void BossBGM();
		virtual void OnDestroy() override;

		void SetCollisionSwich(bool ONorOFF);

	};
}