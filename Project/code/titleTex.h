//==============================================================
//
//�^�C�g���w�b�_�[[title.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _TITLETEX_H_						//���̃}�N������`����Ă��Ȃ�������
#define _TITLETEX_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"


#define NUM_TITLE_TEX		(2)		//�^�C�g���̃e�N�X�`���̐�

//�O���錾
class CModel;
class CField;
class CObject2D;

//==============================================================
//�^�C�g���N���X
//==============================================================
class CTitleTex : public CObject
{
public:
	CTitleTex();								//�R���X�g���N�^
	~CTitleTex();								//�f�X�g���N�^

	static CTitleTex *Create(void);			//�v���C���[�̐���

	HRESULT Init(void);						//�^�C�g���̏���������
	void Uninit(void);						//�^�C�g���̏I������
	void Update(void);						//�^�C�g���̍X�V����
	void Draw(void);						//�^�C�g���̕`�揈��

private:

	static CObject2D *m_apObject2D[NUM_TITLE_TEX];		//�I�u�W�F�N�g2D�̃|�C���^
	int m_nIdxTexture[NUM_TITLE_TEX];		//�e�N�X�`���̔ԍ�
	int m_nCntAppear;				//�_�ŃJ�E���^�[
	bool m_bAppear;					//�_�ł̐؂�ւ�
	float m_fAlpha;					//�A���t�@�l
	STATE m_state;					//���
};
#endif // !_PLAYER_H_

