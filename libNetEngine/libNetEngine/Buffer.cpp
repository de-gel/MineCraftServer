#include "Buffer.h"
#include <memory.h>
#include <string.h>

CBuffer::CBuffer(int iBuffSize)
{
	m_pBuff = new char[iBuffSize];
	m_iDataLen = 0;
	m_iBuffLen = iBuffSize;
}

CBuffer::~CBuffer(void)
{
	if (m_pBuff)
	{
		delete[]m_pBuff;
		m_pBuff = 0;
	}
}
bool CBuffer::WriteData(const char* pData, int iLen)
{
	if (!m_pBuff || !pData)
		return false;

	// 数据大小超出了buff最大允许的大小
	if (m_iDataLen + iLen > m_iBuffLen)
		return false;

	memcpy(&m_pBuff[m_iDataLen], pData, iLen);
	m_iDataLen = m_iDataLen + iLen;

	return true;
}

bool CBuffer::RemoveData(int iLen)
{
	if (iLen > m_iDataLen)
		return false;

	if (iLen == m_iDataLen)
	{
		m_iDataLen = 0;
		return true;
	}

	m_iDataLen = m_iDataLen - iLen;
	memmove(m_pBuff, &m_pBuff[iLen], m_iDataLen);
	return true;
}


void CBuffer::ResetData()
{
	m_iDataLen = 0;
}
char* CBuffer::GetData()  // 这个地方，可以保证一点，读数据始终是从0开始
{
	return m_pBuff;
}

// 数据快大小
int CBuffer::GetDataLen()
{
	return m_iDataLen;
}

// 剩余大小
int CBuffer::GetSpaceLen()
{
	return m_iBuffLen - m_iDataLen;
}

void CBuffer::ResetBuffLen(int iNewLen)
{
	if (m_iDataLen != 0)
		return;

	if (iNewLen <= m_iBuffLen)
		return;

	char* pNewBuff = new char[iNewLen];
	delete m_pBuff;
	m_pBuff = pNewBuff;
	m_iBuffLen = iNewLen;
}