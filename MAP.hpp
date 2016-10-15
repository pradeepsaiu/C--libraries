#ifndef DEQHPP
#define DEQHPP
//to  get pair
#include <utility> 

namespace cs540{

#define MAX_NUM_LEVELS 100
//this should always be greater than 0
#define INITIAL_HEIGHT 64 

template <typename Key_T, typename Mapped_T>
class skip_list{
        public:
		class node{
			public:
				std::pair< Key_T, Mapped_T> data;
				node *next,*prev,*top,*down;
		};
		//Meta data about the skip list
		int 	total_levels;
		int	current_height;
		int 	height_index;//points to current max head.
		/*To keep track of number of nodes in each level*/
		int	count_level[MAX_NUM_LEVELS];
		/*To keep track of first and last node at each level*/
		node *head[MAX_NUM_LEVELS],*tail[MAX_NUM_LEVELS],*temp_head[MAX_NUM_LEVELS];
		/*To initialize the skip list structure 4 nodes pointing to null*/
		skip_list(){
			//to help generate random numbers in different runs.
			srand(time(NULL));
			total_levels 			= MAX_NUM_LEVELS;
			current_height 			= INITIAL_HEIGHT;
			height_index			= 0;
		//	head[current_height-1] 		= new node();	
			int i = current_height-1;//zero indexing.
			//i = 0 being the main list where all elements are present.
			while(i>=0){
				head[i] 	= new node();
				temp_head[i]	= head[i];
				head[i]->next 	= NULL;	head[i]->prev 	= NULL;
				head[i]->top  	= NULL;	head[i]->down 	= NULL;
				count_level[i]  = 0;
				i--;
			}
			i=0;
		// Initializing the head list of elements
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
//			std::cout<<"\n###################\n";
		//	std::cout<<data.first<<data.second<<std::endl;	
			node *to_insert 	= new node();			
			node *base;
			to_insert->data 	= data;
			int temp_level		= height_index;
			node *start	 	= head[height_index];

			while( temp_level > 0){
//			Traverse to the level 0 where element needs to be inserted
				if(start->next == NULL || data.first < start->next->data.first){
//					std::cout<<"\n^^^1\n";
					temp_head[temp_level] = start;
					temp_level -= 1;
					start = start->down;
					continue;
				}
//					std::cout<<"\n^^^2\n";
					start = start->next;	
			}			
			/*inserting at the end of the linked list or first node of the skip_list*/
			if(start->next == NULL){
	//			std::cout<<head[0]<<"-----------------------";
//				std::cout<<"\n^^^3\n";
				start->next  	= to_insert;
				to_insert->prev	= start;
				tail[0]		= to_insert;
				count_level[0] += 1;	
				return(std::make_pair(start->next,true));
			}
			else{
//				std::cout<<"\n^^^4\n";
			//traverse and find where to insert the element
				while(start->next!=NULL && start->next->data.first<  data.first){
					start = start->next;//	std::cout<<"\n^^^5\n";

				}
				if(start->next == NULL){
				}
				else if(data.first == start->next->data.first){
				//	std::cout<<"\n^^^6\n";
					//returns false for duplicate value.
					return(std::make_pair(start->next,false));
				}else{}
				std::cout<<"\n^^^7\n";
				//inserting at level zero always
				to_insert->prev = start;
				to_insert->next = start->next;
//				if(start->next == NULL){tail[0]=to_insert;}
				start->next 	= to_insert;
				base		= to_insert;
				count_level[0]++;
				//now randomly check whether to promote up or not.
				//promote randomly only for random numbers
				int coin_flip = rand()%2, count=1;
				std::cout<<coin_flip;
				//promote if coin_flip = 1;
				while(coin_flip == 1 && count < current_height){
				//	std::cout<<"\n^^^7\n";
					node *to_insert1 	= new node();			
					to_insert1->data 	= data;
					to_insert1-> prev 	= temp_head[count];
					to_insert1-> next	= temp_head[count]->next;
					//by default top = NULL
					to_insert1-> down	= base;
					base->top		= to_insert1;
					base			= to_insert1;

					temp_head[count]->next	= to_insert1;

					count_level[count]++;	
					coin_flip 		= rand()%2;
					if(count > height_index){
						height_index = count;
					}
					//needn't insert higher, this is at highest peak
					if(count_level[count]==1){break;}
					count++;		
				}

				return(std::make_pair(start->next,true));
			}
		}

		void print(){
			node * traverse  = head[height_index];
			int level	 = height_index;
			std::cout<<"\nTotal height = "<<height_index<<"\n";
			std::cout<<"\n####"<<level<<"####\n";
			while(traverse != NULL){
				std::cout<<traverse->data.first<<traverse->data.second<<"==>";
				traverse = traverse->next;
				if(traverse == NULL and level != 0){
					std::cout<<"\n####"<<level-1<<"####"<<std::endl;
					level--;
					traverse = head[level];
				}
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
	}
	Map(const Map & copy_obj){
		typename skiptype::node *traverse = copy_obj.sk_list.head[0]; 
		while(traverse!=NULL){
			insert(traverse->data);
			traverse = traverse->next;
		}
	}
	Map &operator=(const Map & copy_obj):Map(copy_obj){
		return this;
	}
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
