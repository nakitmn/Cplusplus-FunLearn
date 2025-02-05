//---------------------------------------------------------------------------

#include <vcl.h>
#include <set>
#include <vector>
#pragma hdrstop

#include "TeacherMenu.h"
#include "Authorisation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTeacherFormMenu *TeacherFormMenu;
AnsiString txtname;
bool adding=false;
bool editingTheory=false;
//---------------------------------------------------------------------------
	/*������
	� ��������� ����� ��� �������� �� ������ �������, � ����� ����������� �� ����������� ���� � COMBOBOX
	*/
//---------------------------------------------------------------------------
__fastcall TTeacherFormMenu::TTeacherFormMenu(TComponent* Owner)
	: TForm(Owner)
{
}

//��������� ����� � ����� ��������� ������
struct Test1{
	AnsiString question;
	std::vector<AnsiString> answers;
	AnsiString rightAnswer;
};

//��������� ����� � ������ ������������ ���������
struct Test2{
	AnsiString beforeMiss;
	AnsiString miss;
	AnsiString afterMiss;
};

//��������� ����� � ������������� ��������� �������
struct Test3{
	AnsiString question;
	std::vector<AnsiString> answers;
	std::vector<AnsiString> rightAnswer;
};

std::vector<Test1> test1;
std::vector<Test2> test2;
std::vector<Test3> test3;

class changeTest{
	private:
	int AllQ,AmountT1,AmountT2,AmountT3;
	int currentQ1,currentQ2,currentQ3;
	std::set<int> changedQ1;
	std::set<int> changedQ2;
    std::set<int> changedQ3;
	public:
		changeTest(){
			AllQ=AmountT1=AmountT2=AmountT3=0;
			currentQ1=currentQ2=currentQ3=-1;
			changedQ1.clear();
			changedQ2.clear();
			changedQ3.clear();
		}
		changeTest(int a){
         	AllQ=AmountT1=AmountT2=AmountT3=0;
			currentQ1=currentQ2=currentQ3=-1;
			changedQ1.clear();
			changedQ2.clear();
			changedQ3.clear();
		}
		void loadTest(std::vector<Test1>& test1, std::vector<Test2>& test2, std::vector<Test3>& test3, TMemo* memo){
			memo->Lines->Clear();
			memo->Lines->LoadFromFile("Tests\\"+txtname+".txt",TEncoding::UTF8);
			test1.clear();
			test2.clear();
            test3.clear();
			int j;
			for(j=0;j<memo->Lines->Count;j++){
				if(memo->Lines->Strings[j]== "first"||memo->Lines->Strings[j]== "second"||memo->Lines->Strings[j]== "third") AllQ++;
			}
			j=0;
			for(int i=0;i<AllQ;i++){

				if(memo->Lines->Strings[j]== "first"){  // ���� ������ ������� ����, �� ���������� ��� ���������� � ��������� test
					Test1 add;
					j++; //������� �� ��������� ������
					add.question=memo->Lines->Strings[j];  // � ���� question ���������� ������ �� Memo1
					j++;
					for(int k=0;k<3;k++){   // ���������� ���� �������� ������
						add.answers.push_back(memo->Lines->Strings[j]);
						j++;
					}

					add.rightAnswer=memo->Lines->Strings[j];  // ���������� ������ ����������� ������
					j++;
					j++;
					AmountT1++;
					test1.push_back(add);
				}
				else{
				if( memo->Lines->Strings[j]=="second"){    // ���� ������ ������� ����, �� ���������� ��� ���������� � ��������� test2
					Test2 add2;
					j++;
					add2.beforeMiss=memo->Lines->Strings[j];
					j++;
					add2.miss=memo->Lines->Strings[j];
					j++;
					add2.afterMiss=memo->Lines->Strings[j];
					j++;
					j++;
					AmountT2++;
					test2.push_back(add2);
				}
				else
				{
					if (memo->Lines->Strings[j]=="third"){
					Test3 add3;
					j++;
					int rightA= StrToInt(memo->Lines->Strings[j]);
					j++;
					add3.question= memo->Lines->Strings[j];
					j++;
					for(int k=0;k<3;k++){
						add3.answers.push_back(memo->Lines->Strings[j]);
						j++;
					}
					for(int k=0;k<rightA;k++){
						add3.rightAnswer.push_back(memo->Lines->Strings[j]);
						j++;
					}
					j++;
					AmountT3++;
					test3.push_back(add3);
					}
					else return;
					}
				}

			}
		}

		void showQ1(TPageControl* pc,TTabSheet* ts,TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TComboBox* rightans){
			pc->ActivePage=ts;
			currentQ1++;
			changedQ1.insert(currentQ1);
			question->Text=test1[currentQ1].question;
			ans1->Text=test1[currentQ1].answers[0];
			ans2->Text=test1[currentQ1].answers[1];
			ans3->Text=test1[currentQ1].answers[2];
            rightans->Clear();
			rightans->Items->Add("����� 1");
			rightans->Items->Add("����� 2");
			rightans->Items->Add("����� 3");
			if(ans1->Text==test1[currentQ1].rightAnswer){ rightans->Text="����� 1";
			rightans->ItemIndex=0;
			}
			if(ans2->Text==test1[currentQ1].rightAnswer){rightans->Text="����� 2";
			rightans->ItemIndex=1;
			}
			if(ans3->Text==test1[currentQ1].rightAnswer){ rightans->Text="����� 3";
            rightans->ItemIndex=2;
			}
		}

