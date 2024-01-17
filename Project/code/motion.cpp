//==============================================================
//
//���[�V��������[motion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "motion.h"
#include "modelHierarchy.h"
#include "manager.h"
#include "debugproc.h"

//�}�N����`
#define FILE_NAME		"data\\TXT\\player.txt"		//���[�V�����e�L�X�g
#define MAX_STR			(128)		//�����̍ő吔

//==============================================================
//�R���X�g���N�^
//==============================================================
CMotion::CMotion()
{
	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{
		m_aInfo[nCntMotion].bLoop = false;		//���[�v���邩
		m_aInfo[nCntMotion].nNumKey = 0;		//�L�[�̑���

		for (int nCntKeyInfo = 0; nCntKeyInfo < MAX_KEY; nCntKeyInfo++)
		{
			m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].nFrame = 0;		//�t���[����

			for (int nCntKey = 0; nCntKey < MAX_PARTS; nCntKey++)
			{
				//�ʒu�E����������
				m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fPosX = 0.0f;
				m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fPosY = 0.0f;
				m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fPosZ = 0.0f;
				m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fRotX = 0.0f;
				m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fRotY = 0.0f;
				m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fRotZ = 0.0f;
			}
		}

	}

	m_nNumAll = 0;
	m_nType = MOTION_NEUTRAL;		//���[�V�����̎��
	m_bLoop = false;					//���[�v���邩
	m_NumKey = 0;			//�L�[��
	m_nKey = 0;				//�L�[
	m_nCounter = 0;			//���[�V�����J�E���^�[
	m_bFinish = false;		//�I���������ǂ���

	m_ppModel = NULL;		//���f���ւ̃|�C���^
	m_nNumModel = MAX_PARTS;		//���f���̑���
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CMotion::~CMotion()
{

}

//==============================================================
//�ݒ菈��
//==============================================================
void CMotion::Set(int nType)
{
	m_nType = nType;		//���[�V�����̎��
	m_nCounter = 0;			//���[�V�����J�E���^�[
	m_NumKey = 0;			//�L�[��
	m_bLoop = false;		//���[�v
	m_nKey = 0;				//�L�[
	m_bFinish = false;		//�I�����ĂȂ���Ԃɂ���

							//�S���f��(�p�[�c)�̏����ݒ�
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		//�p�[�c�̈ʒu��ݒ�
		m_ppModel[nCntModel]->SetPosition(D3DXVECTOR3(
			m_aInfo[m_nType].aKeInfo[0].aKey[nCntModel].fPosX,
			m_aInfo[m_nType].aKeInfo[0].aKey[nCntModel].fPosY,
			m_aInfo[m_nType].aKeInfo[0].aKey[nCntModel].fPosZ));

		//�p�[�c�̌�����ݒ�
		m_ppModel[nCntModel]->SetRotation(D3DXVECTOR3(
			m_aInfo[m_nType].aKeInfo[0].aKey[nCntModel].fRotX,
			m_aInfo[m_nType].aKeInfo[0].aKey[nCntModel].fRotY,
			m_aInfo[m_nType].aKeInfo[0].aKey[nCntModel].fRotZ));
	}
}

//==============================================================
//��������
//==============================================================
CMotion *CMotion::Create(void)
{
	CMotion *pMotion = NULL;

	if (pMotion == NULL)
	{//���������g�p����ĂȂ�������

	 //���[�V�����̐���
		pMotion = new CMotion;
	}

	return pMotion;
}

//==============================================================
//����������
//==============================================================
void CMotion::Init(const char *c_MotionFile,int nNumModel)
{
	m_nNumModel = nNumModel;

	//���[�V�����ǂݍ���
	CMotion::FileLoad(c_MotionFile);

	//���[�V�����̐ݒ�
	CMotion::Set(MOTION_NEUTRAL);
}

//==============================================================
//�X�V����
//==============================================================
void CMotion::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	D3DXVECTOR3 posDiff, rotDiff;		//����
	D3DXVECTOR3 posDest, rotDest;		//�ڕW

	m_NumKey = m_aInfo[m_nType].nNumKey;		//�L�[�����
	m_bLoop = m_aInfo[m_nType].bLoop;			//���[�v���邩

												//�S���f��(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		//�ʒu�̍���
		posDiff.x = m_aInfo[m_nType].aKeInfo[(m_nKey + 1) % m_NumKey].aKey[nCntModel].fPosX - m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fPosX;
		posDiff.y = m_aInfo[m_nType].aKeInfo[(m_nKey + 1) % m_NumKey].aKey[nCntModel].fPosY - m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fPosY;
		posDiff.z = m_aInfo[m_nType].aKeInfo[(m_nKey + 1) % m_NumKey].aKey[nCntModel].fPosZ - m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fPosZ;

		//�����̍���
		rotDiff.x = m_aInfo[m_nType].aKeInfo[(m_nKey + 1) % m_NumKey].aKey[nCntModel].fRotX - m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fRotX;
		rotDiff.y = m_aInfo[m_nType].aKeInfo[(m_nKey + 1) % m_NumKey].aKey[nCntModel].fRotY - m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fRotY;
		rotDiff.z = m_aInfo[m_nType].aKeInfo[(m_nKey + 1) % m_NumKey].aKey[nCntModel].fRotZ - m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fRotZ;

		//�ʒu�̖ڕW
		posDest.x = m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fPosX + posDiff.x * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeInfo[m_nKey].nFrame);
		posDest.y = m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fPosY + posDiff.y * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeInfo[m_nKey].nFrame);
		posDest.z = m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fPosZ + posDiff.z * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeInfo[m_nKey].nFrame);

		//�����̍���
		rotDest.x = m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fRotX + rotDiff.x * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeInfo[m_nKey].nFrame);
		rotDest.y = m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fRotY + rotDiff.y * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeInfo[m_nKey].nFrame);
		rotDest.z = m_aInfo[m_nType].aKeInfo[m_nKey].aKey[nCntModel].fRotZ + rotDiff.z * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeInfo[m_nKey].nFrame);

		//�����l�̕����Z
		posDest += m_ppModel[nCntModel]->GetDefaultPosition();
		rotDest += m_ppModel[nCntModel]->GetDefaultRotation();

		//�p�[�c�̈ʒu�E������ݒ�
		m_ppModel[nCntModel]->SetPosition(posDest);
		m_ppModel[nCntModel]->SetRotation(rotDest);
	}

	if (m_nCounter < m_aInfo[m_nType].aKeInfo[m_nKey].nFrame)
	{//���[�V�����J�E���^�[���t���[�����ɒB���ĂȂ��Ƃ�

		m_nCounter++;		//���݂̃L�[���Z
	}
	else
	{//���[�V�����J�E���^�[���t���[�����ɒB������

		m_nKey++;			//���݂̃L�[���Z

		if (m_nKey >= m_NumKey)
		{//�L�[���ő�̃L�[���𒴂��Ă���

			m_nKey = 0;		//������

			if (m_bLoop == false)
			{//���[�v���Ȃ��Ƃ�

				m_bFinish = true;		//�I��������Ԃɂ���
			}
		}

		m_nCounter = 0;		//������
	}
}

