/*
* Copyright 2020 Encapsulate miniblink, libcef and webview2 in one c++ file.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#pragma once
#ifndef LNHISTORY_DLG_H
#define LNHISTORY_DLG_H

#include "DockingDlgInterface.h"
#include "PluginDefinition.h"
#include "SelfCtrl.h"
#include "resource.h"
#include <deque>
#include "menuCmdID.h"
#include "ToolbarPanel.h"

#include "stdafx.h"
#include "CheckFailure.h"
#include <shlwapi.h>

#include "APresenter.h"

class ArticlePresenter;

#define SELF_REFRESH WM_USER+9

using namespace std;

const TCHAR sectionName[] = TEXT("Setting");
const TCHAR strMarkColor[] = TEXT("MarkColor");
const TCHAR strSaveColor[] = TEXT("SaveColor");
const TCHAR configFileName[] = TEXT("MarkDownText.ini");

extern bool legacy ;

extern HWND curScintilla;
//extern CRITICAL_SECTION criCounter;

extern void ClearLocationList();

bool SetPosByIndex(int delta, bool doit=true);
void EnableTBButton(menuList flagIndex, bool state, bool force=false);
#define TB_ENABLEBUTTON         (WM_USER + 1)
class MarkDownTextDlg : public DockingDlgInterface
{
public :
	MarkDownTextDlg() : DockingDlgInterface(IDD_LOCATIONNAVIGATE) {};

    virtual void display(bool toShow = true); 

	HINSTANCE getModule(){ return (HINSTANCE)g_hModule; }

	virtual void setClosed(bool toClose);

	// Refresh the webview. |source| 0=switch docs;1=edit texts;2=switch engines;
	void RefreshWebview(int source=0);

	void refreshDlg(bool updateList, bool fromEditor);

	void setParent(HWND parent2set){
		_hParent = parent2set;
	};
	void saveParameters();
	void readParameters();
	void destoryWebViews(bool exit=false);
	void switchEngineByIndex(int id);

	ArticlePresenter* mWebView0;
	HWND hBrowser=nullptr;

	// 0=MD; 1=HTML; 2=ASCII
	int CustomRoutineIdx=-1;
	char CustomRoutine[MAX_PATH_HALF]={0};
	char MDRoutine[MAX_PATH_HALF]={0};
	char HTMLRoutine[MAX_PATH_HALF]={0};
	char ADRoutine[MAX_PATH_HALF]={0};
	TCHAR* LibPath=nullptr;
	LONG_PTR lastBid=0;
	ToolBar toolBar;

	bool RequestedSwitch=false;
	clock_t browser_deferred_create_time=0;

	void doScintillaScroll(int ln);

	CHAR* loadSourceAsset(uptr_t bid, const char* pathA, DWORD & dataLen);

	CHAR* loadPluginAsset(const char* path, DWORD & dataLen);

	CHAR* GetDocTex(size_t & docLength, LONG_PTR bid, bool * shouldDelete);

	bool checkRenderMarkdown();

	bool checkRenderHtml();

protected :
	virtual INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
	SelfCtrl _color,_savecolor;
public :
	APresenter presenter;
	int kernelType=-1; // -1_auto 0_wke 1_mb 2_bw 3_WV2
	int currentkernelType=0; // 0_wke 1_mb 2_bw 3_WV2
	int skFlags=0;
	bool hasChanged;
	ToolbarPanel ListBoxPanel;
	//Window ListBoxWrap;
	int getToolbarCommand(POINT &pointer);
	void OnToolBarRequestToolTip( LPNMHDR nmhdr );
	void OnToolBarCommand( UINT Cmd, char source=0, POINT* pt=nullptr);
	void AppendPageResidue(char* appendSt);
	void syncWebToline(bool force=false);
	int lastSyncLn=0;
};

#endif //LNHISTORY_DLG_H