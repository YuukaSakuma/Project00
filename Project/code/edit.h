//==============================================================
//
//�G�f�B�b�g�w�b�_�[[edit.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _EDIT_H_						//���̃}�N������`����Ă��Ȃ�������
#define _EDIT_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object.h"
#include"objectX.h"
#include"model.h"

#define NUM_MODEL (256)			//���f����

//�O���錾
class CField;
class CObjectX;

//==============================================================
//�^�C�g���N���X
//==============================================================
class CEdit : public CModel
{
public:

	//���
	typedef enum
	{
		TYPE_KISO = 0,
		TYPE_KISO1,
		TYPE_MAX
	} TYPE;

	CEdit();								//�R���X�g���N�^
	~CEdit();								//�f�X�g���N�^

	static CEdit *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(void);						//�^�C�g���̏���������
	void Uninit(void);						//�^�C�g���̏I������
	void Update(void);						//�^�C�g���̍X�V����
	void Draw(void);						//�^�C�g���̕`�揈��

	static HRESULT LoadFile(void);
	void SaveFile(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	//�擾�p
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;
	static CModel *m_apObjectX[NUM_MODEL];
	int m_nTypeIdx;
	int m_nIdx;
	bool m_bUse;
};
#endif // !_PLAYER_H_

