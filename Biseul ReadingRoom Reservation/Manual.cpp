#include "DBinterface.h"

int main() {

	/// - DBinterface 생성 -
	/// 함수명 : DBinterface() , DBinterface(string filename)
	/// <returns> 없음
	/// <throw> 
	///     DBinterface() : 기본 db파일을 열고, 오픈 실패시 에러코드 문자를 출력하고 false를 throw.
	///     DBinterface(string filename) : 해당 filename 파일을 열고, 오픈 실패시 에러코드 문자를 출력하고 false 를 throw.
	                            
	
	biseul_rroom::DBinterface* interface1 = new biseul_rroom::DBinterface;  //// DB 디폴트 파일 :"dbsys0.db" 를 데이터베이스로 사용하는 DB인터페이스1 생성.
	biseul_rroom::DBinterface* interface2 = new biseul_rroom::DBinterface("desired_filename.db");  //// DB 파일: "dedesired_filename.db" 를 데이터베이스로 사용하는 DB인터페이스2 생성.
	

	/// - 데이터베이스 새로 열거나 종료 -
	/// 함수명 : closeDB(), openDB(string* filename)
	/// <returns> 파일 종료 및 열기 실패시 에러메세지를 출력하고 false를 리턴. 성공시 true를 리턴.
	/// <throw> 없음

	std::string file = "newfile.db";
	interface1->closeDB();  // 현재 DB 파일을 종료하여 성공시 true를 리턴, 실패시 에러메세지를 출력하고 false 를 리턴.
	interface1->openDB(&file);  // file 을오픈하여 성공시 true를 리턴, 실패시 에러코드 메세지를 출력하고 false 를 리턴.

	/// -데이터베이스에 학생정보 저장 -
	/// 함수명 : insert(string* name, int stud_id, _int64 rfid_id)
	/// <returns> 학생정보 저장을 성공하면 True 를 return.
	///           학생정보 저장을 실패하면 실패 이유를 출력하고 false 를 return.
	/// <throw>  없음.

	std::string name = "name";
	interface1->insert(&name, 201011010, 1234);  // 학생이름의 주소, 학번과 rfid를 파라미터로 전달하여 데이터베이스에 학생정보를 저장. 
	                                             // 저장 실패시 False 를 리턴하여 인터페이스 사용자가 실패를 인지할 수 있음. 
	                                             // warning 은 0으로 저장.	

	/// - 데이터베이스에서 특정 학생정보 삭제 -
	/// 함수명 : remove(_int64 rfid_id) , remove_by_studid(int stud_id)
	/// <returns> 해당 학생정보 삭제를 성공하면 true 를 return.
	///           해당 학생정보 삭제를 실패하면 실패 이유를 출력하고 false 를 return.
	/// <throw>  없음.
	

	
	interface1->remove(123);  // 해당 학생 rfid를 파라미터로 전달하여 데이터베이스에서 해당 학생정보를 삭제. 실패시 false 를 리턴.
	interface1->remove_by_studid(20101101);  // 해당 학생 학번을 파라미터로 전달하여 데이터베이스에서 해당 학생정보를 삭제. 실패시 false 를 리턴.
	
	
	/// - 데이터베이스에 해당 학생정보 존재여부 체크 -
	/// 함수명 : existence_check(int stud_id), existence_check(_int64 rfid_id)
	/// <returns> 데이터베이스에 해당 학생정보 존재시 true 를 리턴.
	///           데이터베이스에 해당 학생정보 없을 시 false 를 리턴.
	/// <throw> 없음.
	

	interface1->existence_check(201011010);  // 해당 학생 학번을 파라미터로 전달하여 데이터베이스에서 해당 학생정보 체크하여 존재시 true 리턴,
	                                        // 없을 시 false 리턴.
	interface1->existence_check_byrfid(1234);

	/// - 데이터베이스에 해당 학생정보 가져오기 -
	/// 함수명 : bool get_studinf(string*& name,const int& stud_id,_int64& rfid, int& warning);
	///          bool get_studinf_byrfid(string * &name, int& stud_id, const _int64& rfid, int& warning);
	/// <returns> 데이터베이스에 해당 학생정보 존재시 해당 학생정보를 참조파라미터로 전달하고 true를 리턴. 
	/// .         해당 학생 정보가 없거나 오류 발생시 오류내용을 출력하고 false를 리턴.
	/// <throw> 없음.
	std::string guyname = "john";
	std::string girlname = "katt";
	std::string desired_name;
	std::string* nameptr = &desired_name;
	int desired_stud_id;
	_int64 desired_rfid;
	int desired_warning;
	interface1->insert(&guyname,202011010,1000);
	interface1->insert(&girlname, 202010000, 2000);
	int tmp;

	interface1->get_studinf(nameptr,202011010,desired_rfid,desired_warning);  // 해당 학생 학번을 파라미터로 전달하여 데이터베이스에서 해당 학생정보를 
	                                                                          // 전달된 파라미터에 저장하고 true를 리턴. 실패시 이유를 출력하고 false를 리턴.                           
	std::cout <<"guy name : "<<desired_name << std::endl;
	std::cout << "guy student ID : " << 202011010 << std::endl;
	std::cout << "guy rfid : "<< desired_rfid << std::endl;
	std::cout << "guy warning : " << desired_warning << std::endl;

	interface1->get_studinf_byrfid(nameptr, desired_stud_id,2000, desired_warning);  // 해당 학생 rfid를 파라미터로 전달하여 데이터베이스에서 해당 학생정보를 
																			  // 전달된 파라미터에 저장하고 true를 리턴. 실패시 이유를 출력하고 false를 리턴.
	std::cout << "girl name : " << desired_name << std::endl;
	std::cout << "girl student ID : " << desired_stud_id << std::endl;
	std::cout << "girl rfid : " << 2000 << std::endl;
	std::cout << "girl warning : " << desired_warning << std::endl;

	/// - 데이터베이스의 해당 학생 패널티 증가 -
	/// 함수명 :give_penalty(int& stud_id) , give_penalty_byrfid(_int64 rfid)
	/// <returns> 데이터베이스의 해당 학생 warning 값을 1 증가시키고 true를 리턴. 
	/// .         해당 학생 정보가 없거나 오류 발생시 오류내용을 출력하고 false를 리턴.
	/// <throw> 없음.
	
	interface1->give_penalty(202011010);  // 학번 202011010 인 학생에게 패널티 1 추가하고 성공시 true 리턴. 실패시 에러메세지 출력하고 false 리턴.
	interface1->give_penalty_byrfid(2000);  // rfid 2000 인 학생에게 패널티 1 추가하고 성공시 true 리턴. 실패시 에러메세지 출력하고 false 리턴.

	interface1->get_studinf(nameptr, 202011010, desired_rfid, desired_warning);  
																			                        
	std::cout << "guy name : " << desired_name << std::endl;
	std::cout << "guy student ID : " << 202011010 << std::endl;
	std::cout << "guy rfid : " << desired_rfid << std::endl;
	std::cout << "guy warning : " << desired_warning << std::endl;

	interface1->get_studinf_byrfid(nameptr, desired_stud_id, 2000, desired_warning); 
																			
	std::cout << "girl name : " << desired_name << std::endl;
	std::cout << "girl student ID : " << desired_stud_id << std::endl;
	std::cout << "girl rfid : " << 2000 << std::endl;
	std::cout << "girl warning : " << desired_warning << std::endl;


	/// - 데이터베이스의 해당 학생 정보 변경 -
	/// 함수명 : modify_byrfid(const string name, const int stud_id, const _int64 rfid_id, const int warning)
	/// <returns> 데이터베이스의 해당 학생정보를 전달된 파라미터의 값으로 변경(rfid 제외)하고 true를 리턴. 
	/// .         해당 학생 정보가 없거나 오류 발생시 오류내용을 출력하고 false를 리턴.
	///           해당 학생의 rfid_id를 전달하여야 해당 학생정보를 변경할 수 있음.
	/// <throw> 없음.

	interface1->modify_byrfid("김학생", 20802080, 2000, 0); // rfid 2000 인 학생의 이름과 학번, 경고횟수를 각각 '김학생', 20802080, 0 으로 변경하고 성공시 true 리턴.
	                                                        // 해당학생이 없거나 변경오류시 false를 리턴하고 에러메세지를 출력.

	interface1->get_studinf_byrfid(nameptr, desired_stud_id, 2000, desired_warning);
																			
	std::cout << "girl name : " << desired_name << std::endl;
	std::cout << "girl student ID : " << desired_stud_id << std::endl;
	std::cout << "girl rfid : " << 2000 << std::endl;
	std::cout << "girl warning : " << desired_warning << std::endl;
}