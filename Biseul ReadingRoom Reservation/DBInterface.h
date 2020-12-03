#pragma once
#include "DBsystem.h"
#include <iostream>
#include"sqlite/sqlite3.h"

namespace biseul_rroom {

	class Exception {
	public:
		Exception() {};
		~Exception() {};
		void scenario(int code) {
			switch (code) {
			case (int)signal::DBREMOVEERR:
				std::cout << "From DBsystem: From DBsystem: Despite of data existence remove error.try again" << std::endl;
				return;
			case (int)signal::DBCLOSEFAIL:
				std::cout << "From DBsystem: close DBsystem::filename fail. May be memory leap occur" << std::endl;
				return;
			case (int)signal::DBOVERLAP:
				std::cout << "From DBsystem: student data already exists" << std::endl;
				return;
			case (int)signal::DBPARAMETERERR:
				std::cout << "From DBsystem: Recognize disallowed input. name length >99, student id, rfid = 0 is not allowed." << std::endl;
				return;
			case (int)signal::DBMODIFYERR:
				std::cout << "From DBsystem: Modify error. try again" << std::endl;
				return;
			}
		}
		void scenario(bool expn) {
			switch (expn) {
			case (bool)signal::DBNOTEXIST:
				std::cout << std::endl << "From DBsystem: no data found corresponding to input " << std::endl;
			}
		}
		void scenario(char* error) {
			std::cout << "From DBsystem: Sqlite query FAIL. error message: " << error;
		}
	};

	class DBinterface {
	private:
		DBsystem dbsys;
		class Exception exception;
	public:
		DBinterface()noexcept;
		DBinterface(std::string filename)noexcept;
		DBinterface(std::string filename, int max_name_length)noexcept { DBsystem(&filename, max_name_length) = dbsys; }
		virtual~DBinterface() {}
		virtual bool closeDB();
		virtual bool openDB(std::string* filename);
		virtual bool insert(std::string* name, int stud_id, int rfid_id);
		virtual bool modify_byrfid(const std::string name, const int stud_id, const int rfid_id, const int warning);
		virtual bool remove(int rfid_id);
		virtual bool remove_by_studid(int stud_id);
		virtual bool existence_check(int stud_id);
		virtual bool get_studinf(std::string*& name, const int& stud_id, int& rfid, int& warning);
		virtual bool get_studinf_byrfid(std::string*& name, int& stud_id, const int& rfid, int& warning);
		virtual bool give_penalty(int stud_id);
		virtual bool give_penalty_byrfid(int rfid);
	};
}