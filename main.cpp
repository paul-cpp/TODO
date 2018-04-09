#include <iostream>
#include <time.h>
#include <random>

#include <thread>
#include <mutex>

#include <memory>

#include <string>
#include <vector>
#include <map>
#include <set>

#include <boost\date_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

enum class Priority{
	LOW,
	MIDDLE,
	HIGH
};

static size_t TASK_ID = 0;

class Task
{
public:
	Task(){
		onConstruct();
	}

	Task(string& content_){
		onConstruct();
		content = content_;
	}

	void editContent(string& newContent){
		if (content == newContent){
			return;
		}
		content = newContent;
	}

	~Task(){	};
		
	ptime getFinishTime() const{
		return finishTime;
	}

	void setContent(string& content_){
		content = content_;
	}
	string getContent() const {
		return content;
	}

	bool getFinishStatus() const{
		return isFinished;
	}

	void setMark(bool mark = true){
		isMarked = mark;
	}
	bool getMark() const{
		return isMarked;
	}

	void finishTask(){
		isFinished = true;
		finishTime = second_clock::local_time();
	}

	void printInfo() const{
		cout << content << ":" << endl;
		cout << "\t" << "ID:" << ID << endl;
		cout << "\t" << "priority:" << static_cast<int> (priority)  << endl;
		cout << "\t" << "startTime:" << startTime << endl;
		cout << "\t" << "finishTime:" << finishTime << endl;
		cout << "\t" << "isMarked:" << std::boolalpha << isMarked << endl;
		cout << "\t" << "isFinished:" << std::boolalpha << isFinished << endl;
	}

protected:
	void onConstruct(){
		priority = Priority::MIDDLE;
		isFinished = false;
		startTime = second_clock::local_time();
		isMarked = false;
		ID = TASK_ID++;
		
	}

	void setFinishStatus(bool status = true){
		isFinished = status;
	}
	void setFinishTime(ptime time_){
		finishTime = time_;
	}


private:
	size_t ID;
	string content;
	Priority priority;
	bool isFinished;
	ptime startTime;
	ptime finishTime;
	bool isMarked;
};

class Person
{
public:
	Person(){}
	Person(string name_, size_t age_) {
		name = name_;
		age = age_;
	}
	~Person(){};

private:
	string name;
	size_t age;
};

class Organizer{
public:
	Organizer(){}

	Organizer(string& personName, size_t personAge)
	{
		person = new Person(personName, personAge);
	}
	void createTask(string& taskContent){
		tasks.push_back(Task(taskContent));
	}
	
	~Organizer(){
		if (person != nullptr)
			delete person;
	};

	 Task& getTaskByIndex(size_t index) {
		return tasks.at(index);
	}

	void print() const{
		for (auto i : tasks){
			i.printInfo();
		}
	}

private:
	size_t number;
	Person* person;
	vector<Task> tasks; //массив задач
};

int main()
{
	srand(time(NULL));

	Organizer org(std::string("Paul"), 20);
	
	org.createTask(string ("task1"));
	org.createTask(string ("task2"));
	org.createTask(string ("task3"));

	try
	{
		Task& t = org.getTaskByIndex(10);
		t.setContent(string(t.getContent() + " edited"));
		t.setMark();
		t.finishTask();
	}
	catch (exception &ex){
		cout << ex.what() << endl;
	}

	org.print();

	cin.get();
	return 0;
}