//==============================================================
//
//�G����[enemy.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "enemy.h"
#include "manager.h"
#include "explosion.h"
#include "billboard.h"
#include "texture.h"
#include "object.h"
#include "modelHierarchy.h"
#include "model.h"
#include "motion.h"
#include "player.h"
#include "game.h"
#include "bullet.h"

//�}�N����`
#define LIFE				(50)			//����

//�ÓI�����o�ϐ�
LPD3DXMESH CEnemy::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CEnemy::m_pBuffMat = NULL;				//�}�e���A���ւ̃|�C���^
DWORD CEnemy::m_dwNumMat = NULL;
int CEnemy::m_nNumAll = 0;			//�G�̑���

//�G�̃��f��
char *CEnemy::m_apFileName[ENEMY_MODEL] =
{
	"data\\MODEL\\enemy\\00_waist.x",
	"data\\MODEL\\enemy\\01_body.x",
	"data\\MODEL\\enemy\\02_head.x",
	"data\\MODEL\\enemy\\03_arm_L.x",
	"data\\MODEL\\enemy\\04_arm_R.x",
	"data\\MODEL\\enemy\\05_foot_L.x",
	"data\\MODEL\\enemy\\06_foot_R.x",
	"data\\MODEL\\enemy\\stick.x",
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CEnemy::CEnemy()
{
	for (int nCntPlayer = 0; nCntPlayer < ENEMY_MODEL; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = nullptr;		//�G(�p�[�c)�ւ̃|�C���^
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_nLife = LIFE;								//����
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//��������
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		pEnemy = new CEnemy;

		//����������
		pEnemy->Init();

		pEnemy->SetPosition(pos);

		pEnemy->SetRotation(rot);
	}

	return pEnemy;
}

//==============================================================
//����������
//==============================================================
HRESULT CEnemy::Init(void)
{
	//�G�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < ENEMY_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//���f���̃t�@�C���ǂݍ���
	SetModel("data\\TXT\\enemy01.txt");

	m_pMotion = NULL;

	if (m_pMotion == NULL)
	{
		m_pMotion = m_pMotion->Create();

		if (m_pMotion != NULL)
		{
			//���[�V�����̏������E����
			m_pMotion->SetModel(&m_apModel[0], 7);
			m_pMotion->Init("data\\TXT\\enemy01.txt", ENEMY_MODEL);
		}
	}

	//�ő�l�E�ŏ��l���
	for (int nCntPlayer = 0; nCntPlayer < ENEMY_MODEL; nCntPlayer++)
	{
		if ((nCntPlayer <= 0 && nCntPlayer <= 2) ||
			(nCntPlayer <= 5 && nCntPlayer <= 6))
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//�ő�l���Z
		}
																//�ő�l����ւ�
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//�ŏ��lX
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//�ŏ��lZ

		}

		//�ŏ��l����ւ�
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//�ŏ��lX
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//�ŏ��lY
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//�ŏ��lZ

		}
	}

	////�I�u�W�F�N�g2D�̏���������
	//CObject::Init();

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_ENEMY);

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void CEnemy::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_MODEL; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//�g�p����Ă�Ƃ�

		 //�I������
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//�g�p����Ă�Ƃ�

	 //���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�X�V����
//==============================================================
void CEnemy::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();
	CPlayer *pPlyer = CGame::GetPlayerModel();

		//���[�V�����̍X�V����
		m_pMotion->Update();
	
		m_posOld = m_pos;

		m_pos += (pPlyer->GetPosition() - m_pos) * 0.005f;

		//��]�ʑ���(��)
		//m_rot.y += 0.01f;
	
		SetState();

		pDebugProc->Print("�G�̗̑� : [%d] \n", m_nLife);
}

//==============================================================
//�`�揈��
//==============================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntMat = 0; nCntMat < ENEMY_MODEL; nCntMat++)
	{
		m_apModel[nCntMat]->Draw();
	}
}

