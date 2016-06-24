//============================================================================
// Name        : MenuKit.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CMenuCore.h"


using namespace std;


int main(int argc, char **argv)
{
	if (argc == 1)
	{
		cout<<"MenuKit V1.0, by Wu Jian."<<endl;
		cout<<"Usage: menukit cmdline menu-title menu-item [...]"<<endl<<endl;

		return 0;
	}

	if( argc < 4 )
	{
		cout<<"Error: parameters incorrect."<<endl;
		cout<<"Usage: menukit cmdline menu-title menu-item [...]"<<endl<<endl;

		return -1;
	}

	CMenuCore MyMenu;

	MyMenu.SetCmd(argv[1]);
	MyMenu.SetTitleName(argv[2]);
	for(int i=3; i<argc; i++)
	{
		MyMenu.AddItem(argv[i]);
	}

	MyMenu.Show();

	return 0;
}
