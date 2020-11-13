//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PupilsMenu.h"
#include "Authorisation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <vector>
#include <set>
TPupilsFormMenu *PupilsFormMenu;
AnsiString txtname; //путь к тесту(текстовый документ)
bool testStarted=false;//Показывает, запущен ли тест на данный момент
int timeLimit=0;
int walkthrough=0;
int currentUserID;
AnsiString currentUserName;
Randomize();
bool IsTesting=false;
//---------------------------------------------------------------------------
__fastcall TPupilsFormMenu::TPupilsFormMenu(TComponent* Owner)
	: TForm(Owner)
{
}

//Структура теста с одним вариантом ответа
struct Test1{
	AnsiString question;
	std::vector<AnsiString> answers;
	AnsiString rightAnswer;
};

//Стурктура теста с вводом пропущенного выражения
struct Test2{
	AnsiString beforeMiss;
	AnsiString miss;
	AnsiString afterMiss;
};

//Структура теста с множественным вариантом ответов
struct Test3{
	AnsiString question;
	std::vector<AnsiString> answers;
	std::vector<AnsiString> rightAnswer;
};

std::vector<Test1> test1;
std::vector<Test2> test2;
std::vector<Test3> test3;

class TestLogic{
	private:
		int AllQ, AllAnswers, RightAnswers; // Общее кол-во вопросов, кол-во всех и правильных ответов
		int AmountT1, AmountT2, AmountT3; // Количество тестов 1-го, 2-го, 3-го типов
		int currentQ,currentQ2,currentQ3;
		std::set<int> reachedT1;
		std::set<int> reachedT2;
		std::set<int> reachedT3;
		void showQ1(std::vector<Test1> test1,std::vector<Test2> test2,std::vector<Test3> test3, TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TLabel*q1bl,TLabel*q2bl,TLabel*q3bl,TRadioGroup* answerField,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			answerField->Items->Clear();
			if(reachedT1.size()!=AmountT1){
				pc->ActivePage=ts1;
				do{
				currentQ=Random(test1.size());
				}while(reachedT1.count(currentQ)!=0);
				reachedT1.insert(currentQ);
				q1bl->Caption=test1[currentQ].question;
				int position;
				std::set<int> reachedPos;
				do{
				position=Random(3);
				}while(reachedPos.count(position)!=0);
				answerField->Items->Add(test1[currentQ].answers[position]);
				reachedPos.insert(position);

				do{
				position=Random(3);
				}while(reachedPos.count(position)!=0);
				answerField->Items->Add(test1[currentQ].answers[position]);
				reachedPos.insert(position);

				do{
					position=Random(3);
				}while(reachedPos.count(position)!=0);
				answerField->Items->Add(test1[currentQ].answers[position]);
			}
			else {
			int type;
				do{
				  type=Random(3)+1;
				}while(type==1);
				switch (type) {
				 case 2:{
					showQ2(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					break;
				 }
				 case 3:{
					 showQ3(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
                     break;
				 }
				}
			}
		}

		void showQ2(std::vector<Test1> test1,std::vector<Test2> test2,std::vector<Test3> test3, TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TLabel*q1bl,TLabel*q2bl,TLabel*q3bl,TRadioGroup* answerField,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			q2bl->Caption="";
			if(reachedT2.size()!=AmountT2){
				pc->ActivePage=ts2;
				do{
				currentQ2=Random(test2.size());
				}while(reachedT2.count(currentQ2)!=0);
				reachedT2.insert(currentQ2);

				q2bl->Caption=test2[currentQ2].beforeMiss;
				q2bl->Caption+=" ";
				for(int i=0;i<test2[currentQ2].miss.Length();i++){
					q2bl->Caption=q2bl->Caption+"_";
				}
				q2bl->Caption=q2bl->Caption+" "+test2[currentQ2].afterMiss;
			}
			else{
            	int type;
				do{
				  type=Random(3)+1;
				}while(type==2);

				switch (type) {
					case 1:{
						showQ1(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
						break;
					}
					 case 3:{
						 showQ3(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
						 break;
					}
				}
            }
		}

		void showQ3(std::vector<Test1> test1,std::vector<Test2> test2,std::vector<Test3> test3, TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TLabel*q1bl,TLabel*q2bl,TLabel*q3bl,TRadioGroup* answerField,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			if(reachedT3.size()!=AmountT3){
				pc->ActivePage=ts3;
				do{
				currentQ3=Random(test3.size());
				}while(reachedT3.count(currentQ3)!=0);
				reachedT3.insert(currentQ3);
				q3bl->Caption=test3[currentQ3].question;
				int position;
				std::set<int> reachedPos;
				do{
				position=Random(3);
				}while(reachedPos.count(position)!=0);
				cb1->Caption=test3[currentQ3].answers[position];
				reachedPos.insert(position);

				do{
					position=Random(3);
				}while(reachedPos.count(position)!=0);
				cb2->Caption=test3[currentQ3].answers[position];
				reachedPos.insert(position);

				do{
					position=Random(3);
				}while(reachedPos.count(position)!=0);
				cb3->Caption=test3[currentQ3].answers[position];
			}

			else {
				int type;
				type=Random(2)+1;
				switch (type) {
				 case 1:{
					showQ1(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					break;
				 }
				 case 2:{
					 showQ2(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					 break;
				 }
				}
			}
		}

		void showEnd(TPageControl* pc,TTabSheet* tsEnd,TLabel* endMessage,TLabel* qMessage,TLabel* rightAMessage,TLabel* walkthroughTime,TTimer* timer,TADOQuery* ProgressQuery){
		timer->Enabled=false;
        timeLimit=0;
			pc->ActivePage=tsEnd;
			if(AllQ-RightAnswers>AllQ/3){
				endMessage->Caption="Ты допустил много ошибок :(\nПройди тест ещё раз, у тебя всё получится!";
			}
			else{
				ProgressQuery->SQL->Text="SELECT * FROM `Progress` WHERE `PupilsID` = "+QuotedStr(currentUserID)+" AND `TestID` ="+QuotedStr(txtname);
				ProgressQuery->Active=true;
				endMessage->Caption="Поздравляю! Тест завершён успешно!";
				if(ProgressQuery->IsEmpty()){
					ProgressQuery->Active=false;
					ProgressQuery->SQL->Text="SELECT * FROM `Progress`";
					ProgressQuery->Active=true;
					ProgressQuery->Insert();
					ProgressQuery->Fields->FieldByName("TestID")->Value= txtname;
					ProgressQuery->Fields->FieldByName("PupilsID")->Value=currentUserID;
					ProgressQuery->Post();
					ProgressQuery->Active=false;
				}
			}
			qMessage->Caption="Количество вопросов в тесте: "+IntToStr(AllQ);
			rightAMessage->Caption="Количество правильных ответов: "+ IntToStr(RightAnswers);
			walkthroughTime->Caption="Тест пройден за "+IntToStr(walkthrough)+" секунд";
			AllQ=AllAnswers=RightAnswers=AmountT1=AmountT2=AmountT3=walkthrough=0;
			currentQ=currentQ2=currentQ3=-1;
			reachedT1.clear();
			reachedT2.clear();
			reachedT3.clear();
		}

	public:
		TestLogic(){
			AllQ=AllAnswers=RightAnswers=AmountT1=AmountT2=AmountT3=0;
			currentQ=currentQ2=currentQ3=-1;
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

				if(memo->Lines->Strings[j]== "first"){  // Если вопрос первого типа, то записываем его содержимое в структуру test
					Test1 add;
					j++; //Переход на следующую строку
					add.question=memo->Lines->Strings[j];  // В поле question записываем вопрос из Memo1
					j++;
					for(int k=0;k<3;k++){   // Записываем сами варианты ответа
						add.answers.push_back(memo->Lines->Strings[j]);
						j++;
					}

					add.rightAnswer=memo->Lines->Strings[j];  // Записываем индекс правильного ответа
					j++;
					j++;
					AmountT1++;
					test1.push_back(add);
				}
				else{
				if( memo->Lines->Strings[j]=="second"){    // Если вопрос второго типа, то записываем его содержимое в структуру test2
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

		void beginTest(std::vector<Test1> test1,std::vector<Test2> test2,std::vector<Test3> test3, TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TLabel*q1bl,TLabel*q2bl,TLabel*q3bl,TRadioGroup* answerField,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3){
			int type=Random(3)+1;
			switch (type) {
				 case 1:{
					showQ1(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
				 case 2:{
					 showQ2(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					 return;
				 }
				 case 3:{
					showQ3(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
			}
		}

		void getAnswerFromQ1(std::vector<Test1> test1,std::vector<Test2> test2,std::vector<Test3> test3, TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TLabel*q1bl,TLabel*q2bl,TLabel*q3bl,TRadioGroup* answerField,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3,TTabSheet* tsEnd,TLabel* endMessage,TLabel* qMessage,TLabel* rightAMessage,TLabel* walkthroughTime,TTimer* timer,TADOQuery* ProgressQuery){
			if(answerField->Items->Strings[answerField->ItemIndex]==test1[currentQ].rightAnswer) RightAnswers++;
			AllAnswers++;
			if(AllAnswers== AllQ){
				showEnd(pc,tsEnd,endMessage,qMessage,rightAMessage,walkthroughTime,timer,ProgressQuery);
				return;
			}
			else{
				int type=Random(3)+1;
				switch (type) {
				 case 1:{
					showQ1(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
				 case 2:{
					 showQ2(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					 return;
				 }
				 case 3:{
					showQ3(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
				}
			}
		}

		void getAnswerFromQ2(std::vector<Test1> test1,std::vector<Test2> test2,std::vector<Test3> test3, TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TLabel*q1bl,TLabel*q2bl,TLabel*q3bl,TRadioGroup* answerField,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3,TTabSheet* tsEnd,TLabel* endMessage,TLabel* qMessage,TLabel* rightAMessage,TLabel* walkthroughTime,TLabeledEdit* aEdit,TTimer* timer,TADOQuery* ProgressQuery){
			if(aEdit->Text==test2[currentQ2].miss) RightAnswers++;
			aEdit->Clear();

			AllAnswers++;
			if(AllAnswers== AllQ){
				showEnd(pc,tsEnd,endMessage,qMessage,rightAMessage,walkthroughTime,timer,ProgressQuery);
				return;
			}
			else{
				int type=Random(3)+1;
				switch (type) {
				 case 1:{
					showQ1(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
				 case 2:{
					 showQ2(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					 return;
				 }
				 case 3:{
					showQ3(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
				}
			}
		}

		void getAnswerFromQ3(std::vector<Test1> test1,std::vector<Test2> test2,std::vector<Test3> test3, TPageControl* pc,TTabSheet* ts1,TTabSheet* ts2,TTabSheet* ts3,TLabel*q1bl,TLabel*q2bl,TLabel*q3bl,TRadioGroup* answerField,TCheckBox* cb1,TCheckBox* cb2,TCheckBox* cb3,TTabSheet* tsEnd,TLabel* endMessage,TLabel* qMessage,TLabel* rightAMessage,TLabel* walkthroughTime,TTimer* timer,TADOQuery* ProgressQuery){
			bool mistake=false; //Изначально ошибок нет
				for(int i=0;i<test3[currentQ3].rightAnswer.size();i++){ //Идем по всем правильным ответам
					if(cb1->Caption==test3[currentQ3].rightAnswer[i]){  //Если в CheckBox1 тест совпадает с ответом
						if(cb1->Checked){  //Если этот CheckBox выбран
						mistake=false; //То ошибки в этом выборе нет, прекращаем проверку и идём дальше
						break;
						}
						mistake=true;  //Если же мы остались, значит этот CheckBox не выбран, значит пользователь допустил ошибку.
					}
					else if (cb1->Checked) mistake=true; //Если тест CheckBox1 не совпадает с правильным ответом, а этот CheckBox выбрал, то пользователь допустил ошибку
				}

			if(!mistake){ // Если с предыдущим CheckBox всё в порядке(ошибок не допущенно), то идем проверять следующие CheckBox
				for(int i=0;i<test3[currentQ3].rightAnswer.size();i++){
					if(cb2->Caption==test3[currentQ3].rightAnswer[i]){
						if(cb2->Checked){
						mistake=false;
						break;
						}
						mistake=true;
					}
					else if (cb2->Checked) mistake=true;
				}
				if(!mistake){
					for(int i=0;i<test3[currentQ3].rightAnswer.size();i++){
					if(cb3->Caption==test3[currentQ3].rightAnswer[i]){
						if(cb3->Checked){
						mistake=false;
						break;
						}
						mistake=true;
					}
					else if (cb3->Checked) mistake=true;
				}
				}
			}

			if(!mistake) RightAnswers++; //Если ошибок не найдено, то ответ правильный
			cb1->Checked=false;
			cb2->Checked=false;
			cb3->Checked=false;
			AllAnswers++;
			if(AllAnswers== AllQ){
				showEnd(pc,tsEnd,endMessage,qMessage,rightAMessage,walkthroughTime,timer,ProgressQuery);
				return;
			}
			else{
				int type=Random(3)+1;
				switch (type) {
				 case 1:{
					showQ1(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
				 case 2:{
					 showQ2(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					 return;
				 }
				 case 3:{
					showQ3(test1,test2,test3,pc,ts1,ts2,ts3,q1bl,q2bl,q3bl,answerField,cb1,cb2,cb3);
					return;
				 }
				}
			}
		}

		void TimeOver(TPageControl* pc,TTabSheet* tsEnd,TLabel* endMessage,TLabel* qMessage,TLabel* rightAMessage,TLabel* walkthroughTime,TTimer* timer,TADOQuery* ProgressQuery){
			timer->Enabled=false;
			pc->ActivePage=tsEnd;
		
			if(AllQ-RightAnswers>AllQ/3){
				endMessage->Caption="Время вышло, ну-ка посмотрим что у тебя там получилоь... \nСлишком много ошибок. Пройди тест ещё раз, у тебя всё получится!";
			}
			else{
				endMessage->Caption="Время вышло, ну-ка посмотрим что у тебя там получилоь... \nПоздравляю!Тест завершён успешно!";
				ProgressQuery->SQL->Text="SELECT * FROM `Progress` WHERE `PupilsID` ="+QuotedStr(currentUserID)+" AND `TestID`="+QuotedStr(txtname);
				ProgressQuery->Active=true;
				if(ProgressQuery->IsEmpty()){
					ProgressQuery->Active=false;
					ProgressQuery->SQL->Text="SELECT * FROM `Progress";
					ProgressQuery->Active=true;
					ProgressQuery->Insert();
					ProgressQuery->Fields->FieldByName("TestID")->Value= txtname;
					ProgressQuery->Fields->FieldByName("PupilsID")->Value=currentUserID;
					ProgressQuery->Post();
					ProgressQuery->Active=false;
				}
			}
			qMessage->Caption="Количество вопросов в тесте: "+IntToStr(AllQ);
			rightAMessage->Caption="Количество правильных ответов: "+ IntToStr(RightAnswers);
			walkthroughTime->Caption="Тест пройден за "+IntToStr(walkthrough)+" секунд";
			AllQ=AllAnswers=RightAnswers=AmountT1=AmountT2=AmountT3=walkthrough=0;
			currentQ=currentQ2=currentQ3=-1;
			reachedT1.clear();
			reachedT2.clear();
			reachedT3.clear();
		}
};

TestLogic path;

//Изменяет цвет Label(Для наведения курсора)
void setDesignOnEnterMouse(TLabel* a){
	a->Color=TColor(RGB(93, 48, 154));
}

//Изменяет цвет Label(Для покидания курсора)
void setDesignOnLeaveMouse(TLabel* a){
    a->Color=TColor(RGB(17,84,102));
}

//Скрытое меню
void beginDesignForNavigationPanel(TPanel* a, TImage* b,TPageControl* PageControl1){
	a->Visible=false;
	b->Visible=true;
	PageControl1->Margins->Left=50;
}

//Открытое меню
void openedDesignForNavigationMenu(TPanel* a, TImage* b, TPageControl* PageControl1){
	a->Visible=true;
	b->Visible=false;
    PageControl1->Margins->Left=0;
}

//---------------------------------------------------------------------------
void __fastcall TPupilsFormMenu::FormClose(TObject *Sender, TCloseAction &Action)
{
	Authorization->Close();
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::HideNavigationPanelClick(TObject *Sender)
{
	beginDesignForNavigationPanel(NavigationPanel,OpenMenuImage,PageControl1);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::FormActivate(TObject *Sender)
{
	currentUserID=Authorization->ADOTable1->FieldByName("PID")->AsInteger;
	currentUserName=Authorization->ADOTable1->FieldByName("PName")->AsAnsiString;
	beginDesignForNavigationPanel(NavigationPanel,OpenMenuImage,PageControl1);
	Label1->Caption=Label1->Caption + Authorization->LoginEdit->Text;
	PageControl1->ActivePage=WelcomePage;
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::OpenMenuImageClick(TObject *Sender)
{
	openedDesignForNavigationMenu(NavigationPanel,OpenMenuImage,PageControl1);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::BeginLearningMouseEnter(TObject *Sender)
{
	setDesignOnEnterMouse(BeginLearning);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::BeginLearningMouseLeave(TObject *Sender)
{
	setDesignOnLeaveMouse(BeginLearning);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::OpenTheoryClick(TObject *Sender)
{
    if(!IsTesting) PageControl1->ActivePage=TheoryPage;
}
//---------------------------------------------------------------------------
void __fastcall TPupilsFormMenu::OpenTheoryMouseEnter(TObject *Sender)
{
	setDesignOnEnterMouse(OpenTheory);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::OpenAchieveMouseEnter(TObject *Sender)
{
	setDesignOnEnterMouse(OpenAchieve);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::OpenAchieveMouseLeave(TObject *Sender)
{
	setDesignOnLeaveMouse(OpenAchieve);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::OpenTheoryMouseLeave(TObject *Sender)
{
	setDesignOnLeaveMouse(OpenTheory);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::BeginLearningClick(TObject *Sender)
{
	if(!IsTesting) PageControl1->ActivePage=LearnPage;
}
//---------------------------------------------------------------------------

void loadThemeIntoCombo(TADOQuery* TestQuery, TComboBox* TestBox){
TestQuery->Active=false;
TestQuery->Active=true;
	TestBox->Items->Clear();
	TestQuery->First();
	while(!TestQuery->Eof){
		TestBox->Items->Add(TestQuery->Fields->FieldByName("TestName")->AsString);
		TestQuery->Next();
	}
}

void loadTheoryIntoCombo(TADOQuery* TheoryQuery, TComboBox* TheoryBox){
	TheoryQuery->Active=false;
	TheoryQuery->Active=true;
	TheoryBox->Items->Clear();
	TheoryQuery->First();
	while(!TheoryQuery->Eof){
		TheoryBox->Items->Add(TheoryQuery->Fields->FieldByName("ThName")->AsString);
		TheoryQuery->Next();
	}
}

void __fastcall TPupilsFormMenu::ThemeBoxChange(TObject *Sender)
{
	CommonQuery->Active=false;
	CommonQuery->SQL->Text="SELECT * FROM `Tests` WHERE `TestName` ="+QuotedStr(ThemeBox->Text);
	CommonQuery->Active=true;
	txtname=CommonQuery->Fields->FieldByName("TestID")->AsAnsiString;
	try{
		NameOfTestLabel->Caption= "Название теста: "+ThemeBox->Text;
		Panel1->Visible=true;
	}
	catch(...){
		if(MessageDlg("Ошибка! Похоже, что содержимое выбранной темы было удалено.\nХотите удалить тему из списка?",mtInformation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes)
		{
			TLocateOptions options;
			if(CommonQuery->Locate("TestName",ThemeBox->Text,options)){
				CommonQuery->Delete();
				CommonQuery->Active=false;
				CommonQuery->Active=true;
				loadThemeIntoCombo(TestQuery,ThemeBox);
			}
            else ShowMessage("Не получилось :(");
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::LearnPageShow(TObject *Sender)
{
	loadThemeIntoCombo(TestQuery,ThemeBox);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::StartTestButtonClick(TObject *Sender)
{
	path.loadTest(test1,test2,test3,TestConteinsMemo);
	path.beginTest(test1,test2,test3,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,QLabel,QLabel2,QLabel3,RadioGroup1,CheckBox1,CheckBox2,CheckBox3);
	TestTimer->Enabled=true;
    IsTesting=true;
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::Button3Click(TObject *Sender)
{
	PageControl1->ActivePage=LearnPage;
    IsTesting=false;
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::Button1Click(TObject *Sender)
{
	if(RadioGroup1->ItemIndex==-1) ShowMessage("Выберите правильный вариант ответа");
    else path.getAnswerFromQ1(test1,test2,test3,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,QLabel,QLabel2,QLabel3,RadioGroup1,CheckBox1,CheckBox2,CheckBox3,EndTestPage,ResultsLabel,AmountOfQLabel,AmountOfRightAnswersLabel,TimeOfPassingTestLabel,TestTimer,ProgressQuery);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::Button2Click(TObject *Sender)
{
	path.getAnswerFromQ3(test1,test2,test3,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,QLabel,QLabel2,QLabel3,RadioGroup1,CheckBox1,CheckBox2,CheckBox3,EndTestPage,ResultsLabel,AmountOfQLabel,AmountOfRightAnswersLabel,TimeOfPassingTestLabel,TestTimer,ProgressQuery);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::AnswerEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key==VK_RETURN){
		path.getAnswerFromQ2(test1,test2,test3,PageControl1,FrstKindTest,ScndKindTest,ThrdKindTest,QLabel,QLabel2,QLabel3,RadioGroup1,CheckBox1,CheckBox2,CheckBox3,EndTestPage,ResultsLabel,AmountOfQLabel,AmountOfRightAnswersLabel,TimeOfPassingTestLabel,AnswerEdit,TestTimer,ProgressQuery);
	}
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::TestTimerTimer(TObject *Sender)
{
	timeLimit++;
	walkthrough++;
	if(timeLimit==300) path.TimeOver(PageControl1,EndTestPage,ResultsLabel,AmountOfQLabel,AmountOfRightAnswersLabel,TimeOfPassingTestLabel,TestTimer,ProgressQuery);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::TheoryBoxChange(TObject *Sender)
{
	CommonQuery->Active=false;
	CommonQuery->SQL->Text="SELECT * FROM `Theory` WHERE `ThName` ="+QuotedStr(TheoryBox->Text);
	CommonQuery->Active=true;
	txtname=CommonQuery->Fields->FieldByName("ThID")->AsAnsiString;
	try{
		TextMemo->Visible=true;
		TextMemo->Lines->LoadFromFile("Theory\\"+txtname+".txt",TEncoding::UTF8);
	}
	catch(...){
		if(MessageDlg("Ошибка! Похоже, что содержимое выбранной темы было удалено.\nХотите удалить тему из списка?",mtInformation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes)
		{
			TLocateOptions options;
			if(CommonQuery->Locate("ThName",TheoryBox->Text,options)){
				CommonQuery->Delete();
				loadTheoryIntoCombo(TheoryQuery,TheoryBox);
			}
            else ShowMessage("Не получилось :(");
        }
	}
}
//---------------------------------------------------------------------------


void __fastcall TPupilsFormMenu::TheoryPageShow(TObject *Sender)
{
	loadTheoryIntoCombo(TheoryQuery,TheoryBox);
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::OpenAchieveClick(TObject *Sender)
{
	if(!IsTesting) PageControl1->ActivePage=AchievePage;
}
//---------------------------------------------------------------------------

void __fastcall TPupilsFormMenu::AchievePageShow(TObject *Sender)
{
	ProgressCaptionLabel->Caption="Ученик "+ currentUserName;
	ProgressQuery->SQL->Text="SELECT * FROM `Progress` WHERE `PupilsID`="+QuotedStr(currentUserID);
	ProgressQuery->Active=true;
	int reachedAmount=0;
	int OverallAmount=0;
	ProgressQuery->First();
	while(!ProgressQuery->Eof){
		reachedAmount++;
        ProgressQuery->Next();
	}
	ProgressQuery->Active=false;
	ProgressQuery->SQL->Text="SELECT * FROM `Tests`";
	TestQuery->Active=true;
    TestQuery->First();
	while(!TestQuery->Eof){
		OverallAmount++;
		TestQuery->Next();
	}
	TestQuery->Active=false;
	float percent=(float(reachedAmount)/float(OverallAmount))*100;
	//ProgressTextLabel->Caption="Пройденно тестов: "+IntToStr(reachedAmount)+" из "+IntToStr(OverallAmount)+"\nВаш общий прогресс: "+FloatToStrF(percent, ffGeneral, 2, 2)+"%";
	ProgressTextLabel->Caption="Пройденно тестов: "+IntToStr(reachedAmount)+" из "+IntToStr(OverallAmount)+"\nВаш общий прогресс: "+FormatFloat(0.00,percent)+"%";
}
//---------------------------------------------------------------------------