//==============================================================
//���[�V�������I���������̔���
//==============================================================
bool CMotion::IsFinish(void)
{
	return m_bFinish;
}

//==============================================================
//���[�V�����ǂݍ���
//==============================================================
void CMotion::FileLoad(const char *c_MotionFile)
{
	FILE *pFile;
	char aString[MAX_STR];
	int nLoop = 0;			//���[�v���
	int nCntMotion = 0, nCntKeyInfo = 0, nCntKey = 0;		//���[�V�����̐��A�L�[���̐��A�L�[�v�f
	int nResult = 0;		//�Ō�̍s�܂ŗ�����

							//�t�@�C���J��
	pFile = fopen(c_MotionFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J������

		while (nResult != EOF)
		{//�Ō�̍s����Ȃ���

			while (strcmp(&aString[0], "MOTIONSET") != 0 && nResult != EOF)
			{//[MOTIONSET]������܂ł̊� && �e�L�X�g�̏I��肪���Ȃ���

				nResult = fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
			}

			if (strcmp(&aString[0], "MOTIONSET") == 0)
			{//[MOTIONSET]��������

				nCntKeyInfo = 0;		//�L�[���̐����Z�b�g

				while (strcmp(&aString[0], "END_MOTIONSET") != 0)
				{//[END_MOTIONSET]������܂ł̊�


					while (strcmp(&aString[0], "KEYSET") != 0)
					{//[KEYSET]������܂ł̊�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						if (strcmp(&aString[0], "LOOP") == 0)
						{//���[�v���

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nLoop);		//���[�v���ǂݍ���

							if (nLoop == 0)
							{//���[�v���Ȃ��ꍇ

								m_aInfo[nCntMotion].bLoop = false;		//���[�v���Ȃ���Ԃɂ���
							}
							else if (nLoop == 1)
							{//���[�v����ꍇ

								m_aInfo[nCntMotion].bLoop = true;		//���[�v�����Ԃɂ���

							}
						}
						else if (strcmp(&aString[0], "NUM_KEY") == 0)
						{//�L�[��

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

							fscanf(pFile, "%d", &m_aInfo[nCntMotion].nNumKey);		//�L�[���ǂݍ���

						}
					}

					if (strcmp(&aString[0], "KEYSET") == 0)
					{//[KEYSET]��������

						nCntKey = 0;		//�L�[�����Z�b�g

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						while (strcmp(&aString[0], "FRAME") != 0)
						{//[FRAME]������܂ł̊�

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

							if (strcmp(&aString[0], "FRAME") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
								fscanf(pFile, "%d", &m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].nFrame);		//�t���[�����ǂݍ���

								break;
							}
						}

						while (strcmp(&aString[0], "END_KEYSET") != 0)
						{//[END_KEY]������܂ł̊�

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

							if (strcmp(&aString[0], "KEY") == 0)
							{//[KEY]��������

								while (strcmp(&aString[0], "END_KEY") != 0)
								{//[END_KEY]������܂ł̊�

									fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

									if (strcmp(&aString[0], "POS") == 0)
									{//�ʒu���

										fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

										fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fPosX);		//�ʒu�ǂݍ���
										fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fPosY);		//�ʒu�ǂݍ���
										fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fPosZ);		//�ʒu�ǂݍ���
									}
									else if (strcmp(&aString[0], "ROT") == 0)
									{//�������

										fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

										fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fRotX);		//�����ǂݍ���
										fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fRotY);		//�����ǂݍ���
										fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeInfo[nCntKeyInfo].aKey[nCntKey].fRotZ);		//�����ǂݍ���
									}
								}
								nCntKey++;		//�L�[�����Z
							}
						}
						nCntKeyInfo++;		//�L�[�����Z
					}

					fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
				}

				nCntMotion++;		//���[�V�����̎�މ��Z

				nResult = fscanf(pFile, "%s", &aString[0]);		//�Ō�̍s���m�F
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
}