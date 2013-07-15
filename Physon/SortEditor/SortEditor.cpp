//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", SortEditorForm);
USEFORM("AddProblem.cpp", AddProbForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
    Application->Initialize();
    Application->Title = "Редактор задач";
    String par = ParamStr(0);
    par[4] = 0;
    if (GetDriveType(par.c_str()) != DRIVE_FIXED)
    {
      Application->MessageBox(
        "Программа должна быть запущена с жесткого диска!",
        "Ошибка!", MB_ICONERROR);
      return 0;
    }
    Application->CreateForm(__classid(TSortEditorForm), &SortEditorForm);
    Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
