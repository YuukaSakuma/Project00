//==============================================================
//
//�����w�b�_�[[number.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _NUMBER_H_						//���̃}�N������`����Ă��Ȃ�������
#define _NUMBER_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object.h"

#include "object2D.h"

//==============================================================
//�����̃N���X
//==============================================================
class CNumber
{
public:
	CNumber();			//�R���X�g���N�^
	~CNumber();			//�f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);			//����������
	virtual void Uninit(void);													//�I������
	virtual void Update(void);													//�X�V����
	virtual void Draw(void);													//�`�揈��

	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		//�����̐���
	static HRESULT Load(void);													//�e�N�X�`���̓ǂݍ���
	static void Unload(void);													//�e�N�X�`���̔j��

	void SetNumber(int nNumber);			//�����̐ݒ�
	CObject2D * GetObject2D(void);			//�I�u�W�F�g2D�̎擾
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`��
	CObject2D *m_aObject2D;					//�I�u�W�F�N�g2D�̃|�C���^
	int m_nNumber;							//�����̒l
	int m_nldxTexture;						//�e�N�X�`���ԍ�

};			

#endif // !_MULTIBG_H_
