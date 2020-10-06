//this file is part of notepad++
//Copyright (C) 2011 AustinYoung<pattazl@gmail.com>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H

//
// All difinitions of plugin interface
//
#include "PluginInterface.h"

class MarkDownTextDlg;

//-------------------------------------//
//-- STEP 1. DEFINE YOUR PLUGIN NAME --//
//-------------------------------------//
// Here define your plugin name
//
const TCHAR NPP_PLUGIN_NAME[] = TEXT("Markdown Text");

//-----------------------------------------------//
//-- STEP 2. DEFINE YOUR PLUGIN COMMAND NUMBER --//
//-----------------------------------------------//
//
// Here define the number of your plugin commands
//
enum menuList
{
	menuPrevious = 0,
	menuNext ,
	menuChgPrevious ,
	menuPreviewCurr ,
	menuOption,
	menuSeparator0,

	menuAutoRecord,
	menuManualRecord,
	menuClearRecords,

	menuAlwaysRefresh,
	menuInCurr,
	menuNeedMark,

	menuSeparator1,

	menuSkipClosed,
	menuClearOnClose,
	menuPause,

	menuSeparator2,
	menuPinMenu,
	menuAbout,

	menuCount,
};

const int nbFunc = menuCount;
// 270*300
#define RecordConentMax  81000
extern TCHAR currFile[MAX_PATH];// 当前窗口文件名
//
// Initialization of your plugin data
// It will be called while plugin loading
//
void pluginInit(HANDLE hModule);

//
// Cleaning of your plugin
// It will be called while plugin unloading
//
void pluginCleanUp();

//
//Initialization of your plugin commands
//
void commandMenuInit();

//
//Clean up your plugin commands allocation (if any)
//
void commandMenuCleanUp();

//
// Your plugin command functions
//
void PreviousLocation();
void NextLocation();
//void PreviousChangedLocation();
//void NextChangedLocation();
//
//void MarkDownTextHistoryDlg();
//void AutoRecord();
//void SkipClosed();
//void FlipAutoClean();
//void PauseRecording();
//void ManualRecord();
void ClearAllRecords();
//void NavigateInCurr();
//void MarkChange();
//void ShowAbout();
//void PinMenu();

extern MarkDownTextDlg _MDText;

extern toolbarIcons		g_TBPrevious;

extern bool pinMenu;

extern HANDLE  g_hModule;

__declspec(selectany) bool NPPRunning = false;
#endif //PLUGINDEFINITION_H
