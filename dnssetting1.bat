@echo off
schtasks /Change /TN "Grass7\Setup\Set DNS Server" /Enable
schtasks /RUN /TN "Grass7\Setup\Set DNS Server"