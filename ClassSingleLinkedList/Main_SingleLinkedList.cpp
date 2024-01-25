#include <ctime>
#include "SingleLinkedList.h"
#include <forward_list>
#include <conio.h>

using namespace std;

int random(int minN, int maxN);
void showListLib(forward_list<int> _list);

int main() {
	srand((int)time(0));
	const int length = 10;
	const int minNumber = 1;
	const int maxNumber = 5;
	//forward_list<int> listLib;
	SingleLinkedList<int> list;
	//int numRemove = random(minNumber, maxNumber);
	//for (int i = 0; i < length; i++) {
	//	int iTemp = random(minNumber, maxNumber);
	//	list.addHead(iTemp);
	//	//listLib.push_front(iTemp);
	//}

	list.add_tail(1);
	list.add_tail(2);
	list.add_tail(3);
	list.add_tail(4);
	list.add_tail(5);
	list.add_tail(6);
	list.add_tail(7);

	for (Node<int> * ptr_walker = list.get_head(); ptr_walker != nullptr; ptr_walker = ptr_walker->get_next()) {
		cout << ptr_walker->get_data() << ' ';
	}
	//list.show_list();
	cout << endl;
	cout << "Number will be removed: " << 1 << endl;
	cout << "SingleLinkedList: \n";
	//list.removeFirstFindOf(numRemove);
	Node<int> * ptr_middle_node = list.find_middle_node();
	//list.show_elements_from(ptr_middle_node);
	cout << endl << "-------------------------------------------" << endl;
	//cout << endl << "listLib: \n";
	//listLib.remove(numRemove);
	//showListLib(listLib);
	return 0;
}

int random(int minN, int maxN) {
	return minN + rand() % (maxN + 1 - minN);
}

void showListLib(forward_list<int> _list) {
	for (forward_list<int>::iterator it = _list.begin(); it != _list.end(); ++it)
		cout << *it << ' ';
}
