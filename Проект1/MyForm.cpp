#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <stack>

#include "Transform.h"
#include "Clip.h"
#include "PClip.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
 void Main(array<String^>^ args) {
 Application::EnableVisualStyles();
 Application::SetCompatibleTextRenderingDefault(false);
 Проект1::MyForm form;
 Application::Run(%form);
}
