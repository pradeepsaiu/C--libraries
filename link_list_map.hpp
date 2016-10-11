#ifndef DEQHPP
#define DEQHPP
//to  get pair
#include <utility> 

namespace cs540{

template <typename Key_T, typename Mapped_T>
struct skip_list{
        public:
		int height;
		std::pair< Key_T, Mapped_T> data;
                skip_list *next,*prev,*top,*bottom;
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
		skiptype *point;
		
	};
	typedef std::pair< Key_T, Mapped_T> 			ValueType;
//	typedef Map<Key_T,Mapped_T>::Iterator			Iterator;

	int size;
	skip_list<Key_T,Mapped_T> *skip_head,*skip_tail;
	

	Map(){
		skip_head = NULL;
		size = 0; 
	}
	Map(std::initializer_list<std::pair<const Key_T, Mapped_T> >  list_args){
		
		auto start_ptr = list_args.begin();
		ValueType a;
		while(start_ptr != list_args.end())
		{
			insert(std::make_pair(std::get<0>(*start_ptr),std::get<1>(*start_ptr)));			
			start_ptr++;
		}
	}
	std::pair<Iterator, bool> insert(const ValueType & insert_value){
		Iterator return_it;bool return_flag=true;

		if(skip_head!=NULL){
			skiptype * temp = skip_head;
			while(temp->next != NULL){temp = temp->next;}
			skiptype * newnode = new skiptype();
			temp->next = newnode;
			newnode->prev = temp;
			newnode->data = insert_value;
			return_it.point = newnode;
			size++;
		}
		else{		
			skip_head = new skiptype();
			skip_head->data =  insert_value;
			skip_tail = skip_head;
			return_it.point = skip_head;
			size++;
		}

		return (std::make_pair(return_it,return_flag));
	}
	/*Element access funcitons*/
	//Mapped_T &at(const Key_T &){
	//}
};



}
#endif
