//==============================================================
//
//���d�w�i�w�b�_�[[multibg.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _MULTIBG_H_						//���̃}�N������`����Ă��Ȃ�������
#define _MULTIBG_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object.h"

//�O���錾
class CObject2D;

//==============================================================
//���d�w�i�̃N���X
//==============================================================
class CMultiBg : public CObject
{
public:
	CMultiBg();					//�R���X�g���N�^
	~CMultiBg();				//�f�X�g���N�^

	//�w�i�̎��
	typedef enum 
	{
		TYPE_BG_FIRST,	//�w�i1
		TYPE_BG_SECOND,	//�w�i2
		TYPE_BG_FINAL,	//�w�i3
		TYPE_BG_MAX

	}BG_TYPE;	

	HRESULT Init(void);			//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��

	static CMultiBg *Create(void);		//���d�w�i�̐�������

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�̎擾

private:
	 
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_BG_MAX];		//���L�e�N�X�`��
	static const char *apTexture[TYPE_BG_MAX];				//�t�@�C����

	CObject2D *m_apObject2D[TYPE_BG_MAX];		//�I�u�W�F�N�g2D�̃e�N�X�`��
	D3DXVECTOR3 m_pos;							//�ʒu
	float m_fTexV[TYPE_BG_MAX];					//�e�N�X�`�����W�̊J�n�ʒu(V�l)
	float m_fTexU[TYPE_BG_MAX];					//�e�N�X�`�����W�̊J�n�ʒu(U�l)
	float m_fmoveV[TYPE_BG_MAX];				//�e�N�X�`�����W�̈ړ���V
	float m_fmoveU[TYPE_BG_MAX];				//�e�N�X�`�����W�̈ړ���V

	int m_aldxTexture[TYPE_BG_MAX];				//�e�N�X�`���ԍ�
};			
#endif // !_MULTIBG_H_
