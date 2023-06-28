#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "player.h"
#include "controlui.h"

void ControlUI::Init()
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
		"asset\\texture\\controlUI.png",
		NULL,
		NULL,
		&m_Texture[0],
		NULL);

	assert(m_Texture[0]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial.png",
		NULL,
		NULL,
		&m_Texture[1],
		NULL);

	assert(m_Texture[1]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial_001.png",
		NULL,
		NULL,
		&m_Texture[2],
		NULL);

	assert(m_Texture[2]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial_002.png",
		NULL,
		NULL,
		&m_Texture[3],
		NULL);

	assert(m_Texture[3]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial_003.png",
		NULL,
		NULL,
		&m_Texture[4],
		NULL);

	assert(m_Texture[4]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial_004.png",
		NULL,
		NULL,
		&m_Texture[5],
		NULL);

	assert(m_Texture[5]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial_005.png",
		NULL,
		NULL,
		&m_Texture[6],
		NULL);

	assert(m_Texture[6]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial_006.png",
		NULL,
		NULL,
		&m_Texture[7],
		NULL);

	assert(m_Texture[7]);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile
	(Renderer::GetDevice(),
		"asset\\texture\\tiutolial_007.png",
		NULL,
		NULL,
		&m_Texture[8],
		NULL);

	assert(m_Texture[8]);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_alpha = 0.0f;

}

void ControlUI::Uninit()
{
	m_VertexBuffer->Release();

	for(int i = 0; i < 7; i++)
	{

	m_Texture[i]->Release();
	}


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void ControlUI::Update()
{
}

void ControlUI::Draw()
{

	Scene* scene = Manager::GetScene();
	PLAYER* player = scene->GetGameObject<PLAYER>(1);

	if (scene->GetSceneNumber() == 3)//�R�̓`���[�g���A��
	{

		{
			//���_�f�[�^��������

			D3D11_MAPPED_SUBRESOURCE msr;
			//�}�b�v�֐��Œ��_�̒��g�̏�����������
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[0].TexCoord = D3DXVECTOR2(0, 0);


			vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[1].TexCoord = D3DXVECTOR2(1, 0);


			vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[2].TexCoord = D3DXVECTOR2(0, 1);


			vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[3].TexCoord = D3DXVECTOR2(1, 1);

			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
		}
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

		if ( m_Frame == 0)//�`���[�g���A���ւ悤����
		{
			m_Frame = 0;
			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[1]);

			if ((GetKeyboardPress(DIK_SPACE) || IsButtonTriggered(0, BUTTON_A)) 
				&& m_alpha >= 1.0f && player->GetTutorialStep() == 0)
			{
				m_Frame = 1;
				m_alpha = 0.0f;
			}

		}
		else if (m_Frame == 1 )//W�ňړ�
		{
			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[2]);

			if (m_alpha >= 1.0f && player->GetTutorialStep() == 2)
			{
				m_Frame = 3;
				m_alpha = 0.0f;
			}
		}
		
		else if (m_Frame == 3)//ADS�ňړ�
		{
			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[4]);

			if (m_alpha >= 1.0f && player->GetTutorialStep() == 3)
			{
				m_Frame = 4;
				m_alpha = 0.0f;
			}
		}
		else if (m_Frame == 4)//�{�[����ێ�����
		{
			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[5]);

			if (m_alpha >= 1.0f && player->GetTutorialStep() == 4)
			{
				m_Frame = 5;
				m_alpha = 0.0f;
			}
		}
		else if (m_Frame == 5)//�{�[�����V���[�g
		{
			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[6]);

			if (m_alpha >= 1.0f && player->GetTutorialStep() == 5)
			{
				m_Frame = 6;
				m_alpha = 0.0f;
			}
		}
		else if (m_Frame == 6)//���Z�b�g
		{
			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[7]);

			if (m_alpha >= 1.0f && player->GetTutorialStep() == 6)
			{
				m_Frame = 7;
				m_alpha = 0.0f;
			}
		}
		else if (m_Frame == 7)//���R����
		{
			//�e�N�X�`���ݒ�
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[8]);

			if (m_alpha >= 1.0f && player->GetTutorialStep() == 8)
			{
				m_alpha = 0.0f;
			}
		}
		//�v���~�e�B�u�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//�|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);

		if (m_alpha <= 1.0f)
		{
			m_alpha += 0.003f;
		}
	}

	if (scene->GetSceneNumber() == 2)
	{
		m_alpha = 0.7f;
		{
			//���_�f�[�^��������

			D3D11_MAPPED_SUBRESOURCE msr;
			//�}�b�v�֐��Œ��_�̒��g�̏�����������
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[0].TexCoord = D3DXVECTOR2(0, 0);


			vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[1].TexCoord = D3DXVECTOR2(1, 0);


			vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[2].TexCoord = D3DXVECTOR2(0, 1);


			vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_alpha);
			vertex[3].TexCoord = D3DXVECTOR2(1, 1);

			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
		}
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
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[0]);



		//�v���~�e�B�u�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//�|���S���`��

		Renderer::GetDeviceContext()->Draw(4, 0);
	}

}
