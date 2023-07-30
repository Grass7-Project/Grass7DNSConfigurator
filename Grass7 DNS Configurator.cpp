// DNS Configurator for Grass7

#include "stdafx.h"
#include <windows.h>
#include <shlobj.h>
#include <NTSecAPI.h>
#include <string>
#include <Gr7API.h>

// We do this horribleness
int InfoQueryFailed(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_QUERY_FAIL), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	exit(0);
}

int InfoServiceAlreadyRunning(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_ALREADY_RUNNING), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	exit(0);
}

int InfoServiceAlreadyStopped(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_ALREADY_STOPPED), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	exit(0);
}

int InfoServiceStartFail(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_START_FAIL), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	return 0;
}

int InfoServiceStartSuccess(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_START_SUCCESS), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	return 0;
}

int InfoServiceStopFail(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_STOP_FAIL), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	return 0;
}

int InfoServiceStopSuccess(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_STOP_SUCCESS), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	return 0;
}

int InfoServiceEnableFail(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_ENABLE_FAIL), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	return 0;
} 

int InfoServiceEnableSuccess(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_ENABLE_SUCCESS), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	return 0;
}

int InfoServiceDisableFail(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_DISABLE_FAIL), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	return 0;
}

int InfoServiceDisableSuccess(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_DISABLE_SUCCESS), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	return 0;
}

int InfoServiceAlreadyEnabled(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_ALREADY_ENABLED), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	return 0;
}

int InfoServiceAlreadyDisabled(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_ALREADY_DISABLED), TDCBF_CLOSE_BUTTON, TD_INFORMATION_ICON, NULL);
	return 0;
}

int InfoServiceConfigGetFail(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_CONFIG_GET_FAIL), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	return 0;
}

int InfoQueryServiceConfigFail(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_CONFIG_QUERY_FAIL), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	return 0;
}

int InfoServiceDisabled(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_DISABLED), TDCBF_CLOSE_BUTTON, TD_WARNING_ICON, NULL);
	return 0;
}

int InfoServiceNoExist(void)
{
	TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_SERVICE_NO_EXIST), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
	exit (0);
}

int main(void)
{
	if(gr7::isProcessElevated(GetCurrentProcess()) != 1) {
		TaskDialog(NULL, NULL, gr7::LoadOSBrandingString(), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_INFO_HEADER), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_UAC_ERROR_TEXT), TDCBF_CLOSE_BUTTON, TD_ERROR_ICON, NULL);
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

	SCManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	SCService = OpenService(SCManager, _T("Unbound"), SERVICE_ALL_ACCESS);

	if(! QueryServiceStatusEx(SCService, SC_STATUS_PROCESS_INFO, (LPBYTE) &ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		int errorCode = GetLastError();
		if(errorCode == 6) {
			InfoServiceNoExist();
		} else {
		InfoQueryFailed();
		}
	}

	if(! QueryServiceConfig(SCService, NULL, 0, &dwBytesNeeded2))
	{
		dwError = GetLastError();
		if(ERROR_INSUFFICIENT_BUFFER == dwError)
		{
			cbBufSize = dwBytesNeeded2;
			lpsc = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LMEM_FIXED, cbBufSize);
		} else {
			InfoServiceConfigGetFail();
			exit(0);
		}
	}

	if(! QueryServiceConfig(SCService, lpsc, cbBufSize, &dwBytesNeeded2))
	{
		InfoQueryServiceConfigFail();
	}

	HRESULT hr;
	TASKDIALOGCONFIG tdc = { sizeof(TASKDIALOGCONFIG) };
	int nClickedBtn;
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN_ICON));
	LPCWSTR szTitle = gr7::LoadOSBrandingString(),
	  szHeader = gr7::LoadStringToW(GetModuleHandle(NULL), IDS_HEADER),
	  szBodyText = gr7::LoadStringToW(GetModuleHandle(NULL), IDS_BODY_TEXT);
	TASKDIALOG_BUTTON aCustomButtons[] = {
	  { 1000, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_BUTTON_START) },
	  { 1001, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_BUTTON_STOP) },
	  { 1002, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_BUTTON_ENABLE) },
	  { 1003, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_BUTTON_DISABLE) },
	  { 1004, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_BUTTON_EXIT) }
	};
 
	  tdc.hwndParent = NULL;
	  tdc.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION|TDF_USE_COMMAND_LINKS|TDF_USE_HICON_MAIN;
	  tdc.pButtons = aCustomButtons;
	  tdc.cButtons = _countof(aCustomButtons);
	  tdc.pszWindowTitle = szTitle;
	  tdc.hMainIcon = hIcon;
	  tdc.pszMainInstruction = szHeader;
	  tdc.pszContent = szBodyText;
 
	  hr = TaskDialogIndirect ( &tdc, &nClickedBtn, NULL, NULL );
 

	  if ( SUCCEEDED(hr) && 1000 == nClickedBtn )
		{
			if(lpsc->dwStartType == SERVICE_DISABLED)
			{
				InfoServiceDisabled();
				exit(0);
			}
			if(ssp.dwCurrentState != SERVICE_STOPPED && ssp.dwCurrentState != SERVICE_STOP_PENDING)
			{
				InfoServiceAlreadyRunning();
			}
			if(! StartService(SCService, 0, NULL))
			{
				InfoServiceStartFail();
			} else {
				InfoServiceStartSuccess();
			}
		}
	  if ( SUCCEEDED(hr) && 1001 == nClickedBtn )
		{
			if(ssp.dwCurrentState == SERVICE_STOPPED)
			{
				InfoServiceAlreadyStopped();
			}
			if(! ControlService(SCService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS) &ssp))
			{
				InfoServiceStopFail();
			} else {
				InfoServiceStopSuccess();
			}
		}
	  if ( SUCCEEDED(hr) && 1002 == nClickedBtn )
		{
			if(lpsc->dwStartType == SERVICE_AUTO_START)
			{
				InfoServiceAlreadyEnabled();
				exit(0);
			}
			if(! ChangeServiceConfig(SCService, SERVICE_NO_CHANGE, SERVICE_AUTO_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
			{
				InfoServiceEnableFail();
			} else {
			InfoServiceEnableSuccess();
			}
			ShellExecute(NULL, NULL, L"cmd", L"/c %SystemRoot%\\System32\\dnssetting1.bat", NULL, SW_HIDE);
			if(ssp.dwCurrentState == SERVICE_STOPPED)
			{
				if(! StartService(SCService, 0, NULL))
				{
					InfoServiceStartFail();
				}
			}
		}
	  if ( SUCCEEDED(hr) && 1003 == nClickedBtn )
		{
			if(lpsc->dwStartType == SERVICE_DISABLED)
			{
				InfoServiceAlreadyDisabled();
				exit(0);
			}
			if(ssp.dwCurrentState != SERVICE_STOPPED && ssp.dwCurrentState != SERVICE_STOP_PENDING)
			{
				if(! ControlService(SCService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS) &ssp))
				{
					InfoServiceStopFail();
				}
			}
			ShellExecute(NULL, NULL, L"cmd", L"/c %SystemRoot%\\System32\\dnssetting2.bat", NULL, SW_HIDE);
			if(! ChangeServiceConfig(SCService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
			{
				InfoServiceDisableFail();
			} else {
			InfoServiceDisableSuccess();
			}
		}
	  CloseServiceHandle(SCService);
	  CloseServiceHandle(SCManager);
	return 0;
}

