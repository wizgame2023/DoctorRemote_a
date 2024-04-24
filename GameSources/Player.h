/*!
@file Player.h
@brief プレイヤー
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {

		float m_piece;
		float m_maxPiece;
		float m_speed;

		bool m_radarFlag;

		wstring m_meshResName;
		
		shared_ptr<Transform> m_trans;
		weak_ptr<MainCamera> m_camera;

	private:
		Vec2 GetInputState()const;
		void MovePlayer();

	public:
		//コンストラクタ
		Player(const shared_ptr<Stage>& StagePtr);
		//デストラクタ
		virtual ~Player() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		Vec3 GetMoveVector()const;

		Vec3 GetAngle();
		float GetPiece() const;
		float GetMaxPiece() const;
		void SetPiece(float hp);
		float GetPieceRatio();
		float PlayerAngle() const;
		bool GetRadarFlag();

		void OnCollisionEnter(shared_ptr<GameObject>& other);
	};
}
//end namespace basecross

