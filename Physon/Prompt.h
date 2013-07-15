//---------------------------------------------------------------------------

#ifndef PromptH
#define PromptH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TPromptForm : public TForm
{
__published:
  TImage *PromptImage;
private:
public:		
  __fastcall TPromptForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPromptForm *PromptForm;
//---------------------------------------------------------------------------
#endif
