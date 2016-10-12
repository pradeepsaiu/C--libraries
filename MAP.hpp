#ifndef DEQHPP
#define DEQHPP
//to  get pair
#include <utility> 

namespace cs540{

#define MAX_NUM_LEVELS 100
//this should always be greater than 0
#define INITIAL_HEIGHT 4

template <typename Key_T, typename Mapped_T>
class skip_list{
        public:
		class node{
			public:
				std::pair< Key_T, Mapped_T> data;
				node *next,*prev,*top,*down;
//				node(std::pair< Key_T, Mapped_T> data_input){
//					data = data_input;
//				}	
		};
		//Meta data about the skip list
		int 	total_levels;
		int	current_height;
		int 	height_index;//points to current max head.
		/*To keep track of number of nodes in each level*/
		int	count_level[MAX_NUM_LEVELS];
		/*To keep track of first and last node at each level*/
		node *head[MAX_NUM_LEVELS],*tail[MAX_NUM_LEVELS];
		/*To initialize the skip list structure 4 nodes pointing to null*/
		skip_list(){
			total_levels 			= MAX_NUM_LEVELS;
			current_height 			= INITIAL_HEIGHT;
			height_index			= 0;
		//	head[current_height-1] 		= new node();	
			int i = current_height-1;//zero indexing.
			//i = 0 being the main list where all elements are present.
			while(i>=0){
				head[i] 	= new node();
				head[i]->next 	= NULL;
				head[i]->prev 	= NULL;
				head[i]->top  	= NULL;
				head[i]->down 	= NULL;
				count_level[i]  = 0;
				i--;
			}
			i=0;
			while(i<current_height){
				if(i == current_height-1){
					head[i]->down = head[i-1];
				}
				if(i!=0){
					head[i]->down = head[i-1];
					head[i]->top  = head[i+1];

				}
				else{
					head[i]->top  = head[i+1];
				}
				i++;
			}
		}
		std::pair<node *,bool> insert( std::pair<const Key_T, Mapped_T> data){
		//	std::cout<<data.first<<data.second<<std::endl;	
			node *to_insert 	= new node();			
			to_insert->data 	= data;
			int temp_level		= height_index;
			node *start	 	= head[height_index];

			while( temp_level > 0){
//			Traverse to the level 0 where element needs to be inserte
				if(start->next == NULL || data.first < start->next->data.first){
					temp_level-=1;
					start = start->down;
					continue;
				}
				start = start->next;	
			}			
			/*inserting at the end of the linked list or first node of the skip_list*/
			if(start->next == NULL){
	//			std::cout<<head[0]<<"-----------------------";
				start->next  	= to_insert;
				to_insert->prev	= start;
				tail[0]		= to_insert;
				count_level[0] += 1;	
				return(std::make_pair(start->next,true));
			}
			else{
				//traverse and find where to insert the element
				while(start->next!=NULL && data.first < start->next->data.first){
					start = start->next;
				}
				if(data.first == start->next->data.first){
					return(std::make_pair(start->next,false));
				}
				to_insert->prev = start;
				to_insert->next = start->next;
				if(start->next == NULL){tail[0]=to_insert;}
				start->next = to_insert;
				return(std::make_pair(start->next,true));
			}

		}
		void print(){
			node * traversal = head[0]->next;

			while(traversal!=NULL){
				std::cout<<traversal->data.first<<traversal->data.second<<std::endl;
				traversal = traversal->next;
			}		
		}
};


//declaring class with key value pair template
template <typename Key_T, typename Mapped_T>
class Map{
	public:
//don't change the order here
	typedef Key_T			 	 		KeyType;
	typedef Mapped_T			 		MapType;
	typedef skip_list<Key_T,Mapped_T>	 		skiptype;

	class Iterator{
	public:
		//to treat node as class type, rather than a member.
		typename skiptype::node  *point;
		Iterator(typename skiptype::node *val){
			point = val;
		}
		
	};
	typedef std::pair< Key_T, Mapped_T> 			ValueType;
//	typedef Map<Key_T,Mapped_T>::Iterator			Iterator;

	int size;
	skip_list<Key_T,Mapped_T> sk_list;
	

	Map(){	
		size = 0; 
	}
	Map(std::initializer_list<std::pair<const Key_T, Mapped_T> >  list_args){	
		auto start_ptr = list_args.begin();
		ValueType a;
		while(start_ptr != list_args.end())
		{
			sk_list.insert(std::make_pair(std::get<0>(*start_ptr),std::get<1>(*start_ptr)));			
			start_ptr++;
		}
//		sk_list.print();
	}
//	void insert(const ValueType & insert_value){
	std::pair<Iterator, bool> insert(const ValueType & insert_value){

		typename skiptype::node * ret_iterator;	bool flag;

		auto ret = std::make_pair(ret_iterator,flag);
		ret	 = sk_list.insert(insert_value);

		Iterator it(ret.first);
		flag = ret.second;

		return (std::make_pair(it,flag));
	}
	/*Element access funcitons*/
	//Mapped_T &at(const Key_T &){
	//}
};



}
#endif
