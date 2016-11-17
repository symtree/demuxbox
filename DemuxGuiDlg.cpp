// DemuxGuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "math.h"
#include "DemuxGui.h"
#include "DemuxGuiDlg.h"


#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemuxGuiDlg dialog

CDemuxGuiDlg::CDemuxGuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemuxGuiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemuxGuiDlg)
	m_outputfilevo = _T("");
	m_outputfileao = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemuxGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemuxGuiDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_pro);
	DDX_Text(pDX, IDC_EDIT_VOF, m_outputfilevo);
	DDX_Text(pDX, IDC_EDIT_AOF, m_outputfileao);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemuxGuiDlg, CDialog)
	//{{AFX_MSG_MAP(CDemuxGuiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENSRC, OnButtonOpensrc)
	ON_BN_CLICKED(IDC_BUTTON_VOF, OnButtonVof)
	ON_BN_CLICKED(IDC_BUTTON_AOF, OnButtonAof)
	ON_BN_CLICKED(IDC_BUTTON_DEMUX, OnButtonDemux)
	//}}AFX_MSG_MAP
	//ON_STN_CLICKED(IDC_STATIC_TOTAL, &CDemuxGuiDlg::OnStnClickedStaticTotal)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemuxGuiDlg message handlers

BOOL CDemuxGuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	GetDlgItem(IDC_BUTTON_VOF)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_AOF)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEMUX)->EnableWindow(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemuxGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemuxGuiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemuxGuiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemuxGuiDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDemuxGuiDlg::OnButtonOpensrc() 
{
	// TODO: Add your control notification handler code here
	// able these 3 button
	//GetDlgItem(IDC_BUTTON_VOF)->EnableWindow(false);
	//GetDlgItem(IDC_BUTTON_AOF)->EnableWindow(false);
	//GetDlgItem(IDC_BUTTON_DEMUX)->EnableWindow(false);

	UpdateData(TRUE); // ?
	// open file
	CFileDialog FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"media file(*.avi;*.mp4;*.3gp)|*.avi;*.mp4;*.3gp|all files(*.*)|*.*||");
	//file dialog excute
	if(FileDlg.DoModal()==IDCANCEL)return;
	m_inputfile=FileDlg.GetPathName();

	UpdateData(FALSE);// ?

	DemuxHead();
}

void CDemuxGuiDlg::DemuxHead()
{
	
	GetDlgItem(IDC_BUTTON_VOF)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_AOF)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEMUX)->EnableWindow(false);
