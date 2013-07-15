//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <vector>
#include "Main.h"
#include "Utils.h"
#include "Level3Routines.h"
#include "Game1.h"
#include "Game2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using std::vector;
//---------------------------------------------------------------------------
#define NumCellX(cell) horz_shift + (cell) * (num_w + sign_w)
#define UpdateScore plLeft->Caption = "Очки: " + IntToStr(score)
//---------------------------------------------------------------------------
const char *RULES[4] = {"Вы должны показать быстроту реакции. \
Необходимо защитить корабль от опасных метеоритов, \
несущихся на него. За одну отведённую Вам минуту \
количество сбитых метеоритов должно быть больше \
пропущенных - и тогда Вы получаете 25 баллов.",

"Вы должны показать свои математические способности. \
Перетаскивая карточки с числами при помощи мыши, \
соберите два верных равенства. Каждое правильно \
составленное равенство приносит 20 баллов. Но \
помните, что на размышление у Вас всего 1 минута! \
И что каждую карточку можно использовать только \
один раз.",

"Перед Вами таблица с 16-ю ячейками. \
Вы можете открыть ровно 8 из них. \
За 12-ю ячейками скрываются задачи, правильное \
решение которых может принести Вам сумму, указанную \
на соответствующей ячейке. Ещё в четырёх клетках, \
за знаком \"?\", скрываются три бонуса по +15 баллов \
и одна \"мина\", попав на которую, Вы теряете все \
очки за третий уровень и оканчиваете его.",

"Двигаясь по лабиринту (клавиша W - вперёд, A - прыжок влево, \
S - назад, D - прыжок вправо, движение мышью вправо-влево - поворот), \
необходимо найти 2 ориентира - красный и зелёный шары, за каждым из \
которых скрывается по игре. Разыскав шар, наведите на него прицел \
и щёлкните левой клавишей мыши. За победу в каждой из игр Вы получаете \
50 баллов."};
const double
  LEVEL1_INTERVAL = MSecsToTime(20),
  LEVEL3_INTERVAL = MSecsToTime(90),
  SHOW_INTERVAL = 1e-6,
  LEVEL1_2_LENGTH = SecsToTime(60);
const TCursor crSight = 0x1;
const int pic_h = 60, sign_w = 60, num_w = 70, group1 = 0x10000,
  group2 = 0x20000, nogroup = 0xFFFF;
enum {gs5, gs10, gs20, gsBonus, gsFail, gsQuestion};
const TColor clNumber = clAqua; 
const int eyexl = 86, eyexr = 200 - eyexl, eyey = 28,
  cell_w = 96, cell_h = 96;
const TResImage Cells = "CELLS", PhysonImg = "PHYSON";
//---------------------------------------------------------------------------
TPhysonForm *PhysonForm;
HDC DC;
int level, probnum, score, save_score, sightX, sightY, lost, fight;
double LevelStart;
bool SpacePressed;
enum TTimerEvent {teGName, teRules, teLevel1, teLevel2, teLevel3, teNone}
  TimerEvent = teGName;
vector<TMeteorite> meteorites;
BYTE Nums[2][5];
int between, horz_shift, vert_shift, work_height, points, sel_c, sel_r,
  width, height, clicks;
