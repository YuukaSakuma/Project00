//==============================================================
//
//�v���C���[�w�b�_�[[player.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _PLAYERMODEL_H_						//���̃}�N������`����Ă��Ȃ�������
#define _PLAYERMODEL_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�O���錾
class CModelHier;	//���f���̊K�w�\��
class CMotion;		//���[�V�����̊K�w�\��

//==============================================================
//�v���C���[�N���X
//==============================================================
class CPlayerModel : public CObject
{
public:

	CPlayerModel();								//�R���X�g���N�^
	CPlayerModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�R���X�g���N�^
	~CPlayerModel();								//�f�X�g���N�^

	static CPlayerModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//�v���C���[�̐���

	HRESULT Init(void);						//�v���C���[�̏���������
	void Uninit(void);						//�v���C���[�̏I������
	void Update(void);						//�v���C���[�̍X�V����
	void Draw(void);						//�v���C���[�̕`�揈��

	void Control(void);		//���͏���
	void Screen(void);		//��ʊO����

	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//�����擾
	D3DXVECTOR3 GetSizeMin(void) { return m_min; }
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }


	void SetModel(const char * c_FileName);			//���f���̐ݒ�
	void SetMotion(void);							//���[�V�����̐ݒ�
	void Walk(void);								//�ړ�(����)
	void RotCorrection(void);						//�����̕␳
	void Hit(void);									//�q�b�g����
	void SetState(void);
	
	int GetLife(void) { return m_nLife; }
	void SetCounter(int nCounter) { m_nCntScore = nCounter; }

private:

	static char *m_apFileName[15];		//�t�@�C����

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_posOld;			//�O��̈ʒu
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_rot;				//����
	D3DXVECTOR3 m_max;				//�ő�l
	D3DXVECTOR3 m_min;				//�ŏ��l
	D3DXMATRIX m_mxtWorld;			//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_Wpos;				//�}�b�v�ʒu

	STATE m_state;					//���

	int m_nCntDamage;

	CModelHier *m_apModel[15];		//���f��(�p�[�c)�ւ̃|�C���^

	int m_nNumModel;		//���f��(�p�[�c)�̑���
	bool m_bJump;			//�W�����v�������̔���
	bool m_bMove;			//�����Ă邩�̔���
	bool m_bLand;			//���n������

	int m_nldxTexture;

	float m_fRotDest;		//�ڕW
	float m_fRotDiff;		//����
	float m_fRotMove;

	CMotion *m_pMotion;		//���[�V�������

	int m_nLife;			//�̗�

	int m_nCntStart;		//�J�n�܂ł̎���
	int m_nCntScore;		//�X�R�A�����ʂ̕ω�����

	bool m_bAutoMove;		//�����ړ����邩
	bool m_bSecondJump;		//��i�W�����v���Ă��邩
	bool m_bHit;			//����ł��邩

};
#endif // !_PLAYER_H_
