/*!
@file EffectBrakWall.cpp
@brief キャラクターなど実体
担当　三瓶裕太
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
}
