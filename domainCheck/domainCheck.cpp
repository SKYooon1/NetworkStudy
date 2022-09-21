#include <iostream>
#include "../Common.h"

// ������ �̸� -> IPv4 �ּ�
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

	std::cout << "ȣ��Ʈ �̸�: " << ptr->h_name << std::endl;

	if (ptr->h_aliases[0] == nullptr)
		std::cout << "������ �����ϴ�." << std::endl;
	else for (int i{}; ptr->h_aliases[i] != nullptr; ++i)
		std::cout << i + 1 << "��° ����: " << ptr->h_aliases[i] << std::endl;

	for(int i{}; ptr->h_addr_list[i] != nullptr; ++i)
	{
		memcpy(&addr, ptr->h_addr_list[i], ptr->h_length);
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		std::cout << i + 1 << "��° IP �ּ�: " << str << std::endl;
	}

	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	std::string str;

	while (true)
	{
		std::cout << "�������� �Է����ּ���: ";
		std::cin >> str;

		// ������ �̸� -> IP �ּ�
		struct in_addr addr;
		domainCheck(str.c_str());
	}
}