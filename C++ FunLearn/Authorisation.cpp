//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Authorisation.h"
#include "PupilsMenu.h"
#include "Register.h"
#include "TeacherMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAuthorization *Authorization;
//---------------------------------------------------------------------------
__fastcall TAuthorization::TAuthorization(TComponent* Owner)
	: TForm(Owner)
{
}

void OpenAnotherForm(TForm * auth, TForm* reg){
	auth->Hide();
    reg->Show();
}

void banOnSomeSymbols(System::WideChar &Key){
    if((Key>='a'&&Key<='z')||(Key>='A'&&Key<='Z')) return;
	if(isdigit(Key))return;
	if(Key==VK_BACK) return;
	Key=0;
}

void SetMouseEnterDesign(TLabel * a){
	a->Color=TColor(RGB(80, 22, 91));
}

void SetMouseLeaveDesing(TLabel* a){
	a->Color=TColor(RGB(53, 16, 60));
}

bool IsAccountExist(TADOTable* ADOTable1,TLabeledEdit* LoginEdit, TLabeledEdit* PasswordEdit){
	ADOTable1->Active=false;
	ADOTable1->Active=true;
	ADOTable1->First();
	AnsiString entLog=LoginEdit->Text;
	AnsiString entPas=PasswordEdit->Text;
	AnsiString log, pas;
	while(!ADOTable1->Eof){
	   log=ADOTable1->FieldByName("Login")->AsAnsiString;
	   pas=ADOTable1->FieldByName("Password")->AsAnsiString;
	   if(entLog==log&&entPas==pas) return true;
	   ADOTable1->Next();
	}
    return false;
}

bool IsTeacherAccount(TADOQuery* query,TLabeledEdit* LoginEdit, TLabeledEdit* PasswordEdit){
	query->SQL->Text="SELECT * FROM `Teachersprofiles` WHERE `TLogin`= :log AND `TPassword` = :pas";
	query->Parameters->ParamByName("log")->Value=LoginEdit->Text;
	query->Parameters->ParamByName("pas")->Value=PasswordEdit->Text;
	query->Active=true;
	if(query->IsEmpty()==false)return true;
    else return false;
}
//---------------------------------------------------------------------------
void __fastcall TAuthorization::RegistrationLabelClick(TObject *Sender)
{
	OpenAnotherForm(Authorization,Registration);
}
//---------------------------------------------------------------------------

void __fastcall TAuthorization::LoginEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key==VK_RETURN&&LoginEdit->Text!=""){
		PasswordEdit->SetFocus();
	}
	banOnSomeSymbols(Key);
}
//---------------------------------------------------------------------------

void __fastcall TAuthorization::RegistrationLabelMouseEnter(TObject *Sender)
{
	 SetMouseEnterDesign(RegistrationLabel);
}
//---------------------------------------------------------------------------

void __fastcall TAuthorization::EnterLabelMouseEnter(TObject *Sender)
{
	if(LoginEdit->Text!=""&&PasswordEdit->Text!="")
		SetMouseEnterDesign(EnterLabel);
}
//---------------------------------------------------------------------------


void __fastcall TAuthorization::ShowPasImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ShowPasImage->Picture->LoadFromFile("showpas.png");
	PasswordEdit->PasswordChar= 0;
}
//---------------------------------------------------------------------------

void __fastcall TAuthorization::ShowPasImageMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
		ShowPasImage->Picture->LoadFromFile("hidepas.png");
		PasswordEdit->PasswordChar='*';
}
//---------------------------------------------------------------------------


void __fastcall TAuthorization::PasswordEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	banOnSomeSymbols(Key);
	if(IsAccountExist(ADOTable1,LoginEdit,PasswordEdit)){
		 OpenAnotherForm(Authorization, PupilsFormMenu);
	}
	else{
		if(IsTeacherAccount(ADOQuery1,LoginEdit,PasswordEdit)) OpenAnotherForm(Authorization, TeacherFormMenu);
		else ErrorLabel->Visible=true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TAuthorization::EnterLabelMouseLeave(TObject *Sender)
{
    SetMouseLeaveDesing(EnterLabel);
}
//---------------------------------------------------------------------------


void __fastcall TAuthorization::EnterLabelClick(TObject *Sender)
{
	if(IsAccountExist(ADOTable1,LoginEdit,PasswordEdit)){
		 OpenAnotherForm(Authorization, PupilsFormMenu);
	}
	else{
		if(IsTeacherAccount(ADOQuery1,LoginEdit,PasswordEdit)) OpenAnotherForm(Authorization, TeacherFormMenu);
		else ErrorLabel->Visible=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TAuthorization::PasswordEditChange(TObject *Sender)
{
	if(ErrorLabel->Visible==true)ErrorLabel->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TAuthorization::LoginEditChange(TObject *Sender)
{
    if(ErrorLabel->Visible==true)ErrorLabel->Visible=false;
}
//---------------------------------------------------------------------------





