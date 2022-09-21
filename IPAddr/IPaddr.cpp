#pragma comment(lib, "ws2_32")
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	const char* ipv4test = "147.46.114.70";
	cout << "IPv4 주소 변환 전 = " << ipv4test << endl;

	struct in_addr ipv4num;
	inet_pton(AF_INET, ipv4test, &ipv4num);
	cout << "IPv4 주소 변환 후 = " << hex << ipv4num.s_addr << endl;

	char ipv4str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipv4num, ipv4str, sizeof(ipv4str));
	cout << "IPv4 주소 다시 변환 후 = " << ipv4str << endl;

	cout << endl;

	const char* ipv6test = "2001:0230:abcd:ffab:0023:eb00:ffff:1111";
}