#pragma once
#include <stdlib.h>
#include <crtdbg.h>
#include "UI.h"
#include "Test.h"

int main() {
	Test();
	Run();
	_CrtDumpMemoryLeaks();
	return 0;
}