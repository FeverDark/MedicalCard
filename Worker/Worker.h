#include "..\sqlite\sqlite3.h"
#include <string>
#include <iostream>
#include <vector>
#include "sha256.h"

#ifdef WORKER_EXPORTS
#define WORKER_API __declspec(dllexport)
#else
#define WORKER_API __declspec(dllimport)
#endif

struct WORKER_API Diagnosis {
	std::wstring text;
	std::wstring date;
	int workerid;
	Diagnosis(std::wstring text = L"", std::wstring date = L"", int workerid = 0) {
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
	virtual int getId();
	virtual void pushDiagnosis(Diagnosis);
};

class WORKER_API Patient : public Man {
private:
	int id;
	std::wstring name;
	std::wstring dob;
	std::vector<Diagnosis> a;
public:
	Patient(int, std::wstring, std::wstring, Diagnosis);
	~Patient();
	int getId() override;
	void pushDiagnosis(Diagnosis) override;
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
	int getId() override;
	void pushDiagnosis(Diagnosis) override;
};

class WORKER_API DB {
private:
	std::vector<Man*> db;
public:
	DB();
	~DB();
};
