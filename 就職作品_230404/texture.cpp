#include "texture.h"


int Texture::LoadTexture(const char* fileName)
{
	//読み込まれているテクスチャ名を調べて、同名のものが
	//すでに読み込まれていたらその番号を返す
	for (unsigned int i = 0; i < g_TextureIndex; i++)
	{
		//テクスチャ名を比較
		if (strcmp(g_TextureName[i], fileName) == 0)
		{
			return i;
		}
	}

	//読み込み最大数を超えていたら負の値を返す
	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return -1;
	}

	//ファイルからテクスチャを読み込む
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		fileName,
		NULL,
		NULL,
		&g_pTexture[g_TextureIndex],
		NULL);

	if (S_OK != hr)
	{
		//読み込みに失敗した場合、負の値を返す
		return -1;
	}

	//読み込んだテクスチャ名を保存する
	strcpy_s(g_TextureName[g_TextureIndex], 256, fileName);

	int retIndex = g_TextureIndex;

	//インデックスを一つ進める
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
	//indexの不正値チェック(負の値)
	if (index < 0)
		return NULL;

	//indexの不正値チェック(最大数オーバー)
	if (index >= (int)g_TextureIndex)
		return NULL;

	return &g_pTexture[index];
}