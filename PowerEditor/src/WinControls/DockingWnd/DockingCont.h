// this file is part of docking functionality for Notepad++
// Copyright (C)2005 Jens Lorenz <jens.plugin.npp@gmx.de>
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid
// misunderstandings, we consider an application to constitute a
// "derivative work" for the purpose of this license if it does any of the
// following:
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#ifndef DOCKINGCONT
#define DOCKINGCONT

#ifndef RESOURCE_H
#include "resource.h"
#endif //RESOURCE_H

#ifndef DOCKING_H
#include "Docking.h"
#endif //DOCKING_H

using namespace std;


// window styles
#define POPUP_STYLES   (WS_POPUP|WS_CLIPSIBLINGS|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MAXIMIZEBOX)
#define POPUP_EXSTYLES (WS_EX_CONTROLPARENT|WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW)
#define CHILD_STYLES   (WS_CHILD)
#define CHILD_EXSTYLES (0x00000000L)

#define MIN_TABWIDTH    24

enum eMousePos
{
	posOutside,
	posCaption,
	posClose
};

// some fix modify values for GUI
#define HIGH_CAPTION        18
#define HIGH_TAB            20
#define CAPTION_GAP         2
#define CLOSEBTN_POS_LEFT   3
#define CLOSEBTN_POS_TOP    3


class DockingCont : public StaticDialog
{
public:
	DockingCont();
	~DockingCont();

	HWND getTabWnd()
	{
		return _hContTab;
	};

	HWND getCaptionWnd()
	{ 
		if (_isFloating == false)
			return _hCaption;
		else
			return _hSelf;
	};

	tTbData* createToolbar(tTbData data);
	void     removeToolbar(tTbData data);
	tTbData* findToolbarByWnd(HWND hClient);
	tTbData* findToolbarByName(TCHAR* pszName);

	void showToolbar(tTbData *pTbData, bool show);

	bool updateInfo(HWND hClient)
	{
		for (tTbData* tb : _vTbData)
		{
			if (tb->hClient == hClient)
			{
				updateCaption();
				return true;
			}
		}
		return false;
	};

	void setActiveTb(tTbData* pTbData);
	void setActiveTb(int iItem);
	int getActiveTb();
	tTbData * getDataOfActiveTb();
	vector<tTbData *> getDataOfAllTb()
	{
		return _vTbData;
	};
	vector<tTbData *> getDataOfVisTb();
	bool isTbVis(tTbData* data);

	void doDialog(bool willBeShown = true, bool isFloating = false);

	bool isFloating()
	{
		return _isFloating;
	}

	int getElementCnt()
	{
		return _vTbData.size();
	}

	// interface function for gripper
	bool startMovingFromTab()
	{
		bool dragFromTabTemp = _dragFromTab;
		_dragFromTab = false;
		return dragFromTabTemp;
	};

	void setCaptionTop(bool isTopCaption)
	{
		_isTopCaption = isTopCaption;
		onSize();
	};

	void focusClient();

	void SetActive(BOOL bState)
	{
		_isActive = bState;
		updateCaption();
	};

	void setTabStyle(const bool& bDrawOgLine)
	{
		_bDrawOgLine = bDrawOgLine;
		RedrawWindow(_hContTab, NULL, NULL, 0);
	};

	virtual void destroy()
	{
		for (int iTb = _vTbData.size(); iTb > 0; iTb--)
		{
			delete _vTbData[iTb-1];
		}
		::DestroyWindow(_hSelf);
	};

protected :

	// Subclassing caption
	LRESULT runProcCaption(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK wndCaptionProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return (((DockingCont *)(::GetWindowLongPtr(hwnd, GWL_USERDATA)))->runProcCaption(hwnd, Message, wParam, lParam));
	};

	// Subclassing tab
	LRESULT runProcTab(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK wndTabProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		return (((DockingCont *)(::GetWindowLongPtr(hwnd, GWL_USERDATA)))->runProcTab(hwnd, Message, wParam, lParam));
	};

	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

	// drawing functions
	void drawCaptionItem(DRAWITEMSTRUCT *pDrawItemStruct);
	void drawTabItem(DRAWITEMSTRUCT *pDrawItemStruct);
	void onSize();

	// functions for caption handling and drawing
	eMousePos isInRect(HWND hwnd, int x, int y);

	// handling of toolbars
	void doClose();

	// return new item
	int  SearchPosInTab(tTbData* pTbData);
	void SelectTab(int iTab);

	int  hideToolbar(tTbData* pTbData, bool hideClient = true);
	void viewToolbar(tTbData *pTbData);
	int  removeTab(tTbData* pTbData)
	{
		return hideToolbar(pTbData, false);
	};

	bool updateCaption();
	LPARAM NotifyParent(UINT message);

private:
	// handles
	BOOL            _isActive;
	bool            _isFloating;
	HWND            _hCaption;
	HWND            _hContTab;

	// horizontal font for caption and tab
	HFONT           _hFont;

	// caption params
	bool            _isTopCaption;
	generic_string  _pszCaption;

	bool            _isMouseDown;
	bool            _isMouseClose;
	bool            _isMouseOver;
	RECT            _rcCaption;
	
	// tab style
	bool            _bDrawOgLine;

	// Important value for DlgMoving class
	bool            _dragFromTab;

	// subclassing handle for caption
	WNDPROC         _hDefaultCaptionProc;

	// subclassing handle for tab
	WNDPROC         _hDefaultTabProc;

	// for moving and reordering
	UINT            _prevItem;
	bool            _beginDrag;
	HIMAGELIST      _hImageList;

	// Is tooltip
	bool            _bTabTTHover;
	int             _iLastHovered;

	bool            _bCaptionTT;
	bool            _bCapTTHover;
	eMousePos       _hoverMPos;

	// data of added windows
	vector<tTbData *> _vTbData;
};



#endif // DOCKINGCONT
