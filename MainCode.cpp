// DNS Configurator for Grass7

#include "stdafx.h"
#include "MainCode.h"
#include "Global.h"

MainCodeClass MainCodeObject;

void MainCodeClass::InfoTaskFail(UINT uID, PCWSTR pszIcon)
{
	std::wstring WString(MAX_PATH, 0);
	WString.resize((size_t)LoadStringW(MainObjects.hInst, uID, &WString[0], (int)WString.size()));

	TaskDialog(NULL, NULL, MainCodeObject.szBranding, AppResStringsObjects.InfoHeader.c_str(), WString.c_str(), TDCBF_CLOSE_BUTTON, pszIcon, NULL);
	exit(0);
}

void MainCodeClass::MainCode()
{
	MainObjects.hInst = GetModuleHandleW(NULL);
	Grass7API::String::LoadOSBrandingString(MainCodeObject.szBranding, L"%WINDOWS_GENERIC%");
	if (Grass7API::Check::isProcessElevated(GetCurrentProcess()) != 1) {
		TaskDialog(NULL, NULL, MainCodeObject.szBranding, AppResStringsObjects.UACErrorHeader.c_str(), AppResStringsObjects.UACErrorTxt.c_str(), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
		exit(0);
	}

	SERVICE_STATUS_PROCESS ssp;
	LPQUERY_SERVICE_CONFIG lpsc;
	SC_HANDLE SCManager;
	SC_HANDLE SCService;
	DWORD dwBytesNeeded;
	DWORD dwBytesNeeded2;
	DWORD cbBufSize;
	DWORD dwError;

	SCManager = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	SCService = OpenServiceW(SCManager, _T("Unbound"), SERVICE_ALL_ACCESS);

	if (!QueryServiceStatusEx(SCService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		int errorCode = GetLastError();
		if (errorCode == 6) {
			InfoTaskFail(IDS_INFO_SERVICE_NO_EXIST, TD_ERROR_ICON);
		}
		else {
			InfoTaskFail(IDS_INFO_QUERY_FAIL, TD_ERROR_ICON);
		}
	}

	if (!QueryServiceConfigW(SCService, NULL, 0, &dwBytesNeeded2))
	{
		dwError = GetLastError();
		if (ERROR_INSUFFICIENT_BUFFER == dwError)
		{
			cbBufSize = dwBytesNeeded2;
			lpsc = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LMEM_FIXED, cbBufSize);
		}
		else {
			InfoTaskFail(IDS_INFO_CONFIG_GET_FAIL, TD_ERROR_ICON);
		}
	}

	if (!QueryServiceConfigW(SCService, lpsc, cbBufSize, &dwBytesNeeded2))
	{
		InfoTaskFail(IDS_INFO_CONFIG_QUERY_FAIL, TD_ERROR_ICON);
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

	tdc.hwndParent = NULL;
	tdc.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION | TDF_USE_COMMAND_LINKS | TDF_USE_HICON_MAIN;
	tdc.pButtons = aCustomButtons;
	tdc.cButtons = _countof(aCustomButtons);
	tdc.pszWindowTitle = szTitle;
	tdc.hMainIcon = hIcon;
	tdc.pszMainInstruction = szHeader;
	tdc.pszContent = szBodyText;

	hr = TaskDialogIndirect(&tdc, &nClickedBtn, NULL, NULL);


	if (SUCCEEDED(hr) && 1000 == nClickedBtn)
	{
		if (lpsc->dwStartType == SERVICE_DISABLED)
		{
			InfoTaskFail(IDS_INFO_DISABLED, TD_WARNING_ICON);
		}
		if (ssp.dwCurrentState != SERVICE_STOPPED && ssp.dwCurrentState != SERVICE_STOP_PENDING)
		{
			InfoTaskFail(IDS_INFO_ALREADY_RUNNING, TD_INFORMATION_ICON);
		}
		if (!StartService(SCService, 0, NULL))
		{
			InfoTaskFail(IDS_INFO_START_FAIL, TD_ERROR_ICON);
		}
		else {
			InfoTaskFail(IDS_INFO_START_SUCCESS, TD_INFORMATION_ICON);
		}
	}
	if (SUCCEEDED(hr) && 1001 == nClickedBtn)
	{
		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			InfoTaskFail(IDS_INFO_ALREADY_STOPPED, TD_INFORMATION_ICON);
		}
		if (!ControlService(SCService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp))
		{
			InfoTaskFail(IDS_INFO_STOP_FAIL, TD_INFORMATION_ICON);
		}
		else {
			InfoTaskFail(IDS_INFO_STOP_SUCCESS, TD_INFORMATION_ICON);
		}
	}
	if (SUCCEEDED(hr) && 1002 == nClickedBtn)
	{
		if (lpsc->dwStartType == SERVICE_AUTO_START)
		{
			InfoTaskFail(IDS_INFO_ALREADY_ENABLED, TD_INFORMATION_ICON);
		}
		if (!ChangeServiceConfigW(SCService, SERVICE_NO_CHANGE, SERVICE_AUTO_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
		{
			InfoTaskFail(IDS_INFO_ENABLE_FAIL, TD_ERROR_ICON);
		}
		else {
			InfoTaskFail(IDS_INFO_ENABLE_SUCCESS, TD_INFORMATION_ICON);
		}
		ShellExecuteW(NULL, NULL, L"cmd", L"/c %SystemRoot%\\System32\\dnssetting1.bat", NULL, SW_HIDE);
		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			if (!StartServiceW(SCService, 0, NULL))
			{
				InfoTaskFail(IDS_INFO_START_FAIL, TD_ERROR_ICON);
			}
		}
	}
	if (SUCCEEDED(hr) && 1003 == nClickedBtn)
	{
		if (lpsc->dwStartType == SERVICE_DISABLED)
		{
			InfoTaskFail(IDS_INFO_ALREADY_DISABLED, TD_INFORMATION_ICON);
			exit(0);
		}
		if (ssp.dwCurrentState != SERVICE_STOPPED && ssp.dwCurrentState != SERVICE_STOP_PENDING)
		{
			if (!ControlService(SCService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp))
			{
				InfoTaskFail(IDS_INFO_STOP_FAIL, TD_ERROR_ICON);
			}
		}
		ShellExecuteW(NULL, NULL, L"cmd", L"/c %SystemRoot%\\System32\\dnssetting2.bat", NULL, SW_HIDE);
		if (!ChangeServiceConfigW(SCService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
		{
			InfoTaskFail(IDS_INFO_DISABLE_FAIL, TD_ERROR_ICON);
		}
		else {
			InfoTaskFail(IDS_INFO_DISABLE_SUCCESS, TD_INFORMATION_ICON);
		}
	}
	CloseServiceHandle(SCService);
	CloseServiceHandle(SCManager);
}

