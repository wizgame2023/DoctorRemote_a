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

		int m_dashStatus = 0;
		int m_bulletLengthStatus = 0;
		int m_PieceStatus = 0;
		int m_chainRangeStatus = 0;
		int m_bulletPowerStatus = 0;
		int m_bulletTimeStatus = 0;

		int m_time;
		int m_gameStage;
		int m_nextStage;
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
		float GetDash();
		int GetDashStatus();
		void SetDashStatus(int status);
		void AddDashStatus(int status);
		float GetBulletLength();
		int GetBulletLengthStatus();
		void SetBulletLengthStatus(int status);
		void AddBulletLengthStatus(int status);
		int GetBigPieceUp();
		int GetBigPieceUpStatus();
		void SetBigPieceUpStatus(int status);
		void AddBigPieceUpStatus(int status);
		float GetChainRange();
		int GetChainRangeStatus();
		void SetChainRargeStatus(int status);
		void AddChainRargeStatus(int status);
		float GetBulletPower();
		int GetBulletPowerStatus();
		void SetBulletPowerStatus(int status);
		void AddBulletPowerStatus(int status);
		float GetBulletTime();
		int GetBulletTimeStatus();
		void SetBulletTimeStatus(int status);
		void AddBulletTimeStatus(int status);

		int GetTime();
		void SetTime(int time);
		int GetGameStage();
		void SetGameStage(int gameStage);
		int GetNextStage();
		void SetNextStage(int stage);
		void AddAchievementPoint(int achievementPoint);
		void SetAchievementPoint(int achievementPoint);
		void MinusAchievementPoint(int achievementPoint);
		int GetAchievementPoint();
		int GetBigPieceCount();
		void SetBigPieceCount(int count);
		void ResetButton();
	};

}

//end basecross
