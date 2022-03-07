// System: Display Options
// by PepsiOtaku
// Version 1.1

#include <DynRPG/DynRPG.h>
#define NOT_MAIN_MODULE
#include <sstream>

int confSetFPS;
int confRenderMode;
bool confStartWindowed;
bool confAnotherFullscreenMode;
bool gameInit;
bool resolutionFlag;
bool renderFlag;
bool windowFlag;
int confHoriz;
int confVert;

char headerName[] = "Settings";
//char fileName[] = "RPG_RT.ini";

std::string altExeName;
std::string afmFolder;
std::string gameIniFilename;

int frameTimer;
int horizontal = 0;
int vertical = 0;


std::stringstream filePath;

bool SetDisplayResolution(long PelsWidth, long PelsHeight);
void GetDesktopResolution(int& horizontal, int& vertical);


bool onStartup (char *pluginName) {
    // DynRPG.ini
    std::map<std::string, std::string> configuration = RPG::loadConfiguration(pluginName);
    confSetFPS = atoi(configuration["SetFPS"].c_str());
    altExeName = configuration["AlternateExeName"]; // For moleboxed games mainly
    afmFolder = configuration["AfmFolder"]; // Folder where game_settings_afm.exe resides
    gameIniFilename = configuration["GameIniFilename"]; //
    // RPG_RT.ini
    std::map<std::string, std::string> configGame = RPG::loadConfiguration(headerName, &gameIniFilename[0]);
    confStartWindowed = atoi(configGame["StartWindowed"].c_str());
    confAnotherFullscreenMode = atoi(configGame["AnotherFullscreenMode"].c_str());
    confRenderMode = atoi(configGame["RenderMode"].c_str());
    confHoriz = atoi(configGame["ResHorizontal"].c_str());
    confVert = atoi(configGame["ResVertical"].c_str());
    // the following cast forces RPG_RT.exe to start in a window
    //   (which is later fullscreened based on the ini settings
    //********************************************************************
    *reinterpret_cast<short *>(0x48FA57) = 0x9090;
    //********************************************************************
    return true;
}

void onInitFinished() {
    // After initialization, sets a flag to enable fullscreen if windowed mode is not set
    if (!confStartWindowed) {
        if (!confAnotherFullscreenMode) gameInit = true;
    }
    GetDesktopResolution(horizontal, vertical);
    if (confAnotherFullscreenMode == true) {
        std::stringstream temp;
        temp << afmFolder << "\\" << "game_settings_afm.exe";
        ShellExecute( NULL, NULL, temp.str().c_str(), NULL, NULL, SW_HIDE ); // or Data\\game_settings_afm.exe
        if (!confStartWindowed) {
            SetDisplayResolution(confHoriz,confVert);
            resolutionFlag = true;
        } else windowFlag = true;
        frameTimer = 1;
    }
    if (confSetFPS > 0) RPG::screen->setFPS(confSetFPS);
}

void onInitTitleScreen() {
    // Fullscreen mode if AnotherFullscreenMode=false
    if (gameInit == true) {
        keybd_event(VK_F4, 0, 0, 0); // simulate F4 key down
        keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0); // simulate F4 key up
        gameInit = false;
    }
}

bool onComment(const char* text, const RPG::ParsedCommentData* parsedData, RPG::EventScriptLine* nextScriptLine,
		       RPG::EventScriptData* scriptData, int eventId, int pageId, int lineId, int* nextLineId)
{
    std::string cmd = parsedData->command;
    filePath.str(std::string());
    filePath << ".\\" << gameIniFilename;
    int getFromIni;
    if(!cmd.compare("settings_ini") && parsedData->parametersCount == 3) {
        // Limit to these ini values:
        if (strcmp(parsedData->parameters[0].text,"StartWindowed") == 0 || strcmp(parsedData->parameters[0].text,"AnotherFullscreenMode") == 0
                || strcmp(parsedData->parameters[0].text,"RenderMode") == 0 || strcmp(parsedData->parameters[0].text,"ResHorizontal") == 0
                || strcmp(parsedData->parameters[0].text,"ResVertical") == 0) {
            if (parsedData->parameters[1].number == 1) {
                //if (strcmp(parsedData->parameters[2].text,"true") ==0 || strcmp(parsedData->parameters[2].text,"false") ==0)
                WritePrivateProfileString(headerName, parsedData->parameters[0].text, parsedData->parameters[2].text, filePath.str().c_str());
            } else if (parsedData->parameters[1].number == 0) {
                getFromIni = GetPrivateProfileInt( headerName, parsedData->parameters[0].text, 0, filePath.str().c_str());
                if (parsedData->parameters[2].number) RPG::variables[parsedData->parameters[2].number] = getFromIni;
            }
        }
        return false;
    }
    if(!cmd.compare("toggle_displaymode")) {
        // Only supported in
        if (confAnotherFullscreenMode) {
            keybd_event(119, 0, KEYEVENTF_EXTENDEDKEY | 0, 0); // simulate F8 key down
            keybd_event(119, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); // simulate F8 key up
        }
        return false;
    }
    if(!cmd.compare("toggle_fullscreen")) {
        if (confAnotherFullscreenMode == true) {
            system("cmd.exe /c @echo off");
            keybd_event(117, 0, KEYEVENTF_EXTENDEDKEY | 0, 0); // simulate F6 key down
            keybd_event(117, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); // simulate F6 key up
        } else {
            keybd_event(VK_F4, 0, 0, 0); // simulate F4 key down
            keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0); // simulate F4 key up
        }
        return false;
    }
    if(!cmd.compare("toggle_window_size")) {
        // Prevents the F5 key simulation is AnotherFullscreenMode is active
        if (!confAnotherFullscreenMode) {
            keybd_event(VK_F5, 0, 0, 0); // simulate F5 key down
            keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0); // simulate F5 key up
        }
        return false;
    }
    if(!cmd.compare("force_restart")) {
        WIN32_FIND_DATA lpFindFileData;
        HANDLE hFind;
        hFind = FindFirstFile(altExeName.c_str(), &lpFindFileData);
        if(hFind != INVALID_HANDLE_VALUE) {
            // default switch value = 4005
            ShellExecute(NULL, NULL, altExeName.c_str(), NULL, NULL, SW_HIDE);
            FindClose(hFind);
        } else {
            ShellExecute(NULL, NULL, "RPG_RT.exe", NULL, NULL, SW_HIDE);
            FindClose(hFind);
        }
        exit(0);
        return false;
    }
    if(!cmd.compare("resolution_default")) {
        SetDisplayResolution(horizontal,vertical);
        getFromIni = GetPrivateProfileInt("Settings", "AnotherFullscreenMode", 0, filePath.str().c_str());
        if (getFromIni == 0) resolutionFlag = false;
        return false;
    }
    if(!cmd.compare("resolution_ini")) {
        SetDisplayResolution(confHoriz,confVert);
        getFromIni = GetPrivateProfileInt("Settings", "AnotherFullscreenMode", 0, filePath.str().c_str());
        if (getFromIni == 1) resolutionFlag = true;
        return false;
    }

    return true;
}

