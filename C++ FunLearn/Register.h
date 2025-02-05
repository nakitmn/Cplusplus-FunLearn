//---------------------------------------------------------------------------

#ifndef RegisterH
#define RegisterH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
class TRegistration : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *AuthorisationLabel;
	TImage *Icon;
	TLabel *CaptionLabel1;
	TLabeledEdit *LoginEdit;
	TLabeledEdit *PasswordEdit;
	TLabeledEdit *NameEdit;
	TLabeledEdit *LastNameEdit;
	TLabel *CreateLabel;
	TLabel *CaptionLabel2;
	TLabel *ErrorLabel;
	TADOQuery *ADOQuery1;
	TPanel *Panel1;
	TImage *ShowPasImage;
	TLabel *PassLengthError;
	TADOTable *ADOTable1;
	TLabel *LoginError;
	void __fastcall AuthorisationLabelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall NameEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LastNameEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LoginEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall PasswordEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall CreateLabelClick(TObject *Sender);
	void __fastcall CreateLabelMouseEnter(TObject *Sender);
	void __fastcall CreateLabelMouseLeave(TObject *Sender);
	void __fastcall ShowPasImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ShowPasImageMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TRegistration(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRegistration *Registration;
//---------------------------------------------------------------------------
#endif
