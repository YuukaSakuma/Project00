//==============================================================
//
//���[�V�����w�b�_�[[player.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _MOTION_H_						//���̃}�N������`����Ă��Ȃ�������
#define _MOTION_H_						//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//�}�N����`
#define MAX_PARTS		(9)		//�p�[�c�ő吔
#define MAX_KEY			(32)		//�L�[�ő吔
#define MAX_MOTION		(64)

class CModel;
class CModelHier;

//==============================================================
//���[�V�����N���X�̒�`
//==============================================================
class CMotion
{
public:

	//���[�V�����̎��
	typedef enum
	{
		MOTION_NEUTRAL = 0,		//�ҋ@
		MOTION_WALK,			//����
		MOTION_JUMP,			//�W�����v
		MOTION_LAND,			//���n
		MOTOIN_ATTACK,			//�Ǔo��
		MOTION_MAX

	} MOTION;

	//�L�[�̍\����
	typedef struct
	{
		float fPosX;		//�ʒuX
		float fPosY;		//�ʒuY
		float fPosZ;		//�ʒuZ
		float fRotX;		//����X
		float fRotY;		//����Y
		float fRotZ;		//����Z

	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame;				//�Đ��t���[��
		KEY aKey[MAX_PARTS];	//�e���f���̃L�[�v�f
	} KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;						//���[�v���邩�ǂ���
		int nNumKey;					//�L�[�̑���
		KEY_INFO aKeInfo[MAX_KEY];		//�L�[���

	} INFO;

	CMotion();		//�R���X�g���N�^
	~CMotion();		//�f�X�g���N�^

	static CMotion *Create(void);		//��������

	void Set(int nType);						//�ݒ菈��
	void Init(const char *c_MotionFile, int nNumModel);							//����������
	void Update(void);							//�X�V����
	int GetType(void) { return m_nType; }		//��ނ̎擾
	bool IsFinish(void);						//�I��
	void SetInfo(INFO info) { m_aInfo[m_nType] = info; }
	void SetModel(CModelHier **ppModel, int nNumModel) { m_ppModel = ppModel; }		//���f���̏��ݒ�

	//void FileLoad(void);
	void FileLoad(const char *c_MotionFile);

private:
	INFO m_aInfo[MOTION_MAX];
	int m_nNumAll;				//����
	int m_nType;				//���[�V�����̎��
	bool m_bLoop;				//���[�v���邩
	int m_NumKey;				//�L�[��
	int m_nKey;					//�L�[
	int m_nCounter;				//���[�V�����J�E���^�[
	bool m_bFinish;				//�I���������ǂ���

	CModelHier **m_ppModel;		//���f���ւ̃|�C���^
	int m_nNumModel;			//���f���̑���
};

////==============================================================
////���[�V�����N���X�̒�`
////==============================================================
//class CMotion
//{
//public: // �N�ł��A�N�Z�X�\�Ȓ�`
//
//		// �L�[
//	typedef struct
//	{
//		float fPosX;
//		float fPosY;
//		float fPosZ;
//		float fRotX;
//		float fRotY;
//		float fRotZ;
//	}KEY;
//
//private:	// �����������A�N�Z�X�\�Ȓ�`
//
//			// �L�[���
//	typedef struct
//	{
//		int nFrame;			// �Đ��t���[��
//		KEY *aKey;			// �p�[�c�̑���
//	}KEY_INFO;
//
//	// ���[�V�������
//	typedef struct
//	{
//		bool bLoop;			// ���[�v���邩�ǂ���
//		int nNumKey;		// �L�[��
//		KEY_INFO *pKeyInfo;	// �L�[�̑���
//	}INFO;
//
//	//���̃t�@�C�����
//	typedef struct
//	{
//		CModel **ppParts;		// �p�[�c�̏��
//		int nNumParts;			// �p�[�c��
//	}BodyFileData;
//
//public:		// �N�ł��A�N�Z�X�\
//	CMotion();	// �R���X�g���N�^
//	~CMotion();	// �f�X�g���N�^
//
//				// �����o�֐�
//	void Uninit(void);
//	void Update(void);
//	void Set(int nType);
//	void InitSet(int nType);
//	void SetModel(CModel **pModel, int nNumParts);
//	void LoadMotionData(FILE *pFile);
//
//private:	// �����������A�N�Z�X�\
//
//			// �����o�ϐ�
//	KEY m_OldKey[64];		// �O��̃L�[���
//	INFO aInfo[MAX_MOTION];	// ���[�V�������
//	int m_nNumMotion;		// ���[�V������
//	int m_nNowFrame;		// ���݂̃t���[����
//	int m_nNowMotion;		// ���݂̃��[�V�����ԍ�
//	int m_nNowKey;			// ���݂̃L�[��
//	int m_nOldType;			// �O��̃��[�V�����^�C�v
//	BodyFileData m_FileData;// �t�@�C�����
//};

#endif
