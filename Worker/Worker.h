#include "..\sqlite\sqlite3.h"
#include <string>
#include <iostream>

#ifdef WORKER_EXPORTS
#define WORKER_API __declspec(dllexport)
#else
#define WORKER_API __declspec(dllimport)
#endif

class WORKER_API Man {
private:

public:
	Man();
	virtual ~Man();
};

class WORKER_API Patient : public Man {
private:

public:
	Patient();
	~Patient();
};

class WORKER_API Worker : public Man {
private:

public:
	Worker();
	~Worker();
};

class WORKER_API DB {
private:
	const char* dbname = "card.db";
	sqlite3* db;
public:
	DB();
	~DB();
};
