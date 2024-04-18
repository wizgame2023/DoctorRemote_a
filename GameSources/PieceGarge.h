/*!
@file PieceGarge.h
@brief “G‚ÌŒ‡•Ğ‚ÌƒQ[ƒW
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PieceGarge :public GameObject{

		shared_ptr<Transform> m_transform;
		float m_length;
		float m_maxLength;
		float m_garge;

		shared_ptr<Player> m_player;
		vector<VertexPositionColorTexture> m_vertices;
		shared_ptr<PCTSpriteDraw> m_drawComp;

	public:
		PieceGarge(const shared_ptr<Stage>& StagePtr,const shared_ptr<Player>& player);
		~PieceGarge(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		float GetLength();
		float GetMaxLength();
		void SetLength(float length);
		void UpdateValue(int value);
	};
}
//end namespace basecross
