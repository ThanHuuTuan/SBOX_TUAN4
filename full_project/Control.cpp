#include "User.h"
#include "Model.h"
#include<bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include<conio.h>
using namespace std;

User::User(){}
User::~User(){}
void User::SignIn() {
	username = new (char);
	password = new (char);

	cout << "username: ";
	cin >> username;
	cout << "password: ";
	cin >> password;
	Model conn;
	conn.Open();
	if (conn.SQL_login(conn.db,username,password)>0) {
		cout << "Login successfuly!\n";
		id = conn.SQL_login(conn.db, username, password);
		check = true;
		zID = id;
	}
	else {
		cout << "Login fail!\n";
		check = false;
		_getch();
	}
}
void User::SingUp() {
	username = new (char);
	password = new char;
	birthday = new char;
	fullname = new char;
	gender=new char;
	address= new char;
	cout << "Username:";
	cin >> username;
	cout << "Password:";
	cin >> password;
	cout << "Gender:";
	cin >> gender;
	cout << "Birthday:";
	cin >> birthday;
	cout << "Fullname:";
	cin.ignore(1);
    cin.getline(fullname,30);
	cout << "Address:";
    cin.getline(address,30);
	Model conn;
	conn.Open();
	if (conn.Select_all(conn.db,username)>0) {
		cout << "user exist" << endl;
	}
	else
	{
		conn.SQL_Reg(conn.db, username, password, gender, birthday, fullname, address);
		int id_mask = conn.Select_mask(conn.db);
		conn.Insert_maskuser(conn.db, id_mask, fullname,gender, address);
		cout << "DONE" << endl;
	}
}
void User::SignOut() {
	check = false;
	cout << "-----Please Login.-------\n";
}

void User::SendMess(int id) {
	if (check) {
		int id2;
		cout << "Receiver: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Model conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			char *mess, *dt;
			mess = new char;
			dt = new char;
			if (conn.CheckBlock(conn.db, id, id2)) {
				cout << "====>You is blocked\n";
			}
			else {
				int tt = 1;
				conn.update_tt(conn.db, id, id2);
				cout << "Content: \n";
				cin.ignore();
				cin.getline(mess,100);
				time_t hientai = time(0);
				dt = ctime(&hientai);
				long int x;
				x = static_cast<int> (hientai);
				conn.WriteToMess(conn.db, id, id2, mess, dt,tt, x);
				conn.ShowMessDetail(conn.db, id, id2);
			}
		}
		else cout << "--Account Not Exist--\n";
	}
	else {
		cout << "Please Login\n\n";
	}
}
void User::SendMess_ctr_l(int id) {
 if(check){
	        char choo;
            cout << "Press Ctrl + L to continue.\n";
            cin.ignore();
            choo = getch();
            if(choo == 12){
				Model conn;
				conn.Open();
				ShowFriend(id);
				cout << "Select number: ";
				int n;
				cin >> n;
				int id2=conn.ShowaaFriend(conn.db,id,n);
				char *mess, *dt;
				mess = new char;
				dt = new char;
				int tt = 1;
				conn.update_tt(conn.db, id, id2);
				cout << "Content: \n";
				cin.ignore(1);
				cin.getline(mess, 100);
				time_t hientai = time(0);
				dt = ctime(&hientai);
				long int x;
				x = static_cast<int> (hientai);
				conn.WriteToMess(conn.db, id, id2, mess, dt, tt, x);
            }
 }
        else {
                cout << "Please Login\n\n";
	}
}

