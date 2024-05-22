/*!
@file PieceLittle.cpp
@brief 欠片を壊したらでてくるオブジェクト
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	PieceLittle::PieceLittle(const shared_ptr<Stage>& stagePtr,
		const shared_ptr<GameObject>& obj,
		const float deg
	):
		GameObject(stagePtr),
		m_obj(obj),
		m_deg(deg),
		m_ground(false),
		m_position(Vec3(0.0f,10.0f,0.0f)),
		m_rotete(Vec3(0.0f)),
		m_scale(Vec3(0.5f)),
		m_meshResName(L"DEFAULT_SPHERE")
	{}

	void PieceLittle::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		auto objTrans = m_obj->GetComponent<Transform>();
		auto objPos = objTrans->GetPosition();

		Vec3 pos = ptrTrans->GetPosition();
		pos = objPos;
		pos.y += 0.5f;
		Quat qt = ptrTrans->GetQuaternion();
		//Vec3 rot = qt.toRotVec();
		//float rotY = rot.y;
		float rad = XMConvertToRadians(m_deg);

		Vec3 velo(sin(rad), 0.3f, cos(rad));
		velo.normalize();
		velo *= 5.0f;
		m_velocity = velo;
		ptrTrans->SetPosition(pos);

		//float deg = 45;
		//float rad = XMConvertToRadians(deg);
		//Vec3 velo(sin(rad), 5.0f, cos(rad));
		//velo.normalize();
		//velo *= 5.0f;

		//描画
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(m_meshResName);

		//オブジェクトの影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);
		ptrDraw->SetOwnShadowActive(true);

		//コライダー
		auto colPtr = AddComponent<CollisionSphere>();
		colPtr->SetDrawActive(true);
		colPtr->SetAfterCollision(AfterCollision::Auto);

		//重力をつける
		auto grav = AddComponent<Gravity>();
		
		//auto group = GetStage()->GetSharedObjectGroup(L"EnemyPieceGroup");
		//group->IntoGroup(GetThis<GameObject>());

		AddTag(L"PieceLittle");

	}

	void PieceLittle::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		float elapsed = App::GetApp()->GetElapsedTime();
		if (!m_ground) {
			auto pos = ptrTrans->GetPosition();
			pos += m_velocity * elapsed;
			ptrTrans->SetPosition(pos);
		}

		//auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
		//	auto ptrTrans = GetComponent<Transform>();
		//	Vec3 pos = ptrTrans->GetPosition();
		//	pos.y += 0.3f;
		//	Quat qt = ptrTrans->GetQuaternion();
		//	Vec3 rot = qt.toRotVec();
		//	float rotY = rot.y;
		//	Vec3 velo(sin(rotY), 5.0f, cos(rotY));
		//	velo.normalize();
		//	velo *= 15.0f;
		//}
	}

	void PieceLittle::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {
			GetStage()->RemoveGameObject<PieceLittle>(GetThis<PieceLittle>());
		}
		if (other->FindTag(L"Ground")) {
			m_ground = true;
		}
	}

}
//end namespace basecross