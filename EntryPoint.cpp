#include "stdafx.h"
#include "MainCode.h"
#include "ResourceLoader.h"
#include "Global.h"

GlobalMain MainObjects;
GlobalAppResStrings AppResStringsObjects;

int main(void)
{
	ResourceLoader::LoadStrings();
	MainCodeClass::MainCode();
	return 0;
}