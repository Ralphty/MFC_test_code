
typedef struct SerPortPar{
	int nPort;
	int nBaud;
	BYTE *pDataBuf;
	int nDataBufSize;
	LPVOID lpRecvFun;
	LPVOID lpSendFun;
	LPVOID lpParam1;
	LPVOID lpParam2;
	
	//�ṹ��Ĭ�Ϲ��캯������ʼ������
	SerPortPar()	
	{
		Init();
	}
	
	void Init()
	{
		this->nPort = 0;
		this->nBaud = 0;
		this->lpRecvFun = 0;
		this->lpSendFun = 0;
		this->pDataBuf = NULL;
		this->lpParam1 = FALSE;
		this->lpParam2 = NULL;
	}
};

const int MAX_BLOCK = 10000;
const int MAX_PORT_NUM = 20;

typedef void (*PFCALLBACK_RECV)(LPVOID lpParam, BYTE *pDataBuf, int nDataBufSize);
typedef void (*PFCALLBACK_SEND)(LPVOID lpParam, int nStopType);

BOOL OpenComm(SerPortPar *pSerPortPar);

/**************************************************
* �������ƣ�CloseComm
* ���������1������ 
*           ����1:int nPort		���ں�
* ���������BOOL 
* �������ܣ�
* �������ߣ�zyy
* ����ʱ�䣺2011-8-9 9:38:25
**************************************************/
BOOL CloseComm(int nPort);

BOOL SendComm(SerPortPar *pSerPortPar);
BOOL StopSendComm(int nPort);