//	str_aof = "";
//	str_vof = "";
//	UpdateData(TRUE);

	fileflag = (AviHead())|(Mp4Head());

	CEdit *pEdit_FCC=(CEdit*)GetDlgItem(IDC_EDIT_FCC);//获取控件窗口指针		 
	char *pfcc;
	CString str_fcc;

	CEdit *pEdit_TOTAL=(CEdit*)GetDlgItem(IDC_EDIT_TOTAL);
	CString str_total;
	long total;

	CEdit *pEdit_FPS=(CEdit*)GetDlgItem(IDC_EDIT_FPS);//获取控件窗口指针
	float framerate;
	CString str_framerate;

	CEdit *pEdit_WIDTH=(CEdit*)GetDlgItem(IDC_EDIT_WIDTH);//获取控件窗口指针
	int width;
	CString str_width;

	CEdit *pEdit_HEIGHT=(CEdit*)GetDlgItem(IDC_EDIT_HEIGHT);//获取控件窗口指针		 
	int height;
	CString str_height;

	CEdit *pEdit_TIME=(CEdit*)GetDlgItem(IDC_EDIT_TIME);//获取控件窗口指针
	long vTime;
	CString str_time;

	CEdit *pEdit_VO = (CEdit*)GetDlgItem(IDC_EDIT_VOF);
	CEdit *pEdit_AO = (CEdit*)GetDlgItem(IDC_EDIT_AOF);

	CEdit *pEdit_FCC_A=(CEdit*)GetDlgItem(IDC_EDIT_FCC2);//获取控件窗口指针
	CString str_fcc_a; 

	CEdit *pEdit_TIME_A=(CEdit*)GetDlgItem(IDC_EDIT_TIME2);//获取控件窗口指针
	long aTime;
	CString str_time_a;

	CEdit *pEdit_SR=(CEdit*)GetDlgItem(IDC_EDIT_SAMPLERATE);//获取控件窗口指针
	CString str_sr;

	pEdit_VO->SetSel(0,-1);
	pEdit_VO->ReplaceSel("");

	pEdit_AO->SetSel(0,-1);
	pEdit_AO->ReplaceSel("");

	if(fileflag == 1) // AVI
	{		
		// 显示编码方式
		pfcc = (char*)&vHeader->biCompression;		
		str_fcc.Format("%c%c%c%c",pfcc[0],pfcc[1],pfcc[2],pfcc[3]);		
		pEdit_FCC->SetSel(0,-1);
		pEdit_FCC->ReplaceSel("");
		pEdit_FCC->ReplaceSel(str_fcc);

		// 显示总帧数
		//获取控件窗口指针		
		total = mainHeader.dwTotalFrames;		
		str_total.Format("%d",total);		
		pEdit_TOTAL->SetSel(0,-1);
		pEdit_TOTAL->ReplaceSel("");
		pEdit_TOTAL->ReplaceSel(str_total);

		// 显示帧率				
		framerate = strHeader[0].dwRate/strHeader[0].dwScale;
		str_framerate.Format("%f",framerate);		
		pEdit_FPS->SetSel(0,-1);
		pEdit_FPS->ReplaceSel("");
		pEdit_FPS->ReplaceSel(str_framerate);

		//显示图像宽度				 
		width = mainHeader.dwWidth;
		str_width.Format("%d",width);	
		pEdit_WIDTH->SetSel(0,-1);
		pEdit_WIDTH->ReplaceSel("");
		pEdit_WIDTH->ReplaceSel(str_width);

		//显示图像高度		 
		height = mainHeader.dwHeight;
		str_height.Format("%d",height);
		pEdit_HEIGHT->SetSel(0,-1);
		pEdit_HEIGHT->ReplaceSel("");
		pEdit_HEIGHT->ReplaceSel(str_height);

		//显示播放时间（视频）
		vTime = mainHeader.dwTotalFrames/framerate;
		int vHours = vTime/3600;
		int vMins  = (vTime - vHours*3600)/60;
		int vSecs  = fmod(vTime,60.0);   
		str_time.Format("%02d:%02d:%02d",vHours,vMins,vSecs);
		pEdit_TIME->SetSel(0,-1);
		pEdit_TIME->ReplaceSel("");
		pEdit_TIME->ReplaceSel(str_time);
		//输出路径按钮
		GetDlgItem(IDC_BUTTON_VOF)->EnableWindow(true);
		//显示输出路径
		str_vof  = m_inputfile + "v";
		pEdit_VO->SetSel(0,-1);
		pEdit_VO->ReplaceSel("");
		pEdit_VO->ReplaceSel(str_vof);

		//显示音频编码方式
		int audioflag = 1;
		switch(aHeader->wFormatTag)
		{
			case 0x01:
				str_fcc_a = "PCM";
				break;
			case 0x2000:
				str_fcc_a = "AC3";
				break;
			case 0x55:
				str_fcc_a = "MP3";
				break;
			case 0x50:
				str_fcc_a = "MP2";
				break;
			case 0x2001:
				str_fcc_a = "DTS";
				break;
			case 0x00:
				str_fcc_a = "NO AUDIO";
				audioflag = 0;
				break;
			default:
				str_fcc_a = "Unrecognized";
				break;
		}

		pEdit_FCC_A->SetSel(0,-1);
		pEdit_FCC_A->ReplaceSel("");
		pEdit_FCC_A->ReplaceSel(str_fcc_a);

		//显示播放时间（音频）
		if(audioflag)
		{
			aTime = strHeader[1].dwLength/(strHeader[1].dwRate/strHeader[1].dwScale);
			//输出路径按钮
			GetDlgItem(IDC_BUTTON_AOF)->EnableWindow(true);
			str_aof  = m_inputfile + "a";
			pEdit_AO->SetSel(0,-1);
			pEdit_AO->ReplaceSel("");
			pEdit_AO->ReplaceSel(str_aof);
		}
		else
		{
			aTime = 0;
		}
		int aHours = aTime/3600;
		int aMins  = (aTime - aHours*3600)/60;
		int aSecs  = fmod(aTime,60.0);   
		str_time_a.Format("%02d:%02d:%02d",aHours,aMins,aSecs);
		//str_width = str_width + " pixels";
		pEdit_TIME_A->SetSel(0,-1);
		pEdit_TIME_A->ReplaceSel("");
		pEdit_TIME_A->ReplaceSel(str_time_a);

		//显示采样率
		str_sr.Format("%d",aHeader->nSamplesPerSec);
		pEdit_SR->SetSel(0,-1);
		pEdit_SR->ReplaceSel("");
		pEdit_SR->ReplaceSel(str_sr);

		//解复用按钮
		GetDlgItem(IDC_BUTTON_DEMUX)->EnableWindow(true);
	}
	else if(fileflag == 2)
	{
		// 显示编码方式
		pfcc = (char*)&videoStsd.videoFCC;
		str_fcc.Format("%c%c%c%c",pfcc[0],pfcc[1],pfcc[2],pfcc[3]);		
		pEdit_FCC->SetSel(0,-1);
		pEdit_FCC->ReplaceSel("");
		pEdit_FCC->ReplaceSel(str_fcc);

		// 显示总帧数
		total = videoSampleNum;
		CString str_total;
		str_total.Format("%d",total);		
		pEdit_TOTAL->SetSel(0,-1);
		pEdit_TOTAL->ReplaceSel("");
		pEdit_TOTAL->ReplaceSel(str_total);

		// 显示帧率
		int i;
		for(i = 0;i < streamNum;i++)
		{
			if(hdlr[i].dwHandlerType == FCC('vide'))
			{
				framerate = videoSampleNum/(mdhd[i].dwDuration/mdhd[i].dwTimeScale);
			}
		}		
		str_framerate.Format("%f",framerate);		
		pEdit_FPS->SetSel(0,-1);
		pEdit_FPS->ReplaceSel("");
		pEdit_FPS->ReplaceSel(str_framerate);

		//显示图像宽度
		width = videoStsd.wImageWidth;
		str_width.Format("%d",width);	
		pEdit_WIDTH->SetSel(0,-1);
		pEdit_WIDTH->ReplaceSel("");
		pEdit_WIDTH->ReplaceSel(str_width);

		//显示图像高度
		height = videoStsd.wImageHeight;
		str_height.Format("%d",height);
		pEdit_HEIGHT->SetSel(0,-1);
		pEdit_HEIGHT->ReplaceSel("");
		pEdit_HEIGHT->ReplaceSel(str_height);

		//显示播放时间（视频）
		for(i = 0;i < streamNum;i++)
		{
			if(hdlr[i].dwHandlerType == FCC('vide'))
			{
				vTime = mdhd[i].dwDuration/mdhd[i].dwTimeScale;
			}
		}

		//long vTime = mdhd[i].dwDuration/mdhd[i].dwTimeScale;
		int vHours = vTime/3600;
		int vMins  = (vTime - vHours*3600)/60;
		int vSecs  = fmod(vTime,60.0);   
		str_time.Format("%02d:%02d:%02d",vHours,vMins,vSecs);
		pEdit_TIME->SetSel(0,-1);
		pEdit_TIME->ReplaceSel("");
		pEdit_TIME->ReplaceSel(str_time);

		//输出路径按钮
		GetDlgItem(IDC_BUTTON_VOF)->EnableWindow(true);
		//显示输出路径
		str_vof  = m_inputfile + "v";
		pEdit_VO->SetSel(0,-1);
		pEdit_VO->ReplaceSel("");
		pEdit_VO->ReplaceSel(str_vof);

		// 显示编码方式(音频)
		pfcc = (char*)&audioStsd.audioFCC;
		//CString str_fcc;
		str_fcc.Format("%c%c%c%c",pfcc[0],pfcc[1],pfcc[2],pfcc[3]);		
		pEdit_FCC_A->SetSel(0,-1);
		pEdit_FCC_A->ReplaceSel("");
		pEdit_FCC_A->ReplaceSel(str_fcc);

		//显示播放时间（音频）
		for(i = 0;i < streamNum;i++)
		{
			if(hdlr[i].dwHandlerType == FCC('soun'))
			{
				aTime = mdhd[i].dwDuration/mdhd[i].dwTimeScale;
			}
		}
		int aHours = aTime/3600;
		int aMins  = (aTime - aHours*3600)/60;
		int aSecs  = fmod(aTime,60.0);   
		str_time_a.Format("%02d:%02d:%02d",aHours,aMins,aSecs);
		//str_width = str_width + " pixels";
		pEdit_TIME_A->SetSel(0,-1);
		pEdit_TIME_A->ReplaceSel("");
		pEdit_TIME_A->ReplaceSel(str_time_a);

		
		str_sr.Format("%d",audioStsd.wSampleRate);
		pEdit_SR->SetSel(0,-1);
		pEdit_SR->ReplaceSel("");
		pEdit_SR->ReplaceSel(str_sr);
		//输出路径按钮
		GetDlgItem(IDC_BUTTON_AOF)->EnableWindow(true);
		str_aof  = m_inputfile + "a";
		pEdit_AO->SetSel(0,-1);
		pEdit_AO->ReplaceSel("");
		pEdit_AO->ReplaceSel(str_aof);
		//解复用按钮
		GetDlgItem(IDC_BUTTON_DEMUX)->EnableWindow(true);
	}
	else
	{	
		pEdit_FCC->SetSel(0,-1);
		pEdit_FCC->ReplaceSel("");

		pEdit_TOTAL->SetSel(0,-1);
		pEdit_TOTAL->ReplaceSel("");

		pEdit_FCC_A->SetSel(0,-1);
		pEdit_FCC_A->ReplaceSel("");		
		
		pEdit_TIME->SetSel(0,-1);
		pEdit_TIME->ReplaceSel("");
		
		pEdit_HEIGHT->SetSel(0,-1);
		pEdit_HEIGHT->ReplaceSel("");

		pEdit_WIDTH->SetSel(0,-1);
		pEdit_WIDTH->ReplaceSel("");
		
		pEdit_FPS->SetSel(0,-1);
		pEdit_FPS->ReplaceSel("");
		
		pEdit_TIME_A->SetSel(0,-1);
		pEdit_TIME_A->ReplaceSel("");

		pEdit_AO->SetSel(0,-1);
		pEdit_AO->ReplaceSel("");

		pEdit_SR->SetSel(0,-1);
		pEdit_SR->ReplaceSel("");

		pEdit_VO->SetSel(0,-1);
		pEdit_VO->ReplaceSel("");
		
		AfxMessageBox("can't recognize fileformat！");
	}
}

