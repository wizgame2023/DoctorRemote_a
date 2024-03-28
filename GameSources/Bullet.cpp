/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	Bullet::Bullet(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const Vec3& Scale) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale)
	{
	}
	//デストラクタ
	Bullet::~Bullet()
	{

	}
	//初期化
	void Bullet::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();//toransformを取得

		ptrTransform->SetPosition(m_Position);//位置を設定
		ptrTransform->SetScale(m_Scale);//大きさを設定
		ptrTransform->SetQuaternion(Quat());//クトーニアン（回転）を設定


		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");


	}
	void Bullet::OnUpdate()
	{	
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//デルタタイムを取得

		m_Position.x += 1.0f*delta;
	}
}
//end basecross
