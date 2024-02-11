#include "stdafx.h"
#include "ResourceLoader.h"
#include "Global.h"

void ResourceLoader::LoadStrings()
{
	std::wstring Header(MAX_PATH, 0);
	std::wstring BodyText(MAX_PATH, 0);
	std::wstring ButtonEnable(MAX_PATH, 0);
	std::wstring ButtonDisable(MAX_PATH, 0);
	std::wstring ButtonExit(MAX_PATH, 0);
	std::wstring UACErrorHeader(MAX_PATH, 0);
	std::wstring UACErrorTxt(MAX_PATH, 0);
	std::wstring ButtonStart(MAX_PATH, 0);
	std::wstring ButtonStop(MAX_PATH, 0);
	std::wstring InfoHeader(MAX_PATH, 0);

	Header.resize((size_t)LoadStringW(MainObjects.hInst, IDS_HEADER, &Header[0], (int)Header.size()));
	BodyText.resize((size_t)LoadStringW(MainObjects.hInst, IDS_BODY_TEXT, &BodyText[0], (int)BodyText.size()));
	ButtonEnable.resize((size_t)LoadStringW(MainObjects.hInst, IDS_BUTTON_ENABLE, &ButtonEnable[0], (int)ButtonEnable.size()));
	ButtonDisable.resize((size_t)LoadStringW(MainObjects.hInst, IDS_BUTTON_DISABLE, &ButtonDisable[0], (int)ButtonDisable.size()));
	ButtonExit.resize((size_t)LoadStringW(MainObjects.hInst, IDS_BUTTON_EXIT, &ButtonExit[0], (int)ButtonExit.size()));
	UACErrorHeader.resize((size_t)LoadStringW(MainObjects.hInst, IDS_UAC_ERROR_HEADER, &UACErrorHeader[0], (int)UACErrorHeader.size()));
	UACErrorTxt.resize((size_t)LoadStringW(MainObjects.hInst, IDS_UAC_ERROR_TEXT, &UACErrorTxt[0], (int)UACErrorTxt.size()));
	ButtonStart.resize((size_t)LoadStringW(MainObjects.hInst, IDS_BUTTON_START, &ButtonStart[0], (int)ButtonStart.size()));
	ButtonStop.resize((size_t)LoadStringW(MainObjects.hInst, IDS_BUTTON_STOP, &ButtonStop[0], (int)ButtonStop.size()));
	InfoHeader.resize((size_t)LoadStringW(MainObjects.hInst, IDS_INFO_HEADER, &InfoHeader[0], (int)InfoHeader.size()));

	AppResStringsObjects.Header = Header;
	AppResStringsObjects.BodyText = BodyText;
	AppResStringsObjects.ButtonEnable = ButtonEnable;
	AppResStringsObjects.ButtonDisable = ButtonDisable;
	AppResStringsObjects.ButtonExit = ButtonExit;
	AppResStringsObjects.UACErrorHeader = UACErrorHeader;
	AppResStringsObjects.UACErrorTxt = UACErrorTxt;
	AppResStringsObjects.ButtonStart = ButtonStart;
	AppResStringsObjects.ButtonStop = ButtonStop;
	AppResStringsObjects.InfoHeader = InfoHeader;
}