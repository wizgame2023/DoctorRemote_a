/*!
@file GameStage.h
@brief ゲームステージ
担当　大河原
*/

#pragma once
#include "stdafx.h" 
#include "Bullet.h"
#include "TutorialManager.h"
#include "EnemyPiece.h"
#include "BigPiece.h"
#include "Player.h"

namespace basecross {
	class Enemy :public GameObject
	{
		bool m_enemyflag;
		bool m_posXFlag;
		bool m_posYFlag;
		bool m_pieceFlag;
		bool m_bigPieceFlag;
		bool m_bigPieceFlag2;
		float m_Hp;
		float m_width;
		float m_widthSpeed;
		float m_hegiht;
		float m_hegihtSpeed;
		float m_scaleReduct;
		float m_posYRedect;
		float m_pieceTime;
		float m_bigPieceTime;
		float m_bigPieceTime2;


		float m_deg;
		int m_pieceCount;
		int m_bigPieceCount;
		int m_bigPieceCount2;
		int m_event;
		int m_event2;
		
		Vec3 m_pos;   //初期値
		Vec3 m_posCur;//動かすpos
		Vec3 m_rot;
		Vec3 m_scale;

		wstring m_meshResName;

		weak_ptr<Bullet> m_bullet;
		shared_ptr<Player> m_player;
		shared_ptr<Transform> m_trans;
		shared_ptr<EnemyPiece> m_enemyPiece[10];
		shared_ptr<BigPiece> m_bigEnemyPiece[10];
		shared_ptr<BigPiece> m_bigEnemyPiece2[10];


	public:
		Enemy(const shared_ptr<Stage>& StaegePtr);
		Enemy(const shared_ptr<Stage>& StagePtr,
			const Vec3& pos,
			const Vec3& rot,
			const Vec3& scale
		);

		~Enemy() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;
		void EventMove();
		void SetEnemy(bool enemy);
		bool GetEnemy();
	};
}
//end namespace basecross
