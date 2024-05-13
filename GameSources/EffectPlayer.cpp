/*!
@file EffectPlayer.cpp
@brief Player用のエフェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EffectPlayer::EffectPlayer(shared_ptr<Stage>& Stageptr, wstring TextureName, float maxTime, int addNumber, Vec3 pushPos, Vec3 Scale) :
		Effect(Stageptr, TextureName, maxTime, addNumber, pushPos, Scale)
	{

	}
	EffectPlayer::~EffectPlayer()
	{

	}

}