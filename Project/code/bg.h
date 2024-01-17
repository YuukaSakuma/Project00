//==============================================================
//
//�w�i�w�b�_�[[bg.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _BG_H_						//���̃}�N������`����Ă��Ȃ�������
#define _BG_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object2D.h"

//==============================================================
//�w�i�N���X
//==============================================================
class CBg : public CObject2D
{
public:
	CBg();		//�R���X�g���N�^
	~CBg();		//�f�X�g���N�^

	static CBg *Create(void);		//�w�i�̐���

	HRESULT Init(void);				//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����
	void Draw(void);				//�`�揈��

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�̎擾

private:
	static CObject2D *m_apObject2D;				//�I�u�W�F�N�g2D�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;		//���L�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							//�ʒu
	float m_fTexV;								//�e�N�X�`�����W�̊J�n�ʒu(V�l)
	float m_fTexU;								//�e�N�X�`�����W�̊J�n�ʒu(U�l)
	float m_fmoveV;								//�e�N�X�`�����W�̈ړ���V
	float m_fmoveU;								//�e�N�X�`�����W�̈ړ���V
	int m_nldxTexture;							//�e�N�X�`���ԍ�
};			
#endif // !_BG_H_
