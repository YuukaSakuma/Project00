//==============================================================
//
//�X�R�A�w�b�_�[[score.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _TIME_H_						//���̃}�N������`����Ă��Ȃ�������
#define _TIME_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�O���錾
class CNumber;

//==============================================================
//�X�R�A�̃N���X
//==============================================================
class CTime /*:CObject*/
{
public:
	CTime();		//�R���X�g���N�^
	~CTime();		//�f�X�g���N�^

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

	static CTime *Create(D3DXVECTOR3 pos);		//��������

	void Set(int nNum);					//�X�R�A�ݒ�
	void Add(int nValue);				//�X�R�A�����Đݒ�

	int GetNum(void) { return m_nNum; }			//�X�R�A�擾
	int GetStartNum(void) { return m_nSetNum; }
	float GetAnim(void) { m_fAnimTime; };

private:

#define NUM_TEX (4)	//�e�N�X�`����

	void SetValue(void);

	CNumber *m_apNumber[NUM_TEX];			//�����̃|�C���^
	D3DXVECTOR3 m_pos;				//�ʒu

	int m_nNum;				//���݂̒l
	int m_nSetNum;			//�ݒ肷��l
	float m_fAnimTime;		//�J�E���g
	int m_nldxTexture;		//�e�N�X�`���ԍ�

};			
#endif // !_MULTIBG_H_
