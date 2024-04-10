/*!
@file Bullet.cpp
@brief 弾の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	//Bullet::Bullet(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const Vec3& Scale, float Speed) :
	//	GameObject(StagePtr),
	//	m_Position(Position),
	//	m_Scale(Scale),
	//	m_Speed(Speed)
	//{	

	//}
	//デストラクタ
	//Bullet::~Bullet()
	//{

	//}
	////初期化
	//void Bullet::OnCreate()
	//{
	//	auto ptrTransform = GetComponent<Transform>();//toransformを取得

	//	ptrTransform->SetPosition(m_Position);//位置を設定
	//	ptrTransform->SetScale(m_Scale);//大きさを設定
	//	ptrTransform->SetQuaternion(Quat());//クトーニアン（回転）を設定

	//	//球体のコリジョンを追加
	//	auto ptrcollider = AddComponent<CollisionSphere>();


	//	//描画コンポーネント
	//	auto ptrDraw = AddComponent<BcPNTStaticDraw>();
	//	ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

	//	AddTag(L"Bullet");//Bulletタグを追加


	//}
	//void Bullet::OnUpdate()
	//{	


	//	auto ptrTransform = GetComponent<Transform>();//toransformを取得

	//	auto& app = App::GetApp();
	//	float delta = app->GetElapsedTime();//デルタタイムを取得
	//	//float speed = 1.0f;//速さ
	//	m_Position.x += m_Speed*delta;//移動
	//	ptrTransform->SetPosition(m_Position);//移動を反映指せる

	//}
	////コリジョンがぶつかったら
	//void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other)
	//{
	//	//もしぶつかったコリジョンがEnemyのものだったら
	//	if (Other->FindTag(L"Enemy"))
	//	{
	//		DestroyGameObject();//自分は消える
	//	}
	//}
}
//end basecross
