//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TStand : public TForm
{
__published:	// IDE-managed Components
        TSpeedButton *TurnLeft;
        TSpeedButton *TurnRight;
        TSpeedButton *sbtnPause;
        TTimer *Go;
        TSpeedButton *Slower;
        TSpeedButton *Quicker;
        TSpeedButton *TurnBack;
        void __fastcall sbtnPauseClick(TObject *Sender);
        void __fastcall TurnLeftClick(TObject *Sender);
        void __fastcall TurnRightClick(TObject *Sender);
        void __fastcall GoTimer(TObject *Sender);
        void __fastcall SlowerClick(TObject *Sender);
        void __fastcall QuickerClick(TObject *Sender);
        void __fastcall TurnBackClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TStand(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStand *Stand;
//---------------------------------------------------------------------------
#endif