void onFrame(RPG::Scene scene) {
    // The only time frameTimer will not be 0 is if AnotherFullscreenMode is set to true
    if (frameTimer != 0) {
        frameTimer++;
        if (frameTimer > 15) {
            if (confRenderMode > 0 && !renderFlag) {
                // Hacky way to focus the AnotherFullscreenMode window
                system("cmd.exe /c @echo off");
                // In order to simulate the F8 key
                keybd_event(VK_F8, 0x77, KEYEVENTF_EXTENDEDKEY | 0, 0); // simulate F8 key down
                keybd_event(VK_F8, 0x77, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); // simulate F8 key up
                renderFlag = true;
                if (confRenderMode == 2) {
                    frameTimer = 10;
                }
            } else if (frameTimer == 16 && confRenderMode == 2 && renderFlag == true) {
                // Focus the window again
                system("cmd.exe /c @echo off");
                keybd_event(VK_F8, 0x77, KEYEVENTF_EXTENDEDKEY | 0, 0); // simulate F8 key down
                keybd_event(VK_F8, 0x77, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); // simulate F8 key up
            }
        }
        if (frameTimer > 30) {
            if (windowFlag == true) {
                // Focus the window one more time
                system("cmd.exe /c @echo off");
                keybd_event(VK_F6, 0x75, KEYEVENTF_EXTENDEDKEY | 0, 0); // simulate F6 key down
                keybd_event(VK_F6, 0x75, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); // simulate F6 key up
                windowFlag = false;
                if (renderFlag == true) renderFlag = false;
            }
            frameTimer = 0;
        }
    }
    /*if ((GetAsyncKeyState(117) & 0x8000) == 0x8000) { // F6
        getFromIni = GetPrivateProfileInt("Settings", "AnotherFullscreenMode", 0, filePath.str().c_str());
        if (getFromIni == 1) {
            WritePrivateProfileString("Settings", "StartWindowed", "1", filePath.str().c_str());
            resolutionFlag = true;
        }
        else {
            WritePrivateProfileString("Settings", "StartWindowed", "0", filePath.str().c_str());
            resolutionFlag = false;
        }
    }
    if ((GetAsyncKeyState(115) & 0x8000) == 0x8000) { // F4
        int getFromIni;
        resolutionFlag = false;
        getFromIni = GetPrivateProfileInt("Settings", "AnotherFullscreenMode", 0, filePath.str().c_str());
        if (getFromIni == 0) {
            getFromIni = GetPrivateProfileInt("Settings", "StartWindowed", 0, filePath.str().c_str());
            if (getFromIni == 0) {
                WritePrivateProfileString("Settings", "StartWindowed", "1", filePath.str().c_str());
            } else {
                WritePrivateProfileString("Settings", "StartWindowed", "0", filePath.str().c_str());
            }
        }
    }*/
}

void onExit() {
    if (resolutionFlag == true) SetDisplayResolution(horizontal,vertical);
}


// Sets the screen resolution
bool SetDisplayResolution(long PelsWidth, long PelsHeight)
{
    DEVMODE dm;
    dm.dmSize = sizeof(DEVMODE);
    dm.dmPelsWidth = PelsWidth;
    dm.dmPelsHeight = PelsHeight;
    dm.dmFields = (DM_PELSWIDTH | DM_PELSHEIGHT);
    if (ChangeDisplaySettings(&dm, CDS_TEST) !=DISP_CHANGE_SUCCESSFUL)
    {
        MessageBox(NULL, "Unsupported graphics mode.", "Debug", MB_ICONINFORMATION);
        return false;
    }

    return (ChangeDisplaySettings(&dm, CDS_FULLSCREEN)==DISP_CHANGE_SUCCESSFUL);
}
// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}
