/*!
@file Player.h
@brief プレイヤー
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include"Player.h"
#include "Sprite.h"

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
		float m_dashCountTime;
		float m_dashCool;
		float m_dashCoolTime;
		float m_onePiece;
		float m_bulletTime;
		float m_bulletChargeTime;
		float m_bulletRatio;
		float m_bulletPower;
		float m_blinkCnt;
		float m_rotY;

		int m_statusFlag;
		int m_bulletLevel;

		bool m_startFlag;
		bool m_dashCheck;
		bool m_dashCooldown;
		bool m_radarFlag;
		bool m_enemyFlag;
		bool m_enemyPieceFlag;
		bool m_bulletFlag;
		bool m_chargeBulletSE[3];

		Vec3 m_pos;
		Vec3 m_position;
		Vec3 m_rot;
		Vec3 m_lastAngle;//Playerの進む角度を保存する
		Vec2 m_PadLastAngle;//最後に傾けたpadの傾きを保存する

		wstring m_meshResName;

		shared_ptr<Transform> m_trans;
		weak_ptr<MainCamera> m_camera;
		shared_ptr<GameObject> m_obj;
		shared_ptr<Sprite> m_damegeScreen;

	private:
		Vec2 GetInputState();
		void MovePlayer();
		void DashCoolManager(int count);//ダッシュのクールタイムの管理をする

	public:
		static int STATUSPLAYER;
		//コンストラクタ
		Player(const shared_ptr<Stage>& StagePtr);
		Player(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot,float onePiece = 2.0f);


		//デストラクタ
		virtual ~Player() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		Vec3 GetMoveVector();
		Vec3 FrontVec();
		void Dash();//この引数によってクールタイムなどが変わってくる
		void BulletSE();

		Vec3 GetAngle();
		float GetPiece() const;
		float GetMaxPiece() const;
		void AddPiece(float hp);
		float GetPieceRatio();
		float PlayerAngle() const;
		bool GetRadarFlag();
		void SetRadarPiece(float piece);
		bool GetEnemyFlag();
		shared_ptr<GameObject> GetObj();
		void SetObj(shared_ptr<GameObject>& obj);
		void EffectFlag(int Flag);
		void SpeedCalculation();//スピードを計算する
		bool GetDashFlag();
		int GetBulletLevel();
		float GetBulletRatio();
		void SetSpeed(float speed);

		void OnCollisionEnter(shared_ptr<GameObject>& other);
	};

}
//end namespace basecross

