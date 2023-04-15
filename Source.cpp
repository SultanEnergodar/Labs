#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class Cars {

public:
	
	Cars(const string& model) : m_model(model) {}
	virtual ~Cars() {}
	virtual void print_mod() = 0;

	const string& get_model() const { return m_model; }


private:
	
	string m_model;
};


class Mazda : public Cars {

public:
	
	Mazda(const string& model) : Cars(model) {}
	virtual ~Mazda() { print_mod(); }
	void print_mod() { cout << "Mazda" << get_model() << endl; }
};



class Mitsubishi : public Cars {

public:
	
	Mitsubishi(const string& model) : Cars(model) {}
	virtual ~Mitsubishi() { print_mod(); }
	void print_mod() { cout << "Mitsubishi" << get_model() << endl; }
};


class BMW : public Cars {

public:
	
	BMW(const string& model) : Cars(model) {}
	virtual ~BMW() { print_mod(); }
	void print_mod() { cout << "BMW" << get_model() << endl; }

};


int main() {
	vector <shared_ptr <Cars> > car;
	fstream file;
	file.open("cars.txt");

	if (file.is_open()) {

		string name, model;

		while (file >> name >> model) {
				
			if (name == "Mazda")
				car.push_back(make_shared<Mazda>(model));
			else if (name == "Mitsubishi")
				car.push_back(make_shared<Mitsubishi>(model));
			else if (name == "BMW")
				car.push_back(make_shared<BMW>(model));
		}
	}

	else
		cout << "Error: no file";

	file.close();


	return 0;

}