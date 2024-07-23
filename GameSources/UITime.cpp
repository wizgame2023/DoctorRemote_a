/*!
@file UITime.cpp
@brief 数字の画像
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	UITime::UITime(const shared_ptr<Stage>& stagePtr,int number,Vec3 pos):
		GameObject(stagePtr),
		m_number(number),
		m_pos(pos),
		m_meshResName(L"NumbersWhite"),
		m_width(40.0f),
		m_heigth(80.0f),
		m_color(Col4(0.1640f, 0.8632f, 0.2109f, 1.0f)),
		m_mojiNum(11)
	{}
	UITime::UITime(const shared_ptr<Stage>& stagePtr, int number, Vec3 pos,float width,float heigth, Col4 color) :
		GameObject(stagePtr),
		m_number(number),
		m_pos(pos),
		m_meshResName(L"NumbersWhite"),
		m_width(width),
		m_heigth(heigth),
		m_color(color),
		m_mojiNum(11)
	{}
	UITime::UITime(const shared_ptr<Stage>& stagePtr, int number, Vec3 pos, float width, float heigth , wstring meshResName, Col4 color,int mojiNum) :
		GameObject(stagePtr),
		m_number(number),
		m_pos(pos),
		m_width(width),
		m_heigth(heigth),
		m_meshResName(meshResName),
		m_color(color),
		m_mojiNum(mojiNum)
	{}



	void UITime::OnCreate() {
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetPlayFlag())//stageがPlayするところなら
		{
			GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->SetUiTimePtr(GetThis<UITime>());//自分自身のポインタを渡す
		}

		m_moveW = (512.0f / m_mojiNum) / 512.0f;
		m_moveH = 75.0f/128.0f;
		//m_moveW = 50.0f/512.0f;
		//m_moveH = 100.0f/128.0f;
		int number = m_number;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(0.0f,0.0f,0.0f),color,Vec2((m_moveW * number),0.0f)},
			{Vec3(m_width,0.0f,0.0f),color,Vec2((m_moveW * (number + 1)),0.0f)},
			{Vec3(0.0f,-m_heigth,0.0f),color,Vec2((m_moveW * number),1.0f)},
			{Vec3(m_width,-m_heigth,0.0f),color,Vec2((m_moveW * (number + 1)),1.0f)},
		};

		m_indices = {
			0,1,2,
			2,1,3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_meshResName);
		m_draw->SetSamplerState(SamplerState::LinearWrap);
		m_draw->SetDiffuse(m_color);

		SetAlphaActive(true);
		SetDrawLayer(2);
		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
	}
	void UITime::OnUpdate() {

		//UpdateValue(m_number);
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetPlayFlag())//stageがPlayするところなら
		{
			bool ClearFlag = GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->GetClearFlag();//透明にするかどうか決める
			OnClear(ClearFlag);

		}

	}

	void UITime::OnClear(bool OnOff)
	{
		if (OnOff == true)//オンなら
		{
			//m_color = m_draw->GetDiffuse();
			m_draw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.0f));//透明にする
		}
		if (OnOff == false)//オフなら
		{
			m_draw->SetDiffuse(m_color);//透明でなかった時の色に戻る
		}
	}


	void UITime::UpdateValue(int number) {
		m_vertices[0].textureCoordinate.x = m_moveW * number;
		m_vertices[1].textureCoordinate.x = m_moveW * (number + 1);
		m_vertices[2].textureCoordinate.x = m_moveW * number;
		m_vertices[3].textureCoordinate.x = m_moveW * (number + 1);

		m_draw->UpdateVertices(m_vertices);
	}

	void UITime::ThisDestroy() {
		GetStage()->RemoveGameObject<UITime>(GetThis<UITime>());

	}
	Col4 UITime::GetColor() {
		return m_draw->GetDiffuse();
	}
	void UITime::SetColor(Col4 color) {
		m_draw->SetDiffuse(color);
	}

}
//end namespace basecross