//==============================================================
//
//�Q�[���w�b�_�[[game.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _GAME_H_						//���̃}�N������`����Ă��Ȃ�������
#define _GAME_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"

//�O���錾
class CScore;			//�X�R�A�̏��
class CModel;			//���f���̏��
class CField;			//���̏��
class CScore;
class CTime;
class CEdit;
class CEnemyBoss;
class CMap;
class CGame;
class CEnemy;

//==============================================================
//�v���C���[�N���X
//==============================================================
class CGame : public CScene
{
public:

	CGame();								//�R���X�g���N�^
	~CGame();								//�f�X�g���N�^

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	static CPlayer *GetPlayerModel(void) { return m_pPlayerModel; }				//�v���C���[�̏��
	static CScore *GetScore(void) { return m_pScore; }
	CTime *GetTime(void) { return m_pTime; }

private:

	static CScore *m_pScore;		//�X�R�A�̏��
	static CPlayer *m_pPlayerModel;	//�v���C���[�̏��
	static CModel *m_pModel;		//���f���̏��
	static CField *m_pField;		//���̏��
	static CTime *m_pTime;
	static CEdit *m_pEdit;
	static CMap *m_pMap;
	static CEnemy *m_pEnemy;

	int nData;

	static bool m_bReset;				//���Z�b�g������
};
#endif // !_PLAYER_H_

