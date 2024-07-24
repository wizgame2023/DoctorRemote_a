/*!
@file Garge.cpp
@brief ゲージ
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	Garge::Garge(const shared_ptr<Stage>& stagePtr,
		const float sizeX, const float sizeY, wstring meshResName,//画像のサイズ(動かしたい方に値を入れる)
		float ratio,  float width, float heigth, //ゲージの割合と表示するサイズ
		Col4 color,Col4 color2,
		Vec3 screen,Vec3 distance //大まかな位置と調整
	):
		GameObject(stagePtr),
		m_sizeX(sizeX),
		m_sizeY(sizeY),
		m_meshResName(meshResName),
		m_ratio(ratio),
		m_width(width),
		m_height(heigth),
		m_color(color),
		m_color2(color2),
		m_screen(screen),
		m_distance(distance)
	{}

	void Garge::OnCreate() {
		if (m_sizeX != 0) {
			m_moveW = (m_sizeX * m_ratio) / m_sizeX;
		}
		else {
			m_moveW = 0;
		}
		if (m_sizeY != 0){
			m_moveH = (m_sizeY * m_ratio) / m_sizeY;
		}
		else {
			m_moveH = 0;
		}

		//m_moveW = (m_sizeX * m_ratio) / m_sizeX;
		//m_moveH = (m_sizeY * m_ratio) / m_sizeY;

		if (m_moveW > 0) {
			m_vertices = {

				{Vec3(0,0,0),m_color,Vec2(m_moveW,0.0f)},
				{Vec3(m_width,0,0),m_color,Vec2(0.0f,0.0f)},
				{Vec3(0,-m_height,0),m_color,Vec2(m_moveW,1.0f)},
				{Vec3(m_width,-m_height,0),m_color,Vec2(0.0f,1.0f)}


			};
		}
		else if (m_moveH > 0) {
			m_vertices = {
				{Vec3(0,0,0),m_color,Vec2(0.0f,m_moveH)},
				{Vec3(m_width,0,0),m_color,Vec2(1.0f,m_moveH)},
				{Vec3(0,-m_height,0),m_color,Vec2(0.0f,0.0f)},
				{Vec3(m_width,-m_height,0),m_color,Vec2(1.0f,0.0f)}
			};
		}
		else {
			return;
		}

		m_indices = {
			0,1,2,
			2,1,3
		};

		

		//描画の表示
		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_meshResName);
		m_draw->SetSamplerState(SamplerState::SamplerNone);
		//色の設定
		m_draw->SetDiffuse(m_color2);
		SetDrawLayer(1);
		//場所の設定
		m_trans = GetComponent<Transform>();
		
		m_trans->SetPosition(m_screen + m_distance);
		//m_trans->SetPosition(-300, 300, 0);

		GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->SetUiGargePtr(GetThis<Garge>());//配列にポインタを入れる
		
		SetAlphaActive(true);
	}

	void Garge::OnUpdate() {

		//auto ratio = 2.0f;
		//UpdateValue(ratio);

		//auto position = m_trans->GetPosition();

		//デバック用
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"transform _x:" <<
		//	 position.x<< "\n" <<
		//	L"transform _y:" <<
		//	position.y<<
		//	"\n" <<
		//	endl;
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());


	}


	void Garge::UpdateValue(float ratio) {
		
		if (m_moveW > 0) {

			auto moveW = (m_sizeX * ratio) / m_sizeX;
			m_vertices[0].position.x = m_width + (m_width * ratio);
			m_vertices[2].position.x = m_width + (m_width * ratio);

			m_vertices[0].textureCoordinate.x = moveW;
			m_vertices[2].textureCoordinate.x = moveW;


		}
		else if (m_moveH > 0) {
			auto moveH = (m_sizeY * ratio) / m_sizeY;
			m_vertices[0].position.y = -m_height + (m_height * ratio);
			m_vertices[1].position.y = -m_height + (m_height * ratio);

			m_vertices[0].textureCoordinate.y = moveH;
			m_vertices[1].textureCoordinate.y = moveH;
		}
		m_draw->UpdateVertices(m_vertices);

	}

	void Garge::OnClear(bool OnOff)
	{
		if (OnOff == true)//オンなら
		{
			m_color2 = m_draw->GetDiffuse();
			m_draw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.0f));//透明にする
		}
		if (OnOff == false)//オフなら
		{
			m_draw->SetDiffuse(m_color2);//透明でなかった時の色に戻る
		}

	}

	void Garge::SetColor(Col4 color) {
		m_draw->SetDiffuse(color);
		m_color2 = m_draw->GetDiffuse();

	}
	void Garge::ThisDestroy() {
		GetStage()->RemoveGameObject<Garge>(GetThis<Garge>());
	}


}
//end namespace basecross