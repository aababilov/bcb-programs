//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainGame.cpp", AdjGameForm);
USEFORM("GermanMsg.cpp", MsgForm);
USEFORM("NewGameDlg.cpp", EndGameForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TAdjGameForm), &AdjGameForm);
     Application->CreateForm(__classid(TMsgForm), &MsgForm);
     Application->CreateForm(__classid(TEndGameForm), &EndGameForm);
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
