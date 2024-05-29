/*!
@file TimeManager.h
@brief 時間の表示
担当：
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class JoinManager :public GameObject
	{
	private:
		shared_ptr<Camera> m_Camera;
		Vec3 m_CameraEye;//脱出する際のカメラのポジション
		Vec3 m_CameraAt;//脱出する際のカメラの注視点
		shared_ptr<Sprite> m_Sprite;
		weak_ptr<Player> m_Player;
		Vec3 m_PlayerPos;//Playerのポジション
		Vec3 m_PlayerStartPos;//Startした際のPlayerのポジション
		Vec3 m_MinRange;//最小の値
		Vec3 m_MaxRange;//最大の値
		Vec3 m_TargetPos;//到着地点
		Col4 m_SpriteCol;//暗転するためのスプライトの色
		int m_UpdateFlag;
		float m_Time;
	public:
		JoinManager(const shared_ptr<Stage>& stagePtr, Vec3 cameraEye, Vec3 cameraAt, Vec3 minRange, Vec3 maxRange, Vec3 playerStart, Vec3 m_TargetPos);//コンストラクタ
		virtual ~JoinManager();//デストラクタ

		virtual void OnCreate() override;//生成
		virtual void OnUpdate() override;//更新

		virtual void Start();//動作を開始
	};
}