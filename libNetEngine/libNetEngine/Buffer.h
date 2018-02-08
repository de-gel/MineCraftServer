#pragma once


#define BUFF_DEFAULT_SIZE  16384
//#define BUFF_DEFAULTMAX_SIZE 16384

class CBuffer
{
public:
	CBuffer(int iBuffSize = BUFF_DEFAULT_SIZE);
	~CBuffer(void);

public:
	char* GetData(); // 这个地方，可以保证一点，读数据始终是从0开始
	//获取数据长度
	int GetDataLen();
	//获取剩余程度
	int GetSpaceLen();
	//写入数据
	bool WriteData(const char* pBuff, int iLen); // 加在buff的最后
	//移除数据
	bool RemoveData(int iLen); // 移除头部的数据
	// 重置数据
	void ResetData(); 

	//重置buffer长度
	void ResetBuffLen(int iNewLen);

private:
	char* m_pBuff; // 缓冲区
	int m_iDataLen; // 当前数据长度
	int m_iBuffLen; // 当前 Buffer 大小
};