#include "main.h"
#include "renderer.h"
#include "goal2D.h"

void Goal2D::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);


	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);


	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};//<-これもゼロクリアする。(構造体内をすべてゼロに)
	//構造体内をすべてゼロにする。
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;//デフォルト　->　ダイナミック
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//0 -> D3D11_CPU_ACCESS_WRITE
	//重くなるから変更するのは慎重に
	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;


	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャーの読み込み
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\Goal_001.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");



}

void Goal2D::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Goal2D::Update()
{
}

void Goal2D::Draw()
{
	{
		if (m_trans == true)
		{
			m_Frame = 0.0f;
			m_change.x += 2.0f;
			m_change.y += 1.0f;

			if (m_alpha <= 1.0f)
			{
				m_alpha += 0.005f;

			}
			else
			{
				m_trans = false;

			}
		}

		if (m_trans == false)
		{
			if (m_Frame <= 60 * 3 &&  m_alpha > 0.0f)
			{
				m_Frame++;
				m_alpha -= 0.02f;

			}
			else
			{
				m_change.x = 0.0f;
				m_change.y = 0.0f;
			}
		}
		//頂点データ書き換え

		D3D11_MAPPED_SUBRESOURCE msr;
		//マップ関数で頂点の中身の書き換え準備
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - m_change.x, SCREEN_HEIGHT /2 - m_change.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
		vertex[0].TexCoord = D3DXVECTOR2(0, 0);


		vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH/2 + m_change.x, SCREEN_HEIGHT / 2 - m_change.y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
		vertex[1].TexCoord = D3DXVECTOR2(1, 0);


		vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - m_change.x, SCREEN_HEIGHT/2 + m_change.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
		vertex[2].TexCoord = D3DXVECTOR2(0, 1);


		vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH/2 + m_change.x, SCREEN_HEIGHT/2 + m_change.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
		vertex[3].TexCoord = D3DXVECTOR2(1, 1);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	//マトリクス設定
	Renderer::SetWorldViewProjection2D();


	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画

	Renderer::GetDeviceContext()->Draw(4, 0);

}

void Goal2D::SetAlpha(bool trans)
{
	m_trans = trans;
}
