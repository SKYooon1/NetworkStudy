#include <iostream>
#include "../Common.h"

// 도메인 이름 -> IPv4 주소
void domainCheck(const char* name)
{
	struct hostent* ptr = gethostbyname(name);
	if (ptr == NULL) {
		err_display("gethostbyname()");
		return;
	}
	if (ptr->h_addrtype != AF_INET)
		return;

	struct in_addr addr {};
	char str[INET_ADDRSTRLEN];

	std::cout << "호스트 이름: " << ptr->h_name << std::endl;

	if (ptr->h_aliases[0] == nullptr)
		std::cout << "별명이 없습니다." << std::endl;
	else for (int i{}; ptr->h_aliases[i] != nullptr; ++i)
		std::cout << i + 1 << "번째 별명: " << ptr->h_aliases[i] << std::endl;

	for(int i{}; ptr->h_addr_list[i] != nullptr; ++i)
	{
		memcpy(&addr, ptr->h_addr_list[i], ptr->h_length);
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		std::cout << i + 1 << "번째 IP 주소: " << str << std::endl;
	}

	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	std::string str;

	while (true)
	{
		std::cout << "도메인을 입력해주세요: ";
		std::cin >> str;

		// 도메인 이름 -> IP 주소
		struct in_addr addr;
		domainCheck(str.c_str());
	}
}