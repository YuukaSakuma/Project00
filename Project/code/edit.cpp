//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include"renderer.h"
#include"edit.h"
#include"input.h"
#include"manager.h"
#include"objectX.h"
#include"model.h"
#include"blockX.h"

#define MODEL (1)

//�I�u�W�F�N�g�t�@�C����
const char *c_Obj[MODEL] =
{
	"data\\MODEL\\block.x"
};

//�ÓI�����o�ϐ��錾
CModel *CEdit::m_apObjectX[NUM_MODEL] = {};

//==============================================================
//�R���X�g���N�^
//==============================================================
CEdit::CEdit()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdx = 0;
	m_nTypeIdx = 0;
	m_bUse = false;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEdit::~CEdit()
{

}

//==============================================================
//��������
//==============================================================
CEdit *CEdit::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEdit *pEdit = NULL;

	if (pEdit == NULL)
	{//���������g�p����ĂȂ�������

	 //���[�V�����̐���
		pEdit = new CEdit;
	}

	if (pEdit != NULL)
	{//���������g�p����ĂȂ�������

	 //���[�V�����̐���
		pEdit->Init();
	}

	return pEdit;
}

//==============================================================
//�G�f�B�b�g�̏���������
//==============================================================
HRESULT CEdit::Init(void)
{
	
	return S_OK;
}

//==============================================================
//�G�f�B�b�g�̏I������
//==============================================================
void CEdit::Uninit(void)
{
	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�G�f�B�b�g�̍X�V����
//==============================================================
void CEdit::Update(void)
{
	////�L�[�{�[�h���̎擾
	//CInputKeyboard *pInputKey = CManager::GetInputKeybard();
	//CDebugProc *pDebug = CManager::GetDebugProc();

	//if (pInputKey->GetTrigger(DIK_F3))
	//{
	//	m_bUse = m_bUse ? false : true;			//�g�p���邩�̗L��

	//	if (m_bUse == true)
	//	{
	//		//�I�u�W�F�N�g�̏�����
	//		CModel::Init();
	//	}
	//	else
	//	{
	//		CModel::Release();
	//	}

	//	//�I�u�W�F�N�g��ނ̕ύX
	//	if (pInputKey->GetTrigger(DIK_1))
	//	{
	//		m_nTypeIdx++;

	//		CModel::Create(m_pos, m_rot, c_Obj[m_nTypeIdx]);

	//		m_nTypeIdx %= MAX_MODEL;			//�J��Ԃ�
	//	}

	//	//�ړ�
	//	if (pInputKey->GetPress(DIK_UP))
	//	{
	//		m_pos.z += 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_DOWN))
	//	{
	//		m_pos.z -= 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_LEFT))
	//	{
	//		m_pos.x -= 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_RIGHT))
	//	{
	//		m_pos.x += 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_LSHIFT))
	//	{
	//		m_pos.y += 1.0f;
	//	}
	//	if (pInputKey->GetPress(DIK_LCONTROL))
	//	{
	//		m_pos.y -= 1.0f;
	//	}

	//	//�ʒu�̍X�V
	//	SetPosition(m_pos);

	//	//�I�u�W�F�N�g�̐ݒu
	//	if (pInputKey->GetTrigger(DIK_RETURN))
	//	{
	//		//����
	//		m_apObjectX[m_nIdx] = CModel::Create(m_pos, m_rot, c_Obj[m_nTypeIdx]);

	//		m_nIdx++;
	//	}

	//	//�t�@�C����������(�Z�[�u)
	//	if (pInputKey->GetTrigger(DIK_0))
	//	{
	//		SaveFile();
	//	}
	//}
}

//==============================================================
//�G�f�B�b�g�̕`�揈��
//==============================================================
void CEdit::Draw(void)
{
	////�I�u�W�F�N�g�̕`��
	//CModel::Draw();
}

//==============================================================
//X�t�@�C���̓ǂݍ���
//==============================================================
HRESULT CEdit::LoadFile(void)
{
	char aString[128] = {};		//������̃S�~��
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	FILE *pFile = NULL;			//�t�@�C���|�C���^��錾

								//�t�@�C�����J��
	pFile = fopen("data\\TXT\\map.txt", "r");

	if (pFile != NULL)
	{
		while (strcmp("END_SCRIPT", &aString[0]) != 0)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp("OBJECTSET", &aString[0]) == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp("TYPE", &aString[0]) == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &nType);			//�ʒu�w
					}
					if (strcmp("POS", &aString[0]) == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%f", &pos.x);			//�ʒu�w
						fscanf(pFile, "%f", &pos.y);			//�ʒu�x
						fscanf(pFile, "%f", &pos.z);			//�ʒu�y
					}
					if (strcmp("ROT", &aString[0]) == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%f", &rot.x);			//�ʒu�w
						fscanf(pFile, "%f", &rot.y);			//�ʒu�x
						fscanf(pFile, "%f", &rot.z);			//�ʒu�y

						break;
					}
				}
			}
			else if (strcmp("END_OBJECTSET", &aString[0]) == 0)
			{
				CModel::Create(pos,rot, c_Obj[nType]);
			}
		}
	}

	return S_OK;
}

//==============================================================
//�t�@�C�������o��
//==============================================================
void CEdit::SaveFile(void)
{
	FILE *pFile = NULL;

	pFile = fopen("data\\TXT\\map.txt", "w");

	if (pFile != NULL)
	{
		//�w�b�_�[�R�����g
		fprintf(pFile, "#=====================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# �}�b�v�z�u���  [map.txt]\n");
		fprintf(pFile, "# Auther : ���v�ԗD��\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#=====================================================================\n");

		//���f���z�u���
		fprintf(pFile, "#---------------------------------------------------------------------\n");
		fprintf(pFile, "# ���f���z�u���\n");
		fprintf(pFile, "#---------------------------------------------------------------------\n");

		fprintf(pFile, "\n");

		fprintf(pFile, "SCREPT					#�����Ȃ�\n");

		for (int nCntModel = 0; nCntModel < NUM_MODEL; nCntModel++)
		{
			CObject *pObj = CObject::GetObjectA(nCntModel);

			if (pObj != NULL && pObj->GetType() == TYPE_MODEL)
			{
				D3DXVECTOR3 pos = pObj->GetPosition();
				D3DXVECTOR3 rot = pObj->GetRotation();

				fprintf(pFile, "MODELSET\n");
				fprintf(pFile, "	SET_TYPE = %d\n",m_nTypeIdx);
				fprintf(pFile, "	POS = %.1f %.1f %.1f\n",pos.x, pos.y, pos.z);
				fprintf(pFile, "	ROT = %.1f %.1f %.1f\n",rot.x, rot.y, rot.z);
				fprintf(pFile, "END_MODELSET\n");

				fprintf(pFile, "\n");
			}
		}

		fprintf(pFile, "END_SCREPT					#�����Ȃ�\n");

		fclose(pFile);
	}
}