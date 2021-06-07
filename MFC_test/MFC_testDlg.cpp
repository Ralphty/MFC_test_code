
// MFC_testDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC_test.h"
#include "MFC_testDlg.h"
#include "afxdialogex.h"
#include "stdio.h"
#include <iostream>
#include "afxwin.h"
#include "NComRxC.h"
#include <cmath>
#include "SerialUtils.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

double Tmp_Latitude = 0.0;
double Tmp_Longitude = 0.0;
float  Tmp_Altitude = 0.0;
double Tmp_V = 0.0;
double Tmp_Heading = 0.0;

int32_t longitude_v = 0;
int32_t latitude_v = 0;

int g_IndexNumber = 0;

CSocket Rsu_socket;       //定义网络传输套接字(上位机到RSU)

void OnRecvCommSend(LPVOID lpParam, BYTE *pDataBuf, int nDataBufSize);
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCtestDlg dialog



CMFCtestDlg::CMFCtestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFCtestDlg::~CMFCtestDlg()
{
	
}

void CMFCtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NUMBER, m_CmbNumber);
	DDX_Control(pDX, IDC_COMBO_INFORMATION_SOURCE, m_CmbInfoSource);
	DDX_Control(pDX, IDC_COMBO_TYPE_1, m_CmbType1);
	DDX_Control(pDX, IDC_COMBO_TYPE_2, m_CmbType2);
	DDX_Control(pDX, IDC_COMBO_TYPE_3, m_CmbType3);
	DDX_Control(pDX, IDC_COMBO_COLOR1, m_CmbColor1);
	DDX_Control(pDX, IDC_COMBO_COLOR2, m_CmbColor2);
	DDX_Control(pDX, IDC_COMBO_COLOR3, m_CmbColor3);
	DDX_Text(pDX, IDC_EDIT_CONFIDENCE1, m_TextConfidence1);
	DDX_Text(pDX, IDC_EDIT_LONGITUDE_1, m_TextLongitude1);
	DDX_Text(pDX, IDC_EDIT_LATITUDE_1, m_TextLatitude1);
	DDX_Text(pDX, IDC_EDIT_SPEED_1, m_TextSpeed1);
	DDX_Text(pDX, IDC_EDIT_COURSE_ANGLE_1, m_TextCourseAngle1);
	DDX_Text(pDX, IDC_EDIT_X_1, m_TextPositionX1);
	DDX_Text(pDX, IDC_EDIT_Y_1, m_TextPositionY1);
	DDX_Text(pDX, IDC_EDIT_Z_1, m_TextPositionZ1);
	DDX_Text(pDX, IDC_EDIT_CONFIDENCE2, m_TextConfidence2);
	DDX_Text(pDX, IDC_EDIT_LONGITUDE_2, m_TextLongitude2);
	DDX_Text(pDX, IDC_EDIT_LATITUDE_2, m_TextLatitude2);
	DDX_Text(pDX, IDC_EDIT_SPEED_2, m_TextSpeed2);
	DDX_Text(pDX, IDC_EDIT_COURSE_ANGLE_2, m_TextCourseAngle2);
	DDX_Text(pDX, IDC_EDIT_X_2, m_TextPositionX2);
	DDX_Text(pDX, IDC_EDIT_Y_2, m_TextPositionY2);
	DDX_Text(pDX, IDC_EDIT_Z_2, m_TextPositionZ2);
	DDX_Text(pDX, IDC_EDIT_CONFIDENCE3, m_TextConfidence3);
	DDX_Text(pDX, IDC_EDIT_LONGITUDE_3, m_TextLongitude3);
	DDX_Text(pDX, IDC_EDIT_LATITUDE_3, m_TextLatitude3);
	DDX_Text(pDX, IDC_EDIT_SPEED_3, m_TextSpeed3);
	DDX_Text(pDX, IDC_EDIT_COURSE_ANGLE_3, m_TextCourseAngle3);
	DDX_Text(pDX, IDC_EDIT_X_3, m_TextPositionX3);
	DDX_Text(pDX, IDC_EDIT_Y_3, m_TextPositionY3);
	DDX_Text(pDX, IDC_EDIT_Z_3, m_TextPositionZ3);
	DDX_Text(pDX, IDC_EDIT_LIDAR_LONGITUDE, m_TextLidarLongitude);
	DDX_Text(pDX, IDC_EDIT_LIDAR_LATITUDE, m_TextLidarLatitude);

}

