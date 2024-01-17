//==============================================================
//
//���U���g�w�b�_�[[result.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _RESULT_H_						//���̃}�N������`����Ă��Ȃ�������
#define _RESULT_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"

//�O���錾
class CScore;

//==============================================================
//���U���g�N���X
//==============================================================
class CResult : public CScene
{
public:

	CResult();								//�R���X�g���N�^
	~CResult();								//�f�X�g���N�^

	HRESULT Init(void);						//�^�C�g���̏���������
	void Uninit(void);						//�^�C�g���̏I������
	void Update(void);						//�^�C�g���̍X�V����
	void Draw(void);						//�^�C�g���̕`�揈��

	static CScore *GetScore() { return m_pScore; }
	static void SetScore(int nValue) { m_nScore = nValue; }

private:

	static CScore *m_pScore;
	static int m_nScore;
};
#endif // !_PLAYER_H_


