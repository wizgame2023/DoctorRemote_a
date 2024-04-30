/*!
@file EnemyPiece.h
@brief “G‚ÌŒ‡•Ğ
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyPiece :public GameObject {
	private:
		Vec3 m_scale;
		Vec3 m_rotate;
		Vec3 m_position;
		wstring m_meshResName;

	public:
		EnemyPiece(const shared_ptr<Stage>& StagePtr,
			const Vec3& position,
			const Vec3& rotate,
			const Vec3& scale
		);
		virtual ~EnemyPiece();

		virtual void OnCreate() override;
		//Õ“Ë‚µ‚½
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other);
		Vec3 GetPos();
		Vec3 GetRot();

	};
}
//end namespace basecross
