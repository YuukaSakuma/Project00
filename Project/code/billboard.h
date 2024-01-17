//==============================================================
//
//�r���{�[�h�w�b�_�[[billboard.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _BILLBOARD_H_							//���̃}�N����`������Ă��Ȃ�������
#define _BILLBOARD_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object.h"


//==============================================================
//�r���{�[�h�N���X
//==============================================================
class CBillboard : public CObject
{
public:
	CBillboard();								//�R���X�g���N�^
	~CBillboard();								//�f�X�g���N�^

	static CBillboard *Create(void);			//�r���{�[�h�̐���

	//�v���g�^�C�v�錾
	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	void BindTexture(int pTexture) { m_nldxTexture = pTexture; }		//�e�N�X�`���̊��蓖��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }					//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }						//�ʒu�̎擾

	void SetSize(float width, float heiget, float vertical);	//�T�C�Y�ݒ�

	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//�ړ��ʐݒ�
	D3DXVECTOR3 GetMove(void) { return m_move; }		//�ړ��ʎ擾

	void SetRadius(float fRadius);
	void SetVtx(int nPattern, TYPE type);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_rot;								//����
	D3DXVECTOR3 m_move;								//�ړ���

	int m_nldxTexture;								//�e�N�X�`���ԍ�
};
#endif