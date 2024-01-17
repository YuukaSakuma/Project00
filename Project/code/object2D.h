//==============================================================
//
//�I�u�W�F�N�g2D�w�b�_�[[object2D.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _OBJECT2D_H_						//���̃}�N������`����Ă��Ȃ�������
#define _OBJECT2D_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object.h"

//==============================================================
//�I�u�W�F�N�g2D�N���X
//==============================================================
class CObject2D : public CObject
{
public:

	CObject2D();		//�R���X�g���N�^
	~CObject2D();		//�f�X�g���N�^

	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

	static CObject2D *Create(void);		//��������

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�̎擾

	void SetMove(D3DXVECTOR3 move) { m_move = move; }	//�ړ��ʐݒ�
	D3DXVECTOR3 GetMove(void) { return m_move; }		//�ړ��ʎ擾


	void SetVtx(int nPattern, TYPE type);				//
	void SetVtx(float fTexV,float fTexU);				//
	void SetVtx(int nPatternAnim, float nDigitX);		//�A�j���[�V�����̐ݒ�
	void SetRadius(float m_fRadius);					//���a�̐ݒ�
	void SetSize(float width, float heiget);			//�T�C�Y�̐ݒ�
	void SetVtxBlock(float width, float heiget);		//�u���b�N�̐ݒ�
	void SetVtxPlayer(float width, float heiget);		//�v���C���[�̐ݒ�
	void SetVtxItem(float width, float heiget);			//�A�C�e���̐ݒ�

	void SetCol(D3DXCOLOR col);

	void BindTexture(int nldx) {m_nldx = nldx; }		//�e�N�X�`���ԍ��̐ݒ�

	//void SetType(TYPE type);
	//int GetType(void);
	
private:

	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_move;							//�ʒu
	TYPE m_type;								//���
	float m_fWidth;								//����
	float m_fHeight;							//�c��

	int m_nldx;				//�e�N�X�`���ԍ�
};
#endif // !_MAIN_H_


