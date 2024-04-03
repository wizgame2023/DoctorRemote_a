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
		Quat m_qt;
		Vec3 m_position;
		wstring m_meshResName;

	public:
		EnemyPiece(const shared_ptr<Stage>& StagePtr,
			const Vec3& scale,
			const Quat& qt,
			const Vec3& position
		);
		virtual ~EnemyPiece();

		virtual void OnCreate() override;
		//Õ“Ë‚µ‚½
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other);
	};
}
//end namespace basecross
