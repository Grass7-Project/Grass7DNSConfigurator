#pragma once

class MainCode {
public:
	static int InfoTaskFail(std::wstring &MessageContents, PCWSTR pszIcon);
	static int main();
private:
	wchar_t *szBranding;
};