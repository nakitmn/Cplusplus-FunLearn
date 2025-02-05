//---------------------------------------------------------------------------

#ifndef PupilsMenuH
#define PupilsMenuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.CheckLst.hpp>
//---------------------------------------------------------------------------
class TPupilsFormMenu : public TForm
{
__published:	// IDE-managed Components
	TPanel *NavigationPanel;
	TImage *HideNavigationPanel;
	TLabel *OpenAchieve;
	TLabel *OpenTheory;
	TLabel *BeginLearning;
	TImage *OpenMenuImage;
	TPageControl *PageControl1;
	TTabSheet *WelcomePage;
	TTabSheet *LearnPage;
	TTabSheet *TheoryPage;
	TTabSheet *AchievePage;
	TLabel *Label1;
	TLabel *CaptionLabel;
	TLabel *Label2;
	TTabSheet *FrstKindTest;
	TTabSheet *ScndKindTest;
	TTabSheet *ThrdKindTest;
	TADOTable *ADOTable1;
	TLabel *QLabel;
	TRadioGroup *RadioGroup1;
	TLabel *QLabel3;
	TLabel *QLabel2;
	TLabeledEdit *AnswerEdit;
	TComboBox *ThemeBox;
	TADOQuery *CommonQuery;
	TADOQuery *TestQuery;
	TPanel *Panel1;
	TLabel *NameOfTestLabel;
	TButton *StartTestButton;
	TMemo *TestConteinsMemo;
	TButton *Button1;
	TButton *Button2;
	TTabSheet *EndTestPage;
	TLabel *ResultsLabel;
	TLabel *AmountOfQLabel;
	TLabel *AmountOfRightAnswersLabel;
	TLabel *TimeOfPassingTestLabel;
	TButton *Button3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TTimer *TestTimer;
	TComboBox *TheoryBox;
	TMemo *TextMemo;
	TADOQuery *TheoryQuery;
	TADOQuery *ProgressQuery;
	TLabel *ProgressCaptionLabel;
	TLabel *ProgressTextLabel;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall HideNavigationPanelClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall OpenMenuImageClick(TObject *Sender);
	void __fastcall BeginLearningMouseEnter(TObject *Sender);
	void __fastcall BeginLearningMouseLeave(TObject *Sender);
	void __fastcall OpenTheoryClick(TObject *Sender);
	void __fastcall OpenTheoryMouseEnter(TObject *Sender);
	void __fastcall OpenAchieveMouseEnter(TObject *Sender);
	void __fastcall OpenAchieveMouseLeave(TObject *Sender);
	void __fastcall OpenTheoryMouseLeave(TObject *Sender);
	void __fastcall BeginLearningClick(TObject *Sender);
	void __fastcall ThemeBoxChange(TObject *Sender);
	void __fastcall LearnPageShow(TObject *Sender);
	void __fastcall StartTestButtonClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall AnswerEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall TestTimerTimer(TObject *Sender);
	void __fastcall TheoryBoxChange(TObject *Sender);
	void __fastcall TheoryPageShow(TObject *Sender);
	void __fastcall OpenAchieveClick(TObject *Sender);
	void __fastcall AchievePageShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TPupilsFormMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPupilsFormMenu *PupilsFormMenu;
//---------------------------------------------------------------------------
#endif
