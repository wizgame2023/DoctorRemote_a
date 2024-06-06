/*!
@file MainCamera.cpp
@brief メインカメラ実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class MainCamera : public Camera;
	//--------------------------------------------------------------------------------------

	MainCamera::MainCamera(float angleY) :
		m_angleY(angleY),
		m_distance(6.0f),//6.0
		m_height(2.5f),  //2.5
		m_camDis(5.0f),   //5.0
		m_MoveFlag(true)
	{
	}
	MainCamera::MainCamera() :
		m_angleY(90.0f),
		m_distance(6.0f),//6.0
		m_height(2.5f),  //2.5
		m_camDis(5.0f),   //5.0
		m_MoveFlag(true)
	{
	}

	void MainCamera::OnCreate() {
	}

	void MainCamera::OnUpdate() {

		auto delta = App::GetApp()->GetElapsedTime();

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		Vec2 ret;
		auto speed = 50.0f;


		if (cntlVec[0].bConnected)
		{	
			if (m_MoveFlag)//フラグがたっていなければ操作ができない
			{	
				ret.x = cntlVec[0].fThumbLX;
				ret.y = cntlVec[0].fThumbLY;
			}

		}

		if (abs(ret.x) > 0.5) {
			m_angleY -= speed * delta * ret.x;
		}


		//ディグリー角からラジアン角に直す
		auto rad = XMConvertToRadians(m_angleY);
		Vec3 radVec(cos(rad), 0.0f, sin(rad));

		Vec3 frontVec(cos(XM_PI + rad), 0.0f, sin(XM_PI + rad));

		//カメラの注視点の設定
		auto targetTrans = m_targetTrans.lock();
		auto at = targetTrans->GetPosition();

		at += frontVec * m_camDis;
		SetAt(at);

		//カメラの座標点を設定
		auto eye = at + radVec * m_distance;
		eye.y = at.y + m_height;
		SetEye(eye);

	}

	void MainCamera::SetTarget(const shared_ptr <GameObject>& target)
	{
		m_targetTrans = target->GetComponent<Transform>();
	}

	void MainCamera::SetAngle() {

	}

	void MainCamera::SetMove(bool MoveOn)
	{
		m_MoveFlag = MoveOn;
	}


}
//end basecross
