//==============================================================
//
//�R�A�w�b�_�[[coa.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _COA_H_						//���̃}�N������`����Ă��Ȃ�������
#define _COA_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"

//�O���錾
class CModel;

//==============================================================
//�R�A�N���X
//==============================================================
class CCOa : CObjectX
{
public:

	typedef enum
	{
		TYPE_COA_0 = 0,		//��
		TYPE_COA_1,			//��
		TYPE_COA_MAX,
	}COA;

	CCOa();			//�R���X�g���N�^
	~CCOa();		//�f�X�g���N�^

	HRESULT Init(void);						
	void Uninit(void);						
	void Update(void);						
	void Draw(void);						

	static CCOa *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, COA type);

	//�擾
	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetMove(void) const { return m_move; }
	COA GetCoaType(void) { return m_CoaType; }

	//�ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetCoaType(COA type) { m_CoaType = type; }

	void SetState(void);
	void Hit(void);

private:

	int m_nLife;			//����
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����	
	TYPE m_type;			//���
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�ʒu(�O��)
	int m_nldxTexture;		//�e�N�X�`���ԍ�
	int m_nCntAttack;		//�A�^�b�N�J�E���^�[
	int m_nCntDamage;		//�_���[�W�J�E���^�[
	//STATE m_state;		//���
	COA m_CoaType;			//�R�A�̎��
};
#endif // !_BULLET_H_
