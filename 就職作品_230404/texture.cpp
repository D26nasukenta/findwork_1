#include "texture.h"


int Texture::LoadTexture(const char* fileName)
{
	//�ǂݍ��܂�Ă���e�N�X�`�����𒲂ׂāA�����̂��̂�
	//���łɓǂݍ��܂�Ă����炻�̔ԍ���Ԃ�
	for (unsigned int i = 0; i < g_TextureIndex; i++)
	{
		//�e�N�X�`�������r
		if (strcmp(g_TextureName[i], fileName) == 0)
		{
			return i;
		}
	}

	//�ǂݍ��ݍő吔�𒴂��Ă����畉�̒l��Ԃ�
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return -1;
	}

	//�t�@�C������e�N�X�`����ǂݍ���
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		fileName,
		NULL,
		NULL,
		&g_pTexture[g_TextureIndex],
		NULL);

	if (S_OK != hr)
	{
		//�ǂݍ��݂Ɏ��s�����ꍇ�A���̒l��Ԃ�
		return -1;
	}

	//�ǂݍ��񂾃e�N�X�`������ۑ�����
	strcpy_s(g_TextureName[g_TextureIndex], 256, fileName);

	int retIndex = g_TextureIndex;

	//�C���f�b�N�X����i�߂�
	g_TextureIndex++;

	return retIndex;
}

void Texture::UninitTexture(void)
{
	for (unsigned int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] != NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}

ID3D11ShaderResourceView** Texture::GetTexture(int index)
{
	//index�̕s���l�`�F�b�N(���̒l)
	if (index < 0)
		return NULL;

	//index�̕s���l�`�F�b�N(�ő吔�I�[�o�[)
	if (index >= (int)g_TextureIndex)
		return NULL;

	return &g_pTexture[index];
}