		void showQ2(TPageControl* pc,TTabSheet* ts,TLabeledEdit* beforeMiss,TLabeledEdit* miss,TLabeledEdit* afterMiss){
			pc->ActivePage=ts;
			currentQ2++;
			changedQ2.insert(currentQ2);
			beforeMiss->Text=test2[currentQ2].beforeMiss;
			miss->Text=test2[currentQ2].miss;
			afterMiss->Text=test2[currentQ2].afterMiss;
		}

		void showQ3(TPageControl* pc,TTabSheet* ts,TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			pc->ActivePage=ts;
			currentQ3++;
			changedQ3.insert(currentQ3);
			question->Text=test3[currentQ3].question;
			ans1->Text=test3[currentQ3].answers[0];
			ans2->Text=test3[currentQ3].answers[1];
			ans3->Text=test3[currentQ3].answers[2];
			cb1->Caption="����� 1";
			cb2->Caption="����� 2";
			cb3->Caption="����� 3";
			if(ans1->Text==test3[currentQ3].rightAnswer[0]||ans1->Text==test3[currentQ3].rightAnswer[1]||ans1->Text==test3[currentQ3].rightAnswer[2]) cb1->Checked=true;
			if(ans2->Text==test3[currentQ3].rightAnswer[0]||ans2->Text==test3[currentQ3].rightAnswer[1]||ans2->Text==test3[currentQ3].rightAnswer[2]) cb2->Checked=true;
			if(ans3->Text==test3[currentQ3].rightAnswer[0]||ans3->Text==test3[currentQ3].rightAnswer[1]||ans3->Text==test3[currentQ3].rightAnswer[2]) cb3->Checked=true;
		}

		void endChange(TMemo* memo){
				try{
					memo->Clear();
					for(int i=0;i<test1.size();i++){
						memo->Lines->Add("first");
						memo->Lines->Add(test1[i].question);
						memo->Lines->Add(test1[i].answers[0]);
						memo->Lines->Add(test1[i].answers[1]);
						memo->Lines->Add(test1[i].answers[2]);
						memo->Lines->Add(test1[i].rightAnswer);
						memo->Lines->Add("");
					}
					for(int i=0;i<test2.size();i++){
						memo->Lines->Add("second");
						memo->Lines->Add(test2[i].beforeMiss);
						memo->Lines->Add(test2[i].miss);
						memo->Lines->Add(test2[i].afterMiss);
						memo->Lines->Add("");
					}
					for(int i=0;i<test3.size();i++){
						memo->Lines->Add("third");
						memo->Lines->Add(test3[i].rightAnswer.size());
						memo->Lines->Add(test3[i].question);
						memo->Lines->Add(test3[i].answers[0]);
						memo->Lines->Add(test3[i].answers[1]);
						memo->Lines->Add(test3[i].answers[2]);
						for(int j=0;j<test3[i].rightAnswer.size();j++){
							memo->Lines->Add(test3[i].rightAnswer[j]);
						}
						memo->Lines->Add("");
					}
					memo->Lines->SaveToFile("Tests\\"+txtname+".txt",TEncoding::UTF8);
					ShowMessage("���� ������� �������");
					}
					catch(...){
                        ShowMessage("���... ��������� �� ���� �������, ���-�� ����� �� ���");
					}
					AllQ=AmountT1=AmountT2=AmountT3=0;
					currentQ1=currentQ2=currentQ3=-1;
					changedQ1.clear();
					changedQ2.clear();
					changedQ3.clear();
					}


		void leaveChange(TMemo* memo){
			memo->Clear();
			AllQ=AmountT1=AmountT2=AmountT3=0;
					currentQ1=currentQ2=currentQ3=-1;
					changedQ1.clear();
					changedQ2.clear();
					changedQ3.clear();
		}

		void NextQ(TMemo* memo,TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TTabSheet* ts4,TLabeledEdit* T1question,TLabeledEdit* T1ans1,TLabeledEdit* T1ans2,TLabeledEdit* T1ans3,TComboBox* T1rightans,TLabeledEdit* beforeMiss,TLabeledEdit* miss,TLabeledEdit* afterMiss,TLabeledEdit* T3question,TLabeledEdit* T3ans1,TLabeledEdit* T3ans2,TLabeledEdit* T3ans3,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			if (changedQ1.size()!=AmountT1) {
				showQ1(pc,ts1,T1question,T1ans1,T1ans2,T1ans3,T1rightans);
			}
			else{
				if (changedQ2.size()!=AmountT2) {
					showQ2(pc,ts2,beforeMiss,miss,afterMiss);
				}
				else
					if (changedQ3.size()!=AmountT3) {
						showQ3(pc,ts3,T3question,T3ans1,T3ans2,T3ans3,cb1,cb2,cb3);
					}
					else {
					  endChange(memo);
                      pc->ActivePage=ts4;
					}
			}
		}

