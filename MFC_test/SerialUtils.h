
typedef struct SerPortPar{
	int nPort;
	int nBaud;
	BYTE *pDataBuf;
	int nDataBufSize;
	LPVOID lpRecvFun;
	LPVOID lpSendFun;
	LPVOID lpParam1;
	LPVOID lpParam2;
	
	//结构体默认构造函数，初始化变量
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
* 函数名称：CloseComm
* 输入参数：1个参数 
*           参数1:int nPort		串口号
* 输出参数：BOOL 
* 函数功能：
* 创建作者：zyy
* 创建时间：2011-8-9 9:38:25
**************************************************/
BOOL CloseComm(int nPort);

BOOL SendComm(SerPortPar *pSerPortPar);
BOOL StopSendComm(int nPort);



