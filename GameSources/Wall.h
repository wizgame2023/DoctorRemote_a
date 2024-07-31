/*!
@file BreakWall.h
@brief •Ç
’S“–F‘å‰ÍŒ´
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Wall : public GameObject
	{
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
	public:
		Wall(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale);
		~Wall() {}
		virtual void OnCreate() override; // ‰Šú‰»
		//virtual void OnUpdate() override; // XV
	};

}
//end namespace basecross