		void applyQ1(TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TComboBox* rightans){
			test1[currentQ1].question=question->Text;
			test1[currentQ1].answers[0]=ans1->Text;
			test1[currentQ1].answers[1]=ans2->Text;
			test1[currentQ1].answers[2]=ans3->Text;
			if(rightans->ItemIndex==0)
			test1[currentQ1].rightAnswer=ans1->Text;
			if(rightans->ItemIndex==1)
			test1[currentQ1].rightAnswer=ans2->Text;
			if(rightans->ItemIndex==2)
			test1[currentQ1].rightAnswer=ans3->Text;
		}
		void applyQ2(TLabeledEdit* beforeMiss,TLabeledEdit* miss,TLabeledEdit* afterMiss){
			test2[currentQ2].beforeMiss=beforeMiss->Text;
			test2[currentQ2].miss=miss->Text;
			test2[currentQ2].afterMiss=afterMiss->Text;
		}
		void applyQ3(TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			test3[currentQ3].question=question->Text;
			test3[currentQ3].answers[0]=ans1->Text;
			test3[currentQ3].answers[1]=ans2->Text;
			test3[currentQ3].answers[2]=ans3->Text;
			test3[currentQ3].rightAnswer.clear();
			if(cb1->Checked) test3[currentQ3].rightAnswer.push_back(ans1->Text);
			if(cb2->Checked) test3[currentQ3].rightAnswer.push_back(ans2->Text);
			if(cb3->Checked) test3[currentQ3].rightAnswer.push_back(ans3->Text);
		}
};

class AddTest{
	private:
		int amountt1,amountt2,amountt3;
		int allq;
		int count1,count2,count3;
	public:
		AddTest(){
			allq=amountt1=amountt2=amountt3=0;
			count1=count2=count3=0;
		}

		void getAmount(int questions,int q1,int q2,int q3){
			allq=questions;
			amountt1=q1;
			amountt2=q2;
			amountt3=q3;
		}

		void NextAddQ(TLabeledEdit* testname,TADOQuery* query,TMemo* memo,TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TTabSheet* ts4,TLabeledEdit* T1question,TLabeledEdit* T1ans1,TLabeledEdit* T1ans2,TLabeledEdit* T1ans3,TComboBox* T1rightans,TLabeledEdit* beforeMiss,TLabeledEdit* miss,TLabeledEdit* afterMiss,TLabeledEdit* T3question,TLabeledEdit* T3ans1,TLabeledEdit* T3ans2,TLabeledEdit* T3ans3,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			if(count1!=amountt1)
				showq1(pc,ts1,T1question,T1ans1,T1ans2,T1ans3,T1rightans);
			else{
				if(count2!=amountt2) showq2(pc,ts2,beforeMiss,miss,afterMiss);
				else{
					if(count3!=amountt3) showq3(pc,ts3,T3question,T3ans1,T3ans2,T3ans3,cb1,cb2,cb3);
					else{
						try{
						query->Active=false;
						query->SQL->Text="SELECT * FROM `Tests`";
						query->Active=true;
						query->Insert();
						query->FieldByName("TestName")->Value=testname->Text;
						query->Post();
						txtname=query->FieldByName("TestID")->AsAnsiString;
						memo->Lines->SaveToFile("Tests\\"+txtname+".txt",TEncoding::UTF8);
						query->Active=false;
                        testname->Clear();
						ShowMessage("���� ������� ��������.");
						}
						catch(...) {
							ShowMessage("���... ���-�� ����� �� ���. ���� �� ��� ��������.");
						}
						allq=0;
						amountt1=0;
						amountt2=0;
						amountt3=0;
						count1=count2=count3=0;
                        memo->Lines->Clear();
						adding=false;
						pc->ActivePage=ts4;
					}
                }
            }
		}

		void showq1(TPageControl* pc,TTabSheet* ts,TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TComboBox* rightans){
			pc->ActivePage=ts;
			count1++;
			//changedQ1.insert(currentQ1);
			question->Text="";
			ans1->Text="";
			ans2->Text="";
			ans3->Text="";
            rightans->Clear();
			rightans->Items->Add("����� 1");
			rightans->Items->Add("����� 2");
			rightans->Items->Add("����� 3");
		}

		void showq2(TPageControl* pc,TTabSheet* ts,TLabeledEdit* beforeMiss,TLabeledEdit* miss,TLabeledEdit* afterMiss){
			pc->ActivePage=ts;
			count2++;
			//changedQ2.insert(currentQ2);
			beforeMiss->Text="";
			miss->Text="";
			afterMiss->Text="";
		}

		void showq3(TPageControl* pc,TTabSheet* ts,TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			pc->ActivePage=ts;
			count3++;
			//changedQ3.insert(currentQ3);
			question->Text="";
			ans1->Text="";
			ans2->Text="";
			ans3->Text="";
			cb1->Caption="����� 1";
			cb2->Caption="����� 2";
			cb3->Caption="����� 3";
		}

