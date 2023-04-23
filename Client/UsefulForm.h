#include "Controller.h"
#include <msclr\marshal_cppstd.h>

#pragma once

struct Comp
{
	bool operator()(Man* s, int i) const { return s->getId() < i; }
	bool operator()(int i, Man* s) const { return i < s->getId(); }
};

struct SetComp {
	bool operator() (Man* a, Man* b) const {
		return a->getId() < b->getId();
	}
};

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ UsefulForm
	/// </summary>
	public ref class UsefulForm : public System::Windows::Forms::Form
	{
	public:
		UsefulForm(void)
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
		~UsefulForm()
		{
			if (components)
			{
				delete components;
			}
			for (std::multiset<Man*>::iterator i = container->begin(); i != container->end(); ++i) {
				delete *i;
			}
			delete container;
		}
	private: CController* controller;
	private: DataTable^ Table;
	private: DataSet^ Set;
	private: std::multiset<Man*, SetComp>* container;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UsefulForm::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dataGridView1->EnableHeadersVisualStyles = false;
			this->dataGridView1->Location = System::Drawing::Point(21, 12);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->dataGridView1->ShowCellErrors = false;
			this->dataGridView1->ShowCellToolTips = false;
			this->dataGridView1->ShowEditingIcon = false;
			this->dataGridView1->ShowRowErrors = false;
			this->dataGridView1->Size = System::Drawing::Size(240, 205);
			this->dataGridView1->TabIndex = 0;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(224, 223);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(48, 26);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &UsefulForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(5, 226);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(213, 19);
			this->label1->TabIndex = 3;
			this->label1->Text = L"¬ведите численное значение: ";
			// 
			// UsefulForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->dataGridView1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"UsefulForm";
			this->Text = L"Ћюди в больнице";
			this->Load += gcnew System::EventHandler(this, &UsefulForm::UsefulForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void UsefulForm_Load(System::Object^ sender, System::EventArgs^ e) {
		std::set<Man*> p, w;
		container = new std::multiset<Man*, SetComp>();
		for (int i = 0; i < controller->db->patients.size(); ++i) {
			p.insert(controller->db->patients[i]->copy());
		}
		for (int i = 0; i < controller->db->workers.size(); ++i) {
			w.insert(controller->db->workers[i]->copy());
		}
		std::set_union(p.begin(), p.end(), w.begin(), w.end(), std::inserter(*container, container->begin()));
		Table = gcnew DataTable();
		Set = gcnew DataSet();
		dataGridView1->DataSource = Table;
		Table->Columns->Add(L"»м€");
		Table->Columns->Add(L"ID");
		Set->Tables->Add(Table);
		for (std::multiset<Man*>::iterator i = container->begin(); i != container->end(); ++i) {
			Table->Rows->Add(msclr::interop::marshal_as<System::String^>((*i)->getName()), (*i)->getId());
		}
		for (int i = 0; i < this->dataGridView1->Columns->Count; ++i) {
			this->dataGridView1->Columns[i]->SortMode = DataGridViewColumnSortMode::NotSortable;
		}
		UsefulForm::Update();
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->textBox1->Text->Length != 0) {
			Int32 number1 = 0;
			System::String^ tempstr1 = System::Convert::ToString(this->textBox1->Text);
			if (Int32::TryParse(tempstr1, number1)) {
				auto temp = std::equal_range(container->begin(), container->end(), number1, Comp{});
				this->Table->Clear();
				this->dataGridView1->Refresh();
				for (auto i = temp.first; i != temp.second; ++i) {
					Table->Rows->Add(msclr::interop::marshal_as<System::String^>((*i)->getName()), (*i)->getId());
				}
				UsefulForm::Update();
			}
		}
	}
};
}
