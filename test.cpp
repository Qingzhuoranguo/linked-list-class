#include <iostream>
#include <string.h>
#include "AaronClass.hpp"

using namespace std;


int main () {
	AaronLinkedList list;
	for (int i = 0; i < 10; i++ ){
		list.AddNode (i,1);
	}
	list.print_list();
	list.print_stats();

	for (int i = 0; i < 10; i++ ){
		list.DeleteNode(i);
	}
	list.print_list();



	list.Destory();


	return 0;
}