#include <iostream>
#include <fstream>
#include <string>
#include "../Common.h"

char* serverIp = const_cast<char*>("127.0.0.1");
#define SERVER_PORT	9000
#define BUFFER_SIZE		1024

int main(int argc, char* argv[])
{
	int retval;

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
	inet_pton(AF_INET, serverIp, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVER_PORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// ������ �б�
	std::string data{};
	const std::string fileName = argv[1];
	size_t size{};
	std::ifstream in{ fileName, std::ios::binary };

	// ������ ũ�� Ȯ�� �� ����
	if (in.is_open()) {
		in.seekg(0, std::ios::end);	// ��ġ ������ = ���� ��
		size = in.tellg();					// ��ġ �б�
		data.resize(size);						// ������ �Ҵ�
		in.seekg(0, std::ios::beg);	// ��ġ ������ = ���� ����
		in.read(&data[0], size);				// ������ ����
	}
	else {
		std::cerr << "������ ã�� �� �����ϴ�." << std::endl;
	}

	retval = send(sock, reinterpret_cast<char*>(&size), sizeof(size_t), 0);
	if (retval == SOCKET_ERROR)
		err_display("send()");
	
	// ������ ������
	size_t sent{};

	while (sent != size)
	{
		const char* buf = data.substr(BUFFER_SIZE).c_str();
		sent += sizeof(buf);
		retval = send(sock, buf, sizeof(buf), 0);
		std::cout << retval << " ����Ʈ ����" << std::endl;
	}

	std::cout << "[TCP Ŭ���̾�Ʈ] " <<
		static_cast<int>(sizeof(int)) << " + " << retval <<
		"����Ʈ�� ���½��ϴ�." << std::endl;

	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}
