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
		Vec3 m_CameraEye;//脱出する際のカメラのポジション
		Vec3 m_CameraAt;//脱出する際のカメラの注視点
		shared_ptr<Sprite> m_Sprite;
		shared_ptr<Sprite> m_MyMiniMap;//ミニマップの自分
		weak_ptr<Player> m_Player;
		Vec3 m_PlayerPos;//Playerのポジション
		Vec3 m_PlayerStartPos;//Startした際のPlayerのポジション
		Vec3 m_MinRange;//最小の値
		Vec3 m_MaxRange;//最大の値
		Vec3 m_TargetPos;//到着地点
		Col4 m_SpriteCol;//暗転するためのスプライトの色
		int m_UpdateFlag;
		int m_MapSize;//マップのサイズ
		float m_Time;
		float m_paint;
	public:
		EscapeManager(const shared_ptr<Stage>& stagePtr, Vec3 cameraEye, Vec3 cameraAt, Vec3 minRange, Vec3 maxRange,Vec3 playerStart,Vec3 m_TargetPos,int mapSize = 150);//コンストラクタ
		~EscapeManager();//デストラクタ

		void OnCreate() override;//生成
		void OnUpdate() override;//更新

		void Start();//動作を開始

		float DifferenceRad(float rad);//Playerの傾きに合わせるためのradの差
	};
}