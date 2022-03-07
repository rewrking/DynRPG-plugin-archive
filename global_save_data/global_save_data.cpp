// CMS Tools: Global Save Data (Store a range of variables)
// by PepsiOtaku
// Version 2.0

#define AUTO_DLLMAIN
#include <DynRPG/DynRPG.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

int saveSlotID;
int saveSlotOffset;
unsigned short int varRangeStart;
unsigned short int varRangeEnd;
unsigned short int varRangeDiff;
unsigned short int varRangeMod;
unsigned short int varRangeMultiplier;
unsigned short int varExport;
unsigned short int varImport;
signed int varArray[9999];
int checkVarIndex;
int varPointer;

char filePath [31] = "SaveGlobal.dyn";
int blankData = 0;


fstream binary_file;

// function required to write values to a binary file
void write_to_binary(signed int id, signed int p_Data, int offset){
    fstream binary_file;
    binary_file.open(filePath,fstream::in|fstream::out|fstream::binary);
    if (binary_file.is_open()) {
        binary_file.seekp(offset);
        binary_file.write(reinterpret_cast<char *>(&p_Data),sizeof(id));
    }
}

// function required to read values from a binary file
int read_from_binary(signed int id, signed int g_Data, int offset) {
    fstream binary_file;
    binary_file.open(filePath,fstream::in|fstream::binary);
    if (binary_file.is_open()) {
        binary_file.seekg(offset);
        binary_file.read(reinterpret_cast<char *>(&g_Data),sizeof(id));
    }
    return g_Data;
 }

bool onStartup(char *pluginName) {
    // FindFirstFile function load
    WIN32_FIND_DATA lpFindFileData;
    HANDLE hFind;
    // Find the file defined in char "filePath"
    hFind = FindFirstFile(filePath, &lpFindFileData);
    if(hFind != INVALID_HANDLE_VALUE) {
        FindClose(hFind);
    } else {
        fstream binary_file;
        binary_file.open(filePath,fstream::out|fstream::binary);
        if (binary_file.is_open()) {
            //fill it with zeros!
            write_to_binary(blankData, blankData, 40000);
            binary_file.close();
        }
    }
    std::map<std::string, std::string> configuration = RPG::loadConfiguration(pluginName);
    varRangeStart = atoi(configuration["VarRangeStart"].c_str());
    varRangeEnd = atoi(configuration["VarRangeEnd"].c_str());
    varRangeDiff = varRangeEnd - varRangeStart;
    // the following rounds the varRangeDiff up to multiples of 100
    varRangeMod = varRangeDiff % 100;
    varRangeMod = 100 - varRangeMod;
    varRangeMultiplier = varRangeDiff + varRangeMod;
    varExport = atoi(configuration["ExportVar"].c_str());
    varImport = atoi(configuration["ImportVar"].c_str());
    return true;
}

// used to read values from the binary, and pass them back to rpg2003
bool onSetVariable(int id, int value){
    if (id == varImport){
        if (value > 0){
            binary_file.flush();
            saveSlotID = value;
            saveSlotOffset = (saveSlotID-1)*(4*varRangeMultiplier);
            checkVarIndex = read_from_binary(saveSlotID, saveSlotID, saveSlotOffset); // make sure data's available
            varPointer = varRangeStart;
            if (checkVarIndex == value) { // if index and saveslot are equal, run loop to read variables
                for (int i=1; i<=varRangeDiff; i++) { // loops through each variable value in binary, and loads it to game
                    varArray[i] = read_from_binary(varArray[i], varArray[i], saveSlotOffset+(4*i));
                    RPG::variables[varPointer] = varArray[i];
                    varPointer++;
                }
            }
            if (binary_file.is_open()) {
                binary_file.close();
            }
        }
    }
    // used to save variable range to binary
    if (id == varExport){
        if (value > 0){
            // Write to external file upon saving game
            binary_file.flush();
            saveSlotID = value;
            saveSlotOffset = (saveSlotID-1)*(4*varRangeMultiplier);
            write_to_binary(saveSlotID, saveSlotID, saveSlotOffset);
            varPointer = varRangeStart;
            for (int i=1; i<=varRangeDiff; i++) {
                varArray[i] = RPG::variables[varPointer];
                write_to_binary(varArray[i], varArray[i], saveSlotOffset+(4*i));
                varPointer++;
            }
            if (binary_file.is_open()) {
                binary_file.close();
            }
        }
    }
    return true;
}




