//---------------------------------------------------------------------------

#ifndef UViewH
#define UViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TView : public TForm
{
__published:	// IDE-managed Components
        TImage *RoadView;
        TImage *CarView;
private:	// User declarations
public:		// User declarations
        __fastcall TView(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TView *View;
//---------------------------------------------------------------------------
#endif
