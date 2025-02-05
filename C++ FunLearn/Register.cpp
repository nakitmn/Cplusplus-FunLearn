//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Authorisation.h"
#include "Register.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRegistration *Registration;
//AnsiString showpas="showpas.png";
//AnsiString hidepas="hidepas.png";
//---------------------------------------------------------------------------
__fastcall TRegistration::TRegistration(TComponent* Owner)
	: TForm(Owner)
{
}

bool IsExistAccountWithEnteredLogin(TADOTable* table, TLabeledEdit* a){
	AnsiString entered= a->Text;
	AnsiString temp;
	table->First();
	while(!table->Eof){
		temp=table->FieldByName("Login")->AsAnsiString;
		if(temp==entered)return true;
        table->Next();
	}
	table->First();
    return false;
}

void ShowSomeErrorLabel(TLabel* show,TLabel* hide1,TLabel* hide2){
	show->Visible=true;
	if(hide1->Visible==true)hide1->Visible=false;
    if(hide2->Visible==true)hide2->Visible=false;
}

void OpenAuthorisation(TForm * reg, TForm* auth){
	reg->Close();
	auth->Show();
}

void StartDesign(TLabeledEdit* a  ,TLabeledEdit* b,TLabeledEdit* c,TLabeledEdit* d, TLabel* pas, TLabel* fields){
	a->Text="";
	b->Text="";
	c->Text="";
	d->Text="";
	pas->Visible=false;
	fields->Visible=false;
}

void SetMouseEnterDesign(TLabel * a){
	a->Color=TColor(RGB(80, 22, 91));
}

void SetMouseLeaveDesing(TLabel* a){
	a->Color=TColor(RGB(53, 16, 60));
}

bool IsFieldsFull(TLabeledEdit* a  ,TLabeledEdit* b,TLabeledEdit* c,TLabeledEdit* d){
	if(a->Text!=""&&b->Text!=""&&c->Text!=""&&d->Text!="") return true;
	else return false;
}
//---------------------------------------------------------------------------
void __fastcall TRegistration::AuthorisationLabelClick(TObject *Sender)
{
	OpenAuthorisation(Registration,Authorization);
}
//---------------------------------------------------------------------------
void __fastcall TRegistration::FormClose(TObject *Sender, TCloseAction &Action)
{
	Authorization->Show();
}
//---------------------------------------------------------------------------
void __fastcall TRegistration::NameEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if((Key>='a'&&Key<='z')||(Key>='A'&&Key<='Z')) return;
	if(Key==VK_BACK) return;
	if(Key==VK_RETURN){
		LastNameEdit->SetFocus();
	}
	Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::LastNameEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if((Key>='a'&&Key<='z')||(Key>='A'&&Key<='Z')) return;
	if(Key==VK_BACK) return;
	Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::LoginEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if((Key>='a'&&Key<='z')||(Key>='A'&&Key<='Z')) return;
	if(isdigit(Key))return;
	if(Key==VK_BACK) return;
	if(Key==VK_RETURN){
		PasswordEdit->SetFocus();
	}
	Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::PasswordEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if((Key>='a'&&Key<='z')||(Key>='A'&&Key<='Z')) return;
	if(isdigit(Key))return;
	if(Key==VK_BACK) return;
	if(Key==VK_RETURN){
		NameEdit->SetFocus();
	}
	Key=0;
}
//---------------------------------------------------------------------------
bool AllFieldsFull(TLabeledEdit* a, TLabeledEdit* b, TLabeledEdit* c, TLabeledEdit* d){
	if(a->Text!="" && b->Text!="" && c->Text!="" && d->Text!="") return true;
	else return false;
}

void CreatePupilAccount(TADOQuery* query,TLabeledEdit* a, TLabeledEdit* b, TLabeledEdit* c, TLabeledEdit* d){
	 query->Parameters->ParamByName("RegLog")->Value=a->Text;
	 query->Parameters->ParamByName("RegPas")->Value=b->Text;
	 query->Parameters->ParamByName("RegName")->Value=c->Text;
	 query->Parameters->ParamByName("RegLstname")->Value=d->Text;
	 query->ExecSQL();
	 ShowMessage("������� ������� ������!");
}

void __fastcall TRegistration::CreateLabelClick(TObject *Sender)
{
	if(AllFieldsFull(LoginEdit,PasswordEdit,NameEdit,LastNameEdit)){
        ErrorLabel->Visible=false;
		if(PasswordEdit->Text.Length()>=8){
			if(IsExistAccountWithEnteredLogin(ADOTable1,LoginEdit)==false){
				LoginError->Visible=false;
				CreatePupilAccount(ADOQuery1,LoginEdit,PasswordEdit,NameEdit,LastNameEdit);
				Registration->Close();
				Authorization->LoginEdit->Text=LoginEdit->Text;
				Authorization->PasswordEdit->SetFocus();
				Authorization->ADOTable1->Active=false;
                Authorization->ADOTable1->Active=true;
			}
			else ShowSomeErrorLabel(LoginError,PassLengthError,ErrorLabel);
		}
		else ShowSomeErrorLabel(PassLengthError,ErrorLabel,LoginError);
	}
	else{
		ShowSomeErrorLabel(ErrorLabel,PassLengthError,LoginError);
	}
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::CreateLabelMouseEnter(TObject *Sender)
{
	if(IsFieldsFull(LoginEdit,PasswordEdit,NameEdit,LastNameEdit))
		SetMouseEnterDesign(CreateLabel);
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::CreateLabelMouseLeave(TObject *Sender)
{
	SetMouseLeaveDesing(CreateLabel);
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::ShowPasImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ShowPasImage->Picture->LoadFromFile("showpas.png");
	PasswordEdit->PasswordChar= 0;
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::ShowPasImageMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ShowPasImage->Picture->LoadFromFile("hidepas.png");
	PasswordEdit->PasswordChar='*';
}
//---------------------------------------------------------------------------

void __fastcall TRegistration::FormActivate(TObject *Sender)
{
	StartDesign(LoginEdit,PasswordEdit,NameEdit,LastNameEdit,PassLengthError,ErrorLabel);
}
//---------------------------------------------------------------------------

