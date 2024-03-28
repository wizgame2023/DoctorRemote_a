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

	void Player::OnCreate(){
		//初期位置などの設定
		m_trans = AddComponent<Transform>();
		m_trans->SetScale(1.0f, 1.0f, 1.0f);
		m_trans->SetRotation(0.0f, 0.0f, 0.0f);
		m_trans->SetPosition(0.0f, 0.5f, 0.0f);

		//描画コンポーネント
		auto draw_Comp = AddComponent<BcPNStaticDraw>();
		draw_Comp->SetMeshResource(m_meshResName);
		draw_Comp->SetOwnShadowActive(true);
		draw_Comp->SetFogEnabled(true);

		//影をつける
		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(m_meshResName);

	}
	void Player::OnUpdate(){

	}
}
//end basecross
