#pragma once
#include<iostream>
#include<string>
#include"sqlite/sqlite3.h"
#include"vector"

namespace biseul_rroom {
	enum class signal {
		DBNOTEXIST, DBSUCCESS, DBREMOVEERR, DBCLOSEFAIL, DBOVERLAP, DBPARAMETERERR, DBMODIFYERR,DBUPDATEERR,DBSORTERR
	};

	class studinf final {
	public:
		studinf() {}
		studinf(std::string name, int studid, _int64 rfid, int warning, int index) {
			studinf::name = name;
			studinf::stud_id = studid;
			studinf::rfid_id = rfid;
			studinf::warning = warning;
			studinf::index = index;
		}
		~studinf() {}
		std::string name = "";
		int stud_id = 0;
		_int64 rfid_id = 0;
		int warning = 0;
		int index = 0;
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
		bool datasort(int axis, int mode);
		bool get_data_number(int& number);
		bool update_total_data_number(int add);
		bool insert(std::string* name, int stud_id, _int64 rfid_id);
		bool get_studinf_bystudid(std::string*& name, const int& stud_id, _int64& rfid_id, int& warning, int& index);
		bool get_studinf_byrfid(std::string*& name, int& stud_id, const _int64& rfid_id, int& warning, int& index);
		bool get_studinf_byindex(std::string*& name, int& stud_id, _int64& rfid_id, int& warning, const int& index);
		bool get_all_studinf(std::vector<studinf>& x);
		bool remove_data_bystudid(int& stud_id);
		bool remove_data_byrfidid(_int64& rfid_id);
		bool modify_byrfid(const std::string* name, const int stud_id, const _int64 rfid_id, const int warning, const int index);
		bool add_penalty(int& stud_id);
		bool add_penalty_byrfid(_int64& rfid_id);
		

		//bool update_data_index(int stud_id,int new_index);
	};
}