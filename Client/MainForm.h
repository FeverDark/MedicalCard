#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ articles;
	protected:
	private: System::Windows::Forms::Panel^ articleText;
	private: System::Windows::Forms::Panel^ allArticles;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Panel^ peoples;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Panel^ actionButtons;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;


	private:
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
			this->articles = (gcnew System::Windows::Forms::Panel());
			this->articleText = (gcnew System::Windows::Forms::Panel());
			this->allArticles = (gcnew System::Windows::Forms::Panel());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->peoples = (gcnew System::Windows::Forms::Panel());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->actionButtons = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->allArticles->SuspendLayout();
			this->peoples->SuspendLayout();
			this->actionButtons->SuspendLayout();
			this->SuspendLayout();
			// 
			// articles
			// 
			this->articles->Location = System::Drawing::Point(254, 30);
			this->articles->Name = L"articles";
			this->articles->Size = System::Drawing::Size(586, 219);
			this->articles->TabIndex = 2;
			// 
			// articleText
			// 
			this->articleText->Location = System::Drawing::Point(254, 255);
			this->articleText->Name = L"articleText";
			this->articleText->Size = System::Drawing::Size(586, 201);
			this->articleText->TabIndex = 3;
			// 
			// allArticles
			// 
			this->allArticles->Controls->Add(this->listView1);
			this->allArticles->Controls->Add(this->listBox1);
			this->allArticles->Location = System::Drawing::Point(12, 30);
			this->allArticles->Name = L"allArticles";
			this->allArticles->Size = System::Drawing::Size(221, 219);
			this->allArticles->TabIndex = 5;
			// 
			// listView1
			// 
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(15, 118);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(121, 97);
			this->listView1->TabIndex = 1;
			this->listView1->UseCompatibleStateImageBehavior = false;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(15, 16);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 95);
			this->listBox1->TabIndex = 0;
			// 
			// peoples
			// 
			this->peoples->Controls->Add(this->comboBox1);
			this->peoples->Location = System::Drawing::Point(12, 255);
			this->peoples->Name = L"peoples";
			this->peoples->Size = System::Drawing::Size(221, 201);
			this->peoples->TabIndex = 6;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(15, 19);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 0;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(254, 3);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(219, 21);
			this->comboBox2->TabIndex = 7;
			// 
			// actionButtons
			// 
			this->actionButtons->Controls->Add(this->button4);
			this->actionButtons->Controls->Add(this->button3);
			this->actionButtons->Controls->Add(this->button2);
			this->actionButtons->Controls->Add(this->button1);
			this->actionButtons->Location = System::Drawing::Point(13, 3);
			this->actionButtons->Name = L"actionButtons";
			this->actionButtons->Size = System::Drawing::Size(220, 21);
			this->actionButtons->TabIndex = 8;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(17, 15);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(26, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(17, 15);
			this->button2->TabIndex = 1;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(49, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(17, 15);
			this->button3->TabIndex = 2;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(72, 2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(17, 15);
			this->button4->TabIndex = 3;
			this->button4->Text = L"button4";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 461);
			this->Controls->Add(this->actionButtons);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->peoples);
			this->Controls->Add(this->allArticles);
			this->Controls->Add(this->articleText);
			this->Controls->Add(this->articles);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->allArticles->ResumeLayout(false);
			this->peoples->ResumeLayout(false);
			this->actionButtons->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
