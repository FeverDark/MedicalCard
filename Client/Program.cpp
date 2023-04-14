#include "MainForm.h"
#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Client::LoginForm login;
	login.ShowDialog();
	int^ loginid = login.loginid;
	if (loginid != nullptr) {
		Client::MainForm main(loginid);
		Application::Run(%main);
	}
}