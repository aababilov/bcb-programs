//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH
//---------------------------------------------------------------------------
#define SecsToTime(secs) (static_cast<double>(secs) / SecsPerDay)
#define TimeToSecs(time) ((time) * SecsPerDay)
#define MSecsToTime(msecs) (static_cast<double>(msecs) / MSecsPerDay)
#define SetMinMax(c1, c2, min, max) \
  if (c1 > c2)                      \
  {                                 \
    max = c1;                       \
    min = c2;                       \
  }                                 \
  else                              \
  {                                 \
    min = c1;                       \
    max = c2;                       \
  }
//---------------------------------------------------------------------------
class TResImage
{
public:
  HBITMAP Bitmap;
  HDC DevCtxt;
  BITMAP prop;
  TResImage(const char *Name);
  ~TResImage();
  void DrawSqr(HDC DC, int X, int Y, int Index) const;
  void Draw(HDC DC, int X, int Y) const;
};
//---------------------------------------------------------------------------
class TMeteorite
{
private:
  int Picture, speed;
public:
  static HDC DevCtxt;
  static TCanvas *BmpCanvas;
  int X, Y;
  TMeteorite(void);
  bool DrawSelf(TMeteorite *from);
  void Clean(void);
};
//---------------------------------------------------------------------------
#ifdef __GL_H__
const GLuint FIRST_SYMB = 31, LAST_SYMB = 255, CHARS_START = 100;
#endif
const TColor clStar = 0x03FFF0;
extern HDC MainDC, PanelDC;
extern HGLRC MainRC, PanelRC;
extern int lost;
//---------------------------------------------------------------------------
void InitListsAndTextures(const HWND HForm, const HWND HPanel);
void CleanupGL(const HWND HForm, const HWND HPanel);
void SetupSuperGame(void);
bool DrawGameName(void);
bool DrawRules(void);
bool DrawFly(void);
bool KeyCheckAndProcess(const WORD Key);
void DrawMaze(void);
int ClickProcess(void);
void ChangeAngle(int Delta);
//---------------------------------------------------------------------------
#endif