		void applyq1(TMemo* memo,TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TComboBox* rightans){
            memo->Lines->Add("first");
			memo->Lines->Add(question->Text);
			memo->Lines->Add(ans1->Text);
			memo->Lines->Add(ans2->Text);
			memo->Lines->Add(ans3->Text);
			if(rightans->ItemIndex==0) memo->Lines->Add(ans1->Text);
			if(rightans->ItemIndex==1) memo->Lines->Add(ans2->Text);
			if(rightans->ItemIndex==2) memo->Lines->Add(ans3->Text);
			memo->Lines->Add("");
		}
		void applyq2(TMemo* memo,TLabeledEdit* beforeMiss,TLabeledEdit* miss,TLabeledEdit* afterMiss){
			memo->Lines->Add("second");
			memo->Lines->Add(beforeMiss->Text);
			memo->Lines->Add(miss->Text);
			memo->Lines->Add(afterMiss->Text);
			memo->Lines->Add("");
		}
		void applyq3(TMemo* memo,TLabeledEdit* question,TLabeledEdit* ans1,TLabeledEdit* ans2,TLabeledEdit* ans3,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			memo->Lines->Add("third");
			int right=0;
			if(cb1->Checked)right++;
			if(cb2->Checked)right++;
			if(cb3->Checked)right++;
			memo->Lines->Add(right);
			memo->Lines->Add(question->Text);
			memo->Lines->Add(ans1->Text);
			memo->Lines->Add(ans2->Text);
			memo->Lines->Add(ans3->Text);
			if(cb1->Checked) memo->Lines->Add(ans1->Text);
			if(cb2->Checked) memo->Lines->Add(ans2->Text);
            if(cb3->Checked) memo->Lines->Add(ans3->Text);
			memo->Lines->Add("");
		}
};

changeTest path;
AddTest Roockie;

//---------------------------------------------------------------------------
//-------------------------- CUSTOM FUNCTIONS -------------------------------
//---------------------------------------------------------------------------

//�������� ���� Label(��� ��������� �������)
void setDesignOnEnterMouse(TLabel* a){
	a->Color=TColor(RGB(17, 84, 102));
}

//�������� ���� Label(��� ��������� �������)
void setDesignOnLeaveMouse(TLabel* a){
	a->Color=TColor(RGB(35,10,40));
}

//������� ����
void beginDesignForNavigationPanel(TPanel* a, TImage* b,TPageControl* PageControl1){
	a->Visible=false;
	b->Visible=true;
	PageControl1->Margins->Left=50;
}

//�������� ����
void openedDesignForNavigationMenu(TPanel* a, TImage* b, TPageControl* PageControl1){
	a->Visible=true;
	b->Visible=false;
    PageControl1->Margins->Left=0;
}

bool IsTheoryExist(TADOQuery* TheoryQuery,TLabeledEdit* a){
	 TheoryQuery->Active=false;
	 TheoryQuery->SQL->Text="SELECT * FROM `Theory` WHERE `ThName`="+QuotedStr(a->Text);
	 TheoryQuery->Active=true;
	 if(TheoryQuery->IsEmpty()){
		TheoryQuery->Active=false;
		return false;
	 }
	 else {
		 TheoryQuery->Active=false;
         return true;
     }
}

