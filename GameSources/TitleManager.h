/*!
@file TitleManager.h
@brief タイトルの選択
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include"SelectSprite.h"

namespace basecross {
	class TitleManager :public GameObject {
	private:
		shared_ptr<Sprite> m_blackBoard;
		shared_ptr<SelectSprite>m_selectSprite;
		shared_ptr<Transform> m_trans;

		float m_anCollar;
		float m_NextStandMovie;
		float m_bulletTime;
		float m_bulletChargeTime;
		float m_bulletRatio;

		bool m_StandTimeReset;
	public:
		TitleManager(const shared_ptr<Stage>& stagePtr);
		virtual ~TitleManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StandTimeReset();//待機時間をリセットする
	};

	class BoneDraw1 : public GameObject {
		Vec3 m_StartPos;
		bool m_TextureUse;
	public:
		//構築と破棄
		BoneDraw1(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~BoneDraw1();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class BoneDraw2 : public GameObject {
		Vec3 m_StartPos;
		bool m_TextureUse;
	public:
		//構築と破棄
		BoneDraw2(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~BoneDraw2();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	class BoneDraw3 : public GameObject {
		Vec3 m_StartPos;
		bool m_TextureUse;
	public:
		//構築と破棄
		BoneDraw3(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~BoneDraw3();
		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
