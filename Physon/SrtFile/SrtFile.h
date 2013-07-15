//---------------------------------------------------------------------------

#ifndef SrtFileH
#define SrtFileH
//---------------------------------------------------------------------------
class TSortFile
{
private:
  TMemoryStream *ms;
public:
  TStringList *GroupWords[3];
  String GroupNames[3];
  TSortFile(void);
  ~TSortFile(void);
  void LoadFromFile(const AnsiString FileName);
  void SaveToFile(const AnsiString FileName);
};
//---------------------------------------------------------------------------
extern TSortFile SortFile;
//---------------------------------------------------------------------------
#endif
