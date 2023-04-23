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

	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		int^ loginid = nullptr;
		LoginForm(void)
		{
			controller = CController::getInstance();
			InitializeComponent();
		}
	protected:
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
			delete controller;
		}
	private: CController* controller;
	private: System::Windows::Forms::Label^ loginText;
	private: System::Windows::Forms::Label^ passText;
	private: System::Windows::Forms::Button^ loginButton;
	private: System::Windows::Forms::TextBox^ password;
	private: System::Windows::Forms::TextBox^ login;
	private: System::Windows::Forms::Label^ label1;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
			this->loginText = (gcnew System::Windows::Forms::Label());
			this->passText = (gcnew System::Windows::Forms::Label());
			this->loginButton = (gcnew System::Windows::Forms::Button());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->login = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// loginText
			// 
			this->loginText->AutoSize = true;
			this->loginText->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->loginText->Location = System::Drawing::Point(336, 176);
			this->loginText->Name = L"loginText";
			this->loginText->Size = System::Drawing::Size(70, 21);
			this->loginText->TabIndex = 14;
			this->loginText->Text = L"Логин: ";
			// 
			// passText
			// 
			this->passText->AutoSize = true;
			this->passText->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->passText->Location = System::Drawing::Point(328, 211);
			this->passText->Name = L"passText";
			this->passText->Size = System::Drawing::Size(78, 21);
			this->passText->TabIndex = 13;
			this->passText->Text = L"Пароль: ";
			// 
			// loginButton
			// 
			this->loginButton->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->loginButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->loginButton->FlatAppearance->BorderSize = 15;
			this->loginButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->loginButton->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->loginButton->Location = System::Drawing::Point(403, 260);
			this->loginButton->Name = L"loginButton";
			this->loginButton->Size = System::Drawing::Size(100, 27);
			this->loginButton->TabIndex = 12;
			this->loginButton->Text = L"Войти";
			this->loginButton->UseVisualStyleBackColor = false;
			this->loginButton->Click += gcnew System::EventHandler(this, &LoginForm::loginButton_Click);
			// 
			// password
			// 
			this->password->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->password->Location = System::Drawing::Point(412, 208);
			this->password->Name = L"password";
			this->password->PasswordChar = '*';
			this->password->Size = System::Drawing::Size(145, 29);
			this->password->TabIndex = 11;
			// 
			// login
			// 
			this->login->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->login->Location = System::Drawing::Point(412, 173);
			this->login->Name = L"login";
			this->login->Size = System::Drawing::Size(145, 29);
			this->login->TabIndex = 10;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(299, 64);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(304, 36);
			this->label1->TabIndex = 15;
			this->label1->Text = L"Медицинская карта";
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(884, 461);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->loginText);
			this->Controls->Add(this->passText);
			this->Controls->Add(this->loginButton);
			this->Controls->Add(this->password);
			this->Controls->Add(this->login);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"LoginForm";
			this->Text = L"Авторизация";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void loginButton_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string l = msclr::interop::marshal_as<std::string>(this->login->Text);
		std::string p = msclr::interop::marshal_as<std::string>(this->password->Text);

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
			this->Close();
		}
		else {
			MessageBox::Show("Wrong Password Or Login");
		}
	}
};
}
