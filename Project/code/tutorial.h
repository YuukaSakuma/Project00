//==============================================================
//
//�^�C�g���w�b�_�[[title.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _TUTORIAL_H_						//���̃}�N������`����Ă��Ȃ�������
#define _TUTORIAL_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"

//�O���錾
class CScore;			//�X�R�A�̏��
class CPlayerModel;		//�v���C���[�̏��
class CEnemyModel;		//�G�̏��
class CModel;			//���f���̏��
class CField;			//���̏��

//==============================================================
//�^�C�g���N���X
//==============================================================
class CTutorial : public CScene
{
public:
	CTutorial();								//�R���X�g���N�^
	~CTutorial();								//�f�X�g���N�^

	HRESULT Init(void);						//�^�C�g���̏���������
	void Uninit(void);						//�^�C�g���̏I������
	void Update(void);						//�^�C�g���̍X�V����
	void Draw(void);						//�^�C�g���̕`�揈��

private:

	static CScore *m_pScore;
	static CPlayerModel *m_pPlayerModel;
	static CEnemyModel *m_pEnemyModel;
	static CModel *m_pModel;
	static CField *m_pField;

	static bool m_bReset;

};
#endif // !_PLAYER_H_


