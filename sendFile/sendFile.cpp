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

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
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

	// 데이터 읽기
	std::string data{};
	const std::string fileName = argv[1];
	size_t size{};
	std::ifstream in{ fileName, std::ios::binary };

	// 데이터 크기 확인 및 전송
	if (in.is_open()) {
		in.seekg(0, std::ios::end);	// 위치 지정자 = 파일 끝
		size = in.tellg();					// 위치 읽기
		data.resize(size);						// 데이터 할당
		in.seekg(0, std::ios::beg);	// 위치 지정자 = 파일 시작
		in.read(&data[0], size);				// 데이터 저장
	}
	else {
		std::cerr << "파일을 찾을 수 없습니다." << std::endl;
	}

	retval = send(sock, reinterpret_cast<char*>(&size), sizeof(size_t), 0);
	if (retval == SOCKET_ERROR)
		err_display("send()");
	
	// 데이터 보내기
	size_t sent{};

	while (sent != size)
	{
		const char* buf = data.substr(BUFFER_SIZE).c_str();
		sent += sizeof(buf);
		retval = send(sock, buf, sizeof(buf), 0);
		std::cout << retval << " 바이트 전송" << std::endl;
	}

	std::cout << "[TCP 클라이언트] " <<
		static_cast<int>(sizeof(int)) << " + " << retval <<
		"바이트를 보냈습니다." << std::endl;

	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
