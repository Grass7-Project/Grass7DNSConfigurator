#pragma once

// Main Class
class GlobalMain {
public:
	HINSTANCE hInst;
};

// Application Resource Strings
class GlobalAppResStrings {
public:
	std::wstring Header;
	std::wstring BodyText;
	std::wstring ButtonEnable;
	std::wstring ButtonDisable;
	std::wstring ButtonExit;
	std::wstring UACErrorHeader;
	std::wstring UACErrorTxt;
	std::wstring ButtonStart;
	std::wstring ButtonStop;
	std::wstring InfoEnableSuccess;
	std::wstring InfoDisableSuccess;
	std::wstring InfoHeader;
	std::wstring InfoDisableFail;
	std::wstring InfoEnableFail;
	std::wstring InfoStartFail;
	std::wstring InfoStartSuccess;
	std::wstring InfoQueryFail;
	std::wstring InfoAlreadyRunning;
	std::wstring InfoAlreadyStopped;
	std::wstring InfoStopSuccess;
	std::wstring InfoStopFail;
	std::wstring InfoAlreadyEnabled;
	std::wstring InfoAlreadyDisabled;
	std::wstring InfoConfigGetFail;
	std::wstring InfoConfigQueryFail;
	std::wstring InfoDisabled;
	std::wstring InfoServiceNoExist;
	std::wstring CriticalError;
};

extern GlobalMain MainObjects;
extern GlobalAppResStrings AppResStringsObjects;