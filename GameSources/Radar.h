/*!
@file Radar.h
@brief レーダー
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Radar : public GameObject
	{
	private:
		Vec3 m_Position;
		Vec3 m_Scale;
		float m_angle;//傾く角度
	public:
		Radar(
			const shared_ptr<Stage>& StagePtr
		);
		~Radar();
		void OnCreate()override;//初期化UnityでいうところのStart
		void OnUpdate()override;//アップデート
		//void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時
	};
}
//end namespace basecross