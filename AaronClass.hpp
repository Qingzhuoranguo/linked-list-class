class AaronLinkedList {
private:
	class Node_t {
	public:
		int item;
		Node_t* next;
	};
	
	class LL_stats {
	public:
		int NodeCount;
		double Average;
		int Max;
		int Min;
		double Total;
	};
	Node_t* LLHead;
	LL_stats Stats;

	void UpdateStats( int item, int op);
	void Update_extremes();
	Node_t* CreateNode ( int item );
	int Insert ( Node_t* node);
	bool FindNode ( Node_t* node );
	Node_t* Finditem ( int item );
	Node_t* GetTail ();
	Node_t* SortList_insert( Node_t* temp_head,Node_t* node );

public:

	AaronLinkedList();
	void Destory();
	void print_list();
	void print_stats();
	int AddNode ( int item, int dest );
	int DeleteNode ( int item );
	void SortList ();

};