// DlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dlg.h"
#include "DlgDlg.h"
#include <mmsystem.h> // ספריה אודיו ועוד...


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


void CDlgDlg::ClearScreen() //מחיקת כל הצורות בוקטור
{
	figs.clear();
	Invalidate();
}



CDlgDlg::CDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_DIALOG, pParent),isThin(false),isFill(false)
{
	// נקודת הפתיחה איך הכל מתחיל

	futureFigKIND = RECTANGLE;
	curColor = RGB(0,0,240);
	isPressed = false;
	//index = iMax = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgDlg::~CDlgDlg()
{
	int size = figs.size();
	for (int i = 0; i<size; i++)
		figs.erase(figs.begin());
}

void CDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK1, isThin);
	DDX_Check(pDX, IDC_CHECK2, isFill);

}

BEGIN_MESSAGE_MAP(CDlgDlg, CDialog) // הפקודות נותנות להגיב על המסך
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()

	ON_BN_CLICKED(IDC_RADIO1, &CDlgDlg::OnBnClickedRadio1) //button
	ON_BN_CLICKED(IDC_RADIO2, &CDlgDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO4, &CDlgDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CDlgDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgDlg::OnBnClickedButton6)

	ON_COMMAND(ID_FILE_NEW, &CDlgDlg::NewFile)// toolbar.
	ON_COMMAND(ID_FILE_SAVE, &CDlgDlg::SaveFile)
	ON_COMMAND(ID_FILE_OPEN, &CDlgDlg::OpenFile)
	ON_COMMAND(ID_FILE_EXIT, &CDlgDlg::ExitFile)
	ON_COMMAND(ID_SETTING_UNDO, &CDlgDlg::Undo)
	ON_COMMAND(ID_SETTING_REDO, &CDlgDlg::Redo)


END_MESSAGE_MAP()


// CDlgDlg message handlers

BOOL CDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMenu menu;//init to menu
	menu.LoadMenu(IDR_MENU1);
	SetMenu(&menu);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1); // רדיו 1 - רדיו 3 = קבוצה ותתחיל ברדיו 1

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDlgDlg::OnPaint()
{
	int curIndex = figs.size();
	CPaintDC dc(this);

	for (int i = 0; i < curIndex; i++)
		figs[i]->Draw(&dc); // משתמשים בוירטואל
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
int exIndex = -1;

void CDlgDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    
	startP = endP = point;
	isPressed = true;
	int curIndex = figs.size();

	switch (futureFigKIND) {

	case MOVE_OBJECT:
		for (int i = 0; i < curIndex; i++)
			if (figs[i]->isEx(point))
				exIndex = i;
		break;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	int curIndex = figs.size();
	if (isPressed)
	{
		endP = point;
		isPressed = false; // when button up need to be false not pressed.
		CClientDC dc(this);

		if (startP != endP) // if its a shape and not a point do shape.
		{
			switch (futureFigKIND)
			{
			case RECTANGLE:
				
				figs.push_back(new RectangleM(startP.x, startP.y, endP.x, endP.y, isFill, isThin, curColor));	
				Invalidate();
							
				break;

			case ELLIPSE: 
				figs.push_back(new EllipeseM(startP.x, startP.y, endP.x, endP.y, isFill, isThin, curColor));
				Invalidate();
				break;

			case LINE: 
				figs.push_back(new LineM(startP.x, startP.y, endP.x, endP.y, isThin, curColor));
				dc.SetROP2(R2_NOTXORPEN); // עושה קסור עם הצבעים כאשר עולה צבע עם צבע.

				Invalidate();
				break;

			case TRIANGLE:

				figs.push_back(new TriangleM(startP.x, startP.y, endP.x, endP.y, isFill, isThin, curColor));
				Invalidate();
				break;

			case MOVE_OBJECT:
				if (exIndex != -1)
				{
					exIndex = -1;
					Invalidate();
				}
				break;
			}
		}
	
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isPressed) {


		int curIndex = figs.size();
		CClientDC dc(this);

		CBrush mybrush, *oldbrush;
		if (isFill)
		{
			mybrush.CreateSolidBrush(curColor);
			oldbrush = dc.SelectObject(&mybrush);
		}
		dc.SetROP2(R2_NOTXORPEN); // עושה קסור עם הצבעים כאשר עולה צבע עם צבע.
		CPen mypen1(PS_SOLID, isThin ? 1 : 4, curColor);
		CPen *oldpen;

		oldpen = dc.SelectObject(&mypen1);

		switch (futureFigKIND)
		{
		case RECTANGLE: 

			dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
			endP = point;
			dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
			break;
		case ELLIPSE:
			dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
			endP = point;
			dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
			break;
		case LINE:
			dc.MoveTo(startP.x, startP.y);
			dc.LineTo(endP.x, endP.y);
			endP = point;
			dc.MoveTo(startP.x, startP.y);
			dc.LineTo(endP.x, endP.y);
			break;
		case TRIANGLE:
			dc.MoveTo(startP.x, endP.y);
			dc.LineTo(endP.x, endP.y);
			dc.LineTo((startP.x + endP.x) / 2, startP.y);
			dc.LineTo(startP.x, endP.y);
			endP = point;
			dc.MoveTo(startP.x, endP.y);
			dc.LineTo(endP.x, endP.y);
			dc.LineTo((startP.x + endP.x) / 2, startP.y);
			dc.LineTo(startP.x, endP.y);
			break;

		case MOVE_OBJECT:
			if (exIndex != -1) {

				figs[exIndex]->Draw(&dc);
				figs[exIndex]->x2 += endP.x - figs[exIndex]->x1;
				figs[exIndex]->y2 += endP.y - figs[exIndex]->y1;
				figs[exIndex]->x1 = endP.x;
				figs[exIndex]->y1 = endP.y;
				endP = point;
				figs[exIndex]->Draw(&dc);
			}
			break;
		}
	}
	CDialog::OnMouseMove(nFlags, point);

}

void CDlgDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	curColor = dc.GetPixel(point);
	CDialog::OnRButtonDown(nFlags, point);

}



void CDlgDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	futureFigKIND = RECTANGLE;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1),
		GetModuleHandle(NULL),
		SND_RESOURCE);
	
}


void CDlgDlg::OnBnClickedRadio2()
{
	futureFigKIND = ELLIPSE;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE2),
		GetModuleHandle(NULL),
		SND_RESOURCE);
}

void CDlgDlg::OnBnClickedRadio3()
{
	futureFigKIND = TRIANGLE;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE4),
		GetModuleHandle(NULL),
		SND_RESOURCE);
}

void CDlgDlg::OnBnClickedCheck1()//isThin 
{
	 // משתנה בקוסנטרקטור
	UpdateData(true);
}


void CDlgDlg::OnBnClickedCheck2()// isFill 
{
	UpdateData(true); // משנה את המידע בהתאם לקונסטרקטור, וי לטרו בלי וי פולס

}


void CDlgDlg::OnBnClickedButton1()
{
	CColorDialog dcolor;
	if (dcolor.DoModal() == IDOK)
		curColor = dcolor.GetColor();
}

void CDlgDlg::OnBnClickedRadio4()
{
	futureFigKIND = LINE;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE3),
		GetModuleHandle(NULL),
		SND_RESOURCE);
}




void CDlgDlg::OnBnClickedRadio5()
{
	futureFigKIND = MOVE_OBJECT;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE5),
		GetModuleHandle(NULL),
		SND_RESOURCE);
}


void CDlgDlg::OnBnClickedButton5()//undo
{
	if (figs.size() > 0) {
		undoredo.push(figs[figs.size() - 1]);
		figs.erase(figs.end()- 1);
		Invalidate();
	}
}

void CDlgDlg::OnBnClickedButton6() // redo
{
	if (!undoredo.empty()) {
		figs.push_back(undoredo.top());
		undoredo.pop();
		Invalidate();
	}
}

void CDlgDlg::NewFile()
{
	this->ClearScreen();

}

void CDlgDlg::SaveFile()
{
	CString m_strPathName;
	char* File;
	TCHAR szFilters[] =
		_T("Text files (*.txt)¦ *.txt¦ All files (*.*) ¦*.* ¦¦");

	CFileDialog dlg(FALSE, _T("txt"), _T(".txt"),
		OFN_OVERWRITEPROMPT, szFilters);

	if (dlg.DoModal() == IDOK)
		m_strPathName = dlg.GetPathName();


	CFile file(m_strPathName, CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	int size = figs.size();
	ar << size;
	for (int i = 0;i < size;i++)
	{
		ar << figs[i]->KIND;
		ar << figs[i]->isFill;
		ar << figs[i]->isThin;
		ar << figs[i]->objColor;
		ar << figs[i]->x1;
		ar << figs[i]->y1;
		ar << figs[i]->x2;
		ar << figs[i]->y2;
	}
	ar.Close();
	file.Close();
}

void CDlgDlg::OpenFile()
{
	CString filename;

	CFileDialog fOpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL, this);

	if (fOpenDlg.DoModal() == IDOK)
	{

		filename = fOpenDlg.GetPathName();

	}


	CFile file(filename, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	figs.clear();
	int size;
	CPen p;
	COLORREF color;
	ar >> size;
	int x1, x2, y1, y2, Fill, Thin, numOfShape;
	for (int i = 0; i < size; i++)
	{
		ar >> numOfShape;
		ar >> Fill;
		ar >> Thin;
		ar >> color;
		ar >> x1;
		ar >> y1;
		ar >> x2;
		ar >> y2;
		switch (numOfShape)
		{
		case 0:
			figs.push_back(new RectangleM(x1, y1, x2, y2, Fill, Thin, color));
			break;
		case 1:
			figs.push_back(new EllipeseM(x1, y1, x2, y2, Fill, Thin, color));
			break;
		case 2:
			figs.push_back(new LineM(x1, y1, x2, y2, Thin, color));
			break;
		case 3:
			figs.push_back(new TriangleM(x1, y1, x2, y2, Fill, Thin, color));
			break;
		}

	}
	ar.Close();
	file.Close();
	Invalidate();
}

void CDlgDlg::ExitFile()
{
	EndDialog(0);
}

void CDlgDlg::Undo()
{
	if (figs.size() > 0) {
		undoredo.push(figs[figs.size() - 1]);
		figs.erase(figs.end() - 1);
		Invalidate();
	}
}

void CDlgDlg::Redo()
{
	if (!undoredo.empty()) {
		figs.push_back(undoredo.top());
		undoredo.pop();
		Invalidate();
	}
}
