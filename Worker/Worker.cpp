#include "pch.h"
#include "framework.h"
#include "Worker.h"

std::vector<Man*> _tempworkersdb_; // Юзаю глобалку, потому что хочу
std::vector<Man*> _temppatientssdb_; // Юзаю глобалку, потому что хочу

Man::Man() {}
Man::~Man() {}
Man::Man(const Man&) {}
Man* Man::copy() { return NULL; }
int Man::getId() { return NULL; }
void Man::pushOperation(Operation) {}
std::string Man::getLogin() { return NULL; }
std::string Man::getPassword() { return NULL; }
std::wstring Man::getName() { return NULL; }
std::wstring Man::getDob() { return NULL; }
std::wstring Man::getChange() { return NULL; }
std::wstring Man::getCreation() { return NULL; }
std::wstring Man::getDiagnosis() { return NULL; }

Patient::Patient(int id = 0, std::wstring name = L"", std::wstring dob = L"", std::wstring creationdate = L"", std::wstring changedate = L"", std::wstring diagnosis = L"") {
    this->id = id;
    this->name = name;
    this->dob = dob;
    this->creationdate = creationdate;
    this->changedate = changedate;
    this->diagnosis = diagnosis;
}
Patient::~Patient() {}
Patient::Patient(const Patient& temp) {
    id = temp.id;
    name = temp.name;
    dob = temp.dob;
    creationdate = temp.creationdate;
    changedate = temp.changedate;
    a = temp.a;
}
Man* Patient::copy() { return new Patient(*this); }
int Patient::getId() { return this->id; }
void Patient::pushOperation(Operation t) { this->a.push_back(t); }
std::wstring Patient::getName() { return this->name; }
std::wstring Patient::getDob() { return this->dob; }
std::wstring Patient::getChange() { return this->changedate; }
std::wstring Patient::getCreation() { return this->creationdate; }
std::wstring Patient::getDiagnosis() { return this->diagnosis; }

Worker::Worker(int id = 0, std::wstring name = L"", std::wstring job = L"", std::string login = "", std::string password = "") {
    this->id = id;
    this->name = name;
    this->job = job;
    this->login = login;
    this->password = password;
}
Worker::~Worker() {}
Worker::Worker(const Worker& temp) {
    id = temp.id;
    name = temp.name;
    job = temp.job;
    login = temp.login;
    password = temp.password;
}
Man* Worker::copy() { return new Worker(*this); }
int Worker::getId() { return this->id; }
std::string Worker::getLogin() { return this->login; }
std::string Worker::getPassword() { return this->password; }
std::wstring Worker::getName() { return this->name; }

const char* creatingTables = "CREATE TABLE IF NOT EXISTS patients ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	name text NOT NULL,"
"	dob date NOT NULL,"
"	carddate date NOT NULL,"
"	changedate date NOT NULL,"
"	diagnosis text NOT NULL"
");"
"CREATE TABLE IF NOT EXISTS operations ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	people_id integer NOT NULL,"
"	textofoperation text NOT NULL,"
"	operationdate date NOT NULL,"
"	worker integer NOT NULL"
");"
"CREATE TABLE IF NOT EXISTS workers ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	name text NOT NULL,"
"	job text NOT NULL,"
"	login text NOT NULL,"
"	password text NOT NULL"
");";

std::wstring charToWstring(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

std::string getPatientsDataSql = "SELECT * FROM patients";
int getPatientsData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 6) {
        _temppatientssdb_.push_back(new Patient(atoi(argv[i - 1]), charToWstring(argv[i]), charToWstring(argv[i + 1]), charToWstring(argv[i + 2]), charToWstring(argv[i + 3]), charToWstring(argv[i + 4])));
    }
    return 0;
}

std::string getOperationsDataSql = "SELECT * FROM operations";
int getOperations(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 5) {
        for (int j = 0; j < _temppatientssdb_.size(); ++j) {
            if (atoi(argv[i]) == _temppatientssdb_[j]->getId()) {
                _temppatientssdb_[j]->pushOperation(Operation(charToWstring(argv[i + 1]), charToWstring(argv[i + 2]), atoi(argv[i + 3])));
            }
        }
    }
    return 0;
}

std::string getWorkersDataSql = "SELECT * FROM workers";
int getWorkersData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 5) {
        _tempworkersdb_.push_back(new Worker(atoi(argv[i - 1]), charToWstring(argv[i]), charToWstring(argv[i + 1]), std::string(argv[i + 2]), std::string(argv[i + 3])));
    }
    return 0;
}

DB::DB() {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, getWorkersDataSql.c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, getOperationsDataSql.c_str(), getOperations, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, getPatientsDataSql.c_str(), getPatientsData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }        
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
    for (int i = 0; i < _temppatientssdb_.size(); ++i) {
        this->patients.push_back(_temppatientssdb_[i]->copy());
        delete _temppatientssdb_[i];
    }
    _temppatientssdb_.clear();
    for (int i = 0; i < _tempworkersdb_.size(); ++i) {
        this->workers.push_back(_tempworkersdb_[i]->copy());
        delete _tempworkersdb_[i];
    }
    _tempworkersdb_.clear();
}
DB::~DB() {
    for (int i = 0; i < patients.size(); ++i) {
        delete patients[i];
    }
    for (int i = 0; i < workers.size(); ++i) {
        delete workers[i];
    }
}
