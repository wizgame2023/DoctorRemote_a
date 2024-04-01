/*!
@file EnemyPiece.cpp
@brief 敵の欠片実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	EnemyPiece::EnemyPiece(const shared_ptr<Stage>& StagePtr,
		const Vec3& scale,
		const Quat& qt,
		const Vec3& position
	) :
		GameObject(StagePtr),
		m_scale(scale),
		m_qt(qt),
		m_position(position),
		m_meshResName(L"DEFAULT_CUBE")

	{}
	EnemyPiece::~EnemyPiece() {};

	void EnemyPiece::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetQuaternion(m_qt);
		ptrTrans->SetPosition(m_position);

		//オブジェクトの描画
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetOwnShadowActive(true);
		//ptrDraw->SetTextureResource(L"");
		
		//オブジェクトの影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);


		AddTag(L"EnemyPiece");
	}
}
//end basecross