//==============================================================
//��Ԑݒ�
//==============================================================
void CEnemy::SetState(void)
{
	CPlayer *pPlayerModel = CGame::GetPlayerModel();

	float fAngle = 0.0f;
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (m_state)
	{
	case STATE_NONE:

		if (m_nCntAttack >= 50)
		{
			m_state = STATE_ATTACK;
			m_nCntAttack = 0;
		}
		else
		{
			m_nCntAttack++;
		}

		break;

	case STATE_ATTACK:

		//�v���C���[�̍��W�Ɍ����Ēe��
		rot = D3DXVECTOR3(pPlayerModel->GetPosition().x - m_pos.x, pPlayerModel->GetPosition().y - m_pos.y, pPlayerModel->GetPosition().z - m_pos.z);

		move = D3DXVECTOR3(-sinf(m_rot.y) * 10.0f, 0.0f, -cosf(m_rot.y) * 10.0f);

		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f * 0.5f, m_pos.z),m_rot, move,CBullet::TYPE_C ,TYPE_ENEMY);
		
		m_state = STATE_NONE;

		break;

	case STATE_DAMAGE:

		m_nCntDamage--;

		if (m_nCntDamage <= 0)
		{
			m_state = STATE_NONE;

			//��Ԑݒ�
			for (int nCntEnemy = 0; nCntEnemy < ENEMY_MODEL; nCntEnemy++)
			{
				m_apModel[nCntEnemy]->SetState(m_state);		//�ʏ��Ԃɂ���
			}
		}
		break;
	}
}

//==============================================================
//�q�b�g����
//==============================================================
void CEnemy::Hit(void)
{
	m_nLife--;

	if (m_nLife > 0)
	{
		m_state = CObject::STATE_DAMAGE;

		for (int nCntEnemy = 0; nCntEnemy < ENEMY_MODEL; nCntEnemy++)
		{
			m_apModel[nCntEnemy]->SetState(m_state);		//�_���[�W��Ԃɂ���
		}

		m_nCntDamage = 5;
	}
	else if (m_nLife <= 0)
	{
		//�p�[�e�B�N������
		//CParticle::Create(m_pos, D3DXCOLOR(0.1f, 0.4f, 0.5f, 1.0f), TYPE_PLAYER, 30, 40);

		//�I������
		Uninit();

	}
}

//=============================================================
//���f���̓ǂݍ���
//=============================================================
void CEnemy::SetModel(const char * c_FileName)
{
	FILE *pFile;				//�t�@�C���|�C���^
	char aString[126];		//�����ǂݍ���
	int nIndex = 0, nParent = 0;	//�p�[�cNo.,�e�ԍ�
	D3DXVECTOR3 pos, rot;

	//�t�@�C���J��
	pFile = fopen(c_FileName, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]����܂ł̊�

			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]��������

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]������܂ł̊�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]��������

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]������܂ł̊�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						if (strcmp(&aString[0], "INDEX") == 0)
						{//�p�[�cNo.

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nIndex);			//�p�[�cNo.�ǂݍ���

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//�e���

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nParent);			//�e�ԍ��ǂݍ���

							if (nParent == -1)
							{//�e�����Ȃ�������

								m_apModel[nIndex]->SetParent(NULL);		//NULL������
							}
							else
							{//�e��������

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//�e�ԍ������
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//�ʒu���

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &pos.x);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.y);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.z);		//�ʒu�ǂݍ���

							m_apModel[nIndex]->SetPosition(pos);		//�ʒu�ݒ�
							m_apModel[nIndex]->SetDefaultPosition(pos);	//�����ʒu�ݒ�

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//�������

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &rot.x);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.y);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.z);		//�����ǂݍ���

							m_apModel[nIndex]->SetRotation(rot);		//�����ݒ�
							m_apModel[nIndex]->SetDefaultRotation(rot);	//���������ݒ�
						}
					}
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
}