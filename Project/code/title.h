//==============================================================
//
//�^�C�g���w�b�_�[[title.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _TITLE_H_						//���̃}�N������`����Ă��Ȃ�������
#define _TITLE_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"

//�O���錾
class CModel;
class CField;

//==============================================================
//�^�C�g���N���X
//==============================================================
class CTitle : public CScene
{
public:
	CTitle();								//�R���X�g���N�^
	~CTitle();								//�f�X�g���N�^

	//static CTitle *Create(void);			//�v���C���[�̐���

	HRESULT Init(void);						//�^�C�g���̏���������
	void Uninit(void);						//�^�C�g���̏I������
	void Update(void);						//�^�C�g���̍X�V����
	void Draw(void);						//�^�C�g���̕`�揈��

private:

	static CModel *m_pModel;
	static CField *m_pField;

	static bool m_bReset;

	int m_nTimer;	// �����J�ڃ^�C�}�[

};
#endif // !_PLAYER_H_

