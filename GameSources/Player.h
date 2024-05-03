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
		float m_onePiece;

		bool m_radarFlag;
		bool m_enemyFlag;

		Vec3 m_pos;
		Vec3 m_rot;

		wstring m_meshResName;
		
		shared_ptr<Transform> m_trans;
		weak_ptr<MainCamera> m_camera;

	private:
		Vec2 GetInputState()const;
		void MovePlayer();

	public:
		//コンストラクタ
		Player(const shared_ptr<Stage>& StagePtr);
		Player(const shared_ptr<Stage>& StagePtr, const shared_ptr<Transform>& trans);
		Player(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot);


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
		void SetRadarPiece(float piece);
		bool GetEnemyFlag();

		void OnCollisionEnter(shared_ptr<GameObject>& other);
	};
}
//end namespace basecross

