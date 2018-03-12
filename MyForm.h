#pragma once

#include "MP.h"

namespace testCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:  
		bool playing = 0;
		int playingSongIndex;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	public:
		float currentTime = 0;
		MyForm(void)
		{
			InitMusicPlayer();
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			//OpenFile("C:/Users/User/Desktop/08_piece_of_cake.wav");
			//SelectMusic("C:/Users/User/Desktop/08_piece_of_cake.wav");
			//playing = 1;
			
			dataGridView1->Rows->Add("piece of cake", "shiho x rika", "idolm@ster", "4:20", "offline", "C:/Users/User/Desktop/08_piece_of_cake.wav");
			dataGridView1->Rows->Add("sweet sweet soul", "serika x akane x tamaki", "idolm@ster", "4:53", "offline", "C:/Users/User/Desktop/Sweet_Sweet_Soul.wav");
			dataGridView1->Rows->Add("no curry no life", "anna x rio x kana", "idolm@ster", "3:59", "offline", "C:/Users/User/Desktop/NO_CURRY_NO_LIFE.wav");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"PMingLiU", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(154, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(159, 40);
			this->label1->TabIndex = 0;
			this->label1->Text = L"songTitle";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"PMingLiU", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(156, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(125, 27);
			this->label2->TabIndex = 1;
			this->label2->Text = L"song Artist";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(150, 150);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button1->Location = System::Drawing::Point(455, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(62, 62);
			this->button1->TabIndex = 3;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::Previous_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Control;
			this->button2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.BackgroundImage")));
			this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button2->Location = System::Drawing::Point(523, 32);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(62, 62);
			this->button2->TabIndex = 4;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::Play_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Control;
			this->button3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.BackgroundImage")));
			this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button3->Location = System::Drawing::Point(591, 32);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(62, 62);
			this->button3->TabIndex = 5;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::Next_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(395, 105);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(315, 45);
			this->trackBar1->TabIndex = 6;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(797, 23);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Volume";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::Volume_Click);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(868, 23);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(104, 45);
			this->trackBar2->TabIndex = 8;
			// 
			// button5
			// 
			this->button5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button5.BackgroundImage")));
			this->button5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button5->Location = System::Drawing::Point(359, 52);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(40, 40);
			this->button5->TabIndex = 9;
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::Backward_Click);
			// 
			// button6
			// 
			this->button6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button6.BackgroundImage")));
			this->button6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button6->Location = System::Drawing::Point(727, 52);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(40, 40);
			this->button6->TabIndex = 10;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::Forward_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->Column1,
					this->Column2, this->Column3, this->Column4, this->Column5, this->Column6
			});
			this->dataGridView1->Location = System::Drawing::Point(53, 201);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(850, 230);
			this->dataGridView1->TabIndex = 11;
			this->dataGridView1->CellDoubleClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::Table_Select);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Name";
			this->Column1->Name = L"Column1";
			this->Column1->Width = 130;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Artist";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 130;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Album";
			this->Column3->Name = L"Column3";
			this->Column3->Width = 130;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Length";
			this->Column4->Name = L"Column4";
			this->Column4->Width = 130;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Online/Offline";
			this->Column5->Name = L"Column5";
			this->Column5->Width = 130;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Path";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 200;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(348, 105);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(51, 12);
			this->label3->TabIndex = 12;
			this->label3->Text = L"TimeNow";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(716, 105);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 12);
			this->label4->TabIndex = 13;
			this->label4->Text = L"SongLength";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(984, 461);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Play_Click(System::Object^  sender, System::EventArgs^  e) {
		if (playing) {
			playing = 0;
			currentTime = GetCurrentPlaybackTime();

			wchar_t buf[100];
			swprintf_s(buf, 100, L"stopped, Current Time Now %f\n", currentTime);
			OutputDebugString(buf);
			
			PauseMusic();
			//ClosePlayer();			
		}
		else {
			currentTime = GetCurrentPlaybackTime();

			wchar_t buf[100];
			swprintf_s(buf, 100, L"playing, Current Time Now %f\n", currentTime);
			OutputDebugString(buf);

			RestartMusic();
			//Playback(currentTime);
			playing = 1;
		}		
	}
	private: System::Void Forward_Click(System::Object^  sender, System::EventArgs^  e) {
		SkipSecond(10000);
		currentTime = GetCurrentPlaybackTime();

		wchar_t buf[100];
		swprintf_s(buf, 100, L"10s rewind, Current Time Now %f\n", currentTime);
		OutputDebugString(buf);
	}
	private: System::Void Backward_Click(System::Object^  sender, System::EventArgs^  e) {
		SkipSecond(-10000);
		currentTime = GetCurrentPlaybackTime();

		wchar_t buf[100];
		swprintf_s(buf, 100, L"10s forward, Current Time Now %f\n", currentTime);
		OutputDebugString(buf);
	}
	private: System::Void Volume_Click(System::Object^  sender, System::EventArgs^  e) {
		
	}	
	//converting String^ to char*
	void MarshalString(String ^ s, string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	private: System::Void Table_Select(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		System::String^ selectedSongPath;
		selectedSongPath = dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[5]->Value->ToString();
		string songPath;
		MarshalString(selectedSongPath, songPath);
		wchar_t buf[100];
		swprintf_s(buf, 100, L"selected row: \n", dataGridView1->SelectedCells[0]->RowIndex);
		OutputDebugString(buf);
		swprintf_s(buf, 100, L"selected column: \n", dataGridView1->SelectedCells[0]->ColumnIndex);
		OutputDebugString(buf);
		swprintf_s(buf, 100, L"selected song path: \n", songPath);
		OutputDebugString(buf);
		swprintf_s(buf, 100, L"dfjaldkjfalkjdflkajsldkfj: \n", selectedSongPath);
		OutputDebugString(buf);

		playingSongIndex = dataGridView1->SelectedCells[0]->RowIndex;
		SelectMusic(songPath.c_str()); // convert string to char*
		playing = 1;
	}

	private: System::Void Next_Click(System::Object^  sender, System::EventArgs^  e) {
		playingSongIndex++;

		System::String^ selectedSongPath = dataGridView1->Rows[playingSongIndex]->Cells[5]->Value->ToString();
		string songPath;
		MarshalString(selectedSongPath, songPath);

		SelectMusic(songPath.c_str()); // convert string to char*
		playing = 1;
	}
	private: System::Void Previous_Click(System::Object^  sender, System::EventArgs^  e) {
		playingSongIndex--;

		System::String^ selectedSongPath = dataGridView1->Rows[playingSongIndex]->Cells[5]->Value->ToString();
		string songPath;
		MarshalString(selectedSongPath, songPath);

		SelectMusic(songPath.c_str()); // convert string to char*
		playing = 1;
	}
};
}
