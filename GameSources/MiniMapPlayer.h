/*!
@file MiniMapPlayer.h
@brief 光、光源の表現
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MiniMapPlayer : public GameObject
	{
	private:
		Vec3 m_StartPos;//初期位置
		float m_Lenght;//スプライトの一辺の長さ
		float m_MapSize;//元々のマップのサイズ
		float m_MiniMapSize;//ミニマップのサイズ
		float m_MapMagnification;//マップの倍率
	public:	
		MiniMapPlayer(const shared_ptr<Stage>& stagePtr,Vec3 StartPos,float lenght,float m_MapSize,float m_MiniMapSize);
		~MiniMapPlayer();

	    void OnCreate() override;
		void OnUpdate() override;

	};
}
//end namespace basecross
