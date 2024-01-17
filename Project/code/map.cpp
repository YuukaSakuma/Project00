//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"renderer.h"
#include"map.h"
#include"input.h"
#include"playermodel.h"
#include"manager.h"
#include"blockX.h"
#include"field.h"
#include"model.h"
#include"wall.h"

//�ÓI�����o�ϐ�
char *CMap::m_apFileName[MAX_MODEL] =
{
	"data\\MODEL\\Ground00.x",
	"data\\MODEL\\Ground01.x",
	"data\\MODEL\\Ground02.x",
	"data\\MODEL\\Ground03.x",
	"data\\MODEL\\Ground04.x",
	"data\\MODEL\\Ground05.x",
};
//==============================================================
//�R���X�g���N�^
//==============================================================
CMap::CMap()
{

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CMap::~CMap()
{

}

//===========================================================================================
// ����
//===========================================================================================
CMap *CMap::Create(void)
{
	CMap *pMap = nullptr;

	pMap = new CMap;

	if (pMap != nullptr)
	{
		pMap->Init();

		return pMap;
	}

	return pMap;
}

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
HRESULT CMap::Init(void)
{
	Set();

	return E_NOTIMPL;
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void CMap::Uninit(void)
{
	//�I�u�W�F�N�g�i�������g�̔j���j
	//CObject::Release();
}

//===========================================================================================
// �I�u�W�F�N�g�̓ǂݍ���
//===========================================================================================
void CMap::ObjectSet(FILE *pFile)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 rot = {};
	int nIndex = 0;
	char not[128];

	while (strcmp("END_OBJECTSET", &not[0]) != 0)
	{
		fscanf(pFile, "%s", &not[0]);	//������ǂݍ���

		if (strcmp("TYPE", &not[0]) == 0)
		{
			fscanf(pFile, "%s", &not[0]);						//=��ǂݍ���
			fscanf(pFile, "%d", &nIndex);						//���f���ԍ�
		}
		if (strcmp("POS", &not[0]) == 0)
		{
			fscanf(pFile, "%s", &not[0]);	//=��ǂݍ���
			fscanf(pFile, "%f", &pos.x);	//�ʒux
			fscanf(pFile, "%f", &pos.y);	//�ʒuy
			fscanf(pFile, "%f", &pos.z);	//�ʒuz
		}
		if (strcmp("ROT", &not[0]) == 0)
		{
			fscanf(pFile, "%s", &not[0]);						//=��ǂݍ���
			fscanf(pFile, "%f", &rot.x);				//����x
			fscanf(pFile, "%f", &rot.y);				//����y
			fscanf(pFile, "%f", &rot.z);				//����z
		}
	}

	if (strcmp("END_OBJECTSET", &not[0]) == 0)
	{//�������ǂݍ��܂ꂽ��
	 
		//���f���̐ݒu
		CModel::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(rot.x, rot.y, rot.z), m_apFileName[nIndex]);
	}
}

//===========================================================================================
// �I�u�W�F�N�g�̓ǂݍ���
//===========================================================================================
void CMap::WallSet(FILE *pFile)
{
	D3DXVECTOR3 pos = {};
	int nType = 0;
	char not[128];

	while (strcmp("END_WALLSET", &not[0]) != 0)
	{
		fscanf(pFile, "%s", &not[0]);	//������ǂݍ���

		if (strcmp("TYPE", &not[0]) == 0)
		{
			fscanf(pFile, "%s", &not[0]);						//������ǂݍ���
			fscanf(pFile, "%s", &not[0]);						//=��ǂݍ���
			fscanf(pFile, "%d", &nType);						//���
		}
		if (strcmp("POS", &not[0]) == 0)
		{
			fscanf(pFile, "%s", &not[0]);	//=��ǂݍ���
			fscanf(pFile, "%f", &pos.x);	//�ʒux
			fscanf(pFile, "%f", &pos.y);	//�ʒuy
			fscanf(pFile, "%f", &pos.z);	//�ʒuz
		}
	}

	if (strcmp("END_WALLSET", &not[0]) == 0)
	{//�������ǂݍ��܂ꂽ��
	 //�G�̐ݒu
		CWall::Create(CObject3D::TYPE_NONE, D3DXVECTOR3(pos.x, pos.y, pos.z));
	}
}

//===========================================================================================
// �ǂݍ���
//===========================================================================================
void CMap::Set(void)
{
	//�ϐ��錾
	bool bLoad = false;
	char not[128];

	FILE *pFile;			//�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("data\\TXT\\map.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &not[0]);			//�������ǂݍ���

			if (strcmp("SCRIPT", &not[0]) == 0)
			{//SCRIPT���ǂݍ��߂���
				bLoad = true;			//�ǂݍ��݂��J�n
			}

			if (bLoad == true)
			{
				while (strcmp("END_SCRIPT", &not[0]) != 0)
				{
					fscanf(pFile, "%s", &not[0]);				//�������ǂݍ���
	
					if (strcmp("SET_OBJECT", &not[0]) == 0)
					{
						ObjectSet(pFile);
					}
					if(strcmp("SET_WALL", &not[0]) == 0)
					{
						WallSet(pFile);
					}
				}
			}

			if (strcmp("END_SCRIPT", &not[0]) == 0)
			{//SCRIPT���ǂݍ��߂Ȃ������ꍇ
				bLoad = false;			//�ǂݍ��݂��I��
				break;			//�����𔲂���
			}
		}
	}
}