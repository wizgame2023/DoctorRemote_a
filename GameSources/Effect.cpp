/*!
@file effect.cpp
@brief キャラクターなど実体
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Effect::Effect(shared_ptr<Stage>& StagePtr,wstring TextureName,float maxTime,int addNumber,Vec3 pushPos,Vec3 Scale) :
		MultiParticle(StagePtr),
		m_TextureName(TextureName),
		m_pushPos(pushPos),
		m_Scale(Scale),
		m_maxTime(maxTime),
		m_addNumber(addNumber)
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
		auto ptrParticle = InsertParticle(m_addNumber);//何個同時にテクスチャが出てくるか決める
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(m_TextureName);
		ptrParticle->SetMaxTime(m_maxTime);
		//srand(time(0));
		float randamPosX = rand() % 30+10;
		randamPosX -= 20;
		randamPosX /= 10;//小数点を入れる
		float randamPosZ = rand() % 30 + 10;
		randamPosZ -= 20;
		randamPosZ /= 10;//小数点を入れる
		float randamPosY = rand() % 30 + 10;
		randamPosY -= 20;
		randamPosY /= 10;//小数点を入れる

		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec())
		{	
			//パーティクルの生成位置を決定
			rParticleSprite.m_LocalPos.x = (Util::RandZeroToOne() * 2 - 0.5f) * randamPosX;
			rParticleSprite.m_LocalPos.y = (Util::RandZeroToOne() * 2 - 0.5f) * randamPosY;
			rParticleSprite.m_LocalPos.z = (Util::RandZeroToOne() * 2 - 0.5f) * randamPosZ;
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
