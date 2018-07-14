#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h> //  dung cho clrscr
#include "User.h"

using namespace std;
User us = User();

void Detail_send_fr() {
	int chon;
	cout << "-------MENU ------\n"
                "1.SEND MESS TO FRIEND\n"
                "2.EXIT\n"
                "-----------------------\n";
	while (1)
	{
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			us.Detail_Reply(us.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}
void  Ctrl_R() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.Reply Friend\n"
                "2.EXIT\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			us.Reply(us.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			return;
		}
	}
}
void send() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.SEND MESS\n"
                "2.Ctrl L To SEND\n"
                "3.Exit\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			us.SendMess(us.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			us.SendMess_ctr_l(us.id);
			cout << "-----------------------" << endl;
			break;
		case 3:
			return;
		}
	}
}
void showmess() {
	int chon;
	while (1)
	{
		cout << "-------MENU------\n"
                "1.SEND MESS\n"
                "2.RECEIVED MESSAGE\n"
                "3.EXIT\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
		case 1:
			us.ShowMess_send(us.id);
			cout << "-----------------------" << endl;
			break;
		case 2:
			us.ShowMess_rec(us.id);
			cout << "-----------------------" << endl;
			break;
		case 3:
			return;
		}
	}
}
void login() {
	int chon;

	while (1)
	{

		cout << "-------MENU ------\n"
                "1.Show Mess\n"
                "2.Detail Mess\n"
                "3.Send Mess\n"
                "4.Add Friend\n"
                "5.Show Friend\n"
                "6.Block Friend\n"
                "7.Update Friend\n"
                "8.Detail Friend\n"
                "9.Exit\n"
                "-----------------------\n";
		cout << "==>Choose: ";
		cin >> chon;
		switch (chon) {
			case 1:
				showmess();
				break;
			case 2:
				us.ShowMessDetail(us.id);
				if (us.Detail) {
					Ctrl_R();
				}
				break;
			case 3:
				send();
				break;
			case 4:
				us.AddFriend(us.id);
				break;
			case 5:
				us.ShowFriend_ctr_C(us.id);
				break;
			case 6:
				us.BlockFriend(us.id);
				break;
			case 7:
				us.Update_fr(us.id);
				break;
			case 8:
				us.Detail_fr(us.id);
				if (us.Detail) {
					Detail_send_fr();
				}
				break;
			case 9:
				break;
			default:
				printf("\r\n>> ERROR, Reselect..");
				_getch();
		}
		if (chon == 9)
		{
			break;
		}
	}
}


void print_menu() {
	cout << "\t----MENU-----\r\n";
	cout << "\t[1] Login\r\n";
	cout << "\t[2] Registation\r\n";
	cout << "\t[3] Logout\r\n";
	cout << "\t[4] Exit\r\n";
	cout << "\r\n>> Choose: ";
}
int main()
{
	int choice = 0;
	do {
		print_menu();
		fflush(stdin);
		cin >> choice;
		switch (choice) {
		case 1:
			us.SignIn();
			if (us.check) {
				login();
			}
			break;
		case 2:
			us.SingUp();
			break;
		case 3:
			us.SignOut();
			break;
		case 4:
			break;
		default:
			printf("\r\n>>Select:");
			_getch();
		}
		if (choice == 4)
		{
			break;
		}
	} while (1);
	printf("\r\n>> Other key to exit...");
	return 0;
}

