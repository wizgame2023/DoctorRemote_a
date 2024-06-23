/*!
@file EffectPiece.cpp
@brief ウイルスが連鎖する時のエフェクト
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EffectPiece::EffectPiece(const shared_ptr<Stage>& stage):
		GameObject(stage),
		m_height(0.0f),
		m_topRadius(0.0f),
		m_unberRadius(3.0f),
		m_square(30),
		m_loops(1.0f,5.0f),
		m_topCol(0.0f),
		m_underCol(Col4(0.0f,0.0f,1.0f,1.0f)),
		m_meshResName(L"EffectPiece"),
		m_scrollVelocity(0.0f,-1.0f),
		m_isUpdate(false),
		m_effectLoop(3.0f),
		m_effectLoopFlag(false),
		m_colFlag(true),
		m_spreadFlag(true)
	{}
	EffectPiece::EffectPiece(const shared_ptr<Stage>& stage,
		const float height,      //高さ
		const float topRadius,   //上の円の大きさ
		const float underRadius, //下の円の大きさ
		const int square,        //何角形か
		const Vec2 loops,        //画像を縦横何回ループさせるか
		const Col4 topCol,       //上の頂点の色
		const Col4 underCol,     //下の頂点の色
		const wstring meshResname,//テクスチャ
		const Vec2 scrollVec,    //X軸,Y軸方向に動かす
		const Vec3 pos,
		const float effectLoop
		) :
		GameObject(stage),
		m_height(height),
		m_topRadius(topRadius),
		m_unberRadius(underRadius),
		m_square(square),
		m_loops(loops),
		m_topCol(topCol),
		m_underCol(underCol),
		m_meshResName(meshResname),
		m_scrollVelocity(scrollVec),
		m_pos(pos),
		m_isUpdate(false),
		m_effectLoop(effectLoop),
		m_effectLoopFlag(false),
		m_colFlag(false),
		m_spreadFlag(false)

	{}

	void EffectPiece::InitializeVertices() {
		m_vertices.clear();
		//頂点数
		m_vertices.reserve((m_square + 1) * 2);
		for (int i = 0; i <= m_square; i++) {

			Vec3 positon;
			VertexPositionColorTexture vtx;

			//uvデータ
			float rad = XMConvertToRadians(360.0f * i / m_square);
			float u = m_loops.x * static_cast<float>(i) / static_cast<float>(m_square);
			float v = m_loops.y;

			//上の円の頂点
			positon = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_topRadius + Vec3(0.0f, m_height, 0.0f);
			vtx = VertexPositionColorTexture(positon, m_topCol, Vec2(u, 0.0f));
			m_vertices.push_back(vtx);

			//下の円の頂点
			positon = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_unberRadius;
			vtx = VertexPositionColorTexture(positon, m_underCol, Vec2(u, v));
			m_vertices.push_back(vtx);
		}

		const vector<uint16_t> baseIndices = {
			2,1,0,
			3,1,2,
		};

		m_indices.clear();
		m_indices.reserve(m_square * baseIndices.size());
		for (int i = 0; i < m_square; i++) {
			for (auto baseIndex : baseIndices) {
				//0から始まるため2ずつ足していくと次のポリゴンが表示される
				m_indices.push_back(baseIndex + (2 * i));
			}

		}
	}

	
	void EffectPiece::OnCreate() {
		if (m_effectLoop > 0) {
			m_effectLoopFlag = true;
		}
		InitializeVertices();

		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
		m_trans->SetScale(Vec3(3.0f));

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.3f, 0.3f, 0.3f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//頂点データとインディックスを元にポリゴンを生成する
		m_draw = AddComponent<BcPCTStaticDraw>();
		m_draw->SetOriginalMeshUse(true);
		m_draw->SetMeshToTransformMatrix(spanMat);
		m_draw->CreateOriginalMesh(m_vertices, m_indices);
		m_draw->SetSamplerState(SamplerState::LinearWrap);
		m_draw->SetDepthStencilState(DepthStencilState::Read);
		m_draw->SetBlendState(BlendState::Additive);

		if (m_meshResName.length() > 0) {
			m_draw->SetTextureResource(m_meshResName);
		}
		SetAlphaActive(true);
		m_chainRarge = App::GetApp()->GetScene<Scene>()->GetChainRange();
	}
	void EffectPiece::OnUpdate() {
		auto stage = GetStage();
		float elapsed = App::GetApp()->GetElapsedTime();
		m_effectLoop -= elapsed;
		if (m_effectLoopFlag) {
			if (m_effectLoop < 0) {
				stage->RemoveGameObject<EffectPiece>(GetThis<EffectPiece>());
			}
		}
		if (m_scrollVelocity.length() > 0.0f && m_meshResName != L"") {
			for (auto& vertex : m_vertices) {
				//UVの移動
				vertex.textureCoordinate += m_scrollVelocity * elapsed;
			}
		}
		if (m_isUpdate) {
			m_isUpdate = false;
			InitializeVertices();
		}

		if (m_spreadFlag) {
			SetUnderRadius(m_unberRadius + (5.0f * m_chainRarge) * elapsed);
		}

		m_draw->UpdateVertices(m_vertices);
	}

	void EffectPiece::SetScrollSpeed(float x, float y) {
		m_scrollVelocity.x = x;
		m_scrollVelocity.y = -y;
	}
	void EffectPiece::SetTopRadius(float radius) {
		m_isUpdate = true;
		m_topRadius = radius;
	}
	void EffectPiece::SetUnderRadius(float radius) {
		m_isUpdate = true;
		m_unberRadius = radius;
	}
	void EffectPiece::ThihDestroy() {
		GetStage()->RemoveGameObject<EffectPiece>(GetThis<EffectPiece>());
	}
	void EffectPiece::SetBlendState(const BlendState state) {
		m_draw->SetBlendState(state);
	}
	void EffectPiece::SetDeleteTime(float time) {
		m_effectLoop = time;
	}
}
//end namespace basecross
