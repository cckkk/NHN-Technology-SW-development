/*
*@file		RecordMaker.cpp
*@date		2016.05.21.
*@authr	Jeong Changkwon (92fmnsos@gmail.com)
*@detail
*NHN Tchnology Services [2016�� �ϰ�����] SW���� �κ� ������ ��â���Դϴ�.
*�ڱ�Ұ��� �ִ� ������ ���� �ҽ��ڵ��Դϴ�.
*/
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<string>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<vector>

#define HOWTO_FIRST 0 
#define HOWTO_SECOND 1
#define HOWTO HOWTO_SECOND

using namespace std;

/*
*@class	Record
*@date		2016.05.21.
*@brief	����� ��ȣ�� ���� ������ �ִ� Ŭ����
*/
class Record {
private:
	string _id;		///����� ��ȣ
	int _score;		///����� ����
public:
	/*
	*@brief	����� ��ȣ�� �Է��Ѵ�.
	*@param	id�� string���� ����� ��ȣ
	*/
	void SetId(string id) {
		_id = id;
	}

	/*
	*@brief	����� ������ �Է��Ѵ�.
	*@param	score�� int���� ����� ����
	*/
	void SetScore(int score) {
		_score = score;
	}

	/*
	@brief		����� ��ȣ�� ��ȯ�Ѵ�.
	@return	����� ��ȣ
	*/
	string GetNewId() const {
		return _id;
	}

	/*
	@brief		����� ������ ��ȯ�Ѵ�.
	@return	����� ����
	*/
	int GetScore() const {
		return _score;
	}

	/*
	*@brief	����� ��ȣ�� ������ ȭ�鿡 ����Ѵ�. (������� : �����ȣ �������)
	*/
	void  PrintRecord() const {
		cout << _id << " " << _score << endl;
	}
};

/*
*@class	IdGenerator
*@date		2016.05.21.
*@detail
*���ο� ����� ��ȣ�� �����ϴ� Ŭ�����Դϴ�.
*����� ��ȣ�� NTxxxxx(x:[0~9])�� �������� �����Ǹ� ���ڴ� ������ ���� �Ҵ�˴ϴ�.
*����� ��ȣ�� �����ϱ� ������ ������ ��ȣ�� �������� �ʽ��ϴ�.
*���� IdGenerator::GetInstance()->GetNewId();
*/
class IdGenerator {
private:
	set<string> id;		///������� ��ȣ ����
	static IdGenerator *instance;		//IdGenerator�� instance

	IdGenerator() {
		//���귣���Լ�, seed ���� time���� ����
		srand((unsigned)time(NULL));
	}
	~IdGenerator() {
	}
public:
	/*
	*@brief	IdGenerator�� instance�� ��ȯ�ϴ� �Լ��� singleton �������� �����߽��ϴ�.
	*@return	IdGenerator�� ��ü
	*/
	static IdGenerator* GetInstance() {
		if (instance == NULL) {
			instance = new IdGenerator();
		}
		return instance;
	}

	/*
	*@brief	����� ������ ��ȣ�� ����ϴ�.
	*@return	����� ��ȣ
	*/
	string GenerateId() {
		bool flg_id = false;
		int tmp_int;		//�ӽ� int�� ����
		string tmp_str;		//�ӽ� string�� ����
		stringstream ss;		//��ȣ�� ���Ŀ� �°� �ϱ����� stringstream
		set<string>::iterator it;

		while (!flg_id) {		//����� ��ȣ�� �ߺ��� �ȴٸ� ���ο� ��ȣ�� �����Ѵ�.
			tmp_int = rand() % 100000;
			ss << setw(5) << setfill('0') << tmp_int;
			tmp_str = "NT" + ss.str();
			it = id.find(tmp_str);
			if (it == id.end()) {		//true�� ���ο� ��ȣ�� �ߺ��� ��ȣ�� �ƴϴ�.
										//cout << tmp_str << endl;
				id.insert(tmp_str);
				flg_id = true;
			}
			else {
				tmp_int = 0;
				tmp_str = "";
				ss.str("");
			}
		}

		return tmp_str;
	}

	/*
	*@brief	���� ��� ������� ��ȣ�� ����մϴ�.
	*/
	void PrintId() {
		for (set<string>::iterator it = id.begin(); it != id.end(); ++it) {
			cout << *it << endl;
		}
	}

