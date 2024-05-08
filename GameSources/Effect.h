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
	public:
		//コンストラクタ
		explicit Effect(shared_ptr<Stage>& StagePtr,wstring TextureName,Vec3 pushPos);
		//デストラクタ
		virtual ~Effect();

		//初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void InsertEffect(const Vec3& Pos);
	};
}
//end namespace basecross
