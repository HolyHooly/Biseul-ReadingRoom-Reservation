#pragma once
#include<iostream>
#include<string>
#include"sqlite/sqlite3.h"

namespace biseul_rroom {
	enum class signal {
		DBNOTEXIST, DBSUCCESS, DBREMOVEERR, DBCLOSEFAIL, DBOVERLAP, DBPARAMETERERR, DBMODIFYERR
	};

	class DBsystem {
	private:
		sqlite3* DB;
		std::string filename = "dbsys0.db";
		int max_name_length = 100;

	public:

		DBsystem(std::string* filename, int max_name_length)noexcept;
		DBsystem()noexcept;
		virtual~DBsystem();
		bool load();
		bool load(const std::string* filename);
		bool terminate();

		bool insert(std::string* name, int stud_id, _int64 rfid_id);
		bool get_studinf_bystudid(std::string*& name, const int& stud_id, _int64& rfid_id, int& warning);
		bool get_studinf_byrfid(std::string*& name, int& stud_id, const _int64& rfid_id, int& warning);
		bool remove_data_bystudid(int& stud_id);
		bool remove_data_byrfidid(_int64& rfid_id);
		bool modify_byrfid(const std::string* name, const int stud_id, const _int64 rfid_id, const int warning);
		bool add_penalty(int& stud_id);
		bool add_penalty_byrfid(_int64& rfid_id);
	};
}