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

		float m_hp;
		float m_speed;
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

		float GetHp() const;
		void SetHp(float hp);
		//Vec3 GetPos() const;
		//Vec3 GetRot() const;

		void OnCollisionEnter(shared_ptr<GameObject>& other);
	};
}
//end namespace basecross

