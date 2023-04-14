#include "Controller.h"
#include <msclr\marshal_cppstd.h>

#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ LoginForm
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		int^ loginid = nullptr;
		LoginForm(void)
		{
			controller = CController::getInstance();
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ login;
	private: System::Windows::Forms::TextBox^ password;
	private: System::Windows::Forms::Button^ loginButton;
	private:
		CController* controller;
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->login = (gcnew System::Windows::Forms::TextBox());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// login
			// 
			this->login->Location = System::Drawing::Point(87, 60);
			this->login->Name = L"login";
			this->login->Size = System::Drawing::Size(100, 20);
			this->login->TabIndex = 0;
			// 
			// password
			// 
			this->password->Location = System::Drawing::Point(87, 101);
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(100, 20);
			this->password->TabIndex = 1;
			// 
			// loginButton
			// 
			this->loginButton->Location = System::Drawing::Point(87, 149);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(100, 23);
			this->loginButton->TabIndex = 2;
			this->loginButton->Text = L"button1";
			this->loginButton->UseVisualStyleBackColor = true;
			this->loginButton->Click += gcnew System::EventHandler(this, &LoginForm::loginButton_Click);
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->password);
			this->Controls->Add(this->login);
			this->Name = L"LoginForm";
			this->Text = L"LoginForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string l = msclr::interop::marshal_as<std::string>(this->login->Text);
		std::string p = sha_256(msclr::interop::marshal_as<std::string>(this->password->Text));

		if (l.empty() || p.empty()) {
			MessageBox::Show("Cannot be empty");
			return;
		}
		int tempid = -1;
		for (int i = 0; i < controller->db->workers.size(); ++i) {
			if (l == controller->db->workers[i]->getLogin()) {
				tempid = i;
				break;
			}
		}
		if (tempid != -1 && l == controller->db->workers[tempid]->getLogin() && p == controller->db->workers[tempid]->getPassword()) {
			this->loginid = tempid;
			//MessageBox::Show("Yea");
			this->Close();
		}
		else {
			MessageBox::Show("Wrong Password Or Login");
		}
	}
	};
}
