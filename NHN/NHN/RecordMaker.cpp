/*
*@file		RecordMaker.cpp
*@date		2016.05.21.
*@authr	Jeong Changkwon (92fmnsos@gmail.com)
*@detail
*NHN Tchnology Services [2016년 하계인턴] SW개발 부분 지원자 정창권입니다.
*자기소개에 있는 문제에 대한 소스코드입니다.
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
*@brief	사원의 번호와 점수 정보가 있는 클래스
*/
class Record {
private:
	string _id;		///사원의 번호
	int _score;		///사원의 점수
public:
	/*
	*@brief	사원의 번호를 입력한다.
	*@param	id는 string형의 사원의 번호
	*/
	void SetId(string id) {
		_id = id;
	}

	/*
	*@brief	사원의 점수를 입력한다.
	*@param	score는 int형의 사원의 점수
	*/
	void SetScore(int score) {
		_score = score;
	}

	/*
	@brief		사원의 번호를 반환한다.
	@return	사원의 번호
	*/
	string GetNewId() const {
		return _id;
	}

	/*
	@brief		사원의 점수를 반환한다.
	@return	사원의 점수
	*/
	int GetScore() const {
		return _score;
	}

	/*
	*@brief	사원의 번호와 점수를 화면에 출력한다. (출력형식 : 사원번호 사원점수)
	*/
	void  PrintRecord() const {
		cout << _id << " " << _score << endl;
	}
};

/*
*@class	IdGenerator
*@date		2016.05.21.
*@detail
*새로운 사원의 번호를 생성하는 클래스입니다.
*사원의 번호는 NTxxxxx(x:[0~9])의 형식으로 생성되며 숫자는 임의의 수로 할당됩니다.
*사원의 번호는 고유하기 때문에 동일한 번호는 존재하지 않습니다.
*사용법 IdGenerator::GetInstance()->GetNewId();
*/
class IdGenerator {
private:
	set<string> id;		///사원들의 번호 집합
	static IdGenerator *instance;		//IdGenerator의 instance

	IdGenerator() {
		//가산랜덤함수, seed 값은 time으로 설정
		srand((unsigned)time(NULL));
	}
	~IdGenerator() {
	}
public:
	/*
	*@brief	IdGenerator의 instance를 반환하는 함수로 singleton 패턴으로 구현했습니다.
	*@return	IdGenerator의 객체
	*/
	static IdGenerator* GetInstance() {
		if (instance == NULL) {
			instance = new IdGenerator();
		}
		return instance;
	}

	/*
	*@brief	사원의 고유한 번호를 만듭니다.
	*@return	사원의 번호
	*/
	string GenerateId() {
		bool flg_id = false;
		int tmp_int;		//임시 int형 변수
		string tmp_str;		//임시 string형 변수
		stringstream ss;		//번호의 형식에 맞게 하기위한 stringstream
		set<string>::iterator it;

		while (!flg_id) {		//사원의 번호가 중복이 된다면 새로운 번호를 생성한다.
			tmp_int = rand() % 100000;
			ss << setw(5) << setfill('0') << tmp_int;
			tmp_str = "NT" + ss.str();
			it = id.find(tmp_str);
			if (it == id.end()) {		//true면 새로운 번호가 중복된 번호가 아니다.
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
	*@brief	현재 모든 사원들의 번호를 출력합니다.
	*/
	void PrintId() {
		for (set<string>::iterator it = id.begin(); it != id.end(); ++it) {
			cout << *it << endl;
		}
	}

	/*
	*@brief	새로운 사원의 번호를 GenerateId()함수를 이용해 만들어 반환합니다.
	*@return	새로운 사원의 번호
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
*IdGenerator의 클래스와 하는 일은 같습니다.
*다른 점은 IdGenerator클래스는 사원의 번호를 만들때마다 중복된 번호를 검색하지만
*이 클래스는 초기화 과정에서 모든 번호를 만들고 새로운 번호가 필요할때마다 반환하는 것으로 구현하였습니다.
*/
class IdGenerator2 {
private:
	set<string> id;			//사원들의 번호 집합
	string remains[100000];			//남아있는 번호의 string 배열
	int size = 100000;				//남아있는 번호의 개수
	static IdGenerator2 *instance;			//IdGenerator2의 instance

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
	*@brief	IdGenerator2 클래스를 초기화합니다.
	*이 과정에서 사원들의 번호로 사용할 수 있는 모든 번호를 생성하여 remains 배열에 넣습니다.
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
	*@brief	현재 모든 사원들의 번호를 출력합니다.
	*/
	void PrintId() {
		for (set<string>::iterator it = id.begin(); it != id.end(); ++it) {
			cout << *it << endl;
		}
	}

	/*
	*@brief	새로운 사원 번호를 반환합니다.
	*@return	새로운 사원의 번호
	*@detail
	*이 함수는 초기화 과정에서 만들어 놓은 사원 번호 중에서 임의로 하나를 선택해 반환합니다.
	*초기화 과정에서 중복된 번호를 만들지 않았기 때문에 추가적인 작업이 필요하지 않습니다.
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
		cout << "사용법 : " << argv[0] << " [count]" << endl
			<< endl
			<< "Your Input arguments ====" << endl;
		for (int i = 0; i < argc; ++i) {
			cout << argv[i] << " ";
		}
		cout << endl;
		return 1;
	}

	int record_number = atoi(argv[1]);		//현재 record의 수
	Record *record;

	record = new Record[record_number];

	//입력된 record의 수만큼 사원의 번호와 점수를 임의로 생성하여 record 배열에 넣는다.

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