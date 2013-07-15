//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Prompt.h"
//---------------------------------------------------------------------------
USEFORM("Main.cpp", PhysonForm);
USEFORM("Prompt.cpp", PromptForm);
USEFORM("Game1.cpp", Game1Form);
USEFORM("Game2.cpp", Game2Form);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
    Application->Initialize();
    Application->Title = "Физон";
    PromptForm = new TPromptForm(Application);
    PromptForm->Show();
    PromptForm->Update();        
    Application->CreateForm(__classid(TPhysonForm), &PhysonForm);
    Application->CreateForm(__classid(TGame1Form), &Game1Form);
    Application->CreateForm(__classid(TGame2Form), &Game2Form);
    delete PromptForm;
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
