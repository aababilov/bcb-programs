//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <cstdio>
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSudokuForm *SudokuForm;
//---------------------------------------------------------------------------
unsigned tbl[81];
/*
 0  1  2 |  3  4  5 |  6  7  8
 9 10 11 | 12 13 14 | 15 16 17
18 19 20 | 21 22 23 | 24 25 26
______________________________
27 28 29 | 30 31 32 | 33 34 35
36 37 38 | 39 40 41 | 42 43 44
45 46 47 | 48 49 50 | 51 52 53
______________________________
54 55 56 | 57 58 59 | 60 61 62
63 64 65 | 66 67 68 | 69 70 71
72 73 74 | 75 76 77 | 78 79 80
*/
unsigned mask;
int groups[9 * 3][9], subset[9], finss, q[81], curq, finq, specI;
TColor specColor, backColor[81];
bool changed;
//---------------------------------------------------------------------------
inline bool in_set(int n, int r, int *g)
{
	static int l, m;
	l = 0;
	do  {
		m = (l + r) >> 1;
		if (g[m] == n) return true;
		else
			if (g[m] > n) r = m - 1;
			else l = m + 1;
	}
	while (l <= r);
	return false;
}
//---------------------------------------------------------------------------
inline int get_one(unsigned i)
{
	for (int n = 0; n < 9; n++)
		if (i & (1 << n)) return n + 1;
	return 0;
}
//---------------------------------------------------------------------------
inline void clear_bit(int i)
{
	if ((tbl[i] & mask) == tbl[i]) return;
	tbl[i] &= mask;
	if (tbl[i])
	{
		if ((tbl[i] & (tbl[i] - 1)) == 0)
		{
			q[++finq] = i;
			backColor[i] = clYellow;
		}
	}
	else backColor[i] = clBlack;
	changed = true;
}
//---------------------------------------------------------------------------
AnsiString IntToGroup(int i)
{
  const AnsiString gtypes[] = {"Square ", "Horiz ", "Vert "};
  return gtypes[i / 9] + i % 9; 
}
//---------------------------------------------------------------------------
__fastcall TSudokuForm::TSudokuForm(TComponent* Owner)
	: TForm(Owner)
{
	int i, cs, rs, r, c;
	for (i = 0; i < 9; i++)
	{
		cs = (i % 3) * 3;
		rs = (i / 3) * 3;
		for (r = 0; r < 3; r++)
			for (c = 0; c < 3; c++)
				groups[i][r * 3 + c] = (rs + r) * 9 + c + cs;
	}
	for (i = 0; i < 9; i++)
		for (cs = 0; cs < 9; cs++)
		{
			groups[9 + i][cs] = i * 9 + cs;
			groups[18 + i][cs] = cs * 9 + i;
		}
	LoadFromFile("3.sdk");
}
//---------------------------------------------------------------------------
void __fastcall TSudokuForm::LoadFromFile(const char *FileName)
{
	using namespace std;
	FILE *file = fopen(FileName, "rt");
	char buf[16];
	if (!file)
		return;
	curq = 0;
	finq = -1;
	for (int r = 0; r < 9; r++)
	{
		fgets(buf, sizeof(buf), file);
		for (int c = 0; c < 9; c++)
		{
			if (buf[c] != '.')
			{
				tbl[r * 9 + c] = 1 << (buf[c] - '1');
				backColor[r * 9 + c] = clWhite;
				q[++finq] = r * 9 + c;
			}
			else
			{
				tbl[r * 9 + c] =  0x1FF;
				backColor[r * 9 + c] = clGray;
			}
		}
	}
	fclose(file);
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TSudokuForm::FormPaint(TObject *Sender)
{
	int W = ClientWidth, w = W / 9, H = ClientHeight, h = H / 9,
		i, j, n;
	Canvas->Pen->Width = 2;
	AnsiString s;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
		{
			Canvas->Brush->Color = backColor[i * 9 + j];
			Canvas->Rectangle(w * j, h * i, w * (j + 1), h * (i + 1));
			if (tbl[i * 9 + j] & (tbl[i * 9 + j] - 1))
				for (n = 1; n <= 9; n++)
				{
					if (tbl[i * 9 + j] & (1 << (n - 1)))
                                                s += char(n + '0');
					else s += ' ';
					if (n % 3) s += ' ';
					else
					{
						Canvas->TextOutA(16 + w * j, h * i + h * (n - 2) / 10, s);
						s = "";
					}
				}
			else
			{
				Canvas->Font->Size = 34;
				Canvas->Font->Color = specI == i * 9 + j ? specColor : clRed;
				Canvas->TextOutA(25 + w * j, 10 + h * i,
						 AnsiString(get_one(tbl[i * 9 + j])));
				Canvas->Font->Size = 10;
				Canvas->Font->Color = clBlack;
				Canvas->Brush->Color = clBtnFace;
			}
		}
	for (i = 0; i < 9; i++)
	{
		Canvas->MoveTo(0, i * h);
		Canvas->LineTo(W, i * h);
		Canvas->MoveTo(i * w, 0);
		Canvas->LineTo(i * w, H);
	}
	Canvas->Pen->Width = 6;
	w *= 3;
	h *= 3;
	for (i = 1; i < 3; i++)
	{
		Canvas->MoveTo(0, i * h);
		Canvas->LineTo(W, i * h);
		Canvas->MoveTo(i * w, 0);
		Canvas->LineTo(i * w, H);
	}  
}
//---------------------------------------------------------------------------
void __fastcall TSudokuForm::miOpenClick(TObject *Sender)
{
  if (OpenDlg->Execute()) LoadFromFile(OpenDlg->FileName.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TSudokuForm::miGoClick(TObject *Sender)
{
	int i, j, g, n, r, c, *gidx[3];
	changed = false;
	for (; curq <= finq; curq++)
	{
		specI = q[curq];
		specColor = clGreen;
		mask = ~tbl[q[curq]];
		r = q[curq] / 9;
		c = q[curq] % 9;
		gidx[0] = groups[r / 3 * 3 + c / 3];
		gidx[1] = groups[9 + r];
		gidx[2] = groups[18 + c];
		for (j = 0; j < 3; j++)
			for (i = 0; i < 9; i++)
				if (gidx[j][i] != q[curq])
					clear_bit(gidx[j][i]);
		if (changed && miByStep->Checked) goto ch;
	}
	for (n = 0; n < 9; n++)
	{
		mask = 1 << n;
		for (g = 0; g < 27; g++)
		{
			finss = -1;
			for (i = 0; i < 9; i++)
				if (tbl[groups[g][i]] & mask)
					subset[++finss] = groups[g][i];
			if (finss == -1)
			{
				for (i = 0; i < 9; i++)
					backColor[groups[g][i]] = clBlack;
				goto ch;
			}
			if (finss == 0)
			{
				if (tbl[subset[0]] & (tbl[subset[0]] - 1))
				{
					changed = true;
					tbl[subset[0]] = mask;
					q[++finq] = subset[0];
					specI = subset[0];
					specColor = clBlue;
					backColor[subset[0]] = static_cast<TColor>(0xBBBBAA);
					if (miByStep->Checked) goto ch;
				}
			}
		}
	}
ch:
	if (changed == false)
		MessageBoxA(NULL, "No more!", "Ready", MB_OK);
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TSudokuForm::miSaveClick(TObject *Sender)
{
        if (!SaveDlg->Execute())
                return;

        using namespace std;
        FILE *file = fopen(SaveDlg->FileName.c_str(), "w+t");
        for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++)
                        fputc(tbl[i * 9 + j] & (tbl[i * 9 + j] - 1)
			      ? '.' : '0' + get_one(tbl[i * 9 + j]), file);
                fputc('\n', file);
        }
        fclose(file);
}
//---------------------------------------------------------------------------
void __fastcall TSudokuForm::miExtgoClick(TObject *Sender)
{
	int i, j, g, n, r, c, *gidx[3];
	changed = false;
	for (; curq <= finq; curq++)
	{
		specI = q[curq];
		specColor = clGreen;
		mask = ~tbl[q[curq]];
		r = q[curq] / 9;
		c = q[curq] % 9;
		gidx[0] = groups[r / 3 * 3 + c / 3];
		gidx[1] = groups[9 + r];
		gidx[2] = groups[18 + c];
		for (j = 0; j < 3; j++)
			for (i = 0; i < 9; i++)
				if (gidx[j][i] != q[curq])
					clear_bit(gidx[j][i]);
		if (changed && miByStep->Checked) goto ch;
	}
	for (n = 0; n < 9; n++) {
		mask = 1 << n;
		for (g = 0; g < 27; g++) {
			finss = -1;
			for (i = 0; i < 9; i++)
				if (tbl[groups[g][i]] & mask)
					subset[++finss] = groups[g][i];
			if (finss == -1) {
				for (i = 0; i < 9; i++)
					backColor[groups[g][i]] = clBlack;
				goto ch;
			}
			if (finss == 0) {
				if (tbl[subset[0]] & (tbl[subset[0]] - 1)) {
					changed = true;
					tbl[subset[0]] = mask;
					q[++finq] = subset[0];
					specI = subset[0];
					specColor = clBlue;
					backColor[subset[0]] = static_cast<TColor>(0xBBBBAA);
					if (miByStep->Checked) goto ch;
				}
			}
			else if (finss < 3) {
				mask = ~mask;
				for (i = 0; i < 27; i++)
					if (i != g) {
						for (j = 0; j <= finss; j++)
							if (!in_set(subset[j], 8, groups[i]))
								goto bed;
						for (j = 0; j < 9; j++)
							if (!in_set(groups[i][j], finss, subset))
								clear_bit(groups[i][j]);
					bed:
					}
				mask = ~mask;
				if (changed && miByStep->Checked) goto ch;
			}
		}
	}
ch:
	if (changed == false)
		MessageBoxA(NULL, "No more!", "Ready", MB_OK);
	Invalidate();
}
//---------------------------------------------------------------------------


void __fastcall TSudokuForm::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if (Button != mbLeft)
                return;
        String s;
        int idx = (X / (ClientWidth / 9))  +
                (Y / (ClientHeight / 9)) * 9;
        unsigned val = tbl[idx];
        for (int i = 0; i < 9; ++i)
                if (val & (1 << i))
                        s += (i + 1);
        s = InputBox("New value", "Numbers", s);
        val = 0;
        for (int i = s.Length(); i >= 1; --i)
                if ('1' <= s[i] && s[i] <= '9')
                        val |= 1 << (s[i] - '1');
        tbl[idx] = val;

        if (val & (val - 1)) {
                for (int i = 0; i <= finq; ++i)
                        if (q[i] == idx)
                                goto bed;
                q[++finq] = idx;
                MessageBoxA(NULL, "added!", "Ready", MB_OK);
        }
        bed:
        Invalidate();
}
//---------------------------------------------------------------------------

