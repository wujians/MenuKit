/*
 * CMenuCore.cpp
 *
 *  Created on: Aug 21, 2015
 *      Author: wuj
 */

#include "CMenuCore.h"

CMenuCore::CMenuCore()
{
	m_iTitleLen = 0;
	m_iMaxItemLen = 0;
}

CMenuCore::~CMenuCore()
{

}

void CMenuCore::SetTitleName(string strName)
{
	m_strName = strName;

	m_iTitleLen = m_strName.length();
}

void CMenuCore::AddItem(string strItem)
{
	m_vec_strItem.push_back(strItem);

	int iLen = strItem.length();
	if (iLen > m_iMaxItemLen)
	{
		m_iMaxItemLen = iLen;
	}
}

void CMenuCore::SetCmd(string strCmd)
{
	m_strCmd = strCmd;
}

void CMenuCore::Show(void)
{
	setenv("ESCDELAY", "25", TRUE);

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	int iItemNum = m_vec_strItem.size();

	ITEM **ppMItems = new ITEM*[iItemNum+1];

	for(int i=0; i<iItemNum; i++)
	{
		ppMItems[i] = new_item(m_vec_strItem[i].c_str(), NULL);
	}
	ppMItems[iItemNum] = (ITEM*)NULL;

	MENU *pMenu = new_menu(ppMItems);

	int iHeight = m_vec_strItem.size() + 4;
	if (iHeight > 10 )
	{
		iHeight = 10;
	}

	int iWidth = m_iTitleLen > m_iMaxItemLen ? m_iTitleLen : m_iMaxItemLen;
	iWidth += 10;

	if (iWidth > 70)
	{
		iWidth = 70;
	}

	int iXpos = (80 - iWidth)/2;

	WINDOW *pWin = newwin(iHeight, iWidth, 4, iXpos);
	keypad(pWin, TRUE);

	set_menu_win(pMenu, pWin);
	set_menu_sub(pMenu, derwin(pWin, m_vec_strItem.size(),m_iMaxItemLen+1, 3, (iWidth-m_iMaxItemLen)/2));

	curs_set(0);
	set_menu_mark(pMenu, NULL);
	menu_opts_off(pMenu, O_SHOWDESC);

	box(pWin, 0, 0);

	mvwprintw(pWin, 1, 5, "%s", m_strName.c_str());
	refresh();

	post_menu(pMenu);
	wrefresh(pWin);
	refresh();

	bool bQuit = false;
	bool bSel = false;

	while (true)
	{
		int c = getch();
		switch (c)
		{
		case KEY_DOWN:
			menu_driver(pMenu, REQ_DOWN_ITEM);
			break;
		case KEY_UP:
			menu_driver(pMenu, REQ_UP_ITEM);
			break;
		case 27:
			bQuit = true;
			break;
		case 10:
			bSel = true;
			bQuit = true;
			break;
		}

		wrefresh(pWin);

		if( bQuit )
		{
			break;
		}
	}

	ITEM *pSelItem = current_item(pMenu);
	string strSelItem = item_name(pSelItem);

	unpost_menu(pMenu);

	for (int i = 0; i < iItemNum; i++)
	{
		free_item(ppMItems[i]);
	}

	free_menu(pMenu);

	delete[] ppMItems;

	endwin();

	if( bSel )
	{
		RunCmd(strSelItem);
	}

}

int CMenuCore::RunCmd(string strPara)
{
	char pBuffer[1024];
	snprintf(pBuffer, sizeof(pBuffer), m_strCmd.c_str(), strPara.c_str());

	return system(pBuffer);
}
