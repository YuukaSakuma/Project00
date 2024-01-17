//==============================================================
//
//�^�C�g���w�b�_�[[title.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _PAUSE_H_						//���̃}�N������`����Ă��Ȃ�������
#define _PAUSE_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�O���錾
class CObject2D;	

//==============================================================
//�^�C�g���N���X
//==============================================================
class CPause : public CObject
{
public:

	//�|�[�Y���j���[
	typedef enum
	{
		PAUSE_CONTINUE = 0,		//�Q�[���ɖ߂�
		PAUSE_RETRY,			//�Q�[������蒼��
		PAUSE_QUIT,				//�^�C�g����ʂɖ߂�
		PAUSE_MAX
	} PAUSE;

	CPause();								//�R���X�g���N�^
	~CPause();								//�f�X�g���N�^

	static CPause *Create(void);			//�v���C���[�̐���

	HRESULT Init(void);						//�^�C�g���̏���������
	void Uninit(void);						//�^�C�g���̏I������
	void Update(void);						//�^�C�g���̍X�V����
	void Draw(void);						//�^�C�g���̕`�揈��

private:

	static CObject2D *m_apObject2D[PAUSE_MAX];		//�I�u�W�F�N�g2D�̃|�C���^

	static LPDIRECT3DTEXTURE9 m_pTexture[PAUSE_MAX];	//�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture[PAUSE_MAX];		//�e�N�X�`���̔ԍ�
	PAUSE m_pause;						//�|�[�Y���j���[
	int m_nSelect;						//�I����

};
#endif // !_PLAYER_H_

