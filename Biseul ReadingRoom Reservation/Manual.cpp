#include "DBinterface.h"

int main() {

	/// - DBinterface ���� -
	/// �Լ��� : DBinterface() , DBinterface(string filename)
	/// <returns> ����
	/// <throw> 
	///     DBinterface() : �⺻ db������ ����, ���� ���н� �����ڵ� ���ڸ� ����ϰ� false�� throw.
	///     DBinterface(string filename) : �ش� filename ������ ����, ���� ���н� �����ڵ� ���ڸ� ����ϰ� false �� throw.
	                            
	
	biseul_rroom::DBinterface* interface1 = new biseul_rroom::DBinterface;  //// DB ����Ʈ ���� :"dbsys0.db" �� �����ͺ��̽��� ����ϴ� DB�������̽�1 ����.
	biseul_rroom::DBinterface* interface2 = new biseul_rroom::DBinterface("desired_filename.db");  //// DB ����: "dedesired_filename.db" �� �����ͺ��̽��� ����ϴ� DB�������̽�2 ����.
	

	/// - �����ͺ��̽� ���� ���ų� ���� -
	/// �Լ��� : closeDB(), openDB(string* filename)
	/// <returns> ���� ���� �� ���� ���н� �����޼����� ����ϰ� false�� ����. ������ true�� ����.
	/// <throw> ����

	std::string file = "newfile.db";
	interface1->closeDB();  // ���� DB ������ �����Ͽ� ������ true�� ����, ���н� �����޼����� ����ϰ� false �� ����.
	interface1->openDB(&file);  // file �������Ͽ� ������ true�� ����, ���н� �����ڵ� �޼����� ����ϰ� false �� ����.

	/// -�����ͺ��̽��� �л����� ���� -
	/// �Լ��� : insert(string* name, int stud_id, _int64 rfid_id)
	/// <returns> �л����� ������ �����ϸ� True �� return.
	///           �л����� ������ �����ϸ� ���� ������ ����ϰ� false �� return.
	/// <throw>  ����.

	std::string name = "name";
	interface1->insert(&name, 201011010, 1234);  // �л��̸��� �ּ�, �й��� rfid�� �Ķ���ͷ� �����Ͽ� �����ͺ��̽��� �л������� ����. 
	                                             // ���� ���н� False �� �����Ͽ� �������̽� ����ڰ� ���и� ������ �� ����. 
	                                             // warning �� 0���� ����.	

	/// - �����ͺ��̽����� Ư�� �л����� ���� -
	/// �Լ��� : remove(_int64 rfid_id) , remove_by_studid(int stud_id)
	/// <returns> �ش� �л����� ������ �����ϸ� true �� return.
	///           �ش� �л����� ������ �����ϸ� ���� ������ ����ϰ� false �� return.
	/// <throw>  ����.
	

	
	interface1->remove(123);  // �ش� �л� rfid�� �Ķ���ͷ� �����Ͽ� �����ͺ��̽����� �ش� �л������� ����. ���н� false �� ����.
	interface1->remove_by_studid(20101101);  // �ش� �л� �й��� �Ķ���ͷ� �����Ͽ� �����ͺ��̽����� �ش� �л������� ����. ���н� false �� ����.
	
	
	/// - �����ͺ��̽��� �ش� �л����� ���翩�� üũ -
	/// �Լ��� : existence_check(int stud_id), existence_check(_int64 rfid_id)
	/// <returns> �����ͺ��̽��� �ش� �л����� ����� true �� ����.
	///           �����ͺ��̽��� �ش� �л����� ���� �� false �� ����.
	/// <throw> ����.
	

	interface1->existence_check(201011010);  // �ش� �л� �й��� �Ķ���ͷ� �����Ͽ� �����ͺ��̽����� �ش� �л����� üũ�Ͽ� ����� true ����,
	                                        // ���� �� false ����.
	interface1->existence_check_byrfid(1234);

	/// - �����ͺ��̽��� �ش� �л����� �������� -
	/// �Լ��� : bool get_studinf(string*& name,const int& stud_id,_int64& rfid, int& warning);
	///          bool get_studinf_byrfid(string * &name, int& stud_id, const _int64& rfid, int& warning);
	/// <returns> �����ͺ��̽��� �ش� �л����� ����� �ش� �л������� �����Ķ���ͷ� �����ϰ� true�� ����. 
	/// .         �ش� �л� ������ ���ų� ���� �߻��� ���������� ����ϰ� false�� ����.
	/// <throw> ����.
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

	interface1->get_studinf(nameptr,202011010,desired_rfid,desired_warning);  // �ش� �л� �й��� �Ķ���ͷ� �����Ͽ� �����ͺ��̽����� �ش� �л������� 
	                                                                          // ���޵� �Ķ���Ϳ� �����ϰ� true�� ����. ���н� ������ ����ϰ� false�� ����.                           
	std::cout <<"guy name : "<<desired_name << std::endl;
	std::cout << "guy student ID : " << 202011010 << std::endl;
	std::cout << "guy rfid : "<< desired_rfid << std::endl;
	std::cout << "guy warning : " << desired_warning << std::endl;

	interface1->get_studinf_byrfid(nameptr, desired_stud_id,2000, desired_warning);  // �ش� �л� rfid�� �Ķ���ͷ� �����Ͽ� �����ͺ��̽����� �ش� �л������� 
																			  // ���޵� �Ķ���Ϳ� �����ϰ� true�� ����. ���н� ������ ����ϰ� false�� ����.
	std::cout << "girl name : " << desired_name << std::endl;
	std::cout << "girl student ID : " << desired_stud_id << std::endl;
	std::cout << "girl rfid : " << 2000 << std::endl;
	std::cout << "girl warning : " << desired_warning << std::endl;

	/// - �����ͺ��̽��� �ش� �л� �г�Ƽ ���� -
	/// �Լ��� :give_penalty(int& stud_id) , give_penalty_byrfid(_int64 rfid)
	/// <returns> �����ͺ��̽��� �ش� �л� warning ���� 1 ������Ű�� true�� ����. 
	/// .         �ش� �л� ������ ���ų� ���� �߻��� ���������� ����ϰ� false�� ����.
	/// <throw> ����.
	
	interface1->give_penalty(202011010);  // �й� 202011010 �� �л����� �г�Ƽ 1 �߰��ϰ� ������ true ����. ���н� �����޼��� ����ϰ� false ����.
	interface1->give_penalty_byrfid(2000);  // rfid 2000 �� �л����� �г�Ƽ 1 �߰��ϰ� ������ true ����. ���н� �����޼��� ����ϰ� false ����.

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


	/// - �����ͺ��̽��� �ش� �л� ���� ���� -
	/// �Լ��� : modify_byrfid(const string name, const int stud_id, const _int64 rfid_id, const int warning)
	/// <returns> �����ͺ��̽��� �ش� �л������� ���޵� �Ķ������ ������ ����(rfid ����)�ϰ� true�� ����. 
	/// .         �ش� �л� ������ ���ų� ���� �߻��� ���������� ����ϰ� false�� ����.
	///           �ش� �л��� rfid_id�� �����Ͽ��� �ش� �л������� ������ �� ����.
	/// <throw> ����.

	interface1->modify_byrfid("���л�", 20802080, 2000, 0); // rfid 2000 �� �л��� �̸��� �й�, ���Ƚ���� ���� '���л�', 20802080, 0 ���� �����ϰ� ������ true ����.
	                                                        // �ش��л��� ���ų� ��������� false�� �����ϰ� �����޼����� ���.

	interface1->get_studinf_byrfid(nameptr, desired_stud_id, 2000, desired_warning);
																			
	std::cout << "girl name : " << desired_name << std::endl;
	std::cout << "girl student ID : " << desired_stud_id << std::endl;
	std::cout << "girl rfid : " << 2000 << std::endl;
	std::cout << "girl warning : " << desired_warning << std::endl;
}