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
			head[current_height-1] 		= new node();	
			int i = current_height-1;//zero indexing.
			//i = 0 being the main list where all elements are present.
			while(i<=0){
				head[i] 	= new node();
				head[i]->next 	= NULL;
				head[i]->prev 	= NULL;
				head[i]->top  	= NULL;
				head[i]->down 	= NULL;
				count_level[i]  = 0;
				i--;
			}
			while(i<current_height){
				if(i == current_height){
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
		void insert( std::pair<const Key_T, Mapped_T> data){
			std::cout<<data.first<<data.second<<std::endl;	
			node *to_insert = new node();
			to_insert->data = data;
			/*Inserting the first node*/
			if(height_index == 0 && count_level[0] == 0){
				std::cout<<head[0]<<"-----------------------";
			//	head[0]->next  = to_insert;
				count_level[0] = 1;	
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
		skiptype point;
		
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
	}
//	std::pair<Iterator, bool> insert(const ValueType & insert_value){
//		Iterator return_it;bool return_flag=true;
//		return (std::make_pair(return_it,return_flag));
//	}
	/*Element access funcitons*/
	//Mapped_T &at(const Key_T &){
	//}
};



}
#endif
