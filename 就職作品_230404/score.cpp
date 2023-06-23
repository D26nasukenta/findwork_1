#include"main.h"
#include "scene.h"
#include"renderer.h"
#include "manager.h"
#include "score.h"

void Score::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);


	vertex[1].Position = D3DXVECTOR3(00.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);


	vertex[2].Position = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);


	vertex[3].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};//<-������[���N���A����B(�\���̓������ׂă[����)
	//�\���̓������ׂă[���ɂ���B
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;//�f�t�H���g�@->�@�_�C�i�~�b�N
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//0 -> D3D11_CPU_ACCESS_WRITE
	//�d���Ȃ邩��ύX����̂͐T�d��
	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;


	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\figure_001.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");


	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Count = 0;
	m_Score = 0;
}

void Score::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Score::Update()
{
	
}

void Score::Draw()
{

	m_Count = m_Score;
	//���̃J�b�R����ǉ��A�؂�ւ�
	{

		for (int i = 0; i < 2; i++)
		{
			float x = (m_Count % 10);

			//�e�N�X�`�����W�Y�o
			x = m_Count % 5 * (1.0f / 5);
			float y = m_Count / 5 * (1.0f / 2);

			float tx = 0 - 70.0f * i;
			//���_�f�[�^��������

			D3D11_MAPPED_SUBRESOURCE msr;
			//�}�b�v�֐��Œ��_�̒��g�̏�����������
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			vertex[0].Position = D3DXVECTOR3(tx + SCREEN_WIDTH / 2, 10.0f, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = D3DXVECTOR2(x, y);


			vertex[1].Position = D3DXVECTOR3(tx + SCREEN_WIDTH / 2 + 50.0f, 10.0f, 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(x + 0.2, y);


			vertex[2].Position = D3DXVECTOR3(tx + SCREEN_WIDTH / 2, 60.0f, 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.5);


			vertex[3].Position = D3DXVECTOR3(tx + SCREEN_WIDTH / 2 + 50.0f, 60.0f, 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = D3DXVECTOR2(x + 0.2, y + 0.5);

			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

			m_Count /= 10;

			//���̓��C�A�E�g�ݒ�
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

			//�V�F�[�_�ݒ�
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

			//�}�g���N�X�ݒ�
			Renderer::SetWorldViewProjection2D();


			//���_�o�b�t�@�ݒ�
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

			//�}�e���A���ݒ�
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Renderer::SetMaterial(material);

			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			//�v���~�e�B�u�ݒ�
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


			Renderer::GetDeviceContext()->Draw(4, 0);


		}
	}

}
