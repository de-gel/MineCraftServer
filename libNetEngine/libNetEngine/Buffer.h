#pragma once


#define BUFF_DEFAULT_SIZE  16384
//#define BUFF_DEFAULTMAX_SIZE 16384

class CBuffer
{
public:
	CBuffer(int iBuffSize = BUFF_DEFAULT_SIZE);
	~CBuffer(void);

public:
	char* GetData(); // ����ط������Ա�֤һ�㣬������ʼ���Ǵ�0��ʼ
	//��ȡ���ݳ���
	int GetDataLen();
	//��ȡʣ��̶�
	int GetSpaceLen();
	//д������
	bool WriteData(const char* pBuff, int iLen); // ����buff�����
	//�Ƴ�����
	bool RemoveData(int iLen); // �Ƴ�ͷ��������
	// ��������
	void ResetData(); 

	//����buffer����
	void ResetBuffLen(int iNewLen);

private:
	char* m_pBuff; // ������
	int m_iDataLen; // ��ǰ���ݳ���
	int m_iBuffLen; // ��ǰ Buffer ��С
};