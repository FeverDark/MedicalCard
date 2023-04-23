#include "Controller.h"
#include "Creation.h"
#include "EditForm.h"
#include "ProcedureCreation.h"
#include <thread>
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
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(int^ loginid)
		{
			controller = CController::getInstance();
			InitializeComponent((int)loginid);
		}
	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: int lid;
	private: CController* controller;
	private: DataTable^ Table;
	private: DataSet^ Set;
	private: int^ predId;
	private: System::Windows::Forms::Panel^ articles;
	protected:
	private: System::Windows::Forms::Panel^ articleText;
	private: System::Windows::Forms::Panel^ allArticles;
	private: System::Windows::Forms::Panel^ peoples;
	private: System::Windows::Forms::Panel^ actionButtons;
	private: System::Windows::Forms::Button^ deleteButton;
	private: System::Windows::Forms::Button^ editButton;
	private: System::Windows::Forms::Button^ deleteProcedure;
	private: System::Windows::Forms::Button^ addProcedure;
	private: System::Windows::Forms::Button^ addButton;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::RichTextBox^ richTextBox2;
	private: System::Windows::Forms::DataGridView^ mainTable;
	private: System::Windows::Forms::TreeView^ treeView1;
	private: System::Windows::Forms::TextBox^ loginText;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(int loginid)
		{
			lid = loginid;
			this->articles = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->articleText = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->allArticles = (gcnew System::Windows::Forms::Panel());
			this->mainTable = (gcnew System::Windows::Forms::DataGridView());
			this->peoples = (gcnew System::Windows::Forms::Panel());
			this->treeView1 = (gcnew System::Windows::Forms::TreeView());
			this->actionButtons = (gcnew System::Windows::Forms::Panel());
			this->deleteButton = (gcnew System::Windows::Forms::Button());
			this->editButton = (gcnew System::Windows::Forms::Button());
			this->addButton = (gcnew System::Windows::Forms::Button());
			this->deleteProcedure = (gcnew System::Windows::Forms::Button());
			this->addProcedure = (gcnew System::Windows::Forms::Button());
			this->loginText = (gcnew System::Windows::Forms::TextBox());
			this->articles->SuspendLayout();
			this->articleText->SuspendLayout();
			this->allArticles->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainTable))->BeginInit();
			this->peoples->SuspendLayout();
			this->actionButtons->SuspendLayout();
			this->SuspendLayout();
			// 
			// articles
			// 
			this->articles->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->articles->Controls->Add(this->richTextBox1);
			this->articles->Controls->Add(this->label6);
			this->articles->Controls->Add(this->label3);
			this->articles->Controls->Add(this->label2);
			this->articles->Controls->Add(this->label1);
			this->articles->Location = System::Drawing::Point(254, 30);
			this->articles->Name = L"articles";
			this->articles->Size = System::Drawing::Size(586, 219);
			this->articles->TabIndex = 2;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->richTextBox1->Location = System::Drawing::Point(3, 136);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(580, 79);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::richTextBox1_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(5, 112);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(77, 21);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Диагноз";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(5, 45);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 19);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Создан";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(5, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 19);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Изменен";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(3, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(328, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Медицинская карта пациента %s";
			// 
			// articleText
			// 
			this->articleText->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->articleText->Controls->Add(this->label4);
			this->articleText->Controls->Add(this->richTextBox2);
			this->articleText->Controls->Add(this->addProcedure);
			this->articleText->Controls->Add(this->deleteProcedure);
			this->articleText->Location = System::Drawing::Point(254, 255);
			this->articleText->Name = L"articleText";
			this->articleText->Size = System::Drawing::Size(586, 201);
			this->articleText->TabIndex = 3;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(6, 6);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(169, 21);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Протокол процедуры";
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(3, 31);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(580, 167);
			this->richTextBox2->TabIndex = 0;
			this->richTextBox2->Text = L"";
			this->richTextBox2->TextChanged += gcnew System::EventHandler(this, &MainForm::richTextBox2_TextChanged);
			// 
			// allArticles
			// 
			this->allArticles->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->allArticles->Controls->Add(this->mainTable);
			this->allArticles->Location = System::Drawing::Point(12, 30);
			this->allArticles->Name = L"allArticles";
			this->allArticles->Size = System::Drawing::Size(221, 219);
			this->allArticles->TabIndex = 5;
			// 
			// mainTable
			// 
			this->mainTable->AllowUserToAddRows = false;
			this->mainTable->AllowUserToDeleteRows = false;
			this->mainTable->AllowUserToResizeRows = false;
			this->mainTable->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->mainTable->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->mainTable->Location = System::Drawing::Point(3, 3);
			this->mainTable->MultiSelect = false;
			this->mainTable->Name = L"mainTable";
			this->mainTable->ReadOnly = true;
			this->mainTable->RowHeadersVisible = false;
			this->mainTable->ShowEditingIcon = false;
			this->mainTable->Size = System::Drawing::Size(215, 212);
			this->mainTable->TabIndex = 0;
			this->mainTable->SelectionChanged += gcnew System::EventHandler(this, &MainForm::mainTable_SelectionChanged);
			// 
			// peoples
			// 
			this->peoples->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->peoples->Controls->Add(this->treeView1);
			this->peoples->Location = System::Drawing::Point(12, 255);
			this->peoples->Name = L"peoples";
			this->peoples->Size = System::Drawing::Size(221, 201);
			this->peoples->TabIndex = 6;
			// 
			// treeView1
			// 
			this->treeView1->Location = System::Drawing::Point(4, 6);
			this->treeView1->Name = L"treeView1";
			this->treeView1->Size = System::Drawing::Size(214, 192);
			this->treeView1->TabIndex = 0;
			this->treeView1->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::treeView1_AfterSelect);
			// 
			// actionButtons
			// 
			this->actionButtons->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->actionButtons->Controls->Add(this->deleteButton);
			this->actionButtons->Controls->Add(this->editButton);
			this->actionButtons->Controls->Add(this->addButton);
			this->actionButtons->Location = System::Drawing::Point(13, 3);
			this->actionButtons->Name = L"actionButtons";
			this->actionButtons->Size = System::Drawing::Size(220, 21);
			this->actionButtons->TabIndex = 8;
			// 
			// deleteButton
			// 
			this->deleteButton->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->deleteButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->deleteButton->Location = System::Drawing::Point(61, 0);
			this->deleteButton->Name = L"deleteButton";
			this->deleteButton->Size = System::Drawing::Size(20, 21);
			this->deleteButton->TabIndex = 2;
			this->deleteButton->Text = L"✖";
			this->deleteButton->UseVisualStyleBackColor = true;
			this->deleteButton->Click += gcnew System::EventHandler(this, &MainForm::deleteButton_Click);
			// 
			// editButton
			// 
			this->editButton->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->editButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->editButton->Location = System::Drawing::Point(32, 0);
			this->editButton->Name = L"editButton";
			this->editButton->Size = System::Drawing::Size(23, 21);
			this->editButton->TabIndex = 1;
			this->editButton->Text = L"✎";
			this->editButton->UseVisualStyleBackColor = true;
			this->editButton->Click += gcnew System::EventHandler(this, &MainForm::editButton_Click);
			// 
			// addButton
			// 
			this->addButton->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->addButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->addButton->Location = System::Drawing::Point(3, 0);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(24, 21);
			this->addButton->TabIndex = 0;
			this->addButton->Text = L"➕";
			this->addButton->UseVisualStyleBackColor = true;
			this->addButton->Click += gcnew System::EventHandler(this, &MainForm::addButton_Click);

			// 
			// deleteProcedure
			// 
			this->deleteProcedure->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->deleteProcedure->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->deleteProcedure->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->deleteProcedure->Location = System::Drawing::Point(350, 0);
			this->deleteProcedure->Name = L"deleteProcedure";
			this->deleteProcedure->Size = System::Drawing::Size(112, 27);
			this->deleteProcedure->TabIndex = 2;
			this->deleteProcedure->Text = L"-Процедура";
			this->deleteProcedure->UseVisualStyleBackColor = true;
			this->deleteProcedure->Click += gcnew System::EventHandler(this, &MainForm::deleteProcedureButton_Click);
			// 
			// addProcedure
			// 
			this->addProcedure->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->addProcedure->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->addProcedure->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->addProcedure->Location = System::Drawing::Point(203, 0);
			this->addProcedure->Name = L"addProcedure";
			this->addProcedure->Size = System::Drawing::Size(112, 27);
			this->addProcedure->TabIndex = 0;
			this->addProcedure->Text = L"+Процедура";
			this->addProcedure->UseVisualStyleBackColor = true;
			this->addProcedure->Click += gcnew System::EventHandler(this, &MainForm::addProcedureButton_Click);

			// 
			// loginText
			// 
			this->loginText->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->loginText->Location = System::Drawing::Point(254, 0);
			this->loginText->Name = L"loginText";
			this->loginText->ReadOnly = true;
			this->loginText->Size = System::Drawing::Size(219, 26);
			this->loginText->TabIndex = 9;
			this->loginText->Text = L"Пользователь: " + msclr::interop::marshal_as<System::String^>(controller->db->workers[loginid]->getName());
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(884, 461);
			this->Controls->Add(this->loginText);
			this->Controls->Add(this->actionButtons);
			this->Controls->Add(this->peoples);
			this->Controls->Add(this->allArticles);
			this->Controls->Add(this->articleText);
			this->Controls->Add(this->articles);
			this->Name = L"MainForm";
			this->Text = L"Медицинская карта";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->articles->ResumeLayout(false);
			this->articles->PerformLayout();
			this->articleText->ResumeLayout(false);
			this->articleText->PerformLayout();
			this->allArticles->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainTable))->EndInit();
			this->peoples->ResumeLayout(false);
			this->actionButtons->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		void TreeUpdate(int id)
		{
			this->treeView1->BeginUpdate();
			this->treeView1->Nodes->Clear();
			TreeNode^ node = gcnew TreeNode(msclr::interop::marshal_as<String^>("Процедуры"), 0, -1);
			this->treeView1->Nodes->Add(node);
			std::vector<std::wstring> temp = controller->getProcedures(id);
			for (int i = 0; i < temp.size(); ++i) {
				node = gcnew TreeNode(L"", 0, 1);
				node->Name = msclr::interop::marshal_as<String^>(temp[i]);
				node->Text = msclr::interop::marshal_as<String^>(temp[i]);
				this->treeView1->Nodes[0]->Nodes->Add(node);
			}
			this->treeView1->EndUpdate();
		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		ToolTip^ toolTip1 = gcnew ToolTip;
		toolTip1->SetToolTip(this->deleteButton, "Удалить карту");
		toolTip1->SetToolTip(this->editButton, "Редактирование карты");
		toolTip1->SetToolTip(this->addButton, "Добавить карту");
		Table = gcnew DataTable();
		Set = gcnew DataSet();
		mainTable->DataSource = Table;
		Table->Columns->Add(L"Имя");
		Table->Columns->Add(L"Дата рождения");
		Set->Tables->Add(Table);
		for (int i = 0; i < controller->db->patients.size(); ++i) {
			Table->Rows->Add(msclr::interop::marshal_as<System::String^>(controller->db->patients[i]->getName()), msclr::interop::marshal_as<System::String^>(controller->db->patients[i]->getDob()));
		}
		for (int i = 0; i < this->mainTable->Columns->Count; ++i) {
			this->mainTable->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
		}
		MainForm::Update();
	}
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		// Выгрузка
	}
	private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e) {
		Client::Creation creationform;
		creationform.ShowDialog();
		if (creationform.name->Length != 0 && creationform.dob->Length != 0 && creationform.diagnosis->Length != 0) {
			String^ _ = creationform.name;
			String^ __ = creationform.dob;
			String^ ___ = creationform.diagnosis;
			controller->pushPatient(
				int(controller->db->patients.size() + 1),
				msclr::interop::marshal_as<std::wstring>(_),
				msclr::interop::marshal_as<std::wstring>(__),
				msclr::interop::marshal_as<std::wstring>(DateTime::Now.ToString("dd.MM.yyyy")),
				msclr::interop::marshal_as<std::wstring>(DateTime::Now.ToString("dd.MM.yyyy")),
				msclr::interop::marshal_as<std::wstring>(___)
			);
			Table->Rows->Add(_, __);
			MainForm::Update();
		}
	}
	private: System::Void editButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int tempid = mainTable->CurrentCell->RowIndex;
		if (tempid >= 0 && tempid < controller->db->patients.size()) {
			Client::EditForm editform(this->mainTable->Rows[tempid]->Cells[0]->Value->ToString(), this->mainTable->Rows[tempid]->Cells[1]->Value->ToString());
			editform.ShowDialog();
			if (editform.name->Length != 0 || editform.dob->Length != 0) {
				if (editform.name != this->mainTable->Rows[tempid]->Cells[0]->Value || editform.dob != this->mainTable->Rows[tempid]->Cells[1]->Value) {
					String^ _ = editform.name;
					String^ __ = editform.dob;
					controller->editPatient(tempid,
						msclr::interop::marshal_as<std::wstring>(_),
						msclr::interop::marshal_as<std::wstring>(__));
					this->mainTable->Rows[tempid]->Cells[0]->Value = editform.name;
					this->mainTable->Rows[tempid]->Cells[1]->Value = editform.dob;
					MainForm::Update();
				}
			}
		}
	}
	private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int tempid = mainTable->CurrentCell->RowIndex;
		if (tempid >= 0 && tempid < controller->db->patients.size()) {
			System::Windows::Forms::DialogResult dialogRes = MessageBox::Show(this, L"Вы уверены, что хотите удалить карту?", "Подтверждение", MessageBoxButtons::OKCancel, MessageBoxIcon::Question);
			if (System::Windows::Forms::DialogResult::OK == dialogRes) {
				this->mainTable->Rows->RemoveAt(tempid);
				controller->deletePatient(int(tempid));
				MainForm::Update();
			}
		}
	}
	private: System::Void mainTable_SelectionChanged(System::Object^ sender, System::EventArgs^ e) {
		int tempid = mainTable->CurrentCell->RowIndex;
		if (tempid >= 0 && tempid < controller->db->patients.size() && predId != tempid) {
			TreeUpdate(tempid);
			this->treeView1->ExpandAll();
			this->label1->Text = L"Медицинская карта пациента " + msclr::interop::marshal_as<String^>(controller->db->patients[tempid]->getName());
			this->label2->Text = L"Изменен: " + msclr::interop::marshal_as<String^>(controller->db->patients[tempid]->getChange());
			this->label3->Text = L"Создан: " + msclr::interop::marshal_as<String^>(controller->db->patients[tempid]->getCreation());
			this->richTextBox1->Clear();
			this->richTextBox1->AppendText(msclr::interop::marshal_as<String^>(controller->db->patients[tempid]->getDiagnosis()));
		}
		predId = tempid;
	}
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		int tempid = mainTable->CurrentCell->RowIndex;
		if (tempid >= 0 && tempid < controller->db->patients.size() && this->richTextBox1->Focused) {
			String^ _ = richTextBox1->Text;
			controller->editPatientDiagnosis(tempid, msclr::interop::marshal_as<std::wstring>(_), msclr::interop::marshal_as<std::wstring>(DateTime::Now.ToString("dd.MM.yyyy")));
			this->label2->Text = L"Изменен: " + msclr::interop::marshal_as<String^>(controller->db->patients[tempid]->getChange());
		}
	}
	private: System::Void richTextBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		int tempid = mainTable->CurrentCell->RowIndex;
		if (this->treeView1->SelectedNode->Level == 1 && tempid >= 0 && tempid < controller->db->patients.size() && this->richTextBox2->Focused) {
			String^ _ = richTextBox2->Text;
			controller->editProcedure(tempid, msclr::interop::marshal_as<std::wstring>(this->treeView1->SelectedNode->Text), msclr::interop::marshal_as<std::wstring>(_));
			this->treeView1->SelectedNode->Text = richTextBox2->Text;
		}
	}
	private: System::Void treeView1_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e) {
		if (this->treeView1->SelectedNode->Level == 1) {
			this->richTextBox2->Clear();
			this->richTextBox2->AppendText(this->treeView1->SelectedNode->Text);
		}
	}
	private: System::Void addProcedureButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int tempid = mainTable->CurrentCell->RowIndex;
		if (this->treeView1->Focus()) {
			if (this->treeView1->SelectedNode->Level == 1 && tempid >= 0 && tempid < controller->db->patients.size()) {
				Client::ProcedureCreation create;
				create.ShowDialog();
				if (create.text->Length != 0) {
					String^ _ = create.text;
					controller->addProcedure(tempid,
						msclr::interop::marshal_as<std::wstring>(_),
						msclr::interop::marshal_as<std::wstring>(DateTime::Now.ToString("dd.MM.yyyy")),
						lid);
					this->treeView1->SelectedNode->Parent->Nodes->Add(_);
				}
			}
		}
	}
	private: System::Void deleteProcedureButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int tempid = mainTable->CurrentCell->RowIndex;
		if (this->treeView1->Focus()) {
			if (this->treeView1->SelectedNode->Level == 1 && tempid >= 0 && tempid < controller->db->patients.size()) {
				System::Windows::Forms::DialogResult dialogRes = MessageBox::Show(this, L"Вы уверены, что хотите удалить процедуру?", "Подтверждение", MessageBoxButtons::OKCancel, MessageBoxIcon::Question);
				if (System::Windows::Forms::DialogResult::OK == dialogRes) {
					controller->deleteProcedure(tempid, msclr::interop::marshal_as<std::wstring>(this->treeView1->SelectedNode->Text));
					this->treeView1->SelectedNode->Remove();
				}
			}
		}
	}
};
}
