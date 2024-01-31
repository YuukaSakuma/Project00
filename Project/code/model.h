//==============================================================
//
//���f������[model.h]
//Author:���v�ԗD��
//
//==============================================================
#ifndef _MODEL_H_							//���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_							//2�d�C���N���[�h�h�~�̃}�N�����`����v

#include"objectX.h"

//==============================================================
//���f���N���X
//==============================================================
class CModel:public CObjectX
{
public:

	CModel();																//�R���X�g���N�^
	CModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CModel();																//�f�X�g���N�^

	static HRESULT Load(const char *pFilename);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename);		//��������

	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��

private:

	static LPD3DXMESH m_pMesh;			//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;			//�}�e���A���̐�

	static const char *m_pFilename;					//�t�@�C���̖��O

	int m_nIdxModel;		//���f���̔ԍ�

	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//�ړ���

	//int nldxShadow;
};

////==============================================================
////���f���N���X
////==============================================================
//class CModel :public CObject
//{
//public:
//
//	CModel();	// �R���X�g���N�^
//	~CModel();	// �f�X�g���N�^
//
//
//	HRESULT Init(void);
//	HRESULT Init(const char *pFileName);
//	void Uninit(void);
//	void Update(void);
//	void Draw(void);
//	static CModel *Create(const char *pFileName);
//	void SetParent(D3DXMATRIX *pMtx);
//	void SetCharaParent(D3DXMATRIX *pMtx) { m_pCharacterMtx = pMtx; }
//	void BindModelFile(int nIdx);
//	void SetRotSize(D3DXVECTOR3 &SetMax, D3DXVECTOR3 &SetMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, float fRot);
//
//	D3DXVECTOR3 GetPosition(void) { return m_pos; }
//	D3DXVECTOR3 GetRotation(void) { return m_rot; }
//	D3DXVECTOR3 GetCurrentPosition(void) { return m_CurPos; }
//	D3DXVECTOR3 GetCurrentRotation(void) { return m_CurRot; }
//	D3DXMATRIX *GetMtx(void) { return &m_mtxWorld; }
//	D3DXMATRIX *GetMtxParent(void) { return m_pParentMtx; }
//	int GetId(void) { return m_nIdxModel; }
//
//	void SetPosition(const D3DXVECTOR3 pos);
//	void SetRotation(const D3DXVECTOR3 rot);
//	void SetCurrentPosition(const D3DXVECTOR3 pos);
//	void SetCurrentRotation(const D3DXVECTOR3 rot);
//	void SetDraw(bool bDraw = true) { m_bDraw = bDraw; }
//	void SetShadow(bool bShadow = false) { m_bShadow = bShadow; }
//	void SetMaterial(const D3DMATERIAL9& Material) { m_ChangeMat = Material; }
//	void ChangeCol(bool bValue = false) { m_bChangeCol = bValue; }
//
//private:
//
//			// �����o�ϐ�
//	int m_nIdxModel;		// ���f���ԍ�
//	bool m_bChangeCol;	// �F�ύX�����邩�ǂ���
//	bool m_bDraw;
//	D3DMATERIAL9 m_ChangeMat;
//	D3DXVECTOR3 m_pos;		// �ʒu
//	D3DXVECTOR3 m_rot;		// ����
//	D3DXVECTOR3 m_CurPos;		// ���݂̈ʒu
//	D3DXVECTOR3 m_CurRot;		// ���݂̌���
//	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
//	D3DXMATRIX *m_pParentMtx;	// �e�̃��[���h�}�g���b�N�X
//	D3DXMATRIX *m_pCharacterMtx;	// �܂Ƃ߂Ă���e�̃}�g���b�N�X
//	bool m_bShadow;		// �e���`�悷�邩�ۂ�
//};
#endif