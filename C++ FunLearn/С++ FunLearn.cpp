//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Register.cpp", Registration);
USEFORM("PupilsMenu.cpp", PupilsFormMenu);
USEFORM("Authorisation.cpp", Authorization);
USEFORM("TeacherMenu.cpp", TeacherFormMenu);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->HelpFile = "";
		Application->CreateForm(__classid(TAuthorization), &Authorization);
		Application->CreateForm(__classid(TRegistration), &Registration);
		Application->CreateForm(__classid(TPupilsFormMenu), &PupilsFormMenu);
		Application->CreateForm(__classid(TTeacherFormMenu), &TeacherFormMenu);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
