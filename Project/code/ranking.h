//==============================================================
//
//���U���g�w�b�_�[[result.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _RANKING_H_						//���̃}�N������`����Ă��Ȃ�������
#define _RANKING_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"

#define NUM_RANK	(5)		// �����L���O�̏��ʐ�

//�O���錾
class CScore;

//==============================================================
//���U���g�N���X
//==============================================================
class CRanking : public CScene
{
public:

	CRanking();								//�R���X�g���N�^
	~CRanking();								//�f�X�g���N�^

	HRESULT Init(void);						//�^�C�g���̏���������
	void Uninit(void);						//�^�C�g���̏I������
	void Update(void);						//�^�C�g���̍X�V����
	void Draw(void);						//�^�C�g���̕`�揈��

	static void SetScore(int nValue) { m_nScore = nValue; }

private:
	// �����o�֐�
	void Save(int *pScore);
	void Load(int *pScore);
	void Sort(int *pScore);
	void RankIn(int *pScore, int nResult);

	// �����o�ϐ�
	static CScore *m_apScore[NUM_RANK];	// �X�R�A�̃|�C���^(���ʕ�)
	static int m_nScore;	// ����̃X�R�A
	int m_nTimer;			// �����J�ڃ^�C�}�[
	int m_nRank;

};
#endif // !_PLAYER_H_