void User::ShowMess_send(int ID) {
	if (check) {
		Model conn;
		conn.Open();
		conn.SQL_Mess_send(conn.db, zID);
	}
	else {
		cout << "Please Login\n\n";
	}
}
void User::ShowMess_rec(int ID) {
	if (check) {
		Model conn;
		conn.Open();
		conn.SQL_Mess_receive(conn.db, zID);
	}
	else {
		cout << "Please Login\n\n";
	}
}
int User::ShowMessDetail(int id1) {
	if (check) {
		int id2;
		cout << "Enter User: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Model conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			conn.ShowMessDetail(conn.db, id1, id2);
			zID2 = id2;
			Detail = true;
		}
		else {
              cout << "Account not exist \n";
		       Detail = false;
            }
	}
	else {
		cout << "Please Login\n\n";
	}
	return zID2;
}
void User::ShowFriend(int id) {
	if (check) {
		Model conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
	}
	else {
		cout << "Please Login\n\n";
	}
}
void User::ShowFriend_ctr_C(int id) {
   if(check){
            char choo;
            cout << "Press Ctrl + C to Sort Friend\n";
            cin.ignore();
            choo = getch();
            if(choo == 3){
				Model conn;
				conn.Open();
				conn.ShowFriend(conn.db, id);
            }
    }
	else {
		cout << "Please Login\n\n";
	}
}
void User::AddFriend(int id) {
	if (check) {
		cout << "Username: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (!conn.CheckFriend(conn.db, id, id2)) {
				if (!conn.CheckBlock(conn.db, id, id2)) {
					conn.WriteToFriend(conn.db, id, id2);
					ShowFriend(id);
				}
				else cout << "------You was blocked----\n\n\n";
			}
			else cout << "------You was friend ----------\n\n\n";
		}
		else cout << "--Account not Exist--\n";
	}
	else cout << "Please Login\n\n";
}
void User::BlockFriend(int id) {
	if (check) {
		cout << "Enter username: \n";
		char *usename;
		username = new char;
		cin >> username;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(username);
		if (id2 > 0) {
			conn.BlockFriend(conn.db, id, id2);
			cout << "---------Block Successfuly---------\n";
			conn.ShowFriend(conn.db, id);
		}
		else cout << "--Account not Exist--\n";
	}
	else {
		cout << "Please Login\n\n";
	}
}
void User::Update_fr(int id) {
	if (check) {
		cout << "Enter username: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (conn.CheckFriend(conn.db, id, id2)) {
				fullname = new char;
				gender=new char;
				address=new char;
				cout << "Name: ";
				cin.ignore(1);
                cin.getline(fullname,30);
				cout << "Gender: ";
				cin >> gender;
				cout << "Address:";
				cin.ignore(1);
                cin.getline(address,30);
				conn.Update_fr(conn.db,fullname,gender,address,id2);
			}
			else cout << "-You was friend -\n\n\n";
		}
		else cout << "-Account not Exist-\n";
	}
	else cout << "Please Login\n\n";
}
int User::Detail_fr(int id) {
	if (check) {
		cout << "Enter Username: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Model conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (conn.CheckFriend(conn.db, id, id2)) {
				conn.Detail_fr(conn.db, id2);
				Detail = true;
				zID2 = id2;
			}
			else { cout << "------You was friend -\n\n\n"; Detail = false;}
		}
		else { cout << "--Account Not Exist--\n"; Detail = false;}
	}
	else cout << "Please Login\n\n";
	return zID2;
}
void User::Reply(int id) {
    if(check){

           char choo;
	       cout << "Press Ctrl + R.\n";
           cin.ignore();
           choo = getch();
            if(choo == 18){
			char *mess, *dt;
			mess = new char;
			dt = new char;
			int tt = 1;
			Model conn;
			conn.Open();
			conn.update_tt(conn.db, id, zID2);
			cout << "Content: \n";
			cin.getline(mess,50);
			time_t hientai = time(0);
			dt = ctime(&hientai);
			long int x;
			x = static_cast<int> (hientai);
			conn.WriteToMess(conn.db, id, zID2, mess, dt, tt, x);
			conn.ShowMessDetail(conn.db, id, zID2);
		}
    }
    else
        cout << "Please Login \n";

	}
void User::Detail_Reply(int id) {
	char *mess, *dt;
	mess = new char;
	dt = new char;
	int tt = 1;
	Model conn;
	conn.Open();
	conn.update_tt(conn.db, id, zID2);
	cout << "Content: \n";
	cin.ignore();
	cin.getline(mess,50);
	time_t hientai = time(0);
	dt = ctime(&hientai);
	long int x;
	x = static_cast<int> (hientai);
	conn.WriteToMess(conn.db, id, zID2, mess, dt, tt, x);
	conn.ShowMessDetail(conn.db, id, zID2);
}

