//---------------------------------------------------------------------------

#ifndef TeacherMenuH
#define TeacherMenuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TTeacherFormMenu : public TForm
{
__published:	// IDE-managed Components
	TPanel *NavigationPanel;
	TImage *HideNavigationPanel;
	TLabel *EditTheory;
	TLabel *EditTest;
	TLabel *ShowPupils;
	TLabel *TeacherList;
	TLabel *AddTest;
	TPageControl *PageControl1;
	TTabSheet *WelcomePage;
	TTabSheet *PupilsPage;
	TTabSheet *ChangeTestsPage;
	TTabSheet *ChangeTheoryPage;
	TTabSheet *TeachersPage;
	TTabSheet *TestAddPage;
	TImage *OpenMenuImage;
	TLabel *WelcomeLabel;
	TADOQuery *PupilsQuery;
	TStringGrid *PupilsStringGrid;
	TLabel *PupilsListLabel;
	TADOQuery *ProgressQuery;
	TTabSheet *FrstKindTest;
	TTabSheet *ScndKindTest;
	TTabSheet *ThrdKindTest;
	TLabeledEdit *T1QLabeledEdit;
	TLabeledEdit *T1A1LabeledEdit;
	TLabeledEdit *T1A2LabeledEdit;
	TLabeledEdit *T1A3LabeledEdit;
	TLabel *Label1;
	TLabel *T1Label;
	TComboBox *T1ComboBox;
	TLabeledEdit *BeforeLabeledEdit;
	TLabeledEdit *MissLabeledEdit;
	TLabeledEdit *AfterLabeledEdit;
	TLabel *T2Label;
	TLabel *T1Button;
	TLabel *T2Button;
	TLabel *T3Button;
	TLabeledEdit *T3QLabeledEdit;
	TLabeledEdit *T3A1LabeledEdit;
	TLabeledEdit *T3A2LabeledEdit;
	TLabeledEdit *T3A3LabeledEdit;
	TLabel *T3Label;
	TLabel *Label8;
	TCheckBox *T3CB1;
	TCheckBox *T3CB2;
	TCheckBox *T3CB3;
	TLabel *Label2;
	TComboBox *TestBox;
	TADOQuery *TestQuery;
	TPanel *Panel1;
	TLabel *ChangeButton;
	TLabel *DeleteButton;
	TMemo *Memo1;
	TLabel *Label3;
	TLabel *Label4;
	TLabeledEdit *AllQLabeledEdit;
	TLabeledEdit *T1AmountLabeledEdit;
	TLabeledEdit *T2AmountLabeledEdit;
	TLabeledEdit *T3AmountLabeledEdit;
	TLabel *Label5;
	TMemo *AddMemo;
	TLabeledEdit *NameTLabeledEdit;
	TLabel *ErrorLbl1;
	TLabel *ErrorLbl2;
	TLabel *ErrorLbl3;
	TLabel *Label6;
	TStringGrid *TeachersStringGrid;
	TLabel *AddTeacherLabel;
	TPanel *AddTeacherPanel;
	TLabeledEdit *TLoginLabeledEdit;
	TLabeledEdit *TPasswordLabeledEdit;
	TLabeledEdit *TNameLabeledEdit;
	TLabeledEdit *TLastNameLabeledEdit;
	TLabel *ConfirmLabel;
	TADOQuery *TeachersQuery;
	TLabel *WarningLbl;
	TMemo *TxtMemo;
	TComboBox *TheoryBox;
	TPanel *Panel2;
	TLabel *Label7;
	TLabel *ChangeTheoryLabel;
	TLabel *Label9;
	TADOQuery *TheoryQuery;
	TLabel *AddTheory;
	TTabSheet *ChooseAddTestPAge;
	TLabel *Label11;
	TLabel *ImportTestLbl;
	TLabel *CreateTestLbl;
	TTabSheet *ImportTestPage;
	TLabeledEdit *TestNameLabeledEdit;
	TLabel *Label10;
	TLabel *ImportButton;
	TLabel *Label12;
	TMemo *TestBodyMemo;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TLabel *HelloWorld;
	TTabSheet *AddTheoryPage;
	TLabeledEdit *ThemeOfAddTheory;
	TMemo *TheoryMemo;
	TLabel *Label13;
	TLabel *AddTheoryButton;
	TLabel *ErrorLabel;
	TLabel *Label14;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ShowPupilsClick(TObject *Sender);
	void __fastcall PupilsPageShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OpenMenuImageClick(TObject *Sender);
	void __fastcall HideNavigationPanelClick(TObject *Sender);
	void __fastcall ChangeTestsPageEnter(TObject *Sender);
	void __fastcall TestBoxChange(TObject *Sender);
	void __fastcall ChangeButtonClick(TObject *Sender);
	void __fastcall T1ButtonClick(TObject *Sender);
	void __fastcall T2ButtonClick(TObject *Sender);
	void __fastcall T3ButtonClick(TObject *Sender);
	void __fastcall EditTestClick(TObject *Sender);
	void __fastcall AddTestClick(TObject *Sender);
	void __fastcall Label5Click(TObject *Sender);
	void __fastcall TeacherListClick(TObject *Sender);
	void __fastcall AddTeacherLabelClick(TObject *Sender);
	void __fastcall TeachersPageShow(TObject *Sender);
	void __fastcall ConfirmLabelClick(TObject *Sender);
	void __fastcall ChangeTheoryPageShow(TObject *Sender);
	void __fastcall EditTheoryClick(TObject *Sender);
	void __fastcall TheoryBoxChange(TObject *Sender);
	void __fastcall ChangeTheoryLabelClick(TObject *Sender);
	void __fastcall CreateTestLblClick(TObject *Sender);
	void __fastcall ImportTestLblClick(TObject *Sender);
	void __fastcall ImportButtonClick(TObject *Sender);
	void __fastcall Label12Click(TObject *Sender);
	void __fastcall AddTheoryClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);
	void __fastcall AddTheoryButtonClick(TObject *Sender);
	void __fastcall Label9Click(TObject *Sender);
	void __fastcall TheoryMemoChange(TObject *Sender);
	void __fastcall ThemeOfAddTheoryChange(TObject *Sender);
	void __fastcall TestNameLabeledEditChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TTeacherFormMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTeacherFormMenu *TeacherFormMenu;
//---------------------------------------------------------------------------
#endif
