#include <iostream>

#include "../Common.h"

#define TESTNAME "www.google.com"

// 도메인 이름 -> IPv4 주소
bool GetIPAddr(const char* name, struct in_addr* addr)
{
	struct hostent* ptr = gethostbyname(name);
	if (ptr == NULL) {
		err_display("gethostbyname()");
		return false;
	}
	if (ptr->h_addrtype != AF_INET)
		return false;
	memcpy(addr, ptr->h_addr, ptr->h_length);

	return true;
}

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	// 도메인 이름 -> IP 주소
	struct in_addr addr;
	if (GetIPAddr(TESTNAME, &addr)) {
		// 성공이면 결과 출력
		char str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		std::cout << "IP 주소 변환 후: " << str;

		
	}

}