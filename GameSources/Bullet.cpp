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
		m_Attack(Attack),
		m_statusFlag(0),
		m_shotRange(20.0f)
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
		m_AllStartPosition = ptrTransform->GetPosition();//初期化時点の位置を取得
		//球体のコリジョンを追加
		auto ptrcollider = AddComponent<CollisionSphere>();


		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		AddTag(L"Bullet");//Bulletタグを追加

		m_statusFlag = App::GetApp()->GetScene<Scene>()->GetBulletStatus();
		switch (m_statusFlag)
		{
		case 0:
			m_shotRange = 20.0f;
			break;
		case 1:
			m_shotRange = 30.0f;
			break;
		case 2:
			m_shotRange = 40.0f;
			break;
		default:
			break;
		}
	}
	void Bullet::OnUpdate()
	{		
		//wstringstream wss;//デバック用文字列

		auto& ptrPlayer = GetStage()->GetSharedObject(L"GamePlayer");//GamePlayerというオブジェクトを取得

		auto ptrTransform = GetComponent<Transform>();//toransformを取得

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//デルタタイムを取得
		//float speed = 1.0f;//速さ
		m_Position.x += m_Speed * cos(m_angle) * delta;//移動
		m_Position.z += m_Speed * sin(m_angle) * delta;//移動
		ptrTransform->SetPosition(m_Position);//移動を反映させる
		Vec3 UpdatePosition = ptrTransform->GetPosition();//移動を反映させたpositionを取得

		//auto& Vec = GetStage()->GetGameObjectVec();//ゲームオブジェクトの配列を取得
		//for (auto V : Vec)
		//{
		//	bool chack = V->FindTag(L"Bullet");
		//	if (chack)
		//	{

		//	}
		//}

		
		Vec3 PositionVec = Vec3(m_AllStartPosition.x - UpdatePosition.x,m_AllStartPosition.y - UpdatePosition.y,m_AllStartPosition.z - UpdatePosition.z);
		float AllPosition = abs(PositionVec.x)+abs(PositionVec.y)+abs(PositionVec.z);

		// 初期位置から20.0f離れた弾は破棄する
		if (AllPosition >= m_shotRange)//ちょっと計算違うから直しておく
		{
			// ステージから自身を破棄する
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		}
		//wss << L"AllPosition :" << AllPosition << endl;
		//wss << L"AllStartPosition :" << 20.0f << endl;


		//デバック用文字列を生成
		//auto scene = app->GetScene<Scene>();//シーン取得
		//scene->SetDebugString(L"a\n" + wss.str());


	}
	//コリジョンがぶつかったら
	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		//もしぶつかったコリジョンがEnemyのものだったら
		if (Other->FindTag(L"Enemy"))
		{			
			GetStage()->AddGameObject<EffectBullet>(L"DamageBullet", 3, 2, GetComponent<Transform>()->GetPosition(), 0.1f);
			//DestroyGameObject();//自分は消える
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());

		}
		if (Other->FindTag(L"BreakWall"))
		{
			DestroyGameObject();//自分は消える
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			m_hit = 1;//壊れる壁に当たった
			auto& ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerというオブジェクトを取得
			ptrPlayer->EffectFlag(2);//これでPlayerからエフェクトを出す

		}
		if (Other->FindTag(L"RecoveryWall"))
		{
			DestroyGameObject();//自分は消える
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			auto& ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerというオブジェクトを取得
			ptrPlayer->EffectFlag(1);//これでPlayerからエフェクトを出す
			

		}
		if (Other->FindTag(L"Obj"))
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
