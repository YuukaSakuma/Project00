//==============================================================
//
//�I�u�W�F�N�g����[object.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"object.h"
#include"renderer.h"
#include"manager.h"

//�ÓI�����o�ϐ�
CObject * CObject::m_apObject[MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//==============================================================
//�R���X�g���N�^
//==============================================================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		//�������g����
			m_nID = nCntObject;					//�������g��ID��ۑ�
			m_nNumAll++;						//�������J�E���g�A�b�v
			break;
		}
	} 
}

//==============================================================
//�R���X�g���N�^
//==============================================================
CObject::CObject(TYPE type)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		//�������g����
			m_nID = nCntObject;					//�������g��ID��ۑ�
			m_type = type;
			m_nNumAll++;						//�������J�E���g�A�b�v
			break;
		}
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CObject::~CObject()
{
	
}

//==============================================================
//�S�ẴI�u�W�F�N�g�̔j��
//==============================================================
void CObject::ReleseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//�I������
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//==============================================================
//�S�ẴI�u�W�F�N�g�̍X�V
//==============================================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//�X�V����
			m_apObject[nCntObject]->Update();
		}
	}
}

//==============================================================
//�S�ẴI�u�W�F�N�g�̕`��
//==============================================================
void CObject::DrawAll(void)
{
	//�J�����̎擾
	CCamera *pCamera = CManager::Get()->GetCamera();

	//�J�����̐ݒ�
	pCamera->Set();

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//�`�揈��
			m_apObject[nCntObject]->Draw();
		}
	}	
}

//==============================================================
//�I�u�W�F�N�g�̔j��
//==============================================================
void CObject::Release(void)
{
	int nData = m_nID;

	if (m_apObject[nData] != NULL)
	{//�g�p���Ă�����

		delete m_apObject[nData];
		m_apObject[nData] = NULL;

		m_nNumAll--;
	}
}

//==============================================================
//�}�b�v�̃��Z�b�g
//==============================================================
void CObject::ResetMapAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			if (m_apObject[nCntObject]->m_type != TYPE_PLAYER &&
				m_apObject[nCntObject]->m_type != TYPE_NONE)
			{
				//�I������
				m_apObject[nCntObject]->Uninit();
			}
		}
	}
}