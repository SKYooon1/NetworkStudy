#pragma comment(lib, "ws2_32")
#include <iostream>
#include "winsock2.h"

using namespace std;

bool isLittleEndian(u_long data);
bool isHostDifferentFromNetwork(u_long data);

int main()
{
	constexpr u_long data{ 0x12345678 };

	if (isHostDifferentFromNetwork(data))
		cout << "The host's endian system is different from network's endian system" << endl;
	else cout << "The host's endian system is same as network's endian system" << endl;

	cout << endl;

	if (isLittleEndian(data))
		cout << "The computer uses little endian system" << endl;
	else cout << "The computer uses big endian system" << endl;
}

bool isLittleEndian(u_long data)
{
	cout << hex << reinterpret_cast<long long>(reinterpret_cast<char*>(&data)) << " " <<
		hex << static_cast<int>(*reinterpret_cast<char*>(&data)) << endl;
	cout << hex << reinterpret_cast<long long>(reinterpret_cast<char*>(&data) + 1) << " " <<
		hex << static_cast<int>(*(reinterpret_cast<char*>(&data) + 1)) << endl;
	cout << hex << reinterpret_cast<long long>(reinterpret_cast<char*>(&data) + 2) << " " <<
		hex << static_cast<int>(*(reinterpret_cast<char*>(&data) + 2)) << endl;
	cout << hex << reinterpret_cast<long long>(reinterpret_cast<char*>(&data) + 3) << " " <<
		hex << static_cast<int>(*(reinterpret_cast<char*>(&data) + 3)) << endl;

	if (*reinterpret_cast<char*>(&data) == 0x78)
		return true;
	else return false;
}

bool isHostDifferentFromNetwork(u_long data)
{
	cout << hex << data << endl;
	cout << hex << htonl(data) << endl;

	if (data != htonl(data))
		return true;
	else return false;
}