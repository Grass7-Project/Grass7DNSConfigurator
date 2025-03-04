#include "stdafx.h"
#include "MainCode.h"

MainCode MainCodeObject;

int MainCode::InfoTaskFail(std::wstring &MessageContents, PCWSTR pszIcon)
{
	TaskDialog(nullptr, nullptr, MainCodeObject.szBranding, AppResStringsObjects.InfoHeader.c_str(), MessageContents.c_str(), TDCBF_CLOSE_BUTTON, pszIcon, nullptr);
	return 1;
}

int MainCode::main()
{
	HMODULE hBrandingMod;
	Grass7API::Branding::LoadOSBrandingString(hBrandingMod, MainCodeObject.szBranding, L"%WINDOWS_GENERIC%");
	FreeLibrary(hBrandingMod);
	if (Grass7API::Check::isProcessElevated(GetCurrentProcess()) != 1) {
		TaskDialog(nullptr, nullptr, MainCodeObject.szBranding, AppResStringsObjects.UACErrorHeader.c_str(), AppResStringsObjects.UACErrorTxt.c_str(), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, nullptr);
		return 1;
	}

	SERVICE_STATUS_PROCESS ssp;
	LPQUERY_SERVICE_CONFIG lpsc = nullptr;
	SC_HANDLE SCManager;
	SC_HANDLE SCService;
	DWORD dwBytesNeeded;
	DWORD dwBytesNeeded2;
	DWORD cbBufSize = NULL;
	DWORD dwError;

	SCManager = OpenSCManagerW(nullptr, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	SCService = OpenServiceW(SCManager, L"Unbound", SERVICE_ALL_ACCESS);

	if (!QueryServiceStatusEx(SCService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		int errorCode = GetLastError();
		if (errorCode == 6) {
			return InfoTaskFail(AppResStringsObjects.InfoServiceNoExist, TD_ERROR_ICON);
		}
		else {
			return InfoTaskFail(AppResStringsObjects.InfoQueryFail, TD_ERROR_ICON);
		}
	}

	if (!QueryServiceConfigW(SCService, nullptr, 0, &dwBytesNeeded2))
	{
		dwError = GetLastError();
		if (ERROR_INSUFFICIENT_BUFFER == dwError) {
			cbBufSize = dwBytesNeeded2;
			lpsc = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LMEM_FIXED, cbBufSize);
		}
		else {
			return InfoTaskFail(AppResStringsObjects.InfoConfigGetFail, TD_ERROR_ICON);
		}
	}

	if (lpsc == nullptr) {
		return InfoTaskFail(AppResStringsObjects.CriticalError, TD_ERROR_ICON);
	}

	if (!QueryServiceConfigW(SCService, lpsc, cbBufSize, &dwBytesNeeded2)) {
		return InfoTaskFail(AppResStringsObjects.InfoConfigQueryFail, TD_ERROR_ICON);
	}

	HRESULT hr;
	TASKDIALOGCONFIG tdc = { sizeof(TASKDIALOGCONFIG) };
	int nClickedBtn;
	HICON hIcon = LoadIconW(MainObjects.hInst, MAKEINTRESOURCE(IDI_MAIN_ICON));
	LPCWSTR szTitle = MainCodeObject.szBranding,
		szHeader = AppResStringsObjects.Header.c_str(),
		szBodyText = AppResStringsObjects.BodyText.c_str();
	TASKDIALOG_BUTTON aCustomButtons[] = {
		{ 1000, AppResStringsObjects.ButtonStart.c_str() },
		{ 1001, AppResStringsObjects.ButtonStop.c_str() },
		{ 1002, AppResStringsObjects.ButtonEnable.c_str() },
		{ 1003, AppResStringsObjects.ButtonDisable.c_str() },
		{ 1004, AppResStringsObjects.ButtonExit.c_str() }
	};

	tdc.hwndParent = nullptr;
	tdc.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_USE_COMMAND_LINKS | TDF_USE_HICON_MAIN;
	tdc.pButtons = aCustomButtons;
	tdc.cButtons = _countof(aCustomButtons);
	tdc.pszWindowTitle = szTitle;
	tdc.hMainIcon = hIcon;
	tdc.pszMainInstruction = szHeader;
	tdc.pszContent = szBodyText;

	hr = TaskDialogIndirect(&tdc, &nClickedBtn, nullptr, nullptr);


	if (SUCCEEDED(hr) && 1000 == nClickedBtn) {
		if (lpsc->dwStartType == SERVICE_DISABLED) {
			return InfoTaskFail(AppResStringsObjects.InfoDisabled, TD_WARNING_ICON);
		}
		if (ssp.dwCurrentState != SERVICE_STOPPED && ssp.dwCurrentState != SERVICE_STOP_PENDING) {
			return InfoTaskFail(AppResStringsObjects.InfoAlreadyRunning, TD_INFORMATION_ICON);
		}
		if (!StartService(SCService, 0, nullptr)) {
			return InfoTaskFail(AppResStringsObjects.InfoStartFail, TD_ERROR_ICON);
		}
		else {
			return InfoTaskFail(AppResStringsObjects.InfoStartSuccess, TD_INFORMATION_ICON);
		}
	}
	if (SUCCEEDED(hr) && 1001 == nClickedBtn) {
		if (ssp.dwCurrentState == SERVICE_STOPPED) {
			return InfoTaskFail(AppResStringsObjects.InfoAlreadyStopped, TD_INFORMATION_ICON);
		}
		if (!ControlService(SCService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp)) {
			return InfoTaskFail(AppResStringsObjects.InfoStopFail, TD_INFORMATION_ICON);
		}
		else {
			return InfoTaskFail(AppResStringsObjects.InfoStopSuccess, TD_INFORMATION_ICON);
		}
	}
	if (SUCCEEDED(hr) && 1002 == nClickedBtn) {
		if (lpsc->dwStartType == SERVICE_AUTO_START) {
			return InfoTaskFail(AppResStringsObjects.InfoAlreadyEnabled, TD_INFORMATION_ICON);
		}
		if (!ChangeServiceConfigW(SCService, SERVICE_NO_CHANGE, SERVICE_AUTO_START, SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)) {
			return InfoTaskFail(AppResStringsObjects.InfoEnableFail, TD_ERROR_ICON);
		}
		ShellExecuteW(nullptr, nullptr, L"cmd", L"/c %SystemRoot%\\System32\\dnssetting1.bat", nullptr, SW_HIDE);
		if (ssp.dwCurrentState == SERVICE_STOPPED) {
			if (!StartServiceW(SCService, 0, nullptr)) {
				return InfoTaskFail(AppResStringsObjects.InfoStartFail, TD_ERROR_ICON);
			}
		}
		InfoTaskFail(AppResStringsObjects.InfoEnableSuccess, TD_INFORMATION_ICON);
	}
	if (SUCCEEDED(hr) && 1003 == nClickedBtn) {
		if (lpsc->dwStartType == SERVICE_DISABLED) {
			return InfoTaskFail(AppResStringsObjects.InfoAlreadyDisabled, TD_INFORMATION_ICON);
		}
		if (ssp.dwCurrentState != SERVICE_STOPPED && ssp.dwCurrentState != SERVICE_STOP_PENDING) {
			if (!ControlService(SCService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp)) {
				return InfoTaskFail(AppResStringsObjects.InfoStopFail, TD_ERROR_ICON);
			}
		}
		ShellExecuteW(nullptr, nullptr, L"cmd", L"/c %SystemRoot%\\System32\\dnssetting2.bat", nullptr, SW_HIDE);
		if (!ChangeServiceConfigW(SCService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)) {
			return InfoTaskFail(AppResStringsObjects.InfoDisableFail, TD_ERROR_ICON);
		}
		else {
			return InfoTaskFail(AppResStringsObjects.InfoDisableSuccess, TD_INFORMATION_ICON);
		}
	}
	CloseServiceHandle(SCService);
	CloseServiceHandle(SCManager);
	return 0;
}