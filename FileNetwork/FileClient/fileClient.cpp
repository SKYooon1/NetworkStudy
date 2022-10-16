#include <iostream>
#include <fstream>
#include "../../Common.h"

int connectToServer(SOCKET& sock, const char* ip, short port);

int main(int argc, char* argv[])
{
	char* serverIP{ const_cast<char*>("127.0.0.1") };
	const short serverPort{ 9000 };
	const short bufferSize{ 512 };
	// char* fileName{ const_cast<char*>("test.mp4") };

	// 명령행 인수가 있으면 1번째 인수는 파일 이름
	// if (argc > 1) fileName = argv[1];

	// 명령행 인수가 2개 이상이면 2번째 인수는 IP
	if (argc > 2) serverIP = argv[2];

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// 서버 연결
	if (connectToServer(sock, serverIP, serverPort) == SOCKET_ERROR)
		err_quit("connect()");

	// 데이터 통신에 사용할 변수
	char buf[bufferSize + 1];

	// 서버와 데이터 통신
	while (true) {
		// 데이터 입력
		printf("\n[보낼 데이터] ");
		if (fgets(buf, bufferSize + 1, stdin) == nullptr)
			break;

		// '\n' 문자 제거
		const int len = static_cast<int>(strlen(buf));
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// 데이터 보내기
		int val = send(sock, buf, static_cast<int>(strlen(buf)), 0);
		if (val == SOCKET_ERROR)
		{
			err_display("send()");
			break;
		}
		printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", val);

		// 데이터 받기
		val = recv(sock, buf, val, MSG_WAITALL);
		if (val == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (val == 0)
			break;

		// 받은 데이터 출력
		buf[val] = '\0';
		printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", val);
		printf("[받은 데이터] %s\n", buf);
	}

	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;

}

int connectToServer(SOCKET& sock, const char* ip, short port)
{
	struct sockaddr_in address {};

	address.sin_family = AF_INET;

	inet_pton(AF_INET, ip, &address.sin_addr);

	address.sin_port = htons(port);

	return connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address));
}