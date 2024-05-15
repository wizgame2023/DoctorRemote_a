/*!
@file Radar.h
@brief レーダー
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Radar : public GameObject
	{
	private:
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices; // 頂点インデックス（頂点のつなげ順）
		shared_ptr<PCTSpriteDraw> m_drawComp;

		Vec3 m_PlayerPosition;//Playerのポジション
		Vec3 m_EnemyPosition;//Enemyのポジション
		float m_angle;//傾く角度
	public:
		Radar(
			const shared_ptr<Stage>& StagePtr, const Vec3 m_PlayerPosition, const Vec3 m_EnemyPosition
		);
		~Radar();

		void OnCreate()override;//初期化UnityでいうところのStart
		void OnUpdate()override;//アップデート
		void PlayerEnemyLong(Vec3 RadarVec);//PlayerとEnemyの距離のベクトルの大きさをを計算
		void RadarComvertAngle();//レーダ専用の回転計算
		Vec3 PlayerEnemyVec();//PlayerとEnemyとの距離の計算
		//void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時
	};
}
//end namespace basecross