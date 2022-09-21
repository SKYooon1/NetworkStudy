#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa2_2;
	if (WSAStartup(MAKEWORD(2, 2), &wsa2_2) != 0)
		return 1;
	cout << "[알림] 윈속 2.2 초기화 성공" << endl;

	cout << "wVersion : " << hex << wsa2_2.wVersion << endl;
	cout << "wHighVersion : " << hex << wsa2_2.wHighVersion << endl;
	cout << "szDescription : " << wsa2_2.szDescription << endl;
	cout << "szSystemStatus : " << wsa2_2.szSystemStatus << endl;

	cout << endl;

	WSADATA wsa1_1;
	if (WSAStartup(MAKEWORD(1, 1), &wsa1_1) != 0)
		return 1;
	cout << "[알림] 윈속 1.1 초기화 성공" << endl;

	cout << "wVersion : " << hex << wsa1_1.wVersion << endl;
	cout << "wHighVersion : " << hex << wsa1_1.wHighVersion << endl;
	cout << "szDescription : " << wsa1_1.szDescription << endl;
	cout << "szSystemStatus : " << wsa1_1.szSystemStatus << endl;

	// 윈속 종료
	WSACleanup();
	return 0;
}
