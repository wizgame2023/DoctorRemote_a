/*!
@file EscapeManager.h
@brief 脱出するシーンの処理等
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "MainCamera.h"

namespace basecross {
	class EscapeManager : public GameObject
	{
	private:
		shared_ptr<Camera> m_Camera;
		shared_ptr<Sprite> m_Sprite;
		weak_ptr<Player> m_Player;
		Vec3 m_PlayerPos;
		Col4 m_SpriteCol;//暗転するためのスプライトの色
		int m_UpdateFlag;
		float m_Time;
	public:
		EscapeManager(const shared_ptr<Stage>& stagePtr);//コンストラクタ
		~EscapeManager();//デストラクタ

		void OnCreate() override;//生成
		void OnUpdate() override;//更新

		void Start();//動作を開始
	};
}