int CDemuxGuiDlg::AviHead()
{
	int *nStrlLen,i;
	long nCurPos;
	unsigned long dwTemp[3],nFileLen,nHdrlLen;
	FILE *fpAvi;
	
	const char *inputfile =  m_inputfile.GetBuffer(m_inputfile.GetLength()+10); // CString to char
	if((fpAvi=fopen(inputfile,"rb"))==NULL)
	{
		fclose(fpAvi);
		return 0;
	}

	fread(dwTemp,sizeof(DWORD),3,fpAvi);
	if(dwTemp[0]!=(FCC('RIFF')))
	{
		//判定
		fclose(fpAvi);
		return 0;
	}

	if(dwTemp[2]!=FCC('AVI '))
	{
		//判定
		fclose(fpAvi);
		return 0;
	}
	//mainHeader = (AVIMAINHEADER*)calloc(1,sizeof(AVIMAINHEADER));
	nFileLen = dwTemp[1];  // length of the 1st RIFF list
    
	fread(dwTemp,sizeof(DWORD),3,fpAvi);
	nHdrlLen = dwTemp[1];  // length of the hdrl list
	
	fread(&mainHeader,sizeof(AVIMAINHEADER),1,fpAvi);

	strHeader  = (AVISTREAMHEADER*)calloc(mainHeader.dwStreams,sizeof(AVISTREAMHEADER));
	nStrlLen   = (int*)calloc(mainHeader.dwStreams,sizeof(int));
	nCurPos = ftell(fpAvi);
	//没找到，待处理
	vHeader    = (VIDEOSTREAMHEADER*)calloc(1,sizeof(VIDEOSTREAMHEADER));
	aHeader    = (AUDIOSTREAMHEADER*)calloc(1,sizeof(AUDIOSTREAMHEADER));
	i = 0;
	while(nCurPos < (nHdrlLen + 8 + 12))	
	{
		fread(dwTemp,sizeof(DWORD),3,fpAvi);
		if((dwTemp[0]==(FCC('LIST')))&&(dwTemp[2]==(FCC('strl'))))
		{
			nStrlLen[i] = dwTemp[1];
			fread(&strHeader[i],sizeof(AVISTREAMHEADER),1,fpAvi);
			switch (strHeader[i].fccType)
			{
				case FCC('vids'):
					//vHeader    = (VIDEOSTREAMHEADER*)calloc(1,sizeof(VIDEOSTREAMHEADER));
					fread(vHeader,sizeof(VIDEOSTREAMHEADER),1,fpAvi);
					if(((vHeader->cb)+8)>sizeof(VIDEOSTREAMHEADER))
					{
						fseek(fpAvi,(vHeader->cb+8)-sizeof(VIDEOSTREAMHEADER),SEEK_CUR);
						vHeader->cb = sizeof(VIDEOSTREAMHEADER) - 8;
					}

					break;
				case FCC('auds'):
					//aHeader    = (AUDIOSTREAMHEADER*)calloc(1,sizeof(AUDIOSTREAMHEADER));
					fread(aHeader,sizeof(AUDIOSTREAMHEADER),1,fpAvi);
					if(((aHeader->cb)+8)>sizeof(AUDIOSTREAMHEADER))
					{
						fseek(fpAvi,(aHeader->cb+8)-sizeof(AUDIOSTREAMHEADER),SEEK_CUR);
						aHeader->cb = sizeof(AUDIOSTREAMHEADER) - 8;
					}
					break;
			}
			nCurPos = ftell(fpAvi);	
			i = i + 1;
		}
		else
		{
			fseek(fpAvi,dwTemp[1]-4,SEEK_CUR);
			nCurPos = ftell(fpAvi);	
			if(dwTemp[1] & 1)
			{
				fseek(fpAvi,1,SEEK_CUR);
			}
		}
	}
	fclose(fpAvi);
	return 1;
}

