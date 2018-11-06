#pragma once


#include <vector>
using namespace std;

class Figure
{

protected:
public:
	COLORREF objColor;
	int isFill, isThin;
	Figure() {};

	int x1, y1, x2, y2,KIND;
	Figure(int xx1, int yy1, int xx2, int yy2)
	{
		x1 = xx1;
		y1 = yy1;
		x2 = xx2;
		y2 = yy2;
		isFill = false;
		objColor = RGB(0, 0, 0);
	}
	Figure(int xx1, int yy1, int xx2, int yy2, int fill, int thin, int color)
	{
		x1 = xx1;
		x2 = xx2;
		y1 = yy1;
		y2 = yy2;
		isFill = fill;
		isThin = thin;
		objColor = color;
	}
	virtual int getMinX() {
		if (x1 > x2)
			return x2;
		return x1;
	}
	virtual int getMaxX() {
		if (x1 > x2)
			return x1;
		return x2;
	}
	virtual int getMinY() {
		if (y1 > y2)
			return y2;
		return y1;
	}
	virtual int getMaxY() {
		if (y1 > y2)
			return y1;
		return y2;
	}
	virtual bool isEx(CPoint p) = 0;
	virtual void Draw(CDC *dc) = 0;
	virtual ~Figure(void);
	
};

class RectangleM : public Figure
{
public:
	RectangleM() {};
	RectangleM(int xx1, int yy1, int xx2, int yy2):
		Figure(xx1, yy1, xx2, yy2)
	{
		KIND = 0;
	}
	RectangleM(int xx1, int yy1, int xx2, int yy2, int fill, int thin, COLORREF color)
		:Figure(xx1, yy1, xx2, yy2, fill, thin, color)
	{
		KIND = 0;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, objColor); //PS_SOLID קו שלם
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(objColor);
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));
		dc->SelectObject(myBrush);
		dc->Rectangle(x1, y1, x2, y2);
	}
	bool isEx(CPoint p) {
		if (!(p.x<getMinX() || p.x>getMaxX() || p.y< getMinY() || p.y> getMaxY())) // אם הוא בטווח של המלבן
			return 1;
		return 0;

	}
};
class EllipeseM :public Figure
{
public:

	EllipeseM(int xx1, int yy1, int xx2, int yy2) :
		Figure(xx1, yy1, xx2, yy2) 
	{
		KIND = 1;
	}

	EllipeseM(int xx1, int yy1, int xx2, int yy2, int fill, int thin, COLORREF color)
		:Figure(xx1, yy1, xx2, yy2, fill, thin, color)
	{
		KIND = 1;
	}
	void Draw(CDC *dc)
	{
		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, objColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(objColor); //מילוי צבע פנימי
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));
		dc->SelectObject(myBrush);
		dc->Ellipse(x1, y1, x2, y2);
	}
	bool isEx(CPoint p)
	{
		if (p.x>x1 && p.x<x2 && p.y>y1 && p.y<y2)
			return 1;
		return 0;
	}

};

class LineM :public Figure
{
public:
	LineM() {};
	LineM(int xx1, int yy1, int xx2, int yy2) :
		Figure(xx1, yy1, xx2, yy2)
	{
		KIND=2;
	}
	LineM(int xx1, int yy1, int xx2, int yy2, int thin, COLORREF color)
		:Figure(xx1, yy1, xx2, yy2, 0, thin, color)
	{
		KIND=2;
	}

	LineM(int xx1, int yy1, int xx2, int yy2, int fill, int thin, COLORREF color)
		:Figure(xx1, yy1, xx2, yy2, fill, thin, color)

	{
		KIND = 2;
	}

	void Draw(CDC *dc)
	{
		CPen mypen(PS_SOLID, isThin ? 1 : 4, objColor);
		dc->SelectObject(&mypen);
		dc->MoveTo(x1, y1);
		dc->LineTo(x2, y2);
	}

	bool isEx(CPoint p)
	{
		int yy = y1 - y2, xx = x1 - x2;
		double m = (double)yy / (double)xx;

		if ((p.y - y1 - m * (p.x - x1)) > -7 && (p.y - y1 - m * (p.x - x1) < 7) &&
			(!(p.x < getMinX() || p.x > getMaxX() || p.y < getMinY() || p.y > getMaxY())))
			return 1;
		return 0;
	}

};

class TriangleM :public LineM {
public:
	TriangleM() {};
	TriangleM(int xx1, int yy1, int xx2, int yy2)
		:LineM(xx1, yy1, xx2, yy2)
	{
		KIND = 3;
	}
	TriangleM(int xx1, int yy1, int xx2, int yy2, int fill, int thin, COLORREF color)
		:LineM(xx1, yy1, xx2, yy2, fill, thin, color)
	{
		KIND = 3;
	}

	void Draw(CDC *dc)
	{
		CPoint pt[3];
		pt[0].SetPoint(x1, y2);
		pt[1].SetPoint(x2, y2);
		pt[2].SetPoint((x1 + x2) / 2, y1);

		CBrush myBrush;
		CPen myPen(PS_SOLID, isThin ? 1 : 4, objColor);
		dc->SelectObject(&myPen);
		if (isFill)
			myBrush.CreateSolidBrush(objColor);
		else
			myBrush.CreateSolidBrush(RGB(240, 240, 240));
		dc->SelectObject(myBrush);
		dc->Polygon(pt, 3);
	}

	bool isEx(CPoint p) {
		if (!(p.x<getMinX() || p.x>getMaxX() || p.y< getMinY() || p.y> getMaxY())) // אם הוא בטווח של המשולש
			return 1;
		return 0;

	}

};
