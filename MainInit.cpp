#include "stdafx.h"
#include "MainInit.h"
#include "MainCode.h"
#include "ResourceLoader.h"

int MainInit::Init(HINSTANCE &hInstance)
{
	MainObjects.hInst = hInstance;
	ResourceLoader::LoadStrings();
	return MainCode::main();
}