BEGIN_MESSAGE_MAP(CMFCtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_NET_SENDSignalINFO, &CMFCtestDlg::OnSendData)

	ON_BN_CLICKED(IDCANCEL,&CMFCtestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMFCtestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCtestDlg message handlers

BOOL CMFCtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//添加COMBOX控件初始值
	m_CmbNumber.ResetContent();
	m_CmbNumber.AddString(_T("1"));
	m_CmbNumber.AddString(_T("2"));
	m_CmbNumber.AddString(_T("3"));
	m_CmbNumber.SetCurSel(0);
	m_CmbInfoSource.ResetContent();
	m_CmbInfoSource.AddString(_T("0"));
	m_CmbInfoSource.AddString(_T("1"));
	m_CmbInfoSource.AddString(_T("2"));
	m_CmbInfoSource.SetCurSel(0);
	m_CmbType1.ResetContent();
	m_CmbType1.AddString(_T("0"));
	m_CmbType1.AddString(_T("1"));
	m_CmbType1.AddString(_T("2"));
	m_CmbType1.AddString(_T("3"));
	m_CmbType1.AddString(_T("4"));
	m_CmbType1.AddString(_T("5"));
	m_CmbType1.AddString(_T("6"));
	m_CmbType1.SetCurSel(4);
	m_CmbType2.ResetContent();
	m_CmbType2.AddString(_T("0"));
	m_CmbType2.AddString(_T("1"));
	m_CmbType2.AddString(_T("2"));
	m_CmbType2.AddString(_T("3"));
	m_CmbType2.AddString(_T("4"));
	m_CmbType2.AddString(_T("5"));
	m_CmbType2.AddString(_T("6"));
	m_CmbType2.SetCurSel(5);
	m_CmbType3.ResetContent();
	m_CmbType3.AddString(_T("0"));
	m_CmbType3.AddString(_T("1"));
	m_CmbType3.AddString(_T("2"));
	m_CmbType3.AddString(_T("3"));
	m_CmbType3.AddString(_T("4"));
	m_CmbType3.AddString(_T("5"));
	m_CmbType3.AddString(_T("6"));
	m_CmbType3.SetCurSel(6);
	m_CmbColor1.ResetContent();
	m_CmbColor1.AddString(_T("0"));
	m_CmbColor1.AddString(_T("1"));
	m_CmbColor1.AddString(_T("2"));
	m_CmbColor1.AddString(_T("3"));
	m_CmbColor1.AddString(_T("4"));
	m_CmbColor1.AddString(_T("5"));
	m_CmbColor1.AddString(_T("6"));
	m_CmbColor1.AddString(_T("7"));
	m_CmbColor1.SetCurSel(1);
	m_CmbColor2.ResetContent();
	m_CmbColor2.AddString(_T("0"));
	m_CmbColor2.AddString(_T("1"));
	m_CmbColor2.AddString(_T("2"));
	m_CmbColor2.AddString(_T("3"));
	m_CmbColor2.AddString(_T("4"));
	m_CmbColor2.AddString(_T("5"));
	m_CmbColor2.AddString(_T("6"));
	m_CmbColor2.AddString(_T("7"));
	m_CmbColor2.SetCurSel(2);
	m_CmbColor3.ResetContent();
	m_CmbColor3.AddString(_T("0"));
	m_CmbColor3.AddString(_T("1"));
	m_CmbColor3.AddString(_T("2"));
	m_CmbColor3.AddString(_T("3"));
	m_CmbColor3.AddString(_T("4"));
	m_CmbColor3.AddString(_T("5"));
	m_CmbColor3.AddString(_T("6"));
	m_CmbColor3.AddString(_T("7"));
	m_CmbColor3.SetCurSel(3);

	//添加网络配置
	AfxSocketInit();
	BOOL b = Rsu_socket.Create(0, SOCK_DGRAM);//绑定端口(和RSU通信)	
	if (!b)
	{
		cout << GetLastError() << endl;
	}

	/*
	AfxSocketInit();
	BOOL c = Rt_socket.Create(3000, SOCK_DGRAM);//绑定端口（和RT通信）
	if (!c)
	{
		cout << GetLastError() << endl;
	}
	*/

	//CWinThread *pthread_Senddata2 = AfxBeginThread(ReceiveDataThread, this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//发送UDP数据线程
UINT CMFCtestDlg::SendDataThread(LPVOID pParam)
{
	CMFCtestDlg *pDlg = (CMFCtestDlg *)pParam;
	while (true)
	{
		pDlg->PostMessage(WM_NET_SENDSignalINFO, 0);
		Sleep(1000);
	}
	//pDlg->PostMessage(WM_NET_SENDSignalINFO, 0);

	return 0;
}


//UDP发送函数
LRESULT CMFCtestDlg::OnSendData(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	g_UdpSendRSM.m_MessageContent.m_ParticipantInformation = &g_ParticipantInformation;
	char StatusBuf[100];
	
	g_IndexNumber = m_CmbNumber.GetCurSel();
	
#if 1
	if (g_IndexNumber == 0)
	{
		g_UdpSendRSM.StartBit = 0xFFFF;
		g_UdpSendRSM.SerialNumber = 0;
		g_UdpSendRSM.MasterNumber = 0xE1;
		g_UdpSendRSM.SlaveNumber = 0x02;
		g_UdpSendRSM.StatusBit = 0;
		g_UdpSendRSM.MessageLength = SW_16(0x0040);
		g_UdpSendRSM.m_MessageContent.FacilityID = SW_16(0x0001);
		g_UdpSendRSM.m_MessageContent.Reserved1 = 0;
		g_UdpSendRSM.m_MessageContent.DataFrameNumber = 0;
		g_UdpSendRSM.m_MessageContent.TimeStamp = 0;
		g_UdpSendRSM.m_MessageContent.LidarLongitude = SW_32(m_TextLidarLongitude);
		g_UdpSendRSM.m_MessageContent.LidarLatitude = SW_32(m_TextLidarLatitude);
		g_UdpSendRSM.m_MessageContent.LidarAngle = SW_16(0x0048);
		g_UdpSendRSM.m_MessageContent.TrafficParticipantNumber = 0x01;
		g_UdpSendRSM.m_MessageContent.Reserved2[0] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved2[1] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved2[2] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved2[3] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved2[4] = 0;
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantID = SW_16(0x0001);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantType = m_CmbType1.GetCurSel();
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantConfidence = m_TextConfidence1;
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantColor = m_CmbColor1.GetCurSel();
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantInformationSource = m_CmbInfoSource.GetCurSel();
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantReserved1[0] = 0;
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantReserved1[1] = 0;
		//g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLongitude = SW_32(m_TextLongitude1);
		//g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLatitude = SW_32(m_TextLatitude1);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLongitude = SW_32(longitude_v);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLatitude = SW_32(latitude_v);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantAltitude = SW_16(Tmp_Altitude);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantSpeed = SW_16(Tmp_V);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantCourseAngle = SW_16(Tmp_Heading);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLength = SW_16(0x001E);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantWidth = SW_16(0x001E);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantHeight = SW_16(0x0084);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantPositionX = SW_16(m_TextPositionX1);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantPosotionY = SW_16(m_TextPositionY1);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantPosotionZ = SW_16(m_TextPositionZ1);
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantReserved2[0] = 0;
		g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantReserved2[1] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved3[0] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved3[1] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved3[2] = 0;
		g_UdpSendRSM.m_MessageContent.Reserved3[3] = 0;
		g_UdpSendRSM.ParityBit = 0x01;
		g_UdpSendRSM.EndBit = 0xFF;
		UpdateData(false);



		memcpy(&StatusBuf[0], &g_UdpSendRSM.StartBit, 2);
		memcpy(&StatusBuf[2], &g_UdpSendRSM.SerialNumber, 1);
		memcpy(&StatusBuf[3], &g_UdpSendRSM.MasterNumber, 1);
		memcpy(&StatusBuf[4], &g_UdpSendRSM.SlaveNumber, 1);
		memcpy(&StatusBuf[5], &g_UdpSendRSM.StatusBit, 1);
		memcpy(&StatusBuf[6], &g_UdpSendRSM.MessageLength, 2);
		memcpy(&StatusBuf[8], &g_UdpSendRSM.m_MessageContent.FacilityID, 2);
		memcpy(&StatusBuf[10], &g_UdpSendRSM.m_MessageContent.Reserved1, 2);
		memcpy(&StatusBuf[12], &g_UdpSendRSM.m_MessageContent.DataFrameNumber, 4);
		memcpy(&StatusBuf[16], &g_UdpSendRSM.m_MessageContent.TimeStamp, 8);
		memcpy(&StatusBuf[24], &g_UdpSendRSM.m_MessageContent.LidarLongitude, 4);
		memcpy(&StatusBuf[28], &g_UdpSendRSM.m_MessageContent.LidarLatitude, 4);
		memcpy(&StatusBuf[32], &g_UdpSendRSM.m_MessageContent.LidarAngle, 2);
		memcpy(&StatusBuf[34], &g_UdpSendRSM.m_MessageContent.TrafficParticipantNumber, 1);
		memcpy(&StatusBuf[35], &g_UdpSendRSM.m_MessageContent.Reserved2, 5);
		memcpy(&StatusBuf[40], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantID, 2);
		memcpy(&StatusBuf[42], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantType, 1);
		memcpy(&StatusBuf[43], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantConfidence, 1);
		memcpy(&StatusBuf[44], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantColor, 1);
		memcpy(&StatusBuf[45], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantInformationSource, 1);
		memcpy(&StatusBuf[46], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantReserved1, 2);
		memcpy(&StatusBuf[48], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLongitude, 4);
		memcpy(&StatusBuf[52], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLatitude, 4);
		memcpy(&StatusBuf[56], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantAltitude, 2);
		memcpy(&StatusBuf[58], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantSpeed, 2);
		memcpy(&StatusBuf[60], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantCourseAngle, 2);
		memcpy(&StatusBuf[62], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantLength, 2);
		memcpy(&StatusBuf[64], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantWidth, 2);
		memcpy(&StatusBuf[66], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantHeight, 2);
		memcpy(&StatusBuf[68], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantPositionX, 2);
		memcpy(&StatusBuf[70], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantPosotionY, 2);
		memcpy(&StatusBuf[72], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantPosotionZ, 2);
		memcpy(&StatusBuf[74], &g_UdpSendRSM.m_MessageContent.m_ParticipantInformation->ParticipantReserved2, 2);
		memcpy(&StatusBuf[76], &g_UdpSendRSM.m_MessageContent.Reserved3, 4);
		memcpy(&StatusBuf[80], &g_UdpSendRSM.ParityBit, 1);
		memcpy(&StatusBuf[81], &g_UdpSendRSM.EndBit, 1);

	}
	else if (g_IndexNumber == 1)
	{
		g_UdpSendRSM.StartBit = 0xFFFF;
		g_UdpSendRSM.SerialNumber = 0;
		g_UdpSendRSM.MasterNumber = 0xE1;
		g_UdpSendRSM.SlaveNumber = 0x02;
		g_UdpSendRSM.StatusBit = 0;
		//g_UdpSendRSM.MessageLength =
	}
	else
	{
		g_UdpSendRSM.StartBit = 0xFFFF;
		g_UdpSendRSM.SerialNumber = 0;
		g_UdpSendRSM.MasterNumber = 0xE1;
		g_UdpSendRSM.SlaveNumber = 0x02;
		g_UdpSendRSM.StatusBit = 0;
		//g_UdpSendRSM.MessageLength =
	}
#endif
	Rsu_socket.SendTo((void *)StatusBuf, 82, 6000, _T("192.168.20.110"));
	return 0;
}

/*
UINT ReceiveDataThread(LPVOID pParam)
{

}
*/

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCtestDlg::OnBnClickedCancel()
{
	//退出函数
	Rsu_socket.Close();
	CDialogEx::OnCancel();
}


void CMFCtestDlg::OnBnClickedOk()
{
	int nPort;
	int nBaud;
	CString strTmp;
	SerPortPar serPortPar;
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	CWinThread *pthread_Senddata1 = AfxBeginThread(SendDataThread, this);
	
	serPortPar.nPort = 2;
	serPortPar.nBaud = 115200;
	serPortPar.lpRecvFun = (LPVOID)OnRecvCommSend;
	serPortPar.lpParam1 = (LPVOID)this;
	if (OpenComm(&serPortPar))
	{

	}
	else
	{
		AfxMessageBox(_T("串口打开失败!"));
	}

}

void OnRecvCommSend(LPVOID lpParam, BYTE *pDataBuf, int nDataBufSize)
{
	unsigned int l_u32j = 0;
	int l_n32Ret = 0;
	unsigned int l_u32Index = 0;
	if ((pDataBuf[0] == 0xAA) && ((pDataBuf[1] == 0x55)))
	{
		l_u32Index = l_u32Index + 2;
		longitude_v = ((pDataBuf[l_u32Index] & 0xFF) << 24)
							+ ((pDataBuf[l_u32Index + 1] & 0xFF) << 16)
								+ ((pDataBuf[l_u32Index + 2] & 0xFF) << 8)
									+ ((pDataBuf[l_u32Index + 3] & 0xFF));
		l_u32Index = l_u32Index + 4;
		latitude_v = ((pDataBuf[l_u32Index] & 0xFF) << 24)
							+ ((pDataBuf[l_u32Index + 1] & 0xFF) << 16)
								+ ((pDataBuf[l_u32Index + 2] & 0xFF) << 8)
									+ ((pDataBuf[l_u32Index + 3] & 0xFF));
		l_u32Index = l_u32Index + 4;
		Tmp_V = ((pDataBuf[l_u32Index] & 0xFF) << 8)
					+ ((pDataBuf[l_u32Index + 1] & 0xFF));
		l_u32Index = l_u32Index + 2;
		Tmp_Heading = ((pDataBuf[l_u32Index] & 0xFF) << 8)
			+ ((pDataBuf[l_u32Index + 1] & 0xFF));
		l_u32Index = l_u32Index + 2;
		Tmp_Altitude = ((pDataBuf[l_u32Index] & 0xFF) << 8)
			+ ((pDataBuf[l_u32Index + 1] & 0xFF));
	}
}
