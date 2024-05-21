/*!
@file effect.cpp
@brief 追従するエフェクト
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EffectChase::EffectChase(shared_ptr<Stage>& Stageptr, wstring TextureName, float maxTime, int addNumber,float lenght, Vec3 pushPos, Vec3 Scale) :
		EffectMove(Stageptr, TextureName, maxTime, addNumber,lenght, pushPos, Scale)
	{

	}
	EffectChase::~EffectChase()
	{

	}

	void EffectChase::OnUpdate()
	{

		//親クラスのOnUpdate()を呼ぶ
		MultiParticle::OnUpdate();

		auto ptrTarget = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerというオブジェクトを取得
		auto pos = ptrTarget->GetComponent<Transform>()->GetPosition();
		m_ptrParticle->SetEmitterPos(pos);

		float ElapsedTime = App::GetApp()->GetElapsedTime();//エルダータイム追加

		for (auto ptrParticle : GetParticleVec())
		{
			for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec())
			{
				if (rParticleSprite.m_Active)
				{
					rParticleSprite.m_LocalPos += Vec3(0.0f, 0.0f, 0.0f) + (rParticleSprite.m_Velocity * ElapsedTime);//ここで追従しながらエフェクトの動きをする
					rParticleSprite.m_LocalScale = m_Scale;//エフェクトのサイズを決める
				}
			}
		}

	}
}