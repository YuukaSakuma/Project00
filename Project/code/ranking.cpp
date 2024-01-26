//==============================================================
//
//��������[explosion.cpp]
//Author:���v�ԗD��
//
//==============================================================
#include "ranking.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "sound.h"


#define RANKING_FILE	"data\\TXT\\ranking.bin"	// �����L���O�t�@�C��
#define AUTOMOVE_TITLE	(600)						// �^�C�g�������J�ڃ^�C�}�[


//�ÓI�����o�ϐ�
CScore *CRanking::m_apScore[NUM_RANK] = {};	// �����L���O�̃|�C���^
int CRanking::m_nScore = 0;					// �X�R�A

//==============================================================
//�R���X�g���N�^
//==============================================================
CRanking::CRanking()
{
	// �l���N���A����
	m_nTimer = 0;
	m_nRank = 0;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CRanking::~CRanking()
{

}

//==============================================================
//�^�C�g����ʂ̏���������
//==============================================================
HRESULT CRanking::Init(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	int aScore[NUM_RANK] = {0,0,0,0,0};	// �X�R�A�i�[�p
	m_nRank = -1;	//�����N�C�����ĂȂ����
					
					
	// �f�[�^�̓ǂݍ���
	Load(&aScore[0]);

	// �f�[�^�̃\�[�g
	Sort(&aScore[0]);

	// �����N�C���m�F
	RankIn(&aScore[0], m_nScore);

	// ���S�̐���
	CObject2D *p = CObject2D::Create();
	p->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\ranking.png"));
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f, 0.0f));
	p->SetSize(400, 150);

	// ���ʕ��X�R�A�̐���
	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		if (m_apScore[nCntRank] == NULL)
		{
			p = CObject2D::Create();
			p->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\rank.png"));
			p->SetPosition(D3DXVECTOR3(350.0f, 250.0f + nCntRank * 100.0f, 0.0f));
			p->SetSize(80, 50);
			p->SetVtx(nCntRank, 0.2f);

			m_apScore[nCntRank] = CScore::Create(D3DXVECTOR3(450.0f, 250.0f + nCntRank * 100.0f, 0.0f));
			m_apScore[nCntRank]->Set(aScore[nCntRank]);

			if (m_nRank == nCntRank)
			{
				m_apScore[nCntRank]->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
			}
		}
	}

	pSound->Play(pSound->SOUND_LABEL_RESULT);

	return S_OK;
}

//==============================================================
//�^�C�g����ʂ̏I������
//==============================================================
void CRanking::Uninit(void)
{
	CSound *pSound = CManager::Get()->GetSound();

	pSound->Stop();

	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		if (m_apScore[nCntRank] != NULL)
		{
			m_apScore[nCntRank]->Uninit();
			delete m_apScore[nCntRank];	// �������̊J��
			m_apScore[nCntRank] = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
		}
	}

	m_nScore = 0;

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�^�C�g����ʂ̍X�V����
//==============================================================
void CRanking::Update(void)
{
	CDebugProc *pDebugProc = CManager::Get()->GetDebugProc();

	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeybard();		//�L�[�{�[�h�̏��擾

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//ENTER�L�[��������

	 //�`���[�g���A�����
		CManager::Get()->GetFade()->Set(MODE_TITLE);
	}

	pDebugProc->Print("\n�����L���O\n");

	CScene::Update();

	if (CManager::Get()->GetFade()->GetState() == CFade::STATE_NONE)
	{
		m_nTimer++;

		if (m_nTimer >= AUTOMOVE_TITLE)
		{// �^�C�g�������J�ڋK��l
			CManager::Get()->GetFade()->Set(MODE_TITLE);
		}
	}


	//pDebugProc->Print("\n�����L���O\n");
}

//==============================================================
//�^�C�g����ʂ̕`�揈��
//==============================================================
void CRanking::Draw(void)
{
	CScene::Draw();
}

//===============================================
// �����L���O�f�[�^�ۑ�
//===============================================
void CRanking::Save(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�f�[�^��ǂݍ���
		fwrite(pScore, sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}

//===============================================
// �����L���O�f�[�^�ǂݍ���
//===============================================
void CRanking::Load(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�f�[�^��ǂݍ���
		fread(pScore, sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
	 //�v�f�����Ă���
		for (int nCntRanking = 0; nCntRanking < NUM_RANK; nCntRanking++)
		{
			pScore[nCntRanking] = 5 * (nCntRanking + 1);
		}
	}
}

//===============================================
// �����L���O�f�[�^�\�[�g
//===============================================
void CRanking::Sort(int *pScore)
{
	// �~���\�[�g
	for (int nCntFst = 0; nCntFst < NUM_RANK - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// ���̈�ԑ傫���ԍ�

		for (int nCntSec = nCntFst + 1; nCntSec < NUM_RANK; nCntSec++)
		{
			if (pScore[nCntSec] > pScore[nTempNum])
			{// �l���傫���ꍇ
				nTempNum = nCntSec;	// �傫���ԍ���ύX
			}
		}

		if (nTempNum != nCntFst)
		{// �ύX����ꍇ
			int nTemp = pScore[nCntFst];
			pScore[nCntFst] = pScore[nTempNum];
			pScore[nTempNum] = nTemp;
		}
	}
}

//===============================================
// �����L���O�C���m�F
//===============================================
void CRanking::RankIn(int *pScore, int nResult)
{
	if (nResult > pScore[NUM_RANK - 1])
	{
		pScore[NUM_RANK - 1] = nResult;

		// �\�[�g����
		Sort(pScore);

		// �ۑ�����
		Save(pScore);

		//�����N�C���������ʂ��m�F����
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			if (pScore[nCntRank] == nResult)
			{
				m_nRank = nCntRank;	// �����N�C���������ʂ�ۑ�

				break;
			}
		}
	}
}