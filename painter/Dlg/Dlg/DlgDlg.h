// DlgDlg.h : header file
//

#if !defined(AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)
#define AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgDlg dialog
// added s
#include <vector>
#include "Figure.h"
#include "afxwin.h"
#include <stack>
#include <fstream>
#include <Afxtempl.h> // because of CArray SetCurrentDirectory 

//#include "UndoRedo.h"
using namespace std;
// added e
class CDlgDlg : public CDialog //מקבלת את הפרמטרים של הדיאלוג כפתורים וכו CDialog'...
{
	enum FIGURES { RECTANGLE, ELLIPSE , TRIANGLE, LINE, MOVE_OBJECT};
	FIGURES futureFigKIND;// בקייס איזה צורה אנחנו שואבים
	COLORREF curColor;


	//int index, iMax;
	vector <Figure*> figs;
	stack <Figure *>undoredo;
	bool isPressed;
	CPoint startP;
	CPoint endP;
	void ClearScreen();
	
public:
	CDlgDlg(CWnd* pParent = NULL);	// standard constructor

	~CDlgDlg();
	//{{AFX_DATA(CDlgDlg)
	enum { IDD = IDD_DLG_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
														//}}AFX_VIRTUAL
														// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadio1();//rectangle
	afx_msg void OnBnClickedRadio2();//Ellipse
	afx_msg void OnBnClickedRadio3();//TRIANGLE
	afx_msg void OnBnClickedCheck1();// isThin
	BOOL isFill;
	afx_msg void OnBnClickedCheck2();// isFill
	BOOL isThin; 
	afx_msg void OnBnClickedButton1(); //color
	afx_msg void OnBnClickedRadio4(); //LINE
	

	afx_msg void OnBnClickedRadio5(); //MOVE_OBJECT
	afx_msg void OnBnClickedButton5(); //undo
	afx_msg void OnBnClickedButton6(); //redo


	//menu
	afx_msg void NewFile();
	afx_msg void SaveFile();
	afx_msg void OpenFile();
	afx_msg void ExitFile();
	afx_msg void Undo();
	afx_msg void Redo();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDLG_H__D02F91E6_1066_4AA4_AE0B_1D16C986AE2C__INCLUDED_)