int CDemuxGuiDlg::Mp4Head()
{
	int    posFlag = 0;
	DWORD  nowPos,endPos;
	DWORD  dwType = 0;
	DWORD  dwSize = 0;
	FILE   *fpMp4;

	DWORD  trakSize,trakPos;
	DWORD  stblSize,stblPos;
	DWORD  mdiaSize,mdiaPos;
	DWORD  minfPos;

	DWORD  i,j= 0;
	int    nFileNameLen = 0;	
	
	streamNum  = 0;
	videoNum   = -1;
	audioNum   = -1;
	streamFlag = -1;	

	const char *inputfile =  m_inputfile.GetBuffer(m_inputfile.GetLength()+10); // CString to char
	if((fpMp4=fopen(inputfile,"rb"))==NULL)
	{
		fclose(fpMp4);
		return 0;
	}

	fseek(fpMp4,0,SEEK_END);
	endPos = ftell(fpMp4);
	fseek(fpMp4,0,SEEK_SET);

	// 判断文件格式
	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('moov'))
		{
			posFlag = 1;
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
			nowPos = ftell(fpMp4);
			if(nowPos > endPos)
			{
				fclose(fpMp4);
				return 0;
			}
		}
	}

	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('moov'))
		{
			posFlag = 1;
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
	}
	//  --------------------------trak------------------------
	posFlag = 0;
	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('trak'))
		{
			posFlag = 1;
			trakPos = ftell(fpMp4);
			trakSize = dwSize;
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
	}
	//  --------------------------mdia-----------------------// 
	posFlag = 0;
	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('mdia'))
		{
			posFlag = 1;
			mdiaPos = ftell(fpMp4);
			mdiaSize = dwSize;
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
	}
	nowPos = ftell(fpMp4);
	while(nowPos < mdiaSize - 8 + mdiaPos)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('mdhd'))
		{
			readMdhd(dwSize,fpMp4);
		}
		else if(dwType == FCC('hdlr'))
		{
			readHdlr(dwSize,fpMp4);
		}
		else if(dwType == FCC('minf'))
		{
			minfPos = ftell(fpMp4);
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
		nowPos = ftell(fpMp4);
	}

	//  --------------------------stbl-----------------------
	fseek(fpMp4,minfPos,SEEK_SET);
	posFlag = 0;
	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('stbl'))
		{
			posFlag = 1;
			stblSize = dwSize;
			stblPos  = ftell(fpMp4);
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
	}

	//  ----------------------parsing stbl-----------------
	nowPos = ftell(fpMp4);
	while(nowPos < stblSize - 8 + stblPos)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(streamFlag == 0)//video
		{
			if(dwType == FCC('stsd'))
			{
				readVideoStsd(dwSize,fpMp4);
			}
			else if(dwType == FCC('stts'))
			{
				readVideoStts(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsc'))
			{
				readVideoStsc(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsz'))
			{
				readVideoStsz(dwSize,fpMp4);
			}		
			else if(dwType == FCC('stco'))
			{
				readVideoStco(dwSize,fpMp4);
			}
			else
			{
				fseek(fpMp4,dwSize - 8,SEEK_CUR);
			}
		}
		else if(streamFlag == 1)//audio
		{
			if(dwType == FCC('stsd'))
			{
				readAudioStsd(dwSize,fpMp4);
			/*	fseek(fpMp4,12,SEEK_CUR);
				fread(&videoFCC,sizeof(DWORD),1,fpMp4);
				fseek(fpMp4,-16,SEEK_CUR);
				fseek(fpMp4,dwSize - 8,SEEK_CUR);*/
			}
			else if(dwType == FCC('stts'))
			{
				readAudioStts(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsc'))
			{
				readAudioStsc(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsz'))
			{
				readAudioStsz(dwSize,fpMp4);
			}		
			else if(dwType == FCC('stco'))
			{
				readAudioStco(dwSize,fpMp4);
			}
		}
		else if(streamFlag == 2)
		{
			;
		}
		nowPos = ftell(fpMp4);
	}
	//-------------------another trak---------------------
	fseek(fpMp4,trakPos + trakSize - 8,SEEK_SET);
	posFlag = 0;
	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('trak'))
		{
			posFlag = 1;
			trakPos = ftell(fpMp4);
			trakSize = dwSize;
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
	}
	//  --------------------------mdia-----------------------// 
	posFlag = 0;
	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('mdia'))
		{
			posFlag = 1;
			mdiaPos = ftell(fpMp4);
			mdiaSize = dwSize;
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
	}
	nowPos = ftell(fpMp4);
	while(nowPos < mdiaSize - 8 + mdiaPos)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('mdhd'))
		{
			readMdhd(dwSize,fpMp4);
		}
		else if(dwType == FCC('hdlr'))
		{
			readHdlr(dwSize,fpMp4);
		}
		else if(dwType == FCC('minf'))
		{
			minfPos = ftell(fpMp4);
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
		nowPos = ftell(fpMp4);
	}
	//  --------------------------stbl-----------------------
	fseek(fpMp4,minfPos,SEEK_SET);
	posFlag = 0;
	while(posFlag == 0)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(dwType == FCC('stbl'))
		{
			posFlag = 1;
			stblSize = dwSize;
			stblPos  = ftell(fpMp4);
		}
		else
		{
			fseek(fpMp4,dwSize-8,SEEK_CUR);
		}
	}

	nowPos = ftell(fpMp4);
	while(nowPos < stblSize - 8 + stblPos)
	{
		fread(&dwSize,sizeof(DWORD),1,fpMp4);
		fread(&dwType,sizeof(DWORD),1,fpMp4);
		dwSize = ME(dwSize);
		if(streamFlag == 0)//video
		{
			if(dwType == FCC('stsd'))
			{
				readVideoStsd(dwSize,fpMp4);
			/*	fseek(fpMp4,12,SEEK_CUR);
				fread(&videoFCC,sizeof(DWORD),1,fpMp4);
				fseek(fpMp4,-16,SEEK_CUR);
				fseek(fpMp4,dwSize - 8,SEEK_CUR);*/
			}
			else if(dwType == FCC('stts'))
			{
				readVideoStts(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsc'))
			{
				readVideoStsc(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsz'))
			{
				readVideoStsz(dwSize,fpMp4);
			}		
			else if(dwType == FCC('stco'))
			{
				readVideoStco(dwSize,fpMp4);
			}
			else
			{
				fseek(fpMp4,dwSize-8,SEEK_CUR);
			}
		}
		else if(streamFlag == 1)//audio
		{
			if(dwType == FCC('stsd'))
			{
				readAudioStsd(dwSize,fpMp4);
			/*	fseek(fpMp4,12,SEEK_CUR);
				fread(&videoFCC,sizeof(DWORD),1,fpMp4);
				fseek(fpMp4,-16,SEEK_CUR);
				fseek(fpMp4,dwSize - 8,SEEK_CUR);*/
			}
			else if(dwType == FCC('stts'))
			{
				readAudioStts(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsc'))
			{
				readAudioStsc(dwSize,fpMp4);
			}
			else if(dwType == FCC('stsz'))
			{
				readAudioStsz(dwSize,fpMp4);
			}		
			else if(dwType == FCC('stco'))
			{
				readAudioStco(dwSize,fpMp4);
			}
			else
			{
				fseek(fpMp4,dwSize-8,SEEK_CUR);
			}
		}
		else if(streamFlag == 2)
		{
			;
		}
		nowPos = ftell(fpMp4);
	}
	fclose(fpMp4);
	return 2;
}
void  CDemuxGuiDlg::readMdhd(DWORD dwSize,FILE *fpMp4)
{
	fread(&mdhd[streamNum],sizeof(MDHDATOM),1,fpMp4);
	mdhd[streamNum].dwCreationTime = ME(mdhd[streamNum].dwCreationTime);
	mdhd[streamNum].dwDuration     = ME(mdhd[streamNum].dwDuration);
	mdhd[streamNum].dwFlag         = ME(mdhd[streamNum].dwFlag);
	mdhd[streamNum].dwModifyTime   = ME(mdhd[streamNum].dwModifyTime);
	mdhd[streamNum].dwTimeScale    = ME(mdhd[streamNum].dwTimeScale);
	fseek(fpMp4,-(long)sizeof(MDHDATOM) + dwSize - 8,SEEK_CUR);
}

void CDemuxGuiDlg::readHdlr(DWORD dwSize,FILE *fpMp4)
{
	fread(&hdlr[streamNum],sizeof(HDLRATOM),1,fpMp4);
	fseek(fpMp4,-(long)sizeof(HDLRATOM) + dwSize - 8,SEEK_CUR);
	if(hdlr[streamNum].dwHandlerType == FCC('vide'))
	{
		videoNum = streamNum;
		streamFlag = 0;
	}
	else if(hdlr[streamNum].dwHandlerType == FCC('soun'))
	{
		audioNum = streamNum;
		streamFlag = 1;
	}
	else
	{
		streamFlag = 2;
	}
	streamNum++;	
}

void  CDemuxGuiDlg::readVideoStsd(DWORD dwSize,FILE *fpMp4)
{
	int  i,temp;
	//BYTE *esdsData;

	DWORD esdsSize;
	esdsUpSize = dwSize;

	fseek(fpMp4,12,SEEK_CUR);
	fread(&videoStsd.videoFCC,sizeof(DWORD),1,fpMp4);

	fseek(fpMp4,24,SEEK_CUR);
	fread(&videoStsd.wImageWidth,sizeof(WORD),1,fpMp4);

	videoStsd.wImageWidth = ME2(videoStsd.wImageWidth);
	
	fread(&videoStsd.wImageHeight,sizeof(WORD),1,fpMp4);
	videoStsd.wImageHeight = ME2(videoStsd.wImageHeight);
	
	fread(&videoStsd.dwHorizResolution,sizeof(DWORD),1,fpMp4);
	videoStsd.dwHorizResolution = ME(videoStsd.dwHorizResolution);
	
	fread(&videoStsd.dwVertResolution,sizeof(DWORD),1,fpMp4);
	videoStsd.dwVertResolution = ME(videoStsd.dwVertResolution);

	
	if(videoStsd.videoFCC == FCC('mp4v'))
	{
		fseek(fpMp4,-52,SEEK_CUR);
		
		esdsData = (BYTE*)calloc(dwSize - 8,sizeof(BYTE));
		fread(esdsData,sizeof(BYTE),dwSize - 8,fpMp4);

		for(i = 0;i < dwSize - 9;i++)
		{
			if((esdsData[i]==0x65)&&(esdsData[i + 1]==0x73)&&(esdsData[i + 2]==0x64)&&(esdsData[i + 3]==0x73))
			{
				esdsSize = esdsData[i - 1] + 256 * esdsData[i - 2]+ 256 * 256 * esdsData[i - 3] + 256 * 256 * 256 * esdsData[i - 4];
				temp     = i;
			}	
		}
		for(i = temp;i < dwSize - 9;i++)
		{
			if((esdsData[i]==0x00)&&(esdsData[i + 1]==0x00)&&(esdsData[i + 2]==0x01)&&(esdsData[i + 3]<=0xB6))
			{
				esdsPos = i;
				break;
			}
		}
		//fwrite(esdsData+temp,sizeof(BYTE),dwSize - 8 - temp,fpV);
	}
	else
	{
		fseek(fpMp4,dwSize - 60,SEEK_CUR);
	}
}

void  CDemuxGuiDlg::readAudioStsd(DWORD dwSize,FILE *fpMp4)
{
	DWORD pos;
	pos = ftell(fpMp4);
	
	fseek(fpMp4,12,SEEK_CUR);
	fread(&audioStsd.audioFCC,sizeof(DWORD),1,fpMp4);
	fseek(fpMp4,16,SEEK_CUR);
	fread(&audioStsd.wChannelCount,sizeof(WORD),1,fpMp4);
	audioStsd.wChannelCount = ME2(audioStsd.wChannelCount);
	
	//--------from sj---------
	fseek(fpMp4,6,SEEK_CUR); //sampleSize 2 + reserved 4
	fread(&audioStsd.wSampleRate ,sizeof(WORD),1,fpMp4);
	audioStsd.wSampleRate = ME2(audioStsd.wSampleRate);
	//--------from sj---------
	fseek(fpMp4,pos + dwSize - 8,SEEK_SET);
}

void  CDemuxGuiDlg::readVideoStts(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i;

	fseek(fpMp4,4,SEEK_CUR);
	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);

	videoStts = (STTSENTRY*)calloc(entryNum,sizeof(STTSENTRY));
	fread(videoStts,sizeof(STTSENTRY),entryNum,fpMp4);
	for(i = 0;i < entryNum;i++)
	{
		videoStts[i].dwSampleCount = ME(videoStts[i].dwSampleCount);
		videoStts[i].dwSampleDuration = ME(videoStts[i].dwSampleDuration);
	}
}

void  CDemuxGuiDlg::readAudioStts(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i;
	
	fseek(fpMp4,4,SEEK_CUR);
	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);

	audioStts = (STTSENTRY*)calloc(entryNum,sizeof(STTSENTRY));
	fread(audioStts,sizeof(STTSENTRY),entryNum,fpMp4);

	for(i = 0;i < entryNum;i++)
	{
		audioStts[i].dwSampleCount = ME(audioStts[i].dwSampleCount);
		audioStts[i].dwSampleDuration = ME(audioStts[i].dwSampleDuration);
	}
}

void  CDemuxGuiDlg::readVideoStco(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i;
	
	fseek(fpMp4,4,SEEK_CUR);
	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);
	videoChunkNum = entryNum;

	videoStco = (DWORD*)calloc(entryNum,sizeof(DWORD));
	fread(videoStco,sizeof(DWORD),entryNum,fpMp4);
	for(i = 0;i < entryNum;i++)
	{
		videoStco[i] = ME(videoStco[i]);
	}
}

void  CDemuxGuiDlg::readAudioStco(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i;

	fseek(fpMp4,4,SEEK_CUR);
	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);
	audioChunkNum = entryNum;

	audioStco = (DWORD*)calloc(entryNum,sizeof(DWORD));
	fread(audioStco,sizeof(DWORD),entryNum,fpMp4);
	for(i = 0;i < entryNum;i++)
	{
		audioStco[i] = ME(audioStco[i]);
	}
}

void  CDemuxGuiDlg::readVideoStsz(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i;

	fseek(fpMp4,4,SEEK_CUR);
	fread(&videoSampleSize,sizeof(DWORD),1,fpMp4);
	videoSampleSize = ME(videoSampleSize);

	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);

	videoSampleNum = entryNum;
	
	if(videoSampleSize == 0)
	{
		videoStsz = (DWORD*)calloc(entryNum,sizeof(DWORD));
		fread(videoStsz,sizeof(DWORD),entryNum,fpMp4);
		for(i = 0;i < entryNum;i++)
		{
			videoStsz[i] = ME(videoStsz[i]);
		}
	}
}

void  CDemuxGuiDlg::readAudioStsz(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i;
	
	fseek(fpMp4,4,SEEK_CUR);
	fread(&audioSampleSize,sizeof(DWORD),1,fpMp4);
	audioSampleSize = ME(audioSampleSize);

	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);
	
	audioSampleNum = ME(audioSampleNum);

	if(audioSampleSize == 0)
	{
		audioStsz = (DWORD*)calloc(entryNum,sizeof(DWORD));
		fread(audioStsz,sizeof(DWORD),entryNum,fpMp4);
		for(i = 0;i < entryNum;i++)
		{
			audioStsz[i] = ME(audioStsz[i]);
		}
	}
}

void  CDemuxGuiDlg::readVideoStsc(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i = 0;

	fseek(fpMp4,4,SEEK_CUR);
	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);
	videoStscNum = entryNum;

	videoStsc = (STSCENTRY*)calloc(entryNum + 1,sizeof(STSCENTRY));
	fread(videoStsc,sizeof(STSCENTRY),entryNum,fpMp4);
	for(i = 0;i < entryNum;i++)
	{
		videoStsc[i].dwFirstChunk = ME(videoStsc[i].dwFirstChunk);
		videoStsc[i].dwSamplePerChunk = ME(videoStsc[i].dwSamplePerChunk);
	}
}

void  CDemuxGuiDlg::readAudioStsc(DWORD dwSize,FILE *fpMp4)
{
	DWORD entryNum;
	DWORD i;
	
	fseek(fpMp4,4,SEEK_CUR);
	fread(&entryNum,sizeof(DWORD),1,fpMp4);
	entryNum = ME(entryNum);
	audioStscNum = entryNum;

	audioStsc = (STSCENTRY*)calloc(entryNum + 1,sizeof(STSCENTRY));
	fread(audioStsc,sizeof(STSCENTRY),entryNum,fpMp4);
	for(i = 0;i < entryNum;i++)
	{
		audioStsc[i].dwFirstChunk = ME(audioStsc[i].dwFirstChunk);
		audioStsc[i].dwSamplePerChunk = ME(audioStsc[i].dwSamplePerChunk);
	}
}

void CDemuxGuiDlg::OnButtonVof() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFileDialog FileVopDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"所有文件(*.*)|*.*||");
	if(FileVopDlg.DoModal()==IDCANCEL)return;
	m_outputfilevo=FileVopDlg.GetPathName();
	UpdateData(FALSE);
	str_vof = m_outputfilevo;
	CEdit *pEdit_VO = (CEdit*)GetDlgItem(IDC_EDIT_VOF);
	//CString str_vo  = m_inputfile + "v";
	pEdit_VO->SetSel(0,-1);
	pEdit_VO->ReplaceSel("");
	pEdit_VO->ReplaceSel(str_vof);
}

void CDemuxGuiDlg::OnButtonAof() 
{
	UpdateData(TRUE);
	CFileDialog FileAopDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"所有文件(*.*)|*.*||");
	if(FileAopDlg.DoModal()==IDCANCEL)return;
	m_outputfileao=FileAopDlg.GetPathName();
	UpdateData(FALSE);
	str_aof = m_outputfileao;
	CEdit *pEdit_AO = (CEdit*)GetDlgItem(IDC_EDIT_AOF);
	//CString str_vo  = m_inputfile + "v";
	pEdit_AO->SetSel(0,-1);
	pEdit_AO->ReplaceSel("");
	pEdit_AO->ReplaceSel(str_aof);	
}

void CDemuxGuiDlg::OnButtonDemux() 
{
	// TODO: Add your control notification handler code here
	if(fileflag == 1)
	{
		BYTE	*videoStr,*audioStr;
		DWORD	strSize;
		FOURCC	strID;
		DWORD   nPosMovi = 0;
		int     i = 0;
		int     audioflag = 1;
		DWORD   dwTemp[3];
		FILE    *fpAvi, *fpV,*fpA;
		long    nowPos;
		

		m_pro.SetRange(0,mainHeader.dwTotalFrames);
		//AviDemux();
		const char *inputfile =  m_inputfile.GetBuffer(m_inputfile.GetLength()+10); // CString to char
		fpAvi=fopen(inputfile,"rb"); //没有容错处理，偷懒

		fseek(fpAvi,0,SEEK_END);
		long endPos = ftell(fpAvi);
		fseek(fpAvi,0,SEEK_SET);
		
		fseek(fpAvi,12,SEEK_SET);
		nPosMovi = nPosMovi + 12;
		fread(dwTemp,sizeof(DWORD),3,fpAvi);
		nPosMovi = nPosMovi + 12;
		while(dwTemp[2]!=FCC('movi'))
		{
			fseek(fpAvi,dwTemp[1] - 4,SEEK_CUR);
			nPosMovi = nPosMovi + dwTemp[1] + 8;
			fread(dwTemp,sizeof(DWORD),3,fpAvi);		
		}
		
		const char *voutfile = str_vof.GetBuffer(str_vof.GetLength()+10); 
		fpV = fopen(voutfile,"wb");
		
		if(str_aof == "")
		{
			audioflag = 0; 
		}
		if(audioflag == 1)
		{
			const char *aoutfile = str_aof.GetBuffer(str_aof.GetLength()+10);
			fpA = fopen(aoutfile,"wb");
		}

		fseek(fpAvi,nPosMovi,SEEK_SET);
		i = 0;
		//while(i<framesNeed)
		nowPos = ftell(fpAvi);
		while(nowPos < endPos)
		{
			fread(dwTemp,sizeof(DWORD),3,fpAvi);

			if(dwTemp[0]==FCC('LIST'))
			{			
				fread(&strID,sizeof(DWORD),1,fpAvi);
				fread(&strSize,sizeof(DWORD),1,fpAvi);		
			}
			else
			{
				strID   = dwTemp[0];
				strSize = dwTemp[1];
				fseek(fpAvi,-4,SEEK_CUR);
			}
			if(strID ==FCC('00dc')&&(strSize != 0))
			{
				videoStr = (BYTE*)calloc(strSize,sizeof(BYTE));
				fread(videoStr,sizeof(BYTE),strSize,fpAvi);
				//fwrite(div3strheader,sizeof(BYTE),3,fpV);         // for divx 3
				fwrite(videoStr,sizeof(BYTE),strSize,fpV);
				free(videoStr);
				i = i + 1;
				m_pro.SetPos(i);
				if(strSize & 1)
				{
					fseek(fpAvi,1,SEEK_CUR);
				}
				nowPos = ftell(fpAvi);
			}
			else if(strID ==FCC('00db'))
			{
				videoStr = (BYTE*)calloc(strSize,sizeof(BYTE));
				fread(videoStr,sizeof(BYTE),strSize,fpAvi);
				fwrite(videoStr,sizeof(BYTE),strSize,fpV);
				free(videoStr);
				i = i + 1;
				m_pro.SetPos(i);
				if(strSize & 1)
				{
					fseek(fpAvi,1,SEEK_CUR);
				}
				nowPos = ftell(fpAvi);
			}
			else if(strID == FCC('idx1'))// 不严密的方法 最好是用文件尺寸约束 要修改
			{
//				fseek(fpAvi,strSize,SEEK_CUR);
//				i = FRAMES_NEED;
//				if(fread(dwTemp,sizeof(DWORD),3,fpAvi) == 0)
					nowPos = endPos;
/*				else(dwTemp[0] == FCC('RIFF'))
				{
				}*/
			}
			else if(strID ==FCC('01wb'))
			{
				if(audioflag == 1)
				{
					audioStr = (BYTE*)calloc(strSize,sizeof(BYTE));
					fread(audioStr,sizeof(BYTE),strSize,fpAvi);
					fwrite(audioStr,sizeof(BYTE),strSize,fpA);
					free(audioStr);
				}
				if(strSize & 1)
				{
					fseek(fpAvi,1,SEEK_CUR);
				}
				nowPos = ftell(fpAvi);
			}
			else
			{

				fseek(fpAvi,strSize,SEEK_CUR);
				if(strSize & 1)
				{
					fseek(fpAvi,1,SEEK_CUR);
				}
				nowPos = ftell(fpAvi);
				if(strSize == FCC('0000'))
				{
					nowPos = endPos;	
				}
			}
			

		}
		//display
		//CProDlg dlg;
		//dlg.DoModal();
		fclose(fpAvi);
		fclose(fpV);
		if(audioflag == 1)
		{
			fclose(fpA);
		}
		AfxMessageBox("done!",MB_OK);
		m_pro.SetPos(0);
		return;
	}
	else if(fileflag == 2)
	{
		FILE *fpMp4,*fpV,*fpA;
		DWORD  i,j= 0;
		DWORD  sampleNum = 0;
		BYTE   *videoStr,*audioStr;
		//Mp4Demux();
		m_pro.SetRange(0,videoSampleNum);
		//AviDemux();
		const char *inputfile =  m_inputfile.GetBuffer(m_inputfile.GetLength()+10); // CString to char
		fpMp4=fopen(inputfile,"rb"); //没有容错处理，偷懒

		const char *voutfile = str_vof.GetBuffer(str_vof.GetLength()+10); 
		fpV = fopen(voutfile,"wb");

		const char *aoutfile = str_aof.GetBuffer(str_aof.GetLength()+10); 
		fpA = fopen(aoutfile,"wb");

		if(videoStsd.videoFCC == FCC('mp4v'))
		{
			fwrite(esdsData+esdsPos,sizeof(BYTE),esdsUpSize - 8 - esdsPos,fpV);
			//fwrite(esdsData+temp,sizeof(BYTE),dwSize - 8 - temp,fpV);
		}

		videoChunkToSample = (DWORD*)calloc(videoChunkNum,sizeof(DWORD));

		videoStsc[videoStscNum].dwFirstChunk = videoChunkNum;
	
		for(i = 0;i < videoStscNum;i++)
		{
			for(j = videoStsc[i].dwFirstChunk - 1;j < videoStsc[i + 1].dwFirstChunk;j++)
			{
				videoChunkToSample[j] = videoStsc[i].dwSamplePerChunk;
			}
		}
	
		videoChunkSize = (DWORD*)calloc(videoChunkNum,sizeof(DWORD));
		startSample = 0;
		if(videoSampleSize == 0)
		{
			for(i = 0;i < videoChunkNum;i++)
			{
				for(j = startSample ;j < startSample + videoChunkToSample[i];j++)
				{
					videoChunkSize[i] = videoChunkSize[i] + videoStsz[j];
				}
				startSample =startSample + videoChunkToSample[i];
			}
		}
		else
		{
			for(i = 0;i < videoChunkNum;i++)
			{
				videoChunkSize[i] = videoSampleSize * videoChunkToSample[i];
			}
		}
	
//	sampleStart = 0;        // for test
//	sampleNeed	= 466;        // for test, first 500 samples
//	sampleNum	= 0;          // for test


		for(i = 0;i < videoChunkNum;i++)
		{
//		if((sampleNum < sampleNeed)&&(sampleNum >= sampleStart)) // for test
//		{
			fseek(fpMp4,videoStco[i],SEEK_SET);
			videoStr = (BYTE*)calloc(videoChunkSize[i],sizeof(BYTE));
			fread(videoStr,sizeof(BYTE),videoChunkSize[i],fpMp4);
			fwrite(videoStr,sizeof(BYTE),videoChunkSize[i],fpV);
			sampleNum = sampleNum + videoChunkToSample[i];
			
			m_pro.SetPos(sampleNum);
//		}
//		else
//		{
			//sampleNum = sampleNum + videoChunkToSample[i];
			//break;
//		}
		}
		audioChunkToSample = (DWORD*)calloc(audioChunkNum,sizeof(DWORD));

		audioStsc[audioStscNum].dwFirstChunk = audioChunkNum;

		for(i = 0;i < audioStscNum;i++)
		{
			for(j = audioStsc[i].dwFirstChunk - 1;j < audioStsc[i + 1].dwFirstChunk;j++)
			{
				audioChunkToSample[j] = audioStsc[i].dwSamplePerChunk;
			}
		}
		
		audioChunkSize = (DWORD*)calloc(audioChunkNum,sizeof(DWORD));
		startSample = 0;
		if(audioSampleSize == 0)
		{
			for(i = 0;i < audioChunkNum;i++)
			{
			
				for(j = startSample ;j < startSample + audioChunkToSample[i];j++)
				{
					audioChunkSize[i] = audioChunkSize[i] + audioStsz[j];
				}
				startSample =startSample + audioChunkToSample[i];
			}
		}
		else
		{
			for(i = 0;i < audioChunkNum;i++)
			{
				audioChunkSize[i] = audioSampleSize * audioChunkToSample[i];
			}
		}
		
		for(i = 0;i < audioChunkNum;i++)
		{
			fseek(fpMp4,audioStco[i],SEEK_SET);
			audioStr = (BYTE*)calloc(audioChunkSize[i],sizeof(BYTE));
			fread(audioStr,sizeof(BYTE),audioChunkSize[i],fpMp4);
			fwrite(audioStr,sizeof(BYTE),audioChunkSize[i],fpA);
		}

		fclose(fpMp4);
		fclose(fpV);
		fclose(fpA);
		AfxMessageBox("done!",MB_OK);
		m_pro.SetPos(0);
		return;
	}
}


