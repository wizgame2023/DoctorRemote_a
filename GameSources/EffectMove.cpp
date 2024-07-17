/*!
@file EffectMove.cpp
@brief 動くエフェクト
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EffectMove::EffectMove(shared_ptr<Stage>& Stageptr, wstring TextureName, float maxTime, int addNumber,float lenght, Vec3 pushPos, Vec3 Scale) :
		Effect(Stageptr, TextureName, maxTime, addNumber, pushPos, Scale),
		m_length(lenght)
	{

	}
	EffectMove::~EffectMove()
	{

	}

	void EffectMove::InsertEffect(const Vec3& Pos)
	{
		auto ptrParticle = InsertParticle(m_addNumber);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(m_TextureName);
		ptrParticle->SetMaxTime(m_maxTime);


		float randamPosX = (float)(rand() % 30 + 10);
		randamPosX -= 20;
		randamPosX /= 10;//小数点を入れる
		float randamPosZ = (float)(rand() % 30 + 10);
		randamPosZ -= 20;
		randamPosZ /= 10;//小数点を入れる
		float randamPosY = (float)(rand() % 30 + 10);
		randamPosY -= 20;
		randamPosY /= 10;//小数点を入れる

		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec())
		{	
			float randamDeg = (float)(rand() % 360);//Playerからみた方向をランダムに決める

			//パーティクルの生成位置を決定
			rParticleSprite.m_LocalPos.x = m_length * cosf(XMConvertToRadians(randamDeg));
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne();
			rParticleSprite.m_LocalPos.z = m_length * sinf(XMConvertToRadians(randamDeg));
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3
			(
				rParticleSprite.m_LocalPos.x * m_pushPos.x,
				rParticleSprite.m_LocalPos.y += m_pushPos.y,
				rParticleSprite.m_LocalPos.z * m_pushPos.z
				);
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		}

		for (auto ptrParticle : GetParticleVec())
		{
			for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec())
			{
				if (rParticleSprite.m_Active)
				{
					rParticleSprite.m_LocalScale = m_Scale;//エフェクトのサイズを決める
				}
			}
		}


	};


}