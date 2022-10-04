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
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// 데이터 보내기(고정 길이)
	retval = send(sock, (char*)buf.length(), sizeof(int), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

	// 데이터 보내기(가변 길이)
	retval = send(sock, buf.c_str(), buf.length(), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}

	std::cout << "[TCP 클라이언트] " << (int)sizeof(int) << " + " << retval <<
		"바이트를 보냈습니다." << std::endl;

	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

long long readFile(const std::string& fileName, std::string& s)
{
	std::ifstream in{ fileName, std::ios::binary };

	if (in.is_open()) {
		in.seekg(0, std::ios::end);			// 위치 지정자 = 파일 끝
		const long long size = in.tellg();	// 위치 읽기
		s.resize(size);						// 데이터 할당
		in.seekg(0, std::ios::beg);		// 위치 지정자 = 파일 시작
		in.read(&s[0], size);					// 데이터 저장
		return size;
	}
	else {
		std::cerr << "파일을 찾을 수 없습니다." << std::endl;
	}
}
