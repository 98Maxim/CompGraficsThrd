#pragma once
#include <fstream>
#include <sstream>
#include "Clip.h"
#include "Transform.h"
#include <iostream>

namespace ������1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:System::Collections::Generic::List<line> lines;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;
	private: float height;
	private: float width;
	private: float left, right, top, bottom; //new template
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;
	bool drawNames;
	private: System::Void DrawFigure(Graphics^ g, Pen^ blackPen, Pen^ Pen) {
		g->DrawRectangle(Pen, -30, -20, 61, 41);
		g->DrawLine(blackPen, -20, 220 / 13, 5, 220 / 13);
		g->DrawLine(blackPen, -20, 220 / 13, -20, 60 / 13);
		g->DrawLine(blackPen, -20, 60 / 13, 5, 60 / 13);
		g->DrawLine(blackPen, 5, 220 / 13, 5, 60 / 13);
		g->DrawLine(blackPen, -15, 60 / 13, -15, 20 / 13);
		g->DrawLine(blackPen, 0, 60 / 13, 0, 20 / 13);
		g->DrawLine(blackPen, -30, 20 / 13, -30, -20 / 13);
		g->DrawLine(blackPen, -30, 20 / 13, 30, 20 / 13);
		g->DrawLine(blackPen, -30, -20 / 13, 30, -20 / 13);
		g->DrawLine(blackPen, 30, 20 / 13, 30, -20 / 13);
		g->DrawLine(blackPen, -25, -20 / 13, -25, -20);
		g->DrawLine(blackPen, -20, -20 / 13, -20, -20);
		g->DrawLine(blackPen, -25, -20, -20, -20);
		g->DrawLine(blackPen, 15, 20, 15, 20 / 13);
		g->DrawLine(blackPen, 25, 20, 25, 20 / 13);
		g->DrawLine(blackPen, 15, 20, 25, 20);
		g->DrawLine(blackPen, 17.5, 220 / 13, 22.5, 220 / 13);
		g->DrawLine(blackPen, 5, -20 / 13, 5, -20);
		g->DrawLine(blackPen, 25, -20 / 13, 25, -20);
		g->DrawLine(blackPen, 5, -20, 25, -20);
		g->DrawLine(blackPen, 10, -100 / 13, 10, -140 / 13);
		mat c;
	}

	private:
		/// <summary>
		/// ��������� ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ������������ ����� ��� ��������� ������������ - �� ���������
		/// ���������� ������� ������ ��� ������ ��������� ����.
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
			this->openFileDialog->Filter = L"��������� �����(*txt)|*.txt|��� �����(*.*)|*.*";
			this->openFileDialog->Title = L"������� ����";
			// 
			// btnOpen
			// 
			this->btnOpen->AllowDrop = true;
			this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btnOpen->AutoSize = true;
			this->btnOpen->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->btnOpen->BackColor = System::Drawing::SystemColors::ControlDark;
			this->btnOpen->Location = System::Drawing::Point(627, 12);
			this->btnOpen->MinimumSize = System::Drawing::Size(100, 100);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(102, 100);
			this->btnOpen->TabIndex = 0;
			this->btnOpen->Text = L"������� ������!";
			this->btnOpen->UseVisualStyleBackColor = false;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 562);
			this->Controls->Add(this->btnOpen);
			this->KeyPreview = true;
			this->MaximumSize = System::Drawing::Size(900, 600);
			this->MinimumSize = System::Drawing::Size(900, 600);
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
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) { //��������� �������� �����
		drawNames = false;
		left = 70; 
		right = 30;
		top = 120;
		bottom = 30;
		Wcx = left; //template
		Wcy = Form::ClientRectangle.Height - bottom;
		Wx = Form::ClientRectangle.Width - left - right;
		Wy = Form::ClientRectangle.Height - top - bottom;
		//aaaaaaaa

		lines.Clear();
		unit(T);
	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		System::Drawing::Graphics^ g = e->Graphics;
		Rectangle rect1 = Form::ClientRectangle;
		width = rect1.Width+(left-right);
		height = rect1.Height+(top-bottom);
		System::Drawing::Pen^ blackPen = gcnew Pen(Color::Black);
		System::Drawing::Pen^ rectPen = gcnew Pen(Color::Green);
		rectPen->Width = 2;
		//g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);
		Rectangle rect = System::Drawing::Rectangle(Wcx, top, Wx, Wy);
		g->DrawRectangle(rectPen, rect);
		g->Clip = gcnew System::Drawing::Region(rect);
		blackPen->Width = 4;
		System::Drawing::Pen^ Pen1 = gcnew Pen(Color::Black);
		Pen1->Width = 1;

		g->Transform = gcnew System::Drawing::Drawing2D::Matrix(T[0][0], T[1][0],
			T[0][1], T[1][1],
			T[0][2], T[1][2]);
		for (int i = 0; i < matrices.size(); i++) {
			mat �;
			times(T, matrices[i], �);
			g->Transform = gcnew System::Drawing::Drawing2D::Matrix(�[0][0], �[1][0], �[0][1], �[1][1], �[0][2], �[1][2]);
			DrawFigure(g, blackPen, Pen1);
		}
		

		

		/*for (int i = 0; i<lines.Count; i++) { old method
			vec A, B;
			point2vec(lines[i].start, A);
			point2vec(lines[i].end, B);
			vec A1, B1;
			timesMatVec(T, A, A1);
			timesMatVec(T, B, B1);
			point a, b;
			vec2point(A1, a);
			vec2point(B1, b);
			if (Clip(a.x, b.x, a.y, b.y, Wcx, Wcy - Wy, Wcx + Wx, Wcy))
				g->DrawLine(blackPen, a.x, a.y, b.x, b.y);
			if (drawNames)
			{
				System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 10);
				SolidBrush^ drawBrush = gcnew SolidBrush(Color::Blue);
				if (Clip(a.x, b.x, a.y, b.y, Wcx, Wcy - Wy, Wcx + Wx, Wcy))
					g->DrawString(lines[i].name, drawFont, drawBrush, (a.x + b.x) / 2, (a.y + b.y) / 2);
			}
		}*/
	}
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 if ( this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK){
						wchar_t fileName[1024];
						for (int i = 0; i < openFileDialog->FileName->Length; i++)
						fileName[i] = openFileDialog->FileName[i];
						fileName[openFileDialog->FileName->Length] = '\0';
						std::ifstream in;
					 in.open(fileName);
					 if (in.is_open()) { 
						 matrices.clear(); 
						 std::stack<mat> matStack; 
						 mat K; 
						 unit(K);
						 unit(T);
						 std::string str;
						 getline (in, str);
						
						 while (in) { 
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) { 

								 std::stringstream s(str);
								 std::string cmd; 
								 s >> cmd; 
								 if ( cmd == "frame" ) {
									 float newVcx, newVcy, newVx, newVy;
									 s >>  newVcx >> newVcy >> newVx >> newVy;
									 Vcx = newVcx; 
									 Vcy = newVcy;
									 Vx = newVx;
									 Vy = newVy;
									 frame (Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
								 }
								 else if ( cmd == "figure" ) {
									 matrices.push_back(K); 
								 }
								 else if ( cmd == "pushTransform" ) {
									 matStack.push(K);
								 }
								 else if ( cmd == "popTransform" ) {
									 K = matStack.top(); 
									 matStack.pop(); 
								 }
								 else if ( cmd == "translate" ) {
									 float Tx, Ty; 
									 s >> Tx >> Ty;
									 mat C, C1;
									 move(Tx, Ty, C);
									 times(K, C, C1);
									 K = C1;
								 }
								 else if ( cmd == "scale" ) {
									 float S; 
									 s >> S;
									 mat C, C1;
									 scale_x2(S, S, C);
									 times(K, C, C1);
									 K = C1;
								 }
								 else if ( cmd == "rotate" ) {
									 float Phi; 
									 s >> Phi;
									 float pi = 3.1415926535;
									 float PhiR = Phi * (pi / 180);
									 mat C, C1;
									 rotate(PhiR, C);
									 times(K, C, C1);
									 K = C1;
								 }
							 }
							 getline (in, str);
						 }
						}
						
							frame (Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy,T );
							this -> Refresh();
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
				if (-RANGE < counterZ - 1) {counterZ--;}
				
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
			} else {
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
			unit(R);
			R[1][1] = -1;
			times(R, T, T1);
			set(T1, T);
			move(0, height, R);
			break;
		case Keys::J:
			unit(R);
			R[0][0] = -1;
			times(R, T, T1);
			set(T1, T);
			move(width, 0, R);
			break;
		case Keys::R:
			move(-width / 2-0.0F, -height / 2-0.0F, R);
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
			scale(1/1.1, R);
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
			move(0, -System::Windows::Forms::Form::ClientRectangle.Height / 2.0, R);
			times(R, T, T1);
			set(T1, T);
			scaleY(1 / 1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(0, System::Windows::Forms::Form::ClientRectangle.Height / 2.0, R);
			break;
			break;
		case Keys::I:
			move(0, -System::Windows::Forms::Form::ClientRectangle.Height / 2.0, R);
			times(R, T, T1);
			set(T1, T);
			scaleY(1.1, R);
			times(R, T, T1);
			set(T1, T);
			move(0, System::Windows::Forms::Form::ClientRectangle.Height / 2.0, R);
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
			 mirror(1, width, height, R, T);
			 times(R, T, T1);
			 set(T1, T);
			 unit(R);
			 move(0, -height / 2.0, R);
			 times(R, T, T1);
			 set(T1, T);
			 unit(R);
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
		this->Refresh(); //��������� �����?
	}
};
}