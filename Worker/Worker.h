#ifdef WORKER_EXPORTS
#define WORKER_API __declspec(dllexport)
#else
#define WORKER_API __declspec(dllimport)
#endif

#include "..\sqlite\sqlite3.h"
#include <string>
#include <iostream>

class Man {
private:

public:
	Man() {};
	virtual ~Man() {};
};

class Patient : public Man {
private:

public:
	Patient() {};
	~Patient() {};
};

class Worker : public Man {
private:

public:
	Worker() {};
	~Worker() {};
};

class DB {
private:
	const char* dbname = "card.db";
	sqlite3* db;
public:
	DB();
	~DB() {};
};