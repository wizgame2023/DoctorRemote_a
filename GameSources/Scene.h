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

		int m_playerStatus;
		int m_bulletStatus;

		int m_time;
		int m_ligthStatus;
		int m_gameStage;
		int m_achievementPoint;
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
		int GetPlayerStatus();
		void SetPlayerStatus(int status);
		void AddPlayerStatus(int status);
		int GetBulletStatus();
		void SetBulletStataus(int status);
		void AddBulletStatus(int status);
		int GetLigthStatus();
		void SetLigthStatus(int status);
		void AddLigthStatus(int status);
		int GetTime();
		void SetTime(int time);
		int GetGameStage();
		void SetGameStage(int gameStage);
		void SetAchievementPoint(int achievementPoint);
		int GetAchievementPoint();
	};

}

//end basecross
