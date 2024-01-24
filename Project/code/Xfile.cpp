//==============================================================
//
//�e�N�X�`������[texture.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "Xfile.h"
#include "manager.h"
#include "renderer.h"

//�ÓI�����o�ϐ��錾
int CXFile::m_nNumAll = -1;
const char *CXFile::m_apFilename[MAX_TEX] = {};
CXFile::Material CXFile::m_Material[MAX_TEX] = {};			//�}�e���A���̏��

//==============================================================
//�R���X�g���N�^
//==============================================================
CXFile::CXFile()
{
	//�}�e���A��������
	for (int nCntModel = 0; nCntModel < MAX_TEX; nCntModel++)
	{
		m_Material[nCntModel].pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
		m_Material[nCntModel].pMesh = NULL;			//���b�V���ւ̃|�C���^
		m_Material[nCntModel].dwNumMat = NULL;		//�}�e���A���̐�
		m_Material[nCntModel].pTexture = NULL;		//�e�N�X�`��
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CXFile::~CXFile()
{

}

//==============================================================
//�}�e���A���ǂݍ��ݏ���
//==============================================================
HRESULT CXFile::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	for (int nCntModel = 0; nCntModel < TEX_MAX; nCntModel++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFilename[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_Material[nCntModel].pBuffMat,
			NULL,
			&m_Material[nCntModel].dwNumMat,
			&m_Material[nCntModel].pMesh);

		D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

		m_Material[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[m_Material[nCntModel].dwNumMat];

		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)m_Material[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_Material[nCntModel].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`�������݂���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_Material[nCntModel].pTexture[nCntMat]);
			}
			else
			{//�e�N�X�`�������݂��Ȃ�
				m_Material[nCntModel].pTexture[nCntMat] = NULL;
			}
		}

		m_nNumAll++;		//���f���̐����Z
	}

	return S_OK;
}

//==============================================================
//�}�e���A���j������
//==============================================================
void CXFile::Unload(void)
{
	for (int nCntModel = 0; nCntModel < MAX_TEX; nCntModel++)
	{
		//�e�N�X�`���̔j��
		for (int nCntMat = 0; nCntMat < (int)m_Material[nCntModel].dwNumMat; nCntMat++)
		{
			if (m_Material[nCntModel].pTexture[nCntMat] != NULL)
			{
				m_Material[nCntModel].pTexture[nCntMat]->Release();
				m_Material[nCntModel].pTexture[nCntMat] = NULL;
			}
		}

		//�}�e���A���̔j��
		if (m_Material[nCntModel].pBuffMat != NULL)
		{
			m_Material[nCntModel].pBuffMat->Release();
			m_Material[nCntModel].pBuffMat = NULL;
		}

		//���b�V���̔j��
		if (m_Material[nCntModel].pMesh != NULL)
		{
			m_Material[nCntModel].pMesh->Release();
			m_Material[nCntModel].pMesh = NULL;
		}
	}
}

//==============================================================
//���f���ԍ��w�菈��
//==============================================================
int CXFile::Regit(const char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	for (int nCntModel = 0; nCntModel < MAX_TEX; nCntModel++)
	{
		if (m_apFilename[nCntModel] == pFilename)
		{//�t�@�C�����������Ƃ�

			return nCntModel;		//�ԍ�
		}
		else if (m_apFilename[nCntModel] != pFilename && nCntModel > m_nNumAll)
		{//�t�@�C�������Ⴄ

			m_apFilename[nCntModel] = pFilename;

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(m_apFilename[nCntModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_Material[nCntModel].pBuffMat,
				NULL,
				&m_Material[nCntModel].dwNumMat,
				&m_Material[nCntModel].pMesh);

			D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

			m_Material[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[m_Material[nCntModel].dwNumMat];

			//�}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)m_Material[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_Material[nCntModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//�e�N�X�`�������݂���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&m_Material[nCntModel].pTexture[nCntMat]);
				}
				else
				{//�e�N�X�`�������݂��Ȃ�
					m_Material[nCntModel].pTexture[nCntMat] = NULL;
				}
			}

			m_nNumAll++;

			return m_nNumAll;		//�}�e���A���̔ԍ���Ԃ�
		}
	}

	return m_nNumAll;		//�}�e���A���̔ԍ���Ԃ�
}

//==============================================================
//�e�N�X�`���̏��擾
//==============================================================
LPDIRECT3DTEXTURE9 CXFile::GetTexAddress(int nIdx, int nMat)
{
	return m_Material[nIdx].pTexture[nMat];		//�w��̃e�N�X�`����Ԃ�
}

//==============================================================
//�}�e���A���̏��擾
//==============================================================
LPD3DXBUFFER CXFile::GetMatAddress(int nIdx)
{
	return m_Material[nIdx].pBuffMat;
}

//==============================================================
//�}�e���A���̐��̏��擾
//==============================================================
DWORD CXFile::GetNumMatAddress(int nIdx)
{
	return m_Material[nIdx].dwNumMat;
}

//==============================================================
//���b�V�����擾
//==============================================================
LPD3DXMESH CXFile::GetMeshAddress(int nIdx)
{
	return m_Material[nIdx].pMesh;
}