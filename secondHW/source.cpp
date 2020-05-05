#include <iostream>
#include<string>
#include<fstream>
#include <cstring>

#define _CRT_SECURE_NO_WARNINGS ;

using namespace std;

struct TASK {
	char TaskName[32];
	int ST;
	int ET;

	TASK *NextTask;
};


struct MACHINE {
	int id;
	TASK *firstTask;
	MACHINE *NextMachine;

};


TASK * create_task(char *name, int start, int end) {

	TASK *n;
	n = new TASK;
	strcpy_s(n->TaskName, name);
	n->ST = start;
	n->ET = end;

	n->NextTask = NULL;
	return n;

}
TASK *add_Task(TASK *head , TASK *n) {
	TASK *p1, *p2;

	if (head == NULL) {
		head = n;
		return head;
	}
	if (head->ST > n->ST ) {

		n->NextTask = head;
		head = n;
		return head;
	}
	p1 = p2 = head;
	while (p2 != NULL) {
		if (p2->ST > n->ST) {
			p1->NextTask = n;
			n->NextTask = p2;
			return head;
		}
		else {
			p1 = p2;
			p2 = p2->NextTask;
		}

	}
	n->NextTask = p2;
	p1->NextTask = n; 
	return head;

}
void printe_list(TASK *head) {
	TASK *p;
	if (head == NULL) cout << "emphty list.." << endl;

	p = head;
	while (p != NULL) {
		cout << p->TaskName << "::" << p->ST << "-" << p->ET << endl;
		p = p->NextTask;
	}
}

MACHINE * create_machine(int num) {
	MACHINE *n;
	n = new MACHINE;
	n->firstTask = NULL;
	n->NextMachine = NULL;
	n->id = num;
	return n;
}
MACHINE*add_machine(TASK*n, MACHINE*m, MACHINE*head)
{
	MACHINE*p1, *p2;
	if (head == NULL)
	{
		head = m;
		m->firstTask = n;
		return head;
	}
	if (m->id < head->id)
	{
		m->NextMachine = head;
		head = m;
		m->firstTask = n;
		return head;
	}
	p1 = p2 = head;
	while (p2 != NULL)
	{
		if (m->id < p2->id)
		{
			m->NextMachine = p2;
			p1->NextMachine = m;
			m->firstTask = n;
			return head;
		}
		else
		{
			p1 = p2;
			p2 = p2->NextMachine;
		}
	}
	m->NextMachine = p2;
	p1->NextMachine = m;
	m->firstTask = n;
	return head;
}
MACHINE* add_task_to_machine(MACHINE*headm, TASK*n, int&id)
{
	MACHINE*k;
	TASK*t;
	k = headm;
	t = k->firstTask;
	while (k != NULL)
	{
		t = k->firstTask;
		while (t->NextTask != NULL)
		{
			t = t->NextTask;
		}
		if (n->ST >= t->ET)
		{
			t->NextTask = n;
			break;
		}
		else
		{
			k = k->NextMachine;
		}
	}
	if (k == NULL)
	{
		id = 0;
	}
	return headm;
}
void printm(MACHINE*head)
{
	MACHINE*p1;
	TASK*p2;
	p1 = head;
	while (p1 != NULL)
	{
		cout << "\n";
		cout << "Machine" << p1->id << ":" << endl;;
		p2 = p1->firstTask;
		printe_list(p2);
		p1 = p1->NextMachine;
	}
}

void main() {
	int number_line; //numbers of line given by the user in file
	char task_name[32];
	int start, end , count = 1;
	TASK *head;
	TASK *n;
	TASK *p1, *p2, *p3, *p4;
	head = NULL;
	//machin var
	MACHINE *first_machine;
	first_machine = NULL;
	MACHINE *z;

	//the end of machine declaration

	cout << "type in the filename : " << endl; 
	char file_name[32];
	cin >> file_name;

	ifstream file_in(file_name, ios::in);
	file_in >> number_line;

	for (int i = 0; i < number_line ;i++) {

		file_in >> task_name >> start >> end;
		n = create_task(task_name, start, end);
		head = add_Task(head, n);
	}
	if (head == NULL) {
		cout << "No machine can be created.." << endl;
	}
	
	p1 = NULL;
	p2 = p3 = head;
	while (head != NULL)
	{
		if (p2 = head)
		{
			z = create_machine(count);
			p3 = p3->NextTask;
			head = head->NextTask;
			p2->NextTask = NULL;
			first_machine = add_machine(p2, z, first_machine);
		}
		while (head != NULL)
		{
			p3 = head;
			head = head->NextTask;
			p3->NextTask = NULL;
			int N = 1;
			first_machine = add_task_to_machine(first_machine, p3, N);
			if (N == 0)
			{
				count++;
				z = create_machine(count);
				first_machine = add_machine(p3, z, first_machine);
			}
		}
	}
	printm(first_machine);

	

	system("pause");
}