//==============================================================
//
//�I�u�W�F�N�g3D�w�b�_�[[object3D.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _OBJECT3D_H_							//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT3D_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//==============================================================
//�I�u�W�F�N�g3D�N���X
//==============================================================
class CObject3D : public CObject
{
public:
	CObject3D ();		//�R���X�g���N�^
	~CObject3D ();		//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	static CObject3D *Create(void);			//��������

	void BindTexture(int pTexture) { m_nldxTexture = pTexture; }	//�e�N�X�`���ԍ��̎擾

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�̎擾

	void SetSize(float width, float heiget,float vertical);	//�T�C�Y�̐ݒ�

	float GetHeight(D3DXVECTOR3 VecPos);		//�T�C�Y�̐ݒ�

private:
	//�O���[�o���ϐ��錾
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`��(3����)�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR3 m_rot;								//����

	int m_nldxTexture;		//�e�N�X�`���ԍ�
};
#endif