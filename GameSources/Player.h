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

		wstring m_meshResName;
	private:
		Vec2 GetInputState()const;
		Vec3 GetMoveVector()const;

	public:
		//コンストラクタ
		Player(const shared_ptr<Stage>& StagePtr);
		//デストラクタ
		virtual ~Player() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end namespace basecross

