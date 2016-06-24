/*
 * CMenuCore.h
 *
 *  Created on: Aug 21, 2015
 *      Author: wuj
 */

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class CMenuCore
{
public:
	CMenuCore();
	virtual ~CMenuCore();
	void SetTitleName(string strName);
	void AddItem(string strItem);
	void SetCmd(string strCmd);
	void Show(void);

protected:
	string m_strName;
	string m_strCmd;
	vector<string> m_vec_strItem;
	int m_iTitleLen;
	int m_iMaxItemLen;

	int RunCmd(string strPara);

};


