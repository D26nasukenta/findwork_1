//=============================================================================
//
// �X�v���C�g���� [sprite.cpp]
// Author : �n�ӑ�C
//
//=============================================================================
#include "sprite.h"
#include "renderer.h"
#include "texture.h"
#include "Scene.h"
#include "Camera.h"
#include "manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX 4	//�K�v�Ȓ��_�̐�


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer* g_VertexBuffer = NULL;	// ���_���
static ID3D11InputLayout* m_VertexLayout = NULL;
static ID3D11VertexShader* m_VertexShader = NULL;
static ID3D11PixelShader* m_PixelShader = NULL;

//=============================================================================
// ����������
//=============================================================================
void Sprite::InitSprite()
{
	ID3D11Device* pDevice = Renderer::GetDevice();

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer(&bd, NULL, &g_VertexBuffer);

}

//=============================================================================
// �I������
//=============================================================================
void Sprite::UninitSprite()
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F
//=============================================================================
void Sprite::DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�O�ԁi����̒��_�j
	vertex[0].Position = D3DXVECTOR3(X - hw, Y - hh, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	// ���_�P�ԁi�E��̒��_�j
	vertex[1].Position = D3DXVECTOR3(X + hw, Y - hh, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	// ���_�Q�ԁi�����̒��_�j
	vertex[2].Position = D3DXVECTOR3(X - hw, Y + hh, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	// ���_�R�ԁi�E���̒��_�j
	vertex[3].Position = D3DXVECTOR3(X + hw, Y + hh, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�
// ���W�E�T�C�Y�EUV�w��E���_�F�E��]�p�x
//=============================================================================
void Sprite::DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXVECTOR4 Color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	float hw, hh;
	hw = Width * 0.5f;
	hh = Height * 0.5f;

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	float BaseAngle = atan2f(hh, hw);		// ���S�_���璸�_�ɑ΂���p�x
	D3DXVECTOR2 temp = D3DXVECTOR2(hw, hh);
	float Radius = D3DXVec2Length(&temp);	// ���S�_���璸�_�ɑ΂��鋗��

	float x = X - cosf(BaseAngle + Rot) * Radius;
	float y = Y - sinf(BaseAngle + Rot) * Radius;
	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle - Rot) * Radius;
	y = Y - sinf(BaseAngle - Rot) * Radius;
	vertex[1].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X - cosf(BaseAngle - Rot) * Radius;
	y = Y + sinf(BaseAngle - Rot) * Radius;
	vertex[2].Position = D3DXVECTOR3(x, y, 0.0f);

	x = X + cosf(BaseAngle + Rot) * Radius;
	y = Y + sinf(BaseAngle + Rot) * Radius;
	vertex[3].Position = D3DXVECTOR3(x, y, 0.0f);

	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	//�@����ݒ�
	vertex[0].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//UV�̐ݒ�
	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	//�}�g���N�X�̐ݒ�
	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

void Sprite::DrawSpriteBillBoard(int texNo, D3DXVECTOR3 Position,D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale,float U, float V, float UW, float VH, D3DXVECTOR4 Color, float Rot)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(-1.0f,  1.0f, 0.0f);
	vertex[1].Position = D3DXVECTOR3( 1.0f,  1.0f, 0.0f);
	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[3].Position = D3DXVECTOR3( 1.0f, -1.0f, 0.0f);

	vertex[0].Diffuse = Color;
	vertex[1].Diffuse = Color;
	vertex[2].Diffuse = Color;
	vertex[3].Diffuse = Color;

	//�@����ݒ�
	vertex[0].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//UV�̐ݒ�
	vertex[0].TexCoord = D3DXVECTOR2(U, V);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	//�@�J�����̃r���[�}�g���N�X�擾
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	D3DXMATRIX view = camera->GetViewMatrix();

	//�@�r���[�̋t�s��
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);//�t�s��
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale ,rot, trans;
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);

	world = scale * rot* invView * trans;
	Renderer::SetWorldMatrix(&world);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=============================================================================
// �X�v���C�g�f�[�^�ݒ�i����w��j
// ���W�E�T�C�Y�EUV�w��
//=============================================================================
void Sprite::DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ��������_�Ƃ��Đݒ肷��v���O����
	vertex[0].Position = D3DXVECTOR3(X, Y, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(U, V);

	vertex[1].Position = D3DXVECTOR3(X + Width, Y, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(U + UW, V);

	vertex[2].Position = D3DXVECTOR3(X, Y + Height, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(U, V + VH);

	vertex[3].Position = D3DXVECTOR3(X + Width, Y + Height, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(10.0f, 10.0f, 10.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(U + UW, V + VH);

	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(texNo));

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(NUM_VERTEX, 0);
}
