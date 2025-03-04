#include "stdafx.h"
#include "ResourceLoader.h"
#include "Global.h"

void ResourceLoader::LoadStrings()
{
	InternalLoadString(AppResStringsObjects.Header, IDS_HEADER);
	InternalLoadString(AppResStringsObjects.BodyText, IDS_BODY_TEXT);
	InternalLoadString(AppResStringsObjects.ButtonEnable, IDS_BUTTON_ENABLE);
	InternalLoadString(AppResStringsObjects.ButtonDisable, IDS_BUTTON_DISABLE);
	InternalLoadString(AppResStringsObjects.ButtonExit, IDS_BUTTON_EXIT);
	InternalLoadString(AppResStringsObjects.UACErrorHeader, IDS_UAC_ERROR_HEADER);
	InternalLoadString(AppResStringsObjects.UACErrorTxt, IDS_UAC_ERROR_TEXT);
	InternalLoadString(AppResStringsObjects.ButtonStart, IDS_BUTTON_START);
	InternalLoadString(AppResStringsObjects.ButtonStop, IDS_BUTTON_STOP);
	InternalLoadString(AppResStringsObjects.InfoEnableSuccess, IDS_INFO_ENABLE_SUCCESS);
	InternalLoadString(AppResStringsObjects.InfoDisableSuccess, IDS_INFO_DISABLE_SUCCESS);
	InternalLoadString(AppResStringsObjects.InfoHeader, IDS_INFO_HEADER);
	InternalLoadString(AppResStringsObjects.InfoDisableFail, IDS_INFO_DISABLE_FAIL);
	InternalLoadString(AppResStringsObjects.InfoEnableFail, IDS_INFO_ENABLE_FAIL);
	InternalLoadString(AppResStringsObjects.InfoStartFail, IDS_INFO_START_FAIL);
	InternalLoadString(AppResStringsObjects.InfoStartSuccess, IDS_INFO_START_SUCCESS);
	InternalLoadString(AppResStringsObjects.InfoQueryFail, IDS_INFO_QUERY_FAIL);
	InternalLoadString(AppResStringsObjects.InfoAlreadyRunning, IDS_INFO_ALREADY_RUNNING);
	InternalLoadString(AppResStringsObjects.InfoAlreadyStopped, IDS_INFO_ALREADY_STOPPED);
	InternalLoadString(AppResStringsObjects.InfoStopSuccess, IDS_INFO_STOP_SUCCESS);
	InternalLoadString(AppResStringsObjects.InfoStopFail, IDS_INFO_STOP_FAIL);
	InternalLoadString(AppResStringsObjects.InfoAlreadyEnabled, IDS_INFO_ALREADY_ENABLED);
	InternalLoadString(AppResStringsObjects.InfoAlreadyDisabled, IDS_INFO_ALREADY_DISABLED);
	InternalLoadString(AppResStringsObjects.InfoConfigGetFail, IDS_INFO_CONFIG_GET_FAIL);
	InternalLoadString(AppResStringsObjects.InfoConfigQueryFail, IDS_INFO_CONFIG_QUERY_FAIL);
	InternalLoadString(AppResStringsObjects.InfoDisabled, IDS_INFO_DISABLED);
	InternalLoadString(AppResStringsObjects.InfoServiceNoExist, IDS_INFO_SERVICE_NO_EXIST);
	InternalLoadString(AppResStringsObjects.CriticalError, IDS_CRITICAL_ERROR);
}

void ResourceLoader::InternalLoadString(std::wstring &strReturn, UINT uID)
{
	std::wstring strTemp(MAX_PATH, 0);
	strTemp.resize((size_t)LoadStringW(MainObjects.hInst, uID, &strTemp[0], (int)strTemp.size()));
	strReturn = strTemp;
	strTemp.clear();
}