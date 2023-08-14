#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
struct car
{
	string carplate;
	int expiretime = 0;
};
struct user {
	string username;
	string timestamp;
	vector<car> mashin;
	int penalty = 0;
	int balance = 0;
};
int datetoday(string str)
{
	int year = stoi(str.substr(0, 4));
	int month = stoi(str.substr(5, 2));
	int day = stoi(str.substr(8, 2));
	int ttime = ((year - 1) * 360) + ((month - 1) * 30) + day;
	return ttime;
}
void daytodate(int newtime)
{
	newtime = newtime - 1;
	int newyear = (newtime / 360) + 1;
	int newmonth = ((newtime - ((newyear - 1) * 360)) / 30) + 1;
	int newday = (newtime % 30) + 1;
	char str[1000];
	printf("%d/%02d/%02d\n", newyear, newmonth, newday);
}
void REGISTER(vector<user>& list, string req);
void REGISTER_CAR(vector<user>& list, string req);
void NEW_RECORD(vector<user>& list, string req);
void BUY_LICENSE(vector<user>& list, string req);
void ADD_BALANCE(vector<user>& list, string req);
void GET_BALANCE(vector<user>& list, string req);
void GET_PENALTY(vector<user>& list, string req);
void GET_LICENSE_DEADLINE(vector<user>& list, string req);
int main()
{
	int k = 0, flag1, flag2, flag3, flag4, flag5, flag6, flag7, flag8;

	string request = "yallah";
	string str;
	string Register = "REGISTER ", Register_car = "REGISTER_CAR ", New_record = "NEW_RECORD ";
	string Buy_license = "BUY_LICENSE ", Add_balance = "ADD_BALANCE ", Get_balance = "GET_BALANCE ";
	string Get_penalty = "GET_PENALTY ", Get_license_deadline = "GET_LICENSE_DEADLINE ", endstr = "END";

	vector<user> list;

	while (request != "END")
	{
		++k;
		if (k > 300)
			break;
		getline(cin, request);

		flag1 = request.compare(0, 9, Register, 0, 9);
		flag2 = request.compare(0, 13, Register_car, 0, 13);
		flag3 = request.compare(0, 11, New_record, 0, 11);
		flag4 = request.compare(0, 12, Buy_license, 0, 12);
		flag5 = request.compare(0, 12, Add_balance, 0, 12);
		flag6 = request.compare(0, 12, Get_balance, 0, 12);
		flag7 = request.compare(0, 12, Get_penalty, 0, 12);
		flag8 = request.compare(0, 21, Get_license_deadline, 0, 21);


		if (flag1 == 0)
			REGISTER(list, request.substr(9, request.length() - 9));
		else if (flag2 == 0)
			REGISTER_CAR(list, request.substr(13, request.length() - 13));
		else if (flag3 == 0)
			NEW_RECORD(list, request.substr(11, request.length() - 11));
		else if (flag4 == 0)
			BUY_LICENSE(list, request.substr(12, request.length() - 12));
		else if (flag5 == 0)
			ADD_BALANCE(list, request.substr(12, request.length() - 12));
		else if (flag6 == 0)
			GET_BALANCE(list, request.substr(12, request.length() - 12));
		else if (flag7 == 0)
			GET_PENALTY(list, request.substr(12, request.length() - 12));
		else if (flag8 == 0)
			GET_LICENSE_DEADLINE(list, request.substr(21, request.length() - 21));
	}
	return 0;
}
void REGISTER(vector<user>& list, string req)
{

	int i = 0, j = 0, p[1], flag = 1;
	while (i < req.length())
	{
		if (req.at(i) == ' ')
		{
			p[j] = i;
			j++;
		}
		i++;
	}

	for (int o = 0; o < list.size(); ++o)
	{
		if (req.substr(0, p[0]) == list.at(o).username)
		{
			cout << "INVALID USERNAME" << endl;
			flag = 0;
			break;
		}

	}

	if (flag == 1)
	{
		user newuser;
		newuser.username = req.substr(0, p[0]);
		list.push_back(newuser);
		cout << "REGISTER DONE" << endl;

	}

}
void REGISTER_CAR(vector<user>& list, string req)
{

	int i = 0, j = 0;
	int p[2];
	int flagn = 0, flagc = 0;

	while (i < req.length())
	{
		if (req.at(i) == ' ')
		{
			p[j] = i;
			j++;
		}
		i++;
	}

	for (int o = 0; o < list.size(); ++o)
	{
		if (req.substr(0, p[0]) == list.at(o).username)
		{
			flagn = 1;
		}
	}

	for (int o = 0; o < list.size(); ++o)
	{
		for (int w = 0; w < list.at(o).mashin.size(); ++w)
		{
			if ((req.substr(p[0] + 1, 10)) == (list.at(o).mashin.at(w).carplate))
			{
				flagc = 1;
				break;
			}
			if (flagc == 1)
				break;
		}
	}
	if (flagn == 0)
		cout << "INVALID USERNAME" << endl;
	else if (flagc == 1)
		cout << "INVALID CAR PLATE" << endl;
	else if (flagn == 1 && flagc == 0)
	{
		for (int o = 0; o < list.size(); ++o)
		{
			if (req.substr(0, p[0]) == list.at(o).username)
			{
				car newmashin;
				newmashin.carplate = req.substr(p[0] + 1, 10);
				list.at(o).mashin.push_back(newmashin);
				cout << "REGISTER CAR DONE" << endl;
			}
		}
	}
}
void NEW_RECORD(vector<user>& list, string req)
{

	int flagc = 0;
	int o, w;
	for (o = 0; o < list.size(); ++o)
	{
		for (w = 0; w < list.at(o).mashin.size(); ++w)
		{
			if (req.substr(0, 10) == list.at(o).mashin.at(w).carplate)
			{
				flagc = 1;
				break;
			}
		}
		if (flagc == 1)
			break;
	}

	if (flagc == 0)
		cout << "INVALID CAR PLATE" << endl;

	else if (flagc == 1)
	{
		int licencedeadline = list.at(o).mashin.at(w).expiretime;
		int raghamrast = req.at(9);
		int time = datetoday(req.substr(11, 10));
		if ((time % 7 == 0 || time % 7 == 2 || time % 7 == 5) && (raghamrast % 2 == 1))
		{
			if (time > licencedeadline)
			{
				list.at(o).penalty += 100;
				cout << "PENALTY RECORDED" << endl;
			}
			else if (time <= licencedeadline)
			{
				cout << "NORMAL RECORDED" << endl;
			}
		}
		else if ((time % 7 == 1 || time % 7 == 3 || time % 7 == 6) && (raghamrast % 2 == 0))
		{
			if (time > licencedeadline)
			{
				list.at(o).penalty += 100;
				cout << "PENALTY RECORDED" << endl;
			}
			else if (time <= licencedeadline)
			{
				cout << "NORMAL RECORDED" << endl;
			}
		}
		else if ((time % 7 == 1 || time % 7 == 3 || time % 7 == 6) && (raghamrast % 2 == 1))
			cout << "NORMAL RECORDED" << endl;
		else if ((time % 7 == 0 || time % 7 == 2 || time % 7 == 5) && (raghamrast % 2 == 0))
			cout << "NORMAL RECORDED" << endl;
		else if (time % 7 == 4)
			cout << "NORMAL RECORDED" << endl;
	}


}
void BUY_LICENSE(vector<user>& list, string req)
{
	int o, w, i = 0, j = 0, p[3], flagn = 0, flagc = 0;
	while (i < req.length())
	{
		if (req.at(i) == ' ')
		{
			p[j] = i;
			j++;
		}
		i++;
	}

	for (o = 0; o < list.size(); ++o)
	{
		if (req.substr(0, p[0]) == list.at(o).username)
		{
			flagn = 1;
			break;
		}
	}
	if (flagn == 0)
		cout << "INVALID USERNAME" << endl;
	else if (flagn == 1)
	{

		for (w = 0; w < list.at(o).mashin.size(); ++w)
		{
			if (req.substr(p[0] + 1, 10) == list.at(o).mashin.at(w).carplate)
			{
				flagc = 1;
				break;
			}

		}
		if (flagc == 0)
			cout << "INVALID CAR PLATE" << endl;
		else if (flagc == 1)
		{
			int length = stoi(req.substr(p[1] + 1, p[2] - p[1] - 1));
			int paying = 70 * length;
			if (list.at(o).balance < paying)
				cout << "NO ENOUGH MONEY" << endl;
			else
			{
				list.at(o).balance -= paying;

				int t = datetoday(req.substr(p[2] + 1, 10));

				list.at(o).mashin.at(w).expiretime = t +1+ length;
				cout << "BUY LICENSE DONE" << endl;
			}
		}
	}
}
void ADD_BALANCE(vector<user>& list, string req)
{

	int o, i = 0, j = 0, p[2], flagn = 0;
	while (i < req.length())
	{
		if (req.at(i) == ' ')
		{
			p[j] = i;
			j++;
		}
		i++;
	}

	for (o = 0; o < list.size(); ++o)
	{
		if (req.substr(0, p[0]) == list.at(o).username)
		{
			flagn = 1;
			break;
		}
	}
	if (flagn == 0)
		cout << "INVALID USERNAME" << endl;
	else if (flagn == 1)
	{
		int amount = stoi(req.substr(p[0] + 1, p[1] - p[0] - 1));
		list.at(o).balance += amount;
		cout << "ADD BALANCE DONE" << endl;
	}
}
void GET_BALANCE(vector<user>& list, string req)
{

	int o, i = 0, j = 0, p[1], flagn = 0;
	while (i < req.length())
	{
		if (req.at(i) == ' ')
		{
			p[j] = i;
			j++;
		}
		i++;
	}

	for (o = 0; o < list.size(); ++o)
	{
		if (req.substr(0, p[0]) == list.at(o).username)
		{
			flagn = 1;
			break;
		}
	}
	if (flagn == 0)
		cout << "INVALID USERNAME" << endl;
	else if (flagn == 1)
		cout << list.at(o).balance << endl;

}
void GET_PENALTY(vector<user>& list, string req)
{

	int o, i = 0, j = 0, p[1], flagn = 0;
	while (i < req.length())
	{
		if (req.at(i) == ' ')
		{
			p[j] = i;
			j++;
		}
		i++;
	}

	for (o = 0; o < list.size(); ++o)
	{
		if (req.substr(0, p[0]) == list.at(o).username)
		{
			flagn = 1;
			break;
		}
	}
	if (flagn == 0)
		cout << "INVALID USERNAME" << endl;
	else if (flagn == 1)
		cout << list.at(o).penalty << endl;
}
void GET_LICENSE_DEADLINE(vector<user>& list, string req)
{

	int o, w, p[1], flagc = 0;
	for (o = 0; o < list.size(); ++o)
	{
		for (w = 0; w < list.at(o).mashin.size(); ++w)
		{
			if (req.substr(0, 10) == list.at(o).mashin.at(w).carplate)
			{
				flagc = 1;
				break;
			}
		}
		if (flagc == 1)
			break;
	}

	if (flagc == 0)
		cout << "INVALID CAR PLATE" << endl;
	else if (flagc == 1)
	{
		int timestamp = datetoday(req.substr(11, 10));
		int expiretime = list.at(o).mashin.at(w).expiretime;
		if (timestamp <= expiretime)
			daytodate(expiretime + 1);
		if (timestamp > expiretime)
			daytodate(timestamp + 1);

	}
}