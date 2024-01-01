#pragma once

class MainCodeClass {
public:
	static void LoadStrings();
	static void InfoTaskFail(UINT uID, PCWSTR pszIcon);
	static void MainCode();
private:
	wchar_t *szBranding;
};