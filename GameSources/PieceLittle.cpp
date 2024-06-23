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
		const shared_ptr<GameObject>& target,
		const float deg,
		const wstring tag
	):
		GameObject(stagePtr),
		m_obj(obj),
		m_target(target),
		m_deg(deg),
		m_scale(Vec3(0.5f)),
		m_ground(false),
		m_collect(6.0f),//回収距離
		m_count(15.0f), //消滅までの秒数
		m_meshResName(L"LittleKakera"),
		m_tag(tag)
	{}

	void PieceLittle::OnCreate() {

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);

		auto objTrans = m_obj->GetComponent<Transform>();
		auto objPos = objTrans->GetPosition();

		Vec3 pos = ptrTrans->GetPosition();
		pos = objPos;
		//落ちてくる高さ
		pos.y += 1.0f;
		Quat qt = ptrTrans->GetQuaternion();
		//Vec3 rot = qt.toRotVec();
		//float rotY = rot.y;
		float rad = XMConvertToRadians(m_deg);

		Vec3 velo(sin(rad), 0.3f, cos(rad));
		velo.normalize();
		velo *= 5.0f;
		m_velocity = velo;
		ptrTrans->SetPosition(pos);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 10.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//描画
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);

		//影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);
		ptrShadow->SetMeshToTransformMatrix(spanMat);
		
		//コライダー
		auto colPtr = AddComponent<CollisionSphere>();
		colPtr->SetDrawActive(false);
		colPtr->SetAfterCollision(AfterCollision::None);

		//重力をつける
		auto grav = AddComponent<Gravity>();
		
		AddTag(m_tag);

	}

	void PieceLittle::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto targetTrans = m_target->GetComponent<Transform>();
		auto targetPos = targetTrans->GetPosition();
		Vec3 pullPos = targetPos - pos;
		float range = sqrt(pullPos.x * pullPos.x + pullPos.z + pullPos.z);

		float elapsed = App::GetApp()->GetElapsedTime();
		if (!m_ground) {
			auto pos = ptrTrans->GetPosition();
			pos += m_velocity * elapsed;
			ptrTrans->SetPosition(pos);
		}
		if (m_ground && range < m_collect) {
			pos += pullPos * 3.0f * elapsed;
			ptrTrans->SetPosition(pos);
		}
		if (m_ground && m_count > 0) {
			m_count -= elapsed;
			if (m_count < 0) {
				GetStage()->RemoveGameObject<PieceLittle>(GetThis<PieceLittle>());
			}
		}


	}

	void PieceLittle::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {
			GetStage()->RemoveGameObject<PieceLittle>(GetThis<PieceLittle>());
		}
		if (other->FindTag(L"Ground")) {
			m_ground = true;
			auto gra = GetComponent< Gravity>();
			gra->SetGravityZero();
		}
	}


}
//end namespace basecross