TImage *NumImgs[8];
struct TGridCell
{
  bool Open;
  BYTE Value;
} GridCells[4][4];
vector<TColor> EyeColors;
TCanvas *eyescanv;
//---------------------------------------------------------------------------
void SetStars(TImage *Img)
{
  int w = Img->Width, h = Img->Height;
  Img->Canvas->Brush->Color = clBlack;
  Img->Canvas->FillRect(Img->Canvas->ClipRect);
  for (int i = 0; i < 200; i++)
    Img->Canvas->Pixels[random(w)][random(h)] = clStar;
}
//---------------------------------------------------------------------------
TColor RandomColor()
{
  const MIN_LIGHT = 0x70;
  return (TColor)RGB(random(0xFF - MIN_LIGHT) + MIN_LIGHT,
    random(0xFF - MIN_LIGHT) + MIN_LIGHT,
    random(0xFF - MIN_LIGHT) + MIN_LIGHT);
}
//---------------------------------------------------------------------------
void SetAtFree(BYTE value)
{
  int r, c;
  do
  {
    r = random(4);
    c = random(4);
  }
  while (GridCells[r][c].Value != 0);
  GridCells[r][c].Value = value;
}
//---------------------------------------------------------------------------
void DrawEyes(void)
{
  for (int i = 7; i > 0; i--)
  {
    eyescanv->Pen->Color = EyeColors[i];
    eyescanv->Ellipse(horz_shift + eyexl - i, vert_shift + eyey - i,
      horz_shift + eyexl + i, vert_shift + eyey + i);
    eyescanv->Ellipse(horz_shift + eyexr - i, vert_shift + eyey - i,
      horz_shift + eyexr + i, vert_shift + eyey + i);
  }
  EyeColors.erase(&EyeColors[0]);
  EyeColors.push_back(RandomColor());
}
//---------------------------------------------------------------------------
__fastcall TPhysonForm::TPhysonForm(TComponent* Owner)
  : TForm(Owner)
{
  randomize();
  Application->OnMessage = &ApplicationMessage;
  InitListsAndTextures(Handle, ThePanel->Handle);
  DEVMODE dm = {0};
  dm.dmSize = sizeof(DEVMODE);
  dm.dmPelsWidth = 640;
  dm.dmPelsHeight = 480;
  dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
  ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
  PostMessageA(Handle, WM_PHTIMER, 0, 0);
}
//---------------------------------------------------------------------------
__fastcall TPhysonForm::~TPhysonForm(void)
{
  CleanupGL(Handle, ThePanel->Handle);
  ReleaseDC(ThePanel->Handle, DC);
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::ApplicationMessage(tagMSG &Msg,
      bool &Handled)
{
  if (Msg.message == WM_KEYDOWN && Msg.wParam == VK_ESCAPE)
  {
    Application->Terminate();
    Handled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::SmplKeyDown(TObject *Sender, WORD &Key,
  TShiftState Shift)
{
  SpacePressed = Key == VK_SPACE;
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::NextLevel(void)
{
  for (int i = 0; i < ControlCount; i++)
    Controls[i]->Visible = false;
  FormImage->Canvas->Brush->Color = clBlack;
  FormImage->Canvas->FillRect(Canvas->ClipRect);
  FormImage->Canvas->Font->Name = "Georgia";
  FormImage->Canvas->Font->Style = TFontStyles();
  FormImage->Canvas->Font->Color = clYellow;
  FormImage->Canvas->Font->Size = 16;
  RECT r = {30, 240, 610, 470};
  DrawText(FormImage->Canvas->Handle, RULES[level], strlen(RULES[level]),
    &r, DT_WORDBREAK | DT_CENTER);
  AnsiString s;
  if (++level < 4) s = "Уровень " + IntToStr(level);
  else s = "Суперигра";
  FormImage->Canvas->Font->Style = TFontStyles()<<fsBold;
  FormImage->Canvas->Font->Color = clAqua;
  FormImage->Canvas->Font->Size = 50;
  r.top = 140;
  DrawText(FormImage->Canvas->Handle, s.c_str(), s.Length(), &r,
    DT_CENTER);
  FormImage->Visible = true;
  SpacePressed = false;
  while (!SpacePressed)
  {
    Application->ProcessMessages();
    if (Application->Terminated) return;
  }
  SpacePressed = false;
  switch (level)
  {
    case 1:
    PrepareLevel1();
    break;
    case 2:
    PrepareLevel2();
    break;
    case 3:
    PrepareLevel3();
    break;
    case 4:
    PrepareSuperGame();
  }
  LevelStart = Now();
}
//---------------------------------------------------------------------------
#define GoodSize(a) (a) > -8 && (a) < 45
void __fastcall TPhysonForm::PanelImageMouseDown1(TObject *Sender,
  TMouseButton Button, TShiftState Shift, int X, int Y)
{
  TColor levCl = PanelImage->Canvas->Pixels[X][Y],
    dcCl = static_cast<TColor>(GetPixel(DC, X, Y));
  if ((levCl == clBlack || levCl == clStar) && dcCl != clBlack &&
    dcCl != clStar)
    for (int i = meteorites.size() - 1; i >= 0; i--)
      if (GoodSize(X - meteorites[i].X) && GoodSize(Y - meteorites[i].Y))
      {
        meteorites[i].Clean();
        meteorites.erase(&meteorites[i]);
        fight++;
        plLeft->Caption = "Сбито: " + IntToStr(fight);
        return;
      }
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::OnLevel1(void)
{
  static int added = 0;
  if (added > 20 && random(5) == 1 && meteorites.size() < 6)
  {
    meteorites.push_back();
    added = 0;
  }
  else if (meteorites.size() == 0)
  {
    for (int i = 0; i < 5; meteorites[i].X = ++i * (PanelImage->Width / 6))
      meteorites.push_back();
    added = 0;
  }
  else added++;
  for (unsigned i = 0; i < meteorites.size();)
    if (meteorites[i].DrawSelf(meteorites.begin()))
      meteorites.erase(&meteorites[i]);
    else i++;
  plRight->Caption = "Пропущено: " + IntToStr(lost);
  SetTimeCaption();
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::SetTimeCaption(void)
{
  DWORD seconds = TimeToSecs(LEVEL1_2_LENGTH + LevelStart - Now());
  plTime->Caption = IntToStr(seconds / 60) + ":" +
    (seconds % 60 > 9 ? "" : "0") + IntToStr(seconds % 60);
  if (seconds == 0) NextLevel();
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::FormImageDragOver(TObject *Sender,
  TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
  Accept = X <= NumCellX(4) - sign_w;
  if (Accept)
  {
    if (Y <= between + pic_h) Y = between;
    else if (Y > work_height - between - 2 * pic_h)
           Y = 4 * between + 3 * pic_h;
         else return;
    X = NumCellX((X - horz_shift) / (num_w + sign_w));
    for (int i = 0; i < 8; i++)
      if (NumImgs[i]->Left == X && NumImgs[i]->Top == Y)
      {
        Accept = false;
        return;
      }
  }
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::FormImageDragDrop(TObject *Sender,
  TObject *Source, int X, int Y)
{
  int Tag = static_cast<TImage*>(Source)->Tag & nogroup;
  if (Y <= between + pic_h)
  {
    Y = between;
    Tag |= group1;
  }
  else if (Y > work_height - between - 2 * pic_h)
  {
    Y = 4 * between + 3 * pic_h;
    Tag |= group2;
  }
  static_cast<TImage*>(Source)->Tag = Tag;
  X = NumCellX((X - horz_shift) / (num_w + sign_w));
  for (int i = 0; i < 8; i++)
    if (NumImgs[i]->Left == X && NumImgs[i]->Top == Y) return;
  static_cast<TImage*>(Source)->Left = X;
  static_cast<TImage*>(Source)->Top = Y;
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::OnLevel3(void)
{
  DrawEyes();
  if (points == 0) return;
  if (points == 20) OnSortTimer();
  else OnSelectTimer();
  SwapBuffers(PanelDC);
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::OnPhTimer(TMessage Msg)
{
  double ProcStart = Now(), Interval;
  switch (TimerEvent)
  {
    case teGName:
    Interval = SHOW_INTERVAL;
    if (DrawGameName() || SpacePressed)
    {
      SpacePressed = false;
      TimerEvent = teRules;
    }
    break;
    case teRules:
    Interval = SHOW_INTERVAL;
    if (DrawRules() || SpacePressed)
    {
      SpacePressed = false;
      wglMakeCurrent(PanelDC, PanelRC);
      NextLevel();
    }
    break;
    case teLevel1:
    Interval = LEVEL1_INTERVAL;
    OnLevel1();
    break;
    case teLevel2:
    SetTimeCaption();
    if (SpacePressed) NextLevel();
    break;
    case teLevel3:
    Interval = LEVEL3_INTERVAL;
    OnLevel3();
    break;
    case teNone:
    return;
  }
  do
    Application->ProcessMessages();
  while (ProcStart + Interval > Now());
  PostMessageA(Handle, WM_PHTIMER, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::PrepareLevel1(void)
{
  Screen->Cursors[crSight] = LoadCursor(HInstance, "SIGHT");
  PanelImage->Cursor = crSight;
  ThePanel->BoundsRect = BoundsRect;
  ThePanel->Height = ThePanel->Height * 0.9;
  PanelImage->BoundsRect = ThePanel->BoundsRect;
  SetStars(PanelImage);
  TResImage board("BOARD");
  board.Draw(PanelImage->Canvas->Handle, 0, PanelImage->Height -
    board.prop.bmHeight);
  sightX = ThePanel->Width / 2;
  sightY = ThePanel->Height * 0.83;
  DC = GetDC(ThePanel->Handle);
  TMeteorite::DevCtxt = DC;
  TMeteorite::BmpCanvas = PanelImage->Picture->Bitmap->Canvas;
  for (int i = 0; i < 4; i++)
  {
    meteorites.push_back();
    meteorites[i].Y = i * 50;
  }
  for (int i = 0; i < ControlCount; i++)
    Controls[i]->Visible = true;
  TimerEvent = teLevel1;
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::PrepareLevel2(void)
{
  Set<BYTE, 0, 20> UsedNumbers;
  BYTE k;
  int y;
  TRect r;
  AnsiString s;
  work_height = Height - 40;
  between = (work_height - pic_h * 4) / 5;
  horz_shift = (640 - 5 * num_w - 4 * sign_w) / 2;
  PanelImage->Cursor = crDefault;
  FormImage->Canvas->Font->Name = "SimSun";
  FormImage->Canvas->Font->Size = 46;
  FormImage->Canvas->Font->Color = clBlue;
  FormImage->Canvas->Font->Style = TFontStyles()<<fsBold;
  SetStars(FormImage);
  for (int i = 0; i < 2; i++)
  {
    y = i ? 4 * between + 3 * pic_h : between;
    FormImage->Canvas->Brush->Color = clNumber;
    for (int j = 0; j < 4; j++)
    {
      do
        k = random(19) + 1;
      while (UsedNumbers.Contains(k));
      UsedNumbers<<k;
      Nums[i][j] = k;
      FormImage->Canvas->FillRect(Rect(NumCellX(j), y,
          NumCellX(j) + num_w, y + pic_h));
    }
    FormImage->Canvas->Brush->Color = clBlack;
    for (int j = 0; j < 3; j++)
      FormImage->Canvas->TextOutA(NumCellX(j) + num_w + 10, y, "+");
    r.Top = y;
    r.Bottom = r.Top + pic_h;
    r.Left = NumCellX(3) + num_w + 10;
    r.Right = r.Left + num_w + sign_w;
    Nums[i][4] = Nums[i][0] + Nums[i][1] + Nums[i][2] + Nums[i][3];
    s = "= " + IntToStr(Nums[i][4]);
    DrawTextA(FormImage->Canvas->Handle, s.c_str(), s.Length(), &r, 0);
  }
  y = 0;
  TCanvas *canvas;
  for (BYTE i = 1; i < 20; i++)
    if (UsedNumbers.Contains(i))
    {
      NumImgs[y] = new TImage(this);
      NumImgs[y]->SetBounds(NumCellX(y % 4), 2 * between + pic_h +
        (y / 4) * (between + pic_h), num_w, pic_h);
      NumImgs[y]->Parent = this;
      canvas = NumImgs[y]->Canvas;
      canvas->Brush->Color = clWhite;
      canvas->FillRect(canvas->ClipRect);
      canvas->Pen->Style = psClear;
      canvas->Brush->Color = clBlue;
      canvas->RoundRect(0, 0, num_w + 1, pic_h + 1, 30, 30);
      canvas->Font->Assign(FormImage->Canvas->Font);
      canvas->Font->Color = clGreen;
      canvas->Brush->Style = bsClear;
      r = canvas->ClipRect;
      s = i;
      DrawTextA(canvas->Handle, s.c_str(), s.Length(), &r, DT_CENTER);
      NumImgs[y]->Transparent = true;
      NumImgs[y]->DragMode = dmAutomatic;
      NumImgs[y++]->Tag = i;
    }
  if (lost < fight) score = 25;
  UpdateScore;
  plLeft->Font->Color = clAqua;
  plLeft->Visible = true;
  plTime->Visible = true;
  FormImage->OnDragDrop = &FormImageDragDrop;
  FormImage->OnDragOver = &FormImageDragOver;
  TimerEvent = teLevel2;
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::PrepareLevel3(void)
{
  int s1 = 0, s2 = 0;
  for (int i = 0; i < 8; i++)
    if (NumImgs[i]->Tag & group1) s1 += NumImgs[i]->Tag & nogroup;
    else if (NumImgs[i]->Tag & group2) s2 += NumImgs[i]->Tag & nogroup;
  if (s1 == Nums[0][4]) score += 20;
  if (s2 == Nums[1][4]) score += 20;
  UpdateScore;
  save_score = score;

  for (int i = 0; i < 8; i++)
    delete NumImgs[i];
  for (int i = 0; i < 9; i++)
    EyeColors.push_back(RandomColor());
  eyescanv = Canvas;
  TimerEvent = teLevel3;
  SetAtFree(gsFail);
  for (int i = 0; i < 3; i++)
    SetAtFree(gsBonus);
  for (BYTE i = gs10; i <= gs20; i++)
    for (int j = 0; j < 4; j++)
      SetAtFree(i);
  ThePanel->SetBounds(28, (Height - cell_h * 4) / 2, cell_w * 4, cell_h * 4);
  PanelImage->Width = cell_w * 4;
  PanelImage->Height = cell_h * 4;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      Cells.DrawSqr(PanelImage->Canvas->Handle, j * cell_w, i * cell_h,
        GridCells[i][j].Value <= gs20 ? GridCells[i][j].Value :
        gsQuestion);
  FormImage->OnDragDrop = NULL;
  FormImage->OnDragOver = NULL;
  SetStars(FormImage);
  horz_shift = 436;
  vert_shift = (480 - 200) / 2;
  DrawSmile(true);
  PanelImage->OnMouseDown = &PanelImageMouseDown3;
  PanelImage->OnMouseMove = &PanelImageMouseMove;
  ThePanel->Visible = true;
  plLeft->Visible = true;
  wglMakeCurrent(PanelDC, PanelRC);
  width = ThePanel->Width;
  height = ThePanel->Height;
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::DrawSmile(bool Happy)
{
  FormImage->Canvas->Pen->Color = TColor(0x6060F0);
  PhysonImg.Draw(FormImage->Canvas->Handle, horz_shift, vert_shift);
  int X1 = 83 + horz_shift, Y1 = vert_shift, X2 = 117 + horz_shift,
    Y2 = vert_shift, X3 = horz_shift, Y3 = vert_shift, X4 = horz_shift;
  if (Happy)
  {
    X4 += 200;
    Y1 += 42 - 12;
    Y2 += 42 + 12;
    Y3 += 58;
  }
  else
  {
    X3 += 200;
    Y1 += 54 + 7;
    Y2 += 54 - 7;
    Y3 += 46;
  }
  for (int  i = 0; i < 4; i++)
    FormImage->Canvas->Arc(X1, Y1 - i, X2, Y2 - i, X3, Y3, X4, Y3);
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::PanelImageMouseDown3(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  sel_c = X / cell_w;
  sel_r = Y / cell_h;
  if (GridCells[sel_r][sel_c].Open) return;
  RECT r = {sel_c * cell_w, sel_r * cell_h,
    (sel_c + 1) * cell_w, (sel_r + 1) * cell_h};
  double FSt = Now();
  switch (GridCells[sel_r][sel_c].Value)
  {
    case gsFail:
    Cells.DrawSqr(PanelImage->Canvas->Handle, sel_c * cell_w,
      sel_r * cell_h, gsFail);
    InvalidateRect(ThePanel->Handle, &r, false);
    score = save_score;
    UpdateScore;
    DrawSmile(false);
    eyescanv = FormImage->Canvas;
    DrawEyes();
    PanelImage->OnMouseDown = NULL;
    do
      Application->ProcessMessages();
    while (FSt + SecsToTime(2) > Now() && !Application->Terminated);
    NextLevel();
    return;
    case gsBonus:
    score += 15;
    Cells.DrawSqr(PanelImage->Canvas->Handle, sel_c * cell_w,
      sel_r * cell_h, gsBonus);
    InvalidateRect(ThePanel->Handle, &r, false);
    DrawSmile(true);
    UpdateScore;
    break;
    case gs20:
    points = 20;
    LoadSort();
    PanelImage->Visible = false;
    break;
    default:
    points = GridCells[sel_r][sel_c].Value == gs5 ? 5 : 10;
    LoadSelect();
    PanelImage->Visible = false;
  }
  GridCells[sel_r][sel_c].Open = true;
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::PanelImageMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  PanelImage->Cursor = GridCells[Y / cell_h][X / cell_w].Open ?
    crDefault : crHandPoint;
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::ThePanelMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  COLORREF clr;
  if (points == 20)
  {
    switch (OnSortMouseDown(X, Y))
    {
      case 0:
      return;
      case 1:
      score += 20;
      UpdateScore;
      clr = clGreen;
      break;
      case 2:
      clr = clRed;
    }
  }
  else
    if (Y < 358) return;
    else
      if (OnSelectMouseDown(X))
      {
        score += points;
        clr = clGreen;
      }
      else clr = clRed;
  DrawSmile(clr == clGreen);
  if (clr == clGreen) UpdateScore;
  HDC bmdc = PanelImage->Canvas->Handle;
  int hs = sel_c * cell_w, vs = sel_r * cell_h;
  for (int i = 1; i < cell_w; i++)
    for (int j = 1; j < cell_h; j++)
      if (GetPixel(bmdc, hs + i, vs + j) == clLtGray)
        SetPixel(bmdc, hs + i, vs + j, clr);
  PanelImage->Visible = true;
  points = 0;
  clicks++;
  if (clicks == 8) NextLevel();
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::FinishGame(void)
{
  OnKeyDown = &SmplKeyDown;
  OnMouseMove = NULL;
  OnClick = NULL;
  AnsiString OutStr = "Вы набрали " + IntToStr(score) + " баллов!\r\n";
  if (score < 40)
    OutStr += "\r\nЖелаем успеха в следующий раз!";
  else
    if (score < 60)
      OutStr += "Поздравляем!\r\nВы - пассажир корабля!";
    else
      if (score < 140)
        OutStr += "Поздравляем!\r\nВы - член экипажа корабля!";
      else
        OutStr += "Поздравляем!\r\nВы - помощник командира корабля!";
  for (int i = 0; i < ControlCount; i++)
    Controls[i]->Visible = false;
  SetStars(FormImage);
  FormImage->Canvas->Font->Name = "Georgia";
  FormImage->Canvas->Font->Size = 26;
  FormImage->Canvas->Font->Color = clAqua;
  FormImage->Canvas->Font->Style = TFontStyles();
  TEXTMETRIC tmetr;
  GetTextMetrics(FormImage->Canvas->Handle, &tmetr);
  RECT r = {20, (480 - (tmetr.tmHeight + tmetr.tmInternalLeading) * 3)/ 2,
    620, 480};
  DrawTextA(FormImage->Canvas->Handle, OutStr.c_str(), OutStr.Length(),
    &r, DT_CENTER);
  FormImage->Visible = true;
  do
    Application->ProcessMessages();
  while (!(SpacePressed || Application->Terminated));
  SpacePressed = false;
  FormImage->Visible = false;
  do
  {
    LevelStart = Now();
    if (DrawFly()) break;
    Application->ProcessMessages();
    while (-LevelStart + Now() < MSecsToTime(10));
  }
  while (!(SpacePressed || Application->Terminated));
  Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::PrepareSuperGame(void)
{
  TimerEvent = teNone;
  for (int i = 0; i < ControlCount; i++)
    Controls[i]->Visible = false;
  ShowCursor(FALSE);
  Mouse->CursorPos = TPoint(640 / 2, 480 / 2);
  OnKeyDown = &MazeKeyDown;
  OnMouseMove = &MazeMouseMove;
  OnClick = &MazeClick;
  SetupSuperGame();
  Repainting();
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::Repainting(void)
{
  DrawMaze();
  static HCURSOR sight = Screen->Cursors[crSight];
  DrawIcon(Canvas->Handle, (640 - 32) / 2, (480 - 32) / 2, sight);
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::MazeKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (KeyCheckAndProcess(Key)) Repainting();
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::MazeMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  static int bX = 640 / 2;
  ChangeAngle(X - bX);
  if (X < 10 || X > 630)
  {
    X = 640 / 2;
    Mouse->CursorPos = TPoint(X, Y);
  }
  bX = X;
  Repainting();
}
//---------------------------------------------------------------------------
void __fastcall TPhysonForm::MazeClick(TObject *Sender)
{
  static int played = 0;
  static TForm *GameForms[3] = {NULL, Game1Form, Game2Form};
  const char *outt[] = {"Вы проиграли!", "Вы выиграли!"};
  TForm *GameForm = GameForms[ClickProcess()];
  if (GameForm)
  {
    ShowCursor(TRUE);
    GameForm->ShowModal();
    Application->MessageBox(outt[GameForm->Tag], "Игра окончена",
      MB_OK | MB_ICONINFORMATION);
    score += GameForm->Tag * 50;
    ShowCursor(FALSE);
    if (++played == 2) FinishGame();
    else Repainting();
  }
}
//---------------------------------------------------------------------------
