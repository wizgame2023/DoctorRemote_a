/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{

		bool m_PlayFlag;//プレイするステージか確認する

		int m_dashStatus;
		int m_bulletLengthStatus;
		int m_PieceStatus;
		int m_chainRangeStatus;
		int m_bulletPowerStatus;
		int m_bulletTimeStatus;

		int m_time;
		int m_gameStage;
		int m_achievementPoint;
		int m_count;
		//--------------------------------------------------------------------------------------
		/*!
		@brief リソースの作成
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;		
		void SetPlayFlag(bool flag);//GameStageをプレイしているかどうか確認する
		bool GetPlayFlag();
		//ステータス
		int GetDash();
		void SetDash(int status);
		void AddDash(int status);
		int GetBulletLength();
		void SetBulletLength(int status);
		void AddBulletLength(int status);
		int GetBigPieceUp();
		void SetPieceStatus(int status);
		void AddPieceStatus(int status);
		int GetChainRange();
		void SetChainRargeStatus(int status);
		void AddChainRargeStatus(int status);
		int GetBulletPower();
		void SetBulletPower(int status);
		void AddBulletPower(int status);
		int GetBulletTime();
		void SetBulletTime(int status);
		void AddBulletTime(int status);

		int GetTime();
		void SetTime(int time);
		int GetGameStage();
		void SetGameStage(int gameStage);
		void SetAchievementPoint(int achievementPoint);
		int GetAchievementPoint();
		int GetBigPieceCount();
		void SetBigPieceCount(int count);
	};

}

//end basecross
