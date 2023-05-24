#include <iostream>
#include <vector>



class Detail {
protected:
	Detail() {}
public:
	virtual ~Detail() {}
	virtual void print() { std::cout << "create detail" << std::endl; }

	template<typename T>
	friend void CreatePart();
};
std::vector<Detail*> parts;
class Assembly : public Detail {
protected:
	Assembly() {}
public:
	virtual ~Assembly() {}
	void print() override { std::cout << "create assembly" << std::endl; }

	template<typename T>
	friend void CreatePart();
};



template<typename T>
void CreatePart() {
	T* part = new T();
	parts.push_back(part);
}

int main() {
	CreatePart<Detail>();
	CreatePart<Detail>();
	CreatePart<Assembly>();
	CreatePart<Assembly>();

	for (auto p : parts) {
		p->print();
		delete p;
	}
	parts.clear();
	return 0;
}
