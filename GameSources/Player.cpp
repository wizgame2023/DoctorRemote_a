/*!
@file Player.cpp
@brief プレイヤー実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_meshResName(L"DEFAULT_CUBE")
	{}

	Vec2 Player::GetInputState()const {
		Vec2 ret;
		ret.x = 0.0f;
		ret.y = 0.0f;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].bConnected)
		{
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		return ret;
	}

	Vec3 Player::GetMoveVector()const {
		Vec3 angle(0, 0, 0);
		//入力を取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0){
			float moveLength = 0; //動いた時のスピード
			auto ptrTrasform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			//進行方向の向きを計算
			auto front = ptrTrasform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			return angle;
		}
	}

	void Player::OnCreate(){
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(1.0f, 1.0f, 1.0f);
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(0.0f, 0.5f, 0.0f);

		//描画コンポーネント
		auto draw_Comp = AddComponent<BcPNStaticDraw>();
		draw_Comp->SetMeshResource(m_meshResName);
		draw_Comp->SetOwnShadowActive(true);
		draw_Comp->SetFogEnabled(true);

		//影をつける
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(m_meshResName);

		AddTag(L"Player");
	}

	void Player::OnUpdate(){

	}
}
//end basecross