void leaveFromTheoryEdit(TMemo* TxtMemo,TLabel* ChangeTheoryLabel){
	if(editingTheory){
		if(MessageDlg("��������� ���������?",mtInformation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes){
		editingTheory=false;
		TxtMemo->Lines->SaveToFile("Theory\\"+txtname+".txt", TEncoding::UTF8);
		TxtMemo->ReadOnly=true;
		ChangeTheoryLabel->Caption="��������";
		}
		else{
			TxtMemo->ReadOnly=true;
			TxtMemo->Lines->LoadFromFile("Theory\\"+txtname+".txt",TEncoding::UTF8);
			editingTheory=false;
            ChangeTheoryLabel->Caption="��������";
        }
	}
}

void loadThemeIntoCombo(TADOQuery* TestQuery, TComboBox* TestBox){
	TestQuery->Active=false;
    TestQuery->SQL->Text="SELECT * FROM `Tests`";
	TestQuery->Active=true;
	TestBox->Items->Clear();
	TestQuery->First();
	while(!TestQuery->Eof){
		TestBox->Items->Add(TestQuery->Fields->FieldByName("TestName")->AsString);
		TestQuery->Next();
	}
    TestQuery->Active=false;
}

bool IsPupilAccountExist(TADOQuery* query,TLabeledEdit* EnteredLog){
	query->Active=false;
	query->SQL->Text="SELECT * FROM `Pupilsprofiles` WHERE `Login` ="+QuotedStr(EnteredLog->Text);
	//query->Parameters->ParamByName("entLog")->Value= EnteredLog->Text;
	query->Active=true;
	if(query->IsEmpty())return false;
	else return true;
}

bool IsTeacherAccountExist(TADOQuery* query,TLabeledEdit* LoginEdit){
	query->Active=false;
	query->SQL->Text="SELECT * FROM `Teachersprofiles` WHERE `TLogin`="+QuotedStr(LoginEdit->Text);
   //	query->Parameters->ParamByName("log")->Value=LoginEdit->Text;
	query->Active=true;
	if(query->IsEmpty())return false;
	else return true;
}

void loadTheoryIntoCombo(TADOQuery* TheoryQuery, TComboBox* TheoryBox){
	TheoryQuery->Active=false;
	TheoryQuery->SQL->Text="SELECT * FROM `Theory`";
	TheoryQuery->Active=true;
	TheoryBox->Items->Clear();
	TheoryQuery->First();
	while(!TheoryQuery->Eof){
		TheoryBox->Items->Add(TheoryQuery->Fields->FieldByName("ThName")->AsString);
		TheoryQuery->Next();
	}
	TheoryQuery->Active=false;
}

bool IsExistTest(TADOQuery* query,TLabeledEdit* EnteredName){
	query->Active=false;
	query->SQL->Text="SELECT * FROM `Tests` WHERE `TestName` ="+QuotedStr(EnteredName->Text);
	//query->Parameters->ParamByName("entLog")->Value= EnteredLog->Text;
	query->Active=true;
	if(query->IsEmpty())return false;
	else return true;
}
//---------------------------------------------------------------------------
//-------------------------- COMPONENTS -------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTeacherFormMenu::FormActivate(TObject *Sender)
{
	beginDesignForNavigationPanel(NavigationPanel,OpenMenuImage,PageControl1);
	WelcomeLabel->Caption=WelcomeLabel->Caption + Authorization->LoginEdit->Text;
	PageControl1->ActivePage=WelcomePage;
}
//---------------------------------------------------------------------------
void __fastcall TTeacherFormMenu::ShowPupilsClick(TObject *Sender)
{
	leaveFromTheoryEdit(TxtMemo,ChangeTheoryLabel);
	PageControl1->ActivePage=PupilsPage;
	path.leaveChange(Memo1);
}
//---------------------------------------------------------------------------
void __fastcall TTeacherFormMenu::PupilsPageShow(TObject *Sender)
{
	ProgressQuery->SQL->Text="SELECT * FROM `Tests`";
	ProgressQuery->Active=true;
	int allTests=ProgressQuery->RecordCount;
	ProgressQuery->Active=false;
	PupilsStringGrid->ColCount=4;
	PupilsStringGrid->Cells[0][0]="���";
	PupilsStringGrid->Cells[1][0]="�������";
	PupilsStringGrid->Cells[2][0]="�����";
	PupilsStringGrid->Cells[3][0]="��������";
	PupilsQuery->SQL->Text="SELECT * FROM `Pupilsprofiles`";
	PupilsQuery->Active=true;
	PupilsStringGrid->RowCount=PupilsQuery->RecordCount+1;
	PupilsQuery->First();
	int currentUserID,reachedTest;
	for(int i=1;i<PupilsStringGrid->RowCount;i++){
		currentUserID=PupilsQuery->FieldByName("PID")->AsInteger;
		PupilsStringGrid->Cells[0][i]=PupilsQuery->FieldByName("PName")->AsAnsiString;
		PupilsStringGrid->Cells[1][i]=PupilsQuery->FieldByName("PLastName")->AsAnsiString;
		PupilsStringGrid->Cells[2][i]=PupilsQuery->FieldByName("Login")->AsAnsiString;
		ProgressQuery->SQL->Text="SELECT * FROM `Progress` WHERE `PupilsID`="+QuotedStr(currentUserID);
		ProgressQuery->Active=true;
		reachedTest=ProgressQuery->RecordCount;
		ProgressQuery->Active=false;
		PupilsStringGrid->Cells[3][i]=FormatFloat(0.00,(float(reachedTest)/float(allTests))*100)+"%";
		PupilsQuery->Next();
	}
	PupilsQuery->Active=false;
}
//---------------------------------------------------------------------------
void __fastcall TTeacherFormMenu::FormClose(TObject *Sender, TCloseAction &Action)
{
   Authorization->Close();
}
//---------------------------------------------------------------------------
void __fastcall TTeacherFormMenu::OpenMenuImageClick(TObject *Sender)
{
    openedDesignForNavigationMenu(NavigationPanel,OpenMenuImage,PageControl1);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::HideNavigationPanelClick(TObject *Sender)
{
    beginDesignForNavigationPanel(NavigationPanel,OpenMenuImage,PageControl1);
}
//---------------------------------------------------------------------------
void __fastcall TTeacherFormMenu::ChangeTestsPageEnter(TObject *Sender)
{
	 loadThemeIntoCombo(TestQuery,TestBox);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::TestBoxChange(TObject *Sender)
{
	TestQuery->Active=false;
	TestQuery->SQL->Text="SELECT * FROM `Tests` WHERE `TestName` ="+QuotedStr(TestBox->Text);
	TestQuery->Active=true;
	txtname=TestQuery->Fields->FieldByName("TestID")->AsAnsiString;
	try{
		Panel1->Visible=true;
	}
	catch(...){
		if(MessageDlg("������! ������, ��� ���������� ��������� ���� ���� �������.\n������ ������� ���� �� ������?",mtInformation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes);
		{
			TLocateOptions options;
			if(TestQuery->Locate("TestName",TestBox->Text,options)){
				TestQuery->Delete();
				TestQuery->Active=false;
				TestQuery->Active=true;
				loadThemeIntoCombo(TestQuery,TestBox);
			}
            else ShowMessage("�� ���������� :(");
        }
	}
	TestQuery->Active=false;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::ChangeButtonClick(TObject *Sender)
{
	 path.loadTest(test1,test2,test3,Memo1);
	 path.NextQ(Memo1,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,ChangeTestsPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::T1ButtonClick(TObject *Sender)
{
	if(T1QLabeledEdit->Text!=""&&T1A1LabeledEdit->Text!=""&&T1A2LabeledEdit->Text!=""&&T1A3LabeledEdit->Text!=""&&T1ComboBox->ItemIndex!=-1){
	ErrorLbl1->Visible=false;
	if(adding){
		Roockie.applyq1(AddMemo,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox);
		Roockie.NextAddQ(NameTLabeledEdit,TestQuery,AddMemo,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,TestAddPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
	}
	else{
		path.applyQ1(T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox);
		path.NextQ(Memo1,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,ChangeTestsPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
	}
	}
	else ErrorLbl1->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::T2ButtonClick(TObject *Sender)
{
	if(BeforeLabeledEdit->Text!=""&&MissLabeledEdit->Text!=""&&AfterLabeledEdit->Text!=""){
	ErrorLbl2->Visible=false;
	if(adding){
		Roockie.applyq2(AddMemo,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit);
		Roockie.NextAddQ(NameTLabeledEdit,TestQuery,AddMemo,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,TestAddPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
	}
	else{
		path.applyQ2(BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit);
		path.NextQ(Memo1,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,ChangeTestsPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
	}
	}
	else ErrorLbl2->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::T3ButtonClick(TObject *Sender)
{
	if(T3QLabeledEdit->Text!=""&&T3A1LabeledEdit->Text!=""&&T3A2LabeledEdit->Text!=""&&T3A3LabeledEdit!=""&&(T3CB1->Checked==true||T3CB2->Checked==true||T3CB3->Checked==true)){
	ErrorLbl3->Visible=false;
	if(adding){
		Roockie.applyq3(AddMemo,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
		Roockie.NextAddQ(NameTLabeledEdit,TestQuery,AddMemo,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,TestAddPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
	}
	else{
		path.applyQ3(T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
		path.NextQ(Memo1,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,ChangeTestsPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
	}
	}
	else ErrorLbl3->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::EditTestClick(TObject *Sender)
{
	leaveFromTheoryEdit(TxtMemo,ChangeTheoryLabel);
    loadThemeIntoCombo(TestQuery,TestBox);
	PageControl1->ActivePage=ChangeTestsPage;
	path.leaveChange(Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::AddTestClick(TObject *Sender)
{
	leaveFromTheoryEdit(TxtMemo,ChangeTheoryLabel);
	PageControl1->ActivePage=TestAddPage;
    path.leaveChange(Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::Label5Click(TObject *Sender)
{
	if(NameTLabeledEdit->Text!=""&&T1AmountLabeledEdit->Text!=""&&T2AmountLabeledEdit->Text!=""&&T3AmountLabeledEdit->Text!=""&&AllQLabeledEdit->Text!=""){
		int amountt3=StrToInt(T3AmountLabeledEdit->Text);
		int amountt2=StrToInt(T2AmountLabeledEdit->Text);
		int amountt1=StrToInt(T1AmountLabeledEdit->Text);
		int allq=StrToInt(AllQLabeledEdit->Text);
		if(amountt1+amountt2+amountt3!=allq) ShowMessage("����� ������� �������� �� ��������� � ����� ����������� ��������!");
		else{
			adding=true;
			Roockie.getAmount(allq,amountt1,amountt2,amountt3);
			Roockie.NextAddQ(NameTLabeledEdit,TestQuery,AddMemo,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,TestAddPage,T1QLabeledEdit,T1A1LabeledEdit,T1A2LabeledEdit,T1A3LabeledEdit,T1ComboBox,BeforeLabeledEdit,MissLabeledEdit,AfterLabeledEdit,T3QLabeledEdit,T3A1LabeledEdit,T3A2LabeledEdit,T3A3LabeledEdit,T3CB1,T3CB2,T3CB3);
			AllQLabeledEdit->Clear();
			T1AmountLabeledEdit->Clear();
			T2AmountLabeledEdit->Clear();
			T3AmountLabeledEdit->Clear();
		}
	}
	else ShowMessage("��������� ��� ���� ����� ����������");
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::TeacherListClick(TObject *Sender)
{
	leaveFromTheoryEdit(TxtMemo,ChangeTheoryLabel);
	PageControl1->ActivePage=TeachersPage;
    path.leaveChange(Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::AddTeacherLabelClick(TObject *Sender)
{
	if(AddTeacherPanel->Visible==false)AddTeacherPanel->Visible=true;
	else AddTeacherPanel->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TTeacherFormMenu::TeachersPageShow(TObject *Sender)
{
TeachersQuery->Active=false;
	TeachersQuery->SQL->Text="SELECT * FROM `Teachersprofiles`";
	TeachersQuery->Active=true;
	TeachersStringGrid->RowCount=TeachersQuery->RecordCount+1;
	TeachersStringGrid->ColCount=3;
	TeachersQuery->First();
	TeachersStringGrid->Cells[0][0]="���";
	TeachersStringGrid->Cells[1][0]="�������";
	TeachersStringGrid->Cells[2][0]="�����";
	for(int i=1;i<TeachersStringGrid->RowCount;i++){
		TeachersStringGrid->Cells[0][i]=TeachersQuery->FieldByName("TName")->AsString;
		TeachersStringGrid->Cells[1][i]=TeachersQuery->FieldByName("TLastName")->AsString;
		TeachersStringGrid->Cells[2][i]=TeachersQuery->FieldByName("TLogin")->AsString;
		TeachersQuery->Next();
	}
	TeachersQuery->Active=false;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::ConfirmLabelClick(TObject *Sender)
{
	if(TLoginLabeledEdit->Text!=""&&TPasswordLabeledEdit->Text!=""&&TNameLabeledEdit->Text!=""&&TLastNameLabeledEdit->Text!=""){
		if(IsPupilAccountExist(PupilsQuery,TLoginLabeledEdit)==false && IsTeacherAccountExist(TeachersQuery,TLoginLabeledEdit)==false){
			WarningLbl->Visible=false;
			TeachersQuery->Active=false;
			TeachersQuery->SQL->Text="SELECT * FROM `Teachersprofiles`";
			TeachersQuery->Active=true;
			TeachersQuery->Insert();
			TeachersQuery->FieldByName("TLogin")->Value= TLoginLabeledEdit->Text;
			TeachersQuery->FieldByName("TPassword")->Value= TPasswordLabeledEdit->Text;
			TeachersQuery->FieldByName("TName")->Value= TNameLabeledEdit->Text;
			TeachersQuery->FieldByName("TLastName")->Value= TLastNameLabeledEdit->Text;
			TeachersQuery->Post();
			TeachersStringGrid->RowCount=TeachersStringGrid->RowCount+1;
				TeachersStringGrid->Cells[0][TeachersStringGrid->RowCount-1]=TeachersQuery->FieldByName("TName")->AsString;
				TeachersStringGrid->Cells[1][TeachersStringGrid->RowCount-1]=TeachersQuery->FieldByName("TLastName")->AsString;
				TeachersStringGrid->Cells[2][TeachersStringGrid->RowCount-1]=TeachersQuery->FieldByName("TLogin")->AsString;
			TeachersQuery->Active=false;
		}
		else {
			WarningLbl->Caption="����� ����� ��� ������������";
			WarningLbl->Visible=true;
		}
	}
	else {
		WarningLbl->Caption="��������� ��� ����";
		WarningLbl->Visible=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::ChangeTheoryPageShow(TObject *Sender)
{
	loadTheoryIntoCombo(TheoryQuery,TheoryBox);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::EditTheoryClick(TObject *Sender)
{
	PageControl1->ActivePage=ChangeTheoryPage;
    path.leaveChange(Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::TheoryBoxChange(TObject *Sender)
{
	TheoryQuery->Active=false;
	TheoryQuery->SQL->Text="SELECT * FROM `Theory` WHERE `ThName` ="+QuotedStr(TheoryBox->Text);
	TheoryQuery->Active=true;
	txtname=TheoryQuery->Fields->FieldByName("ThID")->AsAnsiString;
	try{
		TxtMemo->Lines->LoadFromFile("Theory\\"+txtname+".txt", TEncoding::UTF8);
		Panel2->Visible=true;
	}
	catch(...){
		if(MessageDlg("������! ������, ��� ���������� ��������� ���� ���� �������.\n������ ������� ���� �� ������?",mtInformation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes)
		{
			TheoryQuery->Active=false;
			TheoryQuery->SQL->Text="SELECT * FROM `Theory`";
            TheoryQuery->Active=true;
			TLocateOptions options;
			if(TheoryQuery->Locate("ThName",TheoryBox->Text,options)){
				TheoryQuery->Delete();
				loadTheoryIntoCombo(TheoryQuery,TheoryBox);
			}
            else ShowMessage("�� ���������� :(");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::ChangeTheoryLabelClick(TObject *Sender)
{
	if(!editingTheory){
		TxtMemo->ReadOnly=false;
		ChangeTheoryLabel->Caption="������";
		editingTheory=true;
	}
	else {
		if(MessageDlg("��������� ���������?",mtInformation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes){
		editingTheory=false;
		TxtMemo->Lines->SaveToFile("Theory\\"+txtname+".txt", TEncoding::UTF8);
		TxtMemo->ReadOnly=true;
		ChangeTheoryLabel->Caption="��������";
		}
    }
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::CreateTestLblClick(TObject *Sender)
{
    PageControl1->ActivePage=TestAddPage;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::ImportTestLblClick(TObject *Sender)
{
    PageControl1->ActivePage=ImportTestPage;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::ImportButtonClick(TObject *Sender)
{
    if(HelloWorld->Visible)HelloWorld->Visible=false;
	if(OpenTextFileDialog1->Execute()){
		TestBodyMemo->Lines->LoadFromFile(OpenTextFileDialog1->FileName,TEncoding::UTF8);
        PageControl1->ActivePage=ImportTestPage;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::Label12Click(TObject *Sender)
{
	if(TestNameLabeledEdit->Text!=""&&OpenTextFileDialog1->FileName!=""){
		if(!IsExistTest(TestQuery,TestNameLabeledEdit)){
        	HelloWorld->Visible=false;
			try{
			TestQuery->Active=false;
			TestQuery->SQL->Text="SELECT * FROM `Tests`";
			TestQuery->Active=true;
			TestQuery->Insert();
			TestQuery->FieldByName("TestName")->Value= TestNameLabeledEdit->Text;
			TestQuery->Post();
			txtname=TestQuery->FieldByName("TestID")->AsAnsiString;
			//AnsiString curdir=GetCurrentDir();
			//curdir=curdir+"\\Tests\\"+txtname+".txt";
			TestBodyMemo->Lines->SaveToFile(txtname+".txt");
			ShowMessage("���� ������� ��������");
			PageControl1->ActivePage=WelcomePage;
			}
			catch(...){
				ShowMessage("���-�� ����� �� ���. ���� �� ��� ��������");
				PageControl1->ActivePage=ChooseAddTestPAge;
			}
			TestNameLabeledEdit->Clear();
            OpenTextFileDialog1->FileName="";
		}
		else{
			HelloWorld->Caption="���� � ����� ��������� ��� ����������";
			HelloWorld->Visible=true;
        }
	}
	else{
		HelloWorld->Caption="�� ��������� ��� ��������. ��� ����������� ���������� ������ �������� ����� � ������� ����, ���������� ����";
		 HelloWorld->Visible=true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::AddTheoryClick(TObject *Sender)
{
	leaveFromTheoryEdit(TxtMemo,ChangeTheoryLabel);
	PageControl1->ActivePage=AddTheoryPage;
    path.leaveChange(Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::DeleteButtonClick(TObject *Sender)
{
	try{
	DeleteFile("Tests\\"+txtname+".txt");
	TestQuery->Active=false;
	TestQuery->SQL->Text="SELECT * FROM `Tests`" ;
	TestQuery->Active=true;
	TLocateOptions options;
	if(TestQuery->Locate("TestName",TestBox->Text,options)){
			ProgressQuery->Active=false;
			ProgressQuery->SQL->Text="SELECT * FROM `Progress` WHERE `TestID` = "+QuotedStr(TestQuery->FieldByName("TestID")->AsString);
			ProgressQuery->Active=true;
			ProgressQuery->First();
			while(!ProgressQuery->IsEmpty()){
                ProgressQuery->Delete();
			}
			TestQuery->Delete();
			loadThemeIntoCombo(TestQuery,TestBox);
	}
	ShowMessage("���� ��� ������� �����");
	TestBox->Text="";
	TestBox->ItemIndex=-1;
	Panel1->Visible=false;
	}
	catch(...){
        ShowMessage("�� ������� ������� ����, �������� �� ��� �����");
	}
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::AddTheoryButtonClick(TObject *Sender)
{
	if(ThemeOfAddTheory->Text!=""&&TheoryMemo->Lines->Count!=0){
		if(!IsTheoryExist(TheoryQuery,ThemeOfAddTheory)) {
		ErrorLabel->Visible=false;
		try{
		TheoryQuery->Active=false;
		TheoryQuery->SQL->Text="SELECT * FROM `Theory`";
		TheoryQuery->Active=true;
		TheoryQuery->Insert();
		TheoryQuery->FieldByName("ThName")->Value=  ThemeOfAddTheory->Text;
		TheoryQuery->Post();
		txtname=TheoryQuery->FieldByName("ThID")->AsAnsiString;
		TheoryMemo->Lines->SaveToFile("Theory\\"+txtname+".txt", TEncoding::UTF8);
        ShowMessage("������ ������� ���������");
		ThemeOfAddTheory->Clear();
		TheoryMemo->Clear();
		} catch(...){
            ShowMessage("������! ������ �� ���� ���������");
		}
		}
		else{
			ErrorLabel->Visible=true;
			ErrorLabel->Caption="������ � ����� ��������� ��� ����������";
		}
	}
    	else{
			ErrorLabel->Visible=true;
			ErrorLabel->Caption="��� ���������� ���������� ��������� ��� ����";
		}
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::Label9Click(TObject *Sender)
{
	try{
	DeleteFile("Theory\\"+txtname+".txt");
	TheoryQuery->Active=false;
	TheoryQuery->SQL->Text="SELECT * FROM `Theory`" ;
	TheoryQuery->Active=true;
	TLocateOptions options;
	if(TheoryQuery->Locate("ThName",TheoryBox->Text,options)){
			TheoryQuery->Delete();
			loadTheoryIntoCombo(TheoryQuery,TheoryBox);
	}
	ShowMessage("������ ������� �������");
	TheoryBox->Text="";
	TheoryBox->ItemIndex=-1;
	Panel2->Visible=false;
    TxtMemo->Clear();
	}
	catch(...){
		ShowMessage("�� ������� ������� ������, �������� ��� ��� �������");
	}
}
//---------------------------------------------------------------------------
void __fastcall TTeacherFormMenu::TheoryMemoChange(TObject *Sender)
{
    if(ErrorLabel->Visible)ErrorLabel->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::ThemeOfAddTheoryChange(TObject *Sender)
{
    if(ErrorLabel->Visible)ErrorLabel->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TTeacherFormMenu::TestNameLabeledEditChange(TObject *Sender)
{
    if(HelloWorld->Visible)HelloWorld->Visible=false;
}
//---------------------------------------------------------------------------
