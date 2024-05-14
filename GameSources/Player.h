/*!
@file Player.h
@brief プレイヤー
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include"Player.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {

	protected:
		float m_piece;
		float m_maxPiece;
		float m_speed;
		float m_maxSpeed;
		float m_dashSpeed;
		float m_dashCount;
		float m_dashCoolTime;
		float m_onePiece;

		int m_statusFlag;

		bool m_dashCheck;
		bool m_dashCooldown;
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
		static int STATUSPLAYER;
		//コンストラクタ
		Player(const shared_ptr<Stage>& StagePtr);
		Player(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot);


		//デストラクタ
		virtual ~Player() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		Vec3 GetMoveVector()const;
		void Dash();

		Vec3 GetAngle();
		float GetPiece() const;
		float GetMaxPiece() const;
		void AddPiece(float hp);
		float GetPieceRatio();
		float PlayerAngle() const;
		bool GetRadarFlag();
		void SetRadarPiece(float piece);
		bool GetEnemyFlag();

		void EffectFlag(int Flag);

		void OnCollisionEnter(shared_ptr<GameObject>& other);
	};

	class ChildPlayer :public Player{
	private:
		weak_ptr<GameObject> m_parent;
		Vec3 m_vecParent;

	public:

		ChildPlayer(const shared_ptr<Stage>& stagePtr, 
			const shared_ptr<GameObject>& parent, const Vec3& vecParent,Vec3& pos,Vec3& rot);
		virtual ~ChildPlayer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
//end namespace basecross

