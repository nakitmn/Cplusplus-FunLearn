//---------------------------------------------------------------------------

#ifndef AuthorisationH
#define AuthorisationH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TAuthorization : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *LoginEdit;
	TLabeledEdit *PasswordEdit;
	TImage *Image1;
	TLabel *CaptionLabel;
	TLabel *EnterLabel;
	TLabel *RegistrationLabel;
	TImage *Icon;
	TLabel *Label1;
	TLabel *ErrorLabel;
	TPanel *Panel1;
	TImage *ShowPasImage;
	TADOConnection *ADOConnection1;
	TADOTable *ADOTable1;
	TADOQuery *ADOQuery1;
	void __fastcall RegistrationLabelClick(TObject *Sender);
	void __fastcall LoginEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall RegistrationLabelMouseEnter(TObject *Sender);
	void __fastcall EnterLabelMouseEnter(TObject *Sender);
	void __fastcall ShowPasImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ShowPasImageMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PasswordEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EnterLabelMouseLeave(TObject *Sender);
	void __fastcall EnterLabelClick(TObject *Sender);
	void __fastcall PasswordEditChange(TObject *Sender);
	void __fastcall LoginEditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAuthorization(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAuthorization *Authorization;
//---------------------------------------------------------------------------
#endif
