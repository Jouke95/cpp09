#include <iostream>
#include <sstream>

void testParse() {
    int num;
    std::stringstream ss("2147483648");
    ss >> num;
    std::cout << "num: " << num << std::endl;
    std::cout << "fail: " << ss.fail() << std::endl;
}

int main() {
	std::string line = "12-12-2026";


	testParse();
}