/*!
@file Effect.h
@brief ゲームステージ
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Effect :public MultiParticle
	{
	private:
		wstring m_TextureName;
		Vec3 m_pushPos;
		Vec3 m_Scale;
		float m_maxTime;//いつまでパーティクルが出るか決まる時間
		int m_addNumber;
	public:
		//コンストラクタ
		Effect(shared_ptr<Stage>& StagePtr,wstring TextureName,float maxTime,int addNumber, Vec3 pushPos = Vec3(1.0f, 1.0f, 1.0f),Vec3 Scale = Vec3(1.0f,1.0f,1.0f));
		//デストラクタ
		virtual ~Effect();

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void InsertEffect(const Vec3& Pos);
	};
}
//end namespace basecross
