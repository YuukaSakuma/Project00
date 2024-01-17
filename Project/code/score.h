//==============================================================
//
//�X�R�A�w�b�_�[[score.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _SCORE_H_						//���̃}�N������`����Ă��Ȃ�������
#define _SCORE_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include"object.h"
#include"number.h"

//�O���錾
class CNumber;

#define NUM_SCORE	(8)	// �X�R�A�̌���

//==============================================================
//�X�R�A�̃N���X
//==============================================================
class CScore /*:CObject*/
{
public:
	CScore();		//�R���X�g���N�^
	~CScore();		//�f�X�g���N�^

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	static CScore *Create(D3DXVECTOR3 pos);		//��������

	//void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�̐ݒ�
	//D3DXVECTOR3 GetPosition(void) { return m_pos; }		//�ʒu�̎擾

	static void Set(int nNum);					//�X�R�A�ݒ�
	static void Add(int nValue);				//�X�R�A�����Đݒ�
	int Get(void) { return m_nNumber; }			//�X�R�A�擾
	static void SetValue(void);
	void SetColor(D3DXCOLOR col);
private:

	static LPDIRECT3DTEXTURE9 m_pTexture;		//���L�e�N�X�`��
	static int m_nNumber;
	static CNumber *m_apNumber[NUM_SCORE];				//�I�u�W�F�N�g2D�̃e�N�X�`��
	D3DXVECTOR3 m_pos;							//�ʒu
	int m_nldxTexture;
};			
#endif // !_MULTIBG_H_
