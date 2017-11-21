#pragma once
#include <fstream>
#include <sstream>
#include "Clip.h"
#include "Transform.h"
#include <iostream>

namespace Проект1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Collections::Generic::List<line> lines;
	private: System::Collections::Generic::List<polygon^> polygons;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
	private: float height;
	private: float width;
	private: float left, right, top, bottom; //new template
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;
	bool drawNames;
	private: int R, G, B = 0; //для цвета красный зеленый голубой, по умолчанию - черный

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
			this->btnOpen->AllowDrop = true;
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->AutoEllipsis = true;
			this->btnOpen->AutoSize = true;
			this->btnOpen->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->btnOpen->BackColor = System::Drawing::SystemColors::ControlDark;
			this->btnOpen->Location = System::Drawing::Point(733, 12);
			this->btnOpen->MinimumSize = System::Drawing::Size(100, 100);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(102, 100);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"Открыть портал!";
			this->btnOpen->UseVisualStyleBackColor = false;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(990, 702);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MinimumSize = System::Drawing::Size(600, 400);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) { //процедура загрузки формы
		drawNames = false;
		left = 70; 
		right = 30;
		top = 120;
		bottom = 30;

		height = Form::ClientRectangle.Height;
		width = Form::ClientRectangle.Width;

		Wcx = left; //template
		Wcy = height - bottom;
		Wx = width - left - right;
		Wy = height - top - bottom;
		//aaaaaaaa

		//lines.Clear();
		polygons.Clear();
		unit(T);
	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		System::Drawing::Graphics^ g = e->Graphics;
		System::Drawing::Pen^ blackPen = gcnew Pen(Color::Red);
		blackPen->Width = 2;
		Pen^ rectPen = gcnew Pen(Color::Green);
		rectPen->Width = 4;
		g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
		System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
		SolidBrush^ drawBrush = gcnew SolidBrush(Color::Red);
		point Pmin, Pmax;
		Pmin.x = left;
		Pmin.y = top;
		Pmax.x = Form::ClientRectangle.Width - right;
		Pmax.y = Form::ClientRectangle.Height - bottom;
		for (int i = 0; i < polygons.Count; i++) {
			polygon^ p = polygons[i];
			polygon^ p1 = gcnew polygon(0);
			point a, b, c;
			vec A, B, A1, B1;
			for (int j = 0; j < p->Count; j++)
			{
				point2vec(p[j], B);
				timesMatVec(T, B, B1);
				vec2point(B1, b);
				p1->Add(b);
			}
			p1 = Pclip(p1, Pmin, Pmax);
			if (p1->Count != 0)
			{
				a = p1[p1->Count - 1];
				for (int j = 0; j < p1->Count; j++)
				{
					b = p1[j];
					g->DrawLine(blackPen, a.x, a.y, b.x, b.y);
					a = b;
				}
			}
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
			if (in.is_open())
			{
				polygons.Clear();
				std::stack<mat> matStack;
				mat K;
				unit(K);
				unit(T);
				std::string str;
				getline(in, str);
				while (in) {
					if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
						std::stringstream s(str);
						std::string cmd1;
						System::String^ cmd;
						s >> cmd1;
						cmd = gcnew String(cmd1.c_str());
						if (cmd == "frame") {
							float newVcx, newVcy, newVx, newVy;
							s >> newVcx >> newVcy >> newVx >> newVy;
							Vcx = newVcx;
							Vcy = newVcy;
							Vx = newVx;
							Vy = newVy;
							frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
						}
						else if (cmd == "polygon") {
							int numpoint;
							s >> numpoint;
							polygon^ P = gcnew polygon(0);
							for (int i = 0; i < numpoint; i++) {
								point p;
								s >> p.x >> p.y;
								P->Add(p);
							}
							polygons.Add(P);
						}
					}
					getline(in, str);
				}
			}
			this->Refresh();
		}
	}
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		const int RANGE = 42;
		static int counterX = 0;
		static int counterZ = 0;
		mat R, T1;
		switch (e->KeyCode) {
		case Keys::W:
			move(0, -1.0, R);
			break;
		case Keys::S:
			move(0, 1.0, R);
			break;
		case Keys::A:
			move(-1.0, 0, R);
			break;
		case Keys::D:
			move(1.0, 0, R);
			break;
		case Keys::E:
			rotate(0.05F, R);
			break;
		case Keys::X:
			if (-RANGE < counterX && counterX < RANGE) {
				counterX++;
				if (-RANGE < counterZ - 1) { counterZ--; }

				scale(1.1, R);
			}
			else {
				scale(1.0, R);
			}
			//if (-RANGE <= counterZ <= RANGE) { counterZ--; }
			break; //end template code

		case Keys::Q:
			rotate(-0.05F, R);
			break;
		case Keys::Z:
			//if (-RANGE <= counterX && counterX <= RANGE) { counterX--; }
			if (-RANGE < counterZ && counterZ < RANGE) {
				counterZ++;
				if (-RANGE < counterX - 1) { counterX--; }
				scale(1 / 1.1, R);
			}
			else {
				scale(1.0, R);
			}
			break;
		case Keys::T:
			move(0, -5.0, R);
			break;
		case Keys::G:
			move(0, 5.0, R);
			break;
		case Keys::F:
			move(-5.0, 0, R);
			break;
		case Keys::H:
			move(5.0, 0, R);
			break;
		case Keys::U:
			reflectH(R);
			times(R, T, T1);
			set(T1, T);
			move(0, height - bottom + top, R);
			break;
		case Keys::J:
			reflectV(R);
			times(R, T, T1);
			set(T1, T);
			move(width - right + left, 0, R);
			break;
		case Keys::R:
			move(-width / 2 - 0.0F, -height / 2 - 0.0F, R);
			times(R, T, T1);
			set(T1, T);
			rotate(-0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2 - 0.0F, height / 2 - 0.0F, R);
			break;
		case Keys::Y:
			move(-width / 2 - 0.0F, -height / 2 - 0.0F, R);
			times(R, T, T1);
			set(T1, T);
			rotate(0.05, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2 - 0.0F, height / 2 - 0.0F, R);
			break;
		case Keys::C:
			move(-width / 2 - 0.0F, -height / 2 - 0.0F, R);
			times(R, T, T1);
			set(T1, T);
			scale(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2 - 0.0F, height / 2 - 0.0F, R);
			break;
		case Keys::V:
			move(-width / 2 - 0.0F, -height / 2 - 0.0F, R);
			times(R, T, T1);
			set(T1, T);
			scale(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2 - 0.0F, height / 2 - 0.0F, R);
			break;




		case Keys::K:
			move(0, -height / 2.0, R);
			times(R, T, T1);
			set(T1, T);
			scaleY(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(0, height / 2.0, R);
			break;
			break;
		case Keys::I:
			move(0, -height / 2.0, R);
			times(R, T, T1);
			set(T1, T);
			scaleY(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(0, height / 2.0, R);
			break;
		case Keys::L:
			move(-width / 2.0, 0, R);
			times(R, T, T1);
			set(T1, T);
			scaleX(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2.0, 0, R);
			break;
		case Keys::O:
			move(-width / 2.0, 0, R);
			times(R, T, T1);
			set(T1, T);
			scaleX(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(width / 2.0, 0, R);
			break;

		case Keys::Escape:
			unit(T);
			unit(R);
			////mirror(1, width, height, R, T);
			//times(R, T, T1);
			//set(T1, T);
			//unit(R);
			//move(0, -height / 2.0, R);
			//times(R, T, T1);
			//set(T1, T);
			//unit(R);
			frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
			counterX = 0;
			counterZ = 0;



		default:unit(R);
		}
		times(R, T, T1);
		set(T1, T);
		this->Refresh();
	}
	private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) { //TODO
		Wcx = left;
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;

		this->Refresh(); //обновляет форму?
	}
};
}