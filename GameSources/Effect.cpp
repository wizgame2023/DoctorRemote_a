/*!
@file effect.cpp
@brief キャラクターなど実体
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Effect::Effect(shared_ptr<Stage>& StagePtr,wstring TextureName,Vec3 pushPos,Vec3 Scale) :
		MultiParticle(StagePtr),
		m_TextureName(TextureName),
		m_pushPos(pushPos),
		m_Scale(Scale),
		m_maxTime(0.5f)
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
					rParticleSprite.m_LocalScale = m_Scale;//エフェクトのサイズを決める
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
		ptrParticle->SetMaxTime(m_maxTime);
		//srand(time(0));
		float randamPosX = rand() % 6 + 1;
		randamPosX -= 3;
		float randamPosZ = rand() % 6 + 1;
		randamPosZ -= 3;

		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec())
		{	
			//パーティクルの生成位置を決定
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne()*randamPosX;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne();
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne()*randamPosZ;
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
