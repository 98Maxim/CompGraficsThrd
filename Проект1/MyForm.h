#pragma once

namespace Проект1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		System::Collections::Generic::List<line> lines;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
	private: float height;
	private: float width;
	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->DefaultExt = L"txt";
			this->openFileDialog->FileName = L"openFileDialog1";
			this->openFileDialog->Filter = L"Текстовые файлы(*txt)|*.txt|Все файлы(*.*)|*.*";
			this->openFileDialog->Title = L"Открыть файл";
			// 
			// btnOpen
			// 
			this->btnOpen->BackColor = System::Drawing::SystemColors::ControlDark;
			this->btnOpen->Location = System::Drawing::Point(623, 34);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(303, 119);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Приоткрыть";
			this->btnOpen->UseVisualStyleBackColor = false;
			this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(990, 702);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		lines.Clear();
		unit(T);
	}
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		System::Drawing::Graphics^ g = e->Graphics;
		Rectangle rect = Form::ClientRectangle;
		width = rect.Width;
		height = rect.Height;
		System::Drawing::Pen^ blackPen = gcnew Pen(Color::Black);
		blackPen->Width = 4;
		for (int i = 0; i<lines.Count; i++) {
			vec A, B;
			point2vec(lines[i].start, A);
			point2vec(lines[i].end, B);
			vec A1, B1;
			timesMatVec(T, A, A1);
			timesMatVec(T, B, B1);
			point a, b;
			vec2point(A1, a);
			vec2point(B1, b);
			g->DrawLine(blackPen, a.x, a.y, b.x, b.y);
			
		}
	}
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) { //click on btn
		if (this->openFileDialog->ShowDialog() ==
			System::Windows::Forms::DialogResult::OK) {
			wchar_t fileName[1024];
			for (int i = 0; i<openFileDialog->FileName->Length; i++)
				fileName[i] = openFileDialog->FileName[i];
			fileName[openFileDialog->FileName->Length] = '\0';
			std::ifstream in;
			in.open(fileName);
			if (in.is_open()) {
				lines.Clear();
				unit(T);
				std::string str;
				getline(in, str);
				while (in) {
					if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
						&& (str[0] != '#')) {
						std::stringstream s(str);
						line l;
						s >> l.start.x >> l.start.y >> l.end.x >> l.end.y;
						std::string linename;
						s >> linename;
						l.name = gcnew String(linename.c_str());
						lines.Add(l);
					}
					getline(in, str);
				}
				mat R, T1;
				mirror(1, width, height, R, T);
				times(R, T, T1);
				set(T1, T);
				unit(R);
				move(0, -height / 2, R);
				times(R, T, T1);
				set(T1, T);
				this->Refresh();
			}
		}
	}
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		mat R, T1;
		switch (e->KeyCode) {
		case Keys::W:
			move(0, -1, R);
			break;
		case Keys::S:
			move(0, 1, R);
			break;
		case Keys::A:
			move(-1, 0, R);
			break;
		case Keys::D:
			move(1, 0, R);
			break;
		case Keys::E:
			rotate(0.05, R);
			break;
		case Keys::X:
			scale(1.1, R);
			break; //end template code

		case Keys::Q:
			rotate(-0.05, R);
			break;
		case Keys::Z:
			scale(1/1.1, R);
			break;
		case Keys::T:
			move(0, -5, R);
			break;
		case Keys::G:
			move(0, 5, R);
			break;
		case Keys::F:
			move(-5, 0, R);
			break;
		case Keys::H:
			move(5, 0, R);
			break;
		case Keys::U:
			mirror(0, width, height, R, T);
			break;
		case Keys::J:
			mirror(1, width, height, R, T);
			break;
		case Keys::R:
			move(-width / 2, -height / 2, R);
			times(R, T, T1);
			set(T1, T);
			rotate(-0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2, height / 2, R);
			break;
		case Keys::Y:
			move(-width / 2, -height / 2, R);
			times(R, T, T1);
			set(T1, T);
			rotate(0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2, height / 2, R);
			break;
		case Keys::C:
			move(-width / 2, -height / 2, R);
			times(R, T, T1);
			set(T1, T);
			scale(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2, height / 2, R);
			break;
		case Keys::V:
			move(-width / 2, -height / 2, R);
			times(R, T, T1);
			set(T1, T);
			scale(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2, height / 2, R);
			break;


		

		case Keys::K:
			move(0, -height / 2, R);
			times(R, T, T1);
			set(T1, T);
			scale_y(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(0, height / 2, R);
			break;
		case Keys::I:
			move(0, -height / 2, R);
			times(R, T, T1);
			set(T1, T);
			scale_y(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(0, height / 2, R);
			break;
		case Keys::L:
			move(-width / 2, 0, R);
			times(R, T, T1);
			set(T1, T);
			scale_x(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2, 0, R);
			break;
		case Keys::O:
			move(-width / 2, 0, R);
			times(R, T, T1);
			set(T1, T);
			scale_x(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2, 0, R);
			break;

		case Keys::Escape:
			unit(T);
			unit(R);
			mirror(1, width, height, R, T);
			times(R, T, T1);
			set(T1, T);
			unit(R);
			move(0, -height / 2, R);
			times(R, T, T1);
			set(T1, T);
			unit(R);

		default:unit(R);
		}
		times(R, T, T1);
		set(T1, T);
		this->Refresh();
	}
	};
}