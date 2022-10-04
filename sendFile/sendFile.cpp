#include <iostream>
#include <fstream>
#include <string>
#include "../Common.h"

char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT 9000

long long readFile(const std::string& fileName, std::string& s);

int main(int argc, char* argv[])
{
	int retval;
	std::string buf{};
	std::string fileName = argv[1];

	readFile(fileName, buf);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// ������ ������(���� ����)
	retval = send(sock, (char*)buf.length(), sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

	// ������ ������(���� ����)
	retval = send(sock, buf.c_str(), buf.length(), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

	std::cout << "[TCP Ŭ���̾�Ʈ] " << (int)sizeof(int) << " + " << retval <<
		"����Ʈ�� ���½��ϴ�." << std::endl;

	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}

long long readFile(const std::string& fileName, std::string& s)
{
	std::ifstream in{ fileName, std::ios::binary };

	if (in.is_open()) {
		in.seekg(0, std::ios::end);			// ��ġ ������ = ���� ��
		const long long size = in.tellg();	// ��ġ �б�
		s.resize(size);						// ������ �Ҵ�
		in.seekg(0, std::ios::beg);		// ��ġ ������ = ���� ����
		in.read(&s[0], size);					// ������ ����
		return size;
	}
	else {
		std::cerr << "������ ã�� �� �����ϴ�." << std::endl;
	}
}
