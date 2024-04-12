/*!
@file Bullet.cpp
@brief 弾の実体
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//コンストラクタ
	Bullet::Bullet(const shared_ptr<Stage>& StagePtr, const Vec3& Position, const Vec3& Scale, float Speed, float Rad, int Attack) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale),
		m_Speed(Speed),
		m_angle(Rad),//角度はRad（弧度法）でお願いします
		m_Attack(Attack)
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

		//球体のコリジョンを追加
		auto ptrcollider = AddComponent<CollisionSphere>();


		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		AddTag(L"Bullet");//Bulletタグを追加


	}
	void Bullet::OnUpdate()
	{
		auto& ptrPlayer = GetStage()->GetSharedObject(L"GamePlayer");//GamePlayerというオブジェクトを取得

		auto ptrTransform = GetComponent<Transform>();//toransformを取得

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//デルタタイムを取得
		//float speed = 1.0f;//速さ
		m_Position.x += m_Speed * cos(m_angle) * delta;//移動
		m_Position.z += m_Speed * sin(m_angle) * delta;//移動
		ptrTransform->SetPosition(m_Position);//移動を反映させる

		//auto& Vec = GetStage()->GetGameObjectVec();//ゲームオブジェクトの配列を取得
		//for (auto V : Vec)
		//{
		//	bool chack = V->FindTag(L"Bullet");
		//	if (chack)
		//	{

		//	}
		//}

		// 原点から20.0f離れた弾は破棄する
		if (m_Position.length() > 20.0f)
		{
			// ステージから自身を破棄する
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		}


	}
	//コリジョンがぶつかったら
	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		//もしぶつかったコリジョンがEnemyのものだったら
		if (Other->FindTag(L"Enemy"))
		{
			DestroyGameObject();//自分は消える
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());

		}
	}

	float Bullet::GetSpeed()
	{
		return m_Speed;
	}

	int Bullet::GetAttack()
	{
		return m_Attack;
	}
}
//end basecross