	/*
	*@brief	���ο� ����� ��ȣ�� GenerateId()�Լ��� �̿��� ����� ��ȯ�մϴ�.
	*@return	���ο� ����� ��ȣ
	*/
	string GetNewId() {
		return GenerateId();
	}
};
IdGenerator* IdGenerator::instance = NULL;

/*
*@class	IdGenerator2
*@date		2016.05.21.
*@detail
*IdGenerator�� Ŭ������ �ϴ� ���� �����ϴ�.
*�ٸ� ���� IdGeneratorŬ������ ����� ��ȣ�� ���鶧���� �ߺ��� ��ȣ�� �˻�������
*�� Ŭ������ �ʱ�ȭ �������� ��� ��ȣ�� ����� ���ο� ��ȣ�� �ʿ��Ҷ����� ��ȯ�ϴ� ������ �����Ͽ����ϴ�.
*/
class IdGenerator2 {
private:
	set<string> id;			//������� ��ȣ ����
	string remains[100000];			//�����ִ� ��ȣ�� string �迭
	int size = 100000;				//�����ִ� ��ȣ�� ����
	static IdGenerator2 *instance;			//IdGenerator2�� instance

	IdGenerator2() {
		srand((unsigned)time(NULL) * 33);
		Init();
	}
	~IdGenerator2() {
	}
public:
	static IdGenerator2* GetInstance() {
		if (instance == NULL) {
			instance = new IdGenerator2();
		}
		return instance;
	}
	/*
	*@brief	IdGenerator2 Ŭ������ �ʱ�ȭ�մϴ�.
	*�� �������� ������� ��ȣ�� ����� �� �ִ� ��� ��ȣ�� �����Ͽ� remains �迭�� �ֽ��ϴ�.
	*/
	void Init() {
		string tmp_str;
		stringstream s;

		for (int i = 0; i < 100000; ++i) {
			s << setw(5) << setfill('0') << i; i;
			tmp_str = "NT" + s.str();
			remains[i] = tmp_str;
			s.str("");
		}
	}

	/*
	*@brief	���� ��� ������� ��ȣ�� ����մϴ�.
	*/
	void PrintId() {
		for (set<string>::iterator it = id.begin(); it != id.end(); ++it) {
			cout << *it << endl;
		}
	}

	/*
	*@brief	���ο� ��� ��ȣ�� ��ȯ�մϴ�.
	*@return	���ο� ����� ��ȣ
	*@detail
	*�� �Լ��� �ʱ�ȭ �������� ����� ���� ��� ��ȣ �߿��� ���Ƿ� �ϳ��� ������ ��ȯ�մϴ�.
	*�ʱ�ȭ �������� �ߺ��� ��ȣ�� ������ �ʾұ� ������ �߰����� �۾��� �ʿ����� �ʽ��ϴ�.
	*/
	string GetNewId() {
		int tmp_int = rand() % size;
		string tmp_id = remains[tmp_int];

		remains[tmp_int] = remains[size - 1];
		remains[size - 1] = "";
		--size;
		id.insert(tmp_id);
		return tmp_id;
	}
};
IdGenerator2* IdGenerator2::instance = NULL;

int main(int argc, char* argv[]) {

	//argument error handling
	if (argc != 2) {
		cout << "���� : " << argv[0] << " [count]" << endl
			<< endl
			<< "Your Input arguments ====" << endl;
		for (int i = 0; i < argc; ++i) {
			cout << argv[i] << " ";
		}
		cout << endl;
		return 1;
	}

	int record_number = atoi(argv[1]);		//���� record�� ��
	Record *record;

	record = new Record[record_number];

	//�Էµ� record�� ����ŭ ����� ��ȣ�� ������ ���Ƿ� �����Ͽ� record �迭�� �ִ´�.

#if HOWTO == HOWTO_FIRST
	for (int i = 0; i < record_number; ++i) {
		record[i].SetId(IdGenerator::GetInstance()->GetNewId());
		record[i].SetScore(rand() % 100);

		record[i].PrintRecord();
	}

#elif HOWTO == HOWTO_SECOND
	for (int i = 0; i < record_number; ++i) {
		record[i].SetId(IdGenerator2::GetInstance()->GetNewId());
		record[i].SetScore(rand() % 100);

		record[i].PrintRecord();
	}
#endif


	return 0;
}