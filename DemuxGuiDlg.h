// DemuxGuiDlg.h : header file
//

#if !defined(AFX_DEMUXGUIDLG_H__A5F18082_71CE_49C9_82D9_8ED513E2664B__INCLUDED_)
#define AFX_DEMUXGUIDLG_H__A5F18082_71CE_49C9_82D9_8ED513E2664B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// for def

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
//typedef __int64             QWORD;
typedef long                LONG; 
//typedef unsigned short      UINT; 
#pragma pack(1)
#define FCC(ch4) ((((DWORD)(ch4) & 0xFF) << 24) |     \
                  (((DWORD)(ch4) & 0xFF00) << 8) |    \
                  (((DWORD)(ch4) & 0xFF0000) >> 8) |  \
                  (((DWORD)(ch4) & 0xFF000000) >> 24))
#define FOURCC DWORD
#define ME(a) ((a << 24) | \
	          ((a << 8) & 0x00FF0000)  | \
              ((a >> 8) & 0x0000FF00)  | \
              (a >> 24)) 
#define ME2(a) (a << 8) |(a >> 8)
// avi def
//          * * * * * * avih * * * * * *             //
typedef struct _avimainheader {
    FOURCC fcc;                     // 'avih'
    DWORD  cb;                      // size of this structure - 8(exclude fcc and cb)
    DWORD  dwMicroSecPerFrame;      // frame display rate (or 0L)
    DWORD  dwMaxBytesPerSec;        // max. transfer rate
    DWORD  dwPaddingGranularity;    // pad to multiples of this size; normally 2K.
    DWORD  dwFlags;                 // the ever-present flags
    #define AVIF_HASINDEX        0x00000010 // Index at end of file
    #define AVIF_MUSTUSEINDEX    0x00000020
    #define AVIF_ISINTERLEAVED   0x00000100
    #define AVIF_TRUSTCKTYPE     0x00000800 // Use CKType to find key frames
    #define AVIF_WASCAPTUREFILE  0x00010000
    #define AVIF_COPYRIGHTED     0x00020000
	DWORD  dwTotalFrames;           // # frames in first movi list
    DWORD  dwInitialFrames;         // can be ignored
    DWORD  dwStreams;               // number of streams in the file
    DWORD  dwSuggestedBufferSize;   // size of buffer required to hold the chunks of the file
    DWORD  dwWidth;                 // the width of the stream
    DWORD  dwHeight;                // the height of the stream
    DWORD  dwReserved[4];
} AVIMAINHEADER;

//          * * * * * * dmlh * * * * * *             //

typedef struct _aviextheader {
    FOURCC  fcc;                    // 'dmlh'
    DWORD   cb;                     // size of this structure -8(exclude fcc and cb)
    DWORD   dwGrandFrames;          // total number of frames in the file
    DWORD   dwFuture[61];           // to be defined later
} AVIEXTHEADER;

//          * * * * * * strh * * * * * *              //

typedef struct _avistreamheader {
    FOURCC fcc;                     // 'strh'
    DWORD  cb;                      // size of this structure - 8(exclude fcc and cb)

    FOURCC fccType;                 // stream type codes,
                                    // 'vids' for video, 'auds' for audio, 'txts' for text, 'mids' for MIDI

    FOURCC fccHandler;              // the codec to be used
    DWORD  dwFlags;      
    #define AVISF_DISABLED          0x00000001   // Stream should not be activated by default
    #define AVISF_VIDEO_PALCHANGES  0x00010000   // the palette used is changing during playback
    WORD   wPriority;   
    WORD   wLanguage;
    DWORD  dwInitialFrames;
    DWORD  dwScale;
    DWORD  dwRate;                  // dwRate/dwScale is stream tick rate in ticks/sec
    DWORD  dwStart;                 // start time of the frame
    DWORD  dwLength;                // size of the stream in units as defined in dwRate and dwScale
    DWORD  dwSuggestedBufferSize;   // size of the buffer necessary to score blocks of the stream 
    DWORD  dwQuality;               // the quality of the stream,not important
    DWORD  dwSampleSize;            
    struct {
       short int left;
       short int top;
       short int right;
       short int bottom;
	}      rcFrame;                 // the rectangle of stream position
} AVISTREAMHEADER;


//          * * * * * * strf(video) * * * * * *              //

typedef struct _videostreamheader {
	FOURCC fcc;                     // 'strf'
    DWORD  cb;                      // size of this structure - 8(exclude fcc and cb)
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} VIDEOSTREAMHEADER;


//          * * * * * * strf(audio) * * * * * *              //

typedef struct _audiostreamheader{ 
	FOURCC fcc;                     // 'strf'
    DWORD  cb;                      // size of this structure - 8(exclude fcc and cb)
	WORD  wFormatTag;               // 0x0055 for MP3
	                                // 0x2000 for AC3
	                                // 0x2001 for TDS
	WORD  nChannels; 
	DWORD nSamplesPerSec; 
	DWORD nAvgBytesPerSec; 
	WORD  nBlockAlign; 
	WORD  wBitsPerSample; 
	WORD  cbSize; 
} AUDIOSTREAMHEADER;

//mp4 def
typedef struct _mvhdatom {
	DWORD dwFlag;
	DWORD dwCreationTime;  //since 1904.Jan.1, in seconds
	DWORD dwModifyTime;    //since 1904.Jan.1, in seconds
	DWORD dwTimeScale;     //number of unit passed in one second
	DWORD dwDuration;
	DWORD dwReserved[20];
} MVHDATOM;

