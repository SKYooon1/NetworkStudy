#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa2_2;
	if (WSAStartup(MAKEWORD(2, 2), &wsa2_2) != 0)
		return 1;
	cout << "[�˸�] ���� 2.2 �ʱ�ȭ ����" << endl;

	cout << "wVersion : " << hex << wsa2_2.wVersion << endl;
	cout << "wHighVersion : " << hex << wsa2_2.wHighVersion << endl;
	cout << "szDescription : " << wsa2_2.szDescription << endl;
	cout << "szSystemStatus : " << wsa2_2.szSystemStatus << endl;

	cout << endl;

	WSADATA wsa1_1;
	if (WSAStartup(MAKEWORD(1, 1), &wsa1_1) != 0)
		return 1;
	cout << "[�˸�] ���� 1.1 �ʱ�ȭ ����" << endl;

	cout << "wVersion : " << hex << wsa1_1.wVersion << endl;
	cout << "wHighVersion : " << hex << wsa1_1.wHighVersion << endl;
	cout << "szDescription : " << wsa1_1.szDescription << endl;
	cout << "szSystemStatus : " << wsa1_1.szSystemStatus << endl;

	// ���� ����
	WSACleanup();
	return 0;
}
