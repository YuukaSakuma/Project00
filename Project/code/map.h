//==============================================================
//
//�^�C�g���w�b�_�[[title.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _MAP_H_						//���̃}�N������`����Ă��Ȃ�������
#define _MAP_H_						//2�d�C���N���[�h�h�~�̃}�N�����`����

#include <stdio.h>
#include "main.h"
#include "object.h"

//�O���錾

//==============================================================
//�^�C�g���N���X
//==============================================================
class CMap
{
	enum STAGE
	{
		STAGE_00 = 0,
		STAGE_01,
		STAGE_02,
		STAGE_03,
		STAGE_04,
		STAGE_05,
		STAGE_MAX
	};

public:

#define MAX_MODEL (6)

	CMap();								//�R���X�g���N�^
	~CMap();								//�f�X�g���N�^

	static CMap *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Set(void);
	
private:

	void ObjectSet(FILE *pFile);
	void WallSet(FILE *pFile);

	static char *m_apFileName[MAX_MODEL];		//�t�@�C����
};
#endif // !_PLAYER_H_


