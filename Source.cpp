#include <iostream>
#include <vector>



class Detail {
protected:
	Detail() {}
public:
	virtual ~Detail() {}
	template<typename T>
	friend T* CreatePart();
};
std::vector<Detail*> parts;
class Assembly : public Detail {
protected:
	Assembly() {}
public:
	virtual ~Assembly() {}

	static Assembly* CreateAssembly() {
		return new Assembly();
	}
	template<typename T>
	friend T* CreatePart();
};



template<typename T>
T* CreatePart() {
	T* part = new T();
	parts.push_back(part);
	return part;
}

int main() {
	Assembly* assembly = Assembly::CreateAssembly();
	Detail* detail1 = CreatePart<Detail>();
	Detail* detail2 = CreatePart<Detail>();
	Assembly* assembly1 = CreatePart<Assembly>();
	Assembly* assembly2 = CreatePart<Assembly>();

	std::cout << parts.size();
	for (auto p : parts) {
		delete p;
	}
	parts.clear();
	std::cout << parts.size();
	return 0;
}