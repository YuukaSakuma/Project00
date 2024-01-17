//==============================================================
//
//�t�F�[�h�w�b�_�[[fade.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _FADE_H_						//���̃}�N������`����Ă��Ȃ�������
#define _FADE_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"manager.h"
#include"object2D.h"
#include"main.h"

//�O���錾

//==============================================================
//���U���g�N���X
//==============================================================
class CFade : public CObject2D
{
public:

	typedef enum
	{
		STATE_NONE = 0,		//�������Ă��Ȃ����
		STATE_IN,			//�t�F�[�h�C�����
		STATE_OUT,			//�t�F�[�h�A�E�g���
		STATE_MAX
	}STATE;

	CFade();								//�R���X�g���N�^
	~CFade();								//�f�X�g���N�^

	HRESULT Init(CScene::MODE modeNext);

	//HRESULT Init(void);					//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	void Set(CScene::MODE modeNext);
	void SetState(STATE state);
	STATE GetFadeState(void) { return m_state; }

	static CFade *Create(CScene::MODE modeNext);

private:

	STATE m_state;				//���
	CScene::MODE m_modeNext;	//���̉��
	D3DXCOLOR m_Col;			//�t�F�[�h�̐F

};
#endif // !_PLAYER_H_

