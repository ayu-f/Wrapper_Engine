#include <iostream>
#include "Wrapper.hpp"
#include "Engine.hpp"

class TestAdding {
public:
	template<typename Type>
	Type runTwo(Type a, Type b) {
		return a + b;
	}
};

class TestString {
public:
	std::string runStr(std::string name, std::string surname) {
		return std::string("named ") + name + " " + surname;
	}
};

int main(void) {
	TestAdding A;
	// test int
	Wrapper<int> wrapper1(&A, &TestAdding::runTwo<int>, { {"arg1", 0}, {"arg2", 0} });
	Engine engine;
	engine.register_command<int>(&wrapper1, "command1");
	std::cout << "2 + 10 = " << engine.execute<int>("command1", {{"arg1", 2}, {"arg2", 10}}) << std::endl;

	// test double 
	Wrapper<double> wrapper2(&A, &TestAdding::runTwo<double>, { {"arg1", 0.0}, {"arg2", 0.0} });
	engine.register_command<double>(&wrapper2, "command2");
	std::cout << "2.5 + 10.5 = " << engine.execute<double>("command2", { {"arg1", 2.5}, {"arg2", 10.5} }) << std::endl;
    
	// test strings
	TestString B;
	Wrapper<std::string> wrapper3(&B, &TestString::runStr, { {"arg1", ""}, {"arg2", ""} });
	engine.register_command<std::string>(&wrapper3, "command3");
	std::cout << "Hello the person " << engine.execute<std::string>("command3", { {"arg1", "Darth"}, {"arg2", "Vader"} }) << std::endl;

	return 0;
}