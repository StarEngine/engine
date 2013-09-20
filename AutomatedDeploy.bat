@echo off

for %%a in (.) do set currentfolder=%%~na
echo %currentfolder%

C:
chdir C:\AndroidTools\cygwin\bin

bash --login -i -c "cd $ANDROID_NDK\%currentfolder%; bash android update project -p .; bash ndk-build; bash"