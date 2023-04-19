#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <iostream>
#include <vector>
#include "..\sqlite\sqlite3.h"

#ifdef WORKER_EXPORTS
#define WORKER_API __declspec(dllexport)
#else
#define WORKER_API __declspec(dllimport)
#endif

struct WORKER_API Operation {
	std::wstring text;
	std::wstring date;
	int workerid;
	Operation(std::wstring text = L"", std::wstring date = L"", int workerid = 0) {
		this->date = date;
		this->text = text;
		this->workerid = workerid;
	}
};

class WORKER_API Man {
private:
public:
	Man();
	virtual ~Man();
	Man(const Man&);
	virtual Man* copy();
	virtual int getId();
	virtual void pushOperation(Operation);
	virtual std::string getLogin();
	virtual std::string getPassword();
	virtual std::wstring getName();
	virtual std::wstring getDob();
	virtual std::wstring getChange();
	virtual std::wstring getCreation();
	virtual std::wstring getDiagnosis();
};

class WORKER_API Patient : public Man {
private:
	int id;
	std::wstring name;
	std::wstring dob;
	std::wstring creationdate;
	std::wstring changedate;
	std::wstring diagnosis;
	std::vector<Operation> a;
public:
	Patient(int, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring);
	~Patient();
	Patient(const Patient&);
	Man* copy() override;
	int getId() override;
	void pushOperation(Operation) override;
	std::wstring getName() override;
	std::wstring getDob() override;
	std::wstring getChange() override;
	std::wstring getCreation() override;
	std::wstring getDiagnosis() override;
};

class WORKER_API Worker : public Man {
private:
	int id;
	std::wstring name;
	std::wstring job;
	std::string login;
	std::string password;
public:
	Worker(int, std::wstring, std::wstring, std::string, std::string);
	~Worker();
	Worker(const Worker&);
	Man* copy() override;
	int getId() override;
	std::string getLogin() override;
	std::string getPassword() override;
	std::wstring getName() override;
};

class WORKER_API DB {
private:
public:
	std::vector<Man*> patients;
	std::vector<Man*> workers;
	DB();
	~DB();
};

#endif //WORKER_H
