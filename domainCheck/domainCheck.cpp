#include <iostream>

#include "../Common.h"

#define TESTNAME "www.google.com"

// ������ �̸� -> IPv4 �ּ�
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
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;


	// ������ �̸� -> IP �ּ�
	struct in_addr addr;
	if (GetIPAddr(TESTNAME, &addr)) {
		// �����̸� ��� ���
		char str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		std::cout << "IP �ּ� ��ȯ ��: " << str;

		
	}

}