//---------------------------------------------------------------------------

#ifndef Level3RoutinesH
#define Level3RoutinesH
//---------------------------------------------------------------------------
const float MAXX = 0.8, MINX = -0.9, MAXY = 0.7, MINY = -0.3;

enum TWordMove { wmTranslateX, wmTranslateY };
class TMovingWord
{
private:
  bool More, xtransfer;
  float minval, maxval, *changing;
public:
  TWordMove WordMove;
  unsigned angle, group;
  float color[3], x, y;
  AnsiString word;
  TMovingWord(AnsiString Word, int Group);
  void ModifyMove(void);
};
//---------------------------------------------------------------------------
void LoadSort(void);
void OnSortTimer(void);
int OnSortMouseDown(int X, int Y);
void LoadSelect(void);
void OnSelectTimer(void);
bool OnSelectMouseDown(int X);
//---------------------------------------------------------------------------
extern int width, height;
//---------------------------------------------------------------------------
#endif
