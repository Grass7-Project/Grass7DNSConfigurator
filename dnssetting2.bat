@echo off
schtasks /Change /TN "Grass7\Setup\Set DNS Server" /Disable
setlocal EnableDelayedExpansion
for /F "tokens=1* delims==" %%I in ('wmic nic where ^(NetConnectionStatus^=2^) get NetConnectionID /VALUE') do for /F "delims=" %%K in ("%%J") do (
	for /f "tokens=* delims=" %%a in ('echo %%K') do (
		set var1=^"%%a^"
	)
	netsh interface ipv4 set dnsservers !var1! source=dhcp
	netsh interface ipv6 set dnsservers !var1! source=dhcp
)
endlocal
ipconfig /flushdns