typedef struct _mdhdatom {
	DWORD dwFlag;
	DWORD dwCreationTime;  //since 1904.Jan.1, in seconds
	DWORD dwModifyTime;    //since 1904.Jan.1, in seconds
	DWORD dwTimeScale;     //number of unit passed in one second
	DWORD dwDuration;
	DWORD dwReserved;
} MDHDATOM;

typedef struct _hdlratom {
	DWORD dwFlag;
	DWORD dwReserved;  
	DWORD dwHandlerType;    
	DWORD dwReserved1[12];     
	
} HDLRATOM;

typedef struct _stcoatom {
	DWORD dwFlag;
	DWORD dwEntryCount;      
	DWORD dwChunkOffset[];     //the num of dwOffset array = dwEntryCount    
} STCOATOM;

typedef struct _stssatom {
	DWORD dwFlag;
	DWORD dwEntryCount;      
	DWORD dwSampleNum[];     //the num of sample size array = dwEntryCount    
} STSSATOM;

typedef struct _stszatom {
	DWORD dwFlag;
	DWORD dwSampleSize;       //if dwSampleSize = 0,then dwSampleSize[] exist;
	DWORD dwSampleCount;
	DWORD dwSampleSize1[];     //if exists,the num of dwOffset array = dwSampleCount    
} STSZATOM;

typedef struct _stts_entry{
	DWORD dwSampleCount;
	DWORD dwSampleDuration;
} STTSENTRY;

typedef struct _sttsatom {
	DWORD dwFlag;
	DWORD dwEntryCount;      
	struct _stts_entry sttsentry[];
} STTSATOM;

typedef struct _stsc_entry{
	DWORD dwFirstChunk;      //the 1st chunk that have X sample per chunk 
	DWORD dwSamplePerChunk;  //X
	DWORD dwSampleDes;
} STSCENTRY;

typedef struct _stscatom {
	DWORD dwFlag;
	DWORD dwEntryCount;      
	STSCENTRY stscentry[];
} STSCATOM;

typedef struct _videostsdatom {
	DWORD videoFCC;
	WORD  wImageWidth;
	WORD  wImageHeight;
	DWORD dwHorizResolution;
	DWORD dwVertResolution;
} VIDEOSTSDATOM;

typedef struct _audiostsdatom {
	DWORD audioFCC;
	WORD  wChannelCount;
	WORD  wSampleRate;
} AUDIOSTSDATOM;

/////////////////////////////////////////////////////////////////////////////
// CDemuxGuiDlg dialog

class CDemuxGuiDlg : public CDialog
{
// Construction
public:
	DWORD esdsUpSize;
	int   esdsPos;
	BYTE* esdsData;
	//mp4 def
	DWORD  videoSampleSize,audioSampleSize;
	DWORD  *videoStsz,*audioStsz,*videoStco,*audioStco;
	DWORD  videoChunkNum,audioChunkNum;
	DWORD  *videoChunkToSample,*audioChunkToSample;
	DWORD  videoStscNum,audioStscNum;
	DWORD  videoSampleNum,audioSampleNum;
	DWORD  *videoChunkSize,*audioChunkSize;
	DWORD  startSample;
	int   streamNum;
	int   videoNum;
	int   audioNum;
	int   streamFlag;

	STTSENTRY *videoStts,*audioStts;
	STSCENTRY *videoStsc,*audioStsc;

	HDLRATOM  hdlr[4];
	MDHDATOM  mdhd[4];

	VIDEOSTSDATOM videoStsd;
	AUDIOSTSDATOM audioStsd;
	int Mp4Head();
	void readMdhd(DWORD dwSize,FILE *fpMp4);
	void readHdlr(DWORD dwSize,FILE *fpMp4);
	void readVideoStsd(DWORD dwSize,FILE *fpMp4);
	void readAudioStsd(DWORD dwSize,FILE *fpMp4);
	void readVideoStts(DWORD dwSize,FILE *fpMp4);
	void readAudioStts(DWORD dwSize,FILE *fpMp4);
	void readVideoStco(DWORD dwSize,FILE *fpMp4);
	void readAudioStco(DWORD dwSize,FILE *fpMp4);
	void readVideoStsz(DWORD dwSize,FILE *fpMp4);
	void readAudioStsz(DWORD dwSize,FILE *fpMp4);
	void readVideoStsc(DWORD dwSize,FILE *fpMp4);
	void readAudioStsc(DWORD dwSize,FILE *fpMp4);

	//avi def
	AUDIOSTREAMHEADER* aHeader;
	VIDEOSTREAMHEADER* vHeader;
	AVISTREAMHEADER* strHeader;
	AVIMAINHEADER mainHeader;
		
	int AviHead();
	//GUI def
	void DemuxHead();
	CString str_aof;
	CString str_vof;
	CString m_inputfile;
	CDemuxGuiDlg(CWnd* pParent = NULL);	// standard constructor
	int fileflag;  // flag for file format, 0 for unsupport, 1 for avi, 2 for mp4&3gp
// Dialog Data
	//{{AFX_DATA(CDemuxGuiDlg)
	enum { IDD = IDD_DEMUXGUI_DIALOG };
	CProgressCtrl	m_pro;
	CString	m_outputfilevo;
	CString	m_outputfileao;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemuxGuiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemuxGuiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnButtonOpensrc();
	afx_msg void OnButtonVof();
	afx_msg void OnButtonAof();
	afx_msg void OnButtonDemux();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnStnClickedStaticTotal();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMUXGUIDLG_H__A5F18082_71CE_49C9_82D9_8ED513E2664B__INCLUDED_)
