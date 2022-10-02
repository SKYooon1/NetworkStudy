#include <iostream>

#pragma pack(1)

struct test5 {
	char a;
	int b;
};

struct test10 {
	char a;
	int b;
	char c;
	int d;
};

#pragma pack()

int main()
{
	test5 s1;
	std::cout << "s1 a size : " << sizeof(s1.a) << " byte" << std::endl;
	std::cout << "s1 b size : " << sizeof(s1.b) << " byte" << std::endl;
	std::cout << "s1 size : " << sizeof(s1) << " byte" << std::endl;

	std::cout << std::endl;

	test10 s2;
	std::cout << "s2 a size : " << sizeof(s2.a) << " byte" << std::endl;
	std::cout << "s2 b size : " << sizeof(s2.b) << " byte" << std::endl;
	std::cout << "s2 c size : " << sizeof(s2.c) << " byte" << std::endl;
	std::cout << "s2 d size : " << sizeof(s2.d) << " byte" << std::endl;
	std::cout << "s2 size : " << sizeof(s2) << " byte" << std::endl;
}
