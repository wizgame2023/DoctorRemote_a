/*!
@file effect.cpp
@brief キャラクターなど実体
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Effect::Effect(shared_ptr<Stage>& StagePtr,wstring TextureName,Vec3 pushPos = Vec3(1.0f,1.0f,1.0f)) :
		MultiParticle(StagePtr),
		m_TextureName(TextureName),
		m_pushPos(pushPos)
	{

	}

	Effect::~Effect()
	{

	}

	void Effect::OnCreate()
	{

	}

	void Effect::OnUpdate()
	{
		
		for (auto ptrParticle : GetParticleVec())
		{
			for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec())
			{
				if (rParticleSprite.m_Active)
				{
					//rParticleSprite.m_LocalScale = Vec3(0.1f, 0.1f, 0.1f);
					//rParticleSprite.m_Color += 0.05f;
					if (rParticleSprite.m_Color.z >= 1.0f)
					{
						rParticleSprite.m_Color.z = 1.0f;
					}
				}
			}
		}

		//親クラスのOnUpdate()を呼ぶ
		MultiParticle::OnUpdate();
	}

	void Effect::InsertEffect(const Vec3& Pos)
	{
		auto ptrParticle = InsertParticle(1);//何個同時にテクスチャが出てくるか決める
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(m_TextureName);
		ptrParticle->SetMaxTime(1.5f);	
		//srand(time(0));
		float randam = rand() % 6 + 1;
		randam -= 3;
		float randam2 = rand() % 6 + 1;
		randam2 -= 3;

		Vec3 pushPos = Vec3(0.2f, 0.8f, 0.2f);

		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec())
		{	

			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne()*randam;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne();
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne()*randam2;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3
			(
				rParticleSprite.m_LocalPos.x * m_pushPos.x,
				rParticleSprite.m_LocalPos.y * m_pushPos.y,
				rParticleSprite.m_LocalPos.z * m_pushPos.z
			);
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		}
	}
}
//end basecross
