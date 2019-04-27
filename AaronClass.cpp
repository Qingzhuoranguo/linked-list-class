#include "AaronClass.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

AaronLinkedList::AaronLinkedList(){
	LLHead = NULL;
	Stats.NodeCount = 0;
	Stats.Average = 0.0;
	Stats.Max = 0;
	Stats.Min = 0;
	Stats.Total = Stats.Average * Stats.NodeCount;
}

void AaronLinkedList::Update_extremes(){
	int min = 0;
	int max = 0;
	Node_t *cur_chekpt = LLHead;
	while (cur_chekpt!=NULL){
		int val = cur_chekpt->item;
		if ( val > max ){
			max = val;
		}
		if ( val < min ){
			min = val;
		}
		cur_chekpt = cur_chekpt-> next;
	}
	Stats.Max = max;
	Stats.Min = min;
}

void AaronLinkedList::UpdateStats( int item, int op ) {
	int total_difference = 0;
	int count_difference = 0;
	if (op == 0) { //addition
		total_difference = 0 + item;
		count_difference = 1;
		if (Stats.Max < item){
			Stats.Max = item;
		}
		if (Stats.Min > item){
			Stats.Min = item;
		}
	}else if (op ==1){ //deletion
		total_difference = 0 - item;
		count_difference = -1;
		if ( Stats.Max == item || Stats.Min == item ){
			Update_extremes();
		} 
	}else {  //destructor
		Stats.NodeCount = 0;
		Stats.Average = 0;
		Stats.Max = 0;
		Stats.Min = 0;
		Stats.Total = Stats.Average * Stats.NodeCount;
		return ;
	}
	Stats.Total = Stats.Total + total_difference;
	Stats.NodeCount = Stats.NodeCount + count_difference;
	if (Stats.NodeCount == 0){
		Stats.Average = 0;
	}else {
		Stats.Average = Stats.Total / ( Stats.NodeCount );
	}

	
	return;
}

AaronLinkedList::Node_t* AaronLinkedList::CreateNode ( int item ){
	Node_t *node = new Node_t;
	if (node == NULL){
		return node;
	}
	node->item = item;
	node->next = NULL;
	return node;
}

int AaronLinkedList::Insert( Node_t* node ){
	if (node == NULL) {
		return -1;
	}

	node->next = LLHead;
	LLHead = node;
	return 0;
}

bool AaronLinkedList::FindNode ( Node_t* node ){
	Node_t* cur_chekpt = LLHead;
	bool flag = false;
	while ( cur_chekpt != NULL ){
		if ( cur_chekpt == node ){
			flag = true;
			break;
		}
		cur_chekpt = cur_chekpt->next;
	}
	return flag;
}

AaronLinkedList::Node_t* AaronLinkedList::Finditem ( int item ){
	Node_t* cur_chekpt = LLHead;
	while ( cur_chekpt != NULL ){
		if ( cur_chekpt->item == item ){
			break;
		}
		cur_chekpt = cur_chekpt->next;
	}
	return cur_chekpt;
}

AaronLinkedList::Node_t* AaronLinkedList::GetTail(){
	Node_t* cur_chekpt = LLHead;
	if (cur_chekpt == NULL){
		return LLHead;
	}
	while ( cur_chekpt->next != NULL ){
		cur_chekpt = cur_chekpt->next;
	}
	return cur_chekpt;
}
AaronLinkedList::Node_t* AaronLinkedList::SortList_insert( Node_t* temp_head, Node_t* node ){
	//have not inserted anything yet
	if ( temp_head == NULL ){ 
		temp_head = node;
		node->next = NULL;
	}else {
		if (node->item <= temp_head->item){//check the first node->item
			node -> next = temp_head;
			temp_head = node;
		}else { //the first node is smaller.
			Node_t* pre_chekpt = temp_head;
			Node_t* cur_chekpt = temp_head->next;
			while ( cur_chekpt != NULL ){
				if ( node->item <= cur_chekpt->item ){
					pre_chekpt -> next = node;
					node->next = cur_chekpt;
					break;
				}
				pre_chekpt = cur_chekpt;
				cur_chekpt = cur_chekpt->next;
			}
		}
	}
	return temp_head;
}

void AaronLinkedList::SortList(){
	Node_t* temp_head = NULL;
	Node_t* cur_chekpt = LLHead;
	while ( cur_chekpt != NULL ){
		LLHead = cur_chekpt->next;
		temp_head = SortList_insert (temp_head, cur_chekpt);

		cur_chekpt = LLHead;
	}
	LLHead = temp_head;
}

void AaronLinkedList::Destory(){
	Node_t* cur_chekpt = LLHead;
	while ( cur_chekpt != NULL ){
		Node_t* temp = cur_chekpt;
		cur_chekpt = cur_chekpt-> next;
		delete temp;
	}
	UpdateStats( 50, 3);
	LLHead = NULL;
}

int AaronLinkedList::DeleteNode ( int item ){
	Node_t* temp = NULL;
	bool flag = false;
	if ( LLHead->item == item ){
		flag = true;
		temp = LLHead;
		LLHead = LLHead->next;
		delete temp;
	}else {
		Node_t* pre_chekpt = LLHead;
		Node_t* cur_chekpt = LLHead -> next;
		while (cur_chekpt != NULL){
			if (cur_chekpt->item == item){
				flag = true;
				pre_chekpt->next = cur_chekpt->next;
				temp = cur_chekpt;
				delete temp;
				break;
			}
			pre_chekpt = cur_chekpt;
			cur_chekpt = cur_chekpt->next;
		}
	}
	if (flag){ //item found
		UpdateStats( item, 1);
		return 0;	
	}else { //item not found
		return -2;
	}
}

void AaronLinkedList::print_list(){
	Node_t* cur_chekpt = LLHead;
	cout << "[ ";
	while (cur_chekpt!=NULL){
		cout << cur_chekpt->item << " ";
		cur_chekpt = cur_chekpt->next;
	}
	cout << "]" <<endl;
}

int AaronLinkedList::AddNode (int item, int dest){
	if ( dest == 0 ){
		int id = Insert ( CreateNode(item) );
		UpdateStats( item, 0);
		return id;
	}else if (dest == 1){
		Node_t* node = CreateNode(item);
		if (node == NULL){
			return -2;
		}
		Node_t* tail = GetTail();
		if ( tail == NULL ){ //if tail is head
			LLHead = node;
		}else {
			tail -> next = node;
		}
		UpdateStats( item, 0 );
		return 0;
	}else {
		return -3;
	}
}

void AaronLinkedList::print_stats(){
	cout << "=============status=============" << endl;
	cout << "# of nodes: " << Stats.NodeCount << endl;
	cout << "Item total: " << Stats.Total << endl;
	cout << "Average of items: " << fixed << setprecision(2) << Stats.Average << endl;
	cout << "Maximum item: " << Stats.Max << endl;
	cout << "Minimum item: " << Stats.Min << endl << endl;
}