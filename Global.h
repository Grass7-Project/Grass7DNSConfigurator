#pragma once

// Main Class
class GlobalMain {
public:
	HINSTANCE hInst;
};

// Application Resource Strings
class GlobalAppResStrings {
public:
	wchar_t *Header;
	wchar_t *BodyText;
	wchar_t *ButtonEnable;
	wchar_t *ButtonDisable;
	wchar_t *ButtonExit;
	wchar_t *UACErrorHeader;
	wchar_t *UACErrorTxt;
	wchar_t *ButtonStart;
	wchar_t *ButtonStop;
	wchar_t *InfoEnableSuccess;
	wchar_t *InfoDisableSuccess;
	wchar_t *InfoHeader;
	wchar_t *DisableFail;
	wchar_t *InfoEnableFail;
	wchar_t *InfoStartFail;
	wchar_t *InfoStartSuccess;
	wchar_t *InfoQueryFail;
	wchar_t *InfoAlreadyRunning;
	wchar_t *InfoAlreadyStopped;
	wchar_t *InfoStopSuccess;
	wchar_t *InfoStopFail;
	wchar_t *InfoAlreadyEnabled;
	wchar_t *InfoAlreadyDisabled;
	wchar_t *InfoConfigGetFail;
	wchar_t *InfoConfigQueryFail;
	wchar_t *InfoDisabled;
	wchar_t *InfoServiceNoExist;
};

extern GlobalMain MainObjects;
extern GlobalAppResStrings AppResStringsObjects;