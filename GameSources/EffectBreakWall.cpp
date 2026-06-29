/*!
@file EffectBrakWall.cpp
@brief BreakWallが壊れたときのエフェクト
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	EffectBreakWall::EffectBreakWall(shared_ptr<Stage>& Stageptr,wstring TextureName,float maxTime,int addNumber,Vec3 pushPos,Vec3 Scale) :
		Effect(Stageptr, TextureName, maxTime, addNumber, pushPos, Scale)
	{

	}
	EffectBreakWall::~EffectBreakWall()
	{

	}

	void EffectBreakWall::InsertEffect(const Vec3& Pos)
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
			//パーティクルの生成位置を決定
			rParticleSprite.m_LocalPos.x = (Util::RandZeroToOne() * 2 - 0.5f) * randamPosX;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne();
			rParticleSprite.m_LocalPos.z = (Util::RandZeroToOne() * 2 - 0.5f) * randamPosZ;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3
			(
				rParticleSprite.m_LocalPos.x += m_pushPos.x,
				rParticleSprite.m_LocalPos.y += m_pushPos.y,
				rParticleSprite.m_LocalPos.z += m_pushPos.z
			);
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		}



	}
}
