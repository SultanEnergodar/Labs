#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;


class Class1 {

public:
	
	virtual Class1* ccopy() const {
		return new Class1(*this);
	}
	virtual ~Class1() {};
};


class Class2 : public Class1 {

public:
	
	Class2* ccopy() const override {
		return new Class2(*this);
	}
	~Class2() override {};
};


void tcopy(const vector<Class1*>& src, vector<Class1*>& bs) {
	for (const auto& obj : src) {
		bs.push_back(obj->ccopy()); //обращение к методу конкретного класса
	}
}


int main() {
	Class1 obj1;
	Class2 obj2;
	vector<Class1*> src = { &obj1, &obj2 }; 
	vector<Class1*> bs; 

	tcopy(src, bs); 

	for (const auto& obj : bs) { 
		cout << typeid(*obj).name() << endl;
		delete obj;
	}

	return 0;
}