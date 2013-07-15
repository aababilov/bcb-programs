//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("NonZeros.cpp", NonZerosForm);
USEFORM("StudEditor.cpp", StudEditorForm);
USEFORM("IntervalEditor.cpp", IntervalFrame); /* TFrame: File Type */
USEFORM("AboutBAR.cpp", AboutForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->Title = "AV BAR";
     Application->CreateForm(__classid(TMainForm), &MainForm);
     Application->CreateForm(__classid(TNonZerosForm), &NonZerosForm);
     Application->CreateForm(__classid(TAboutForm), &AboutForm);
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
