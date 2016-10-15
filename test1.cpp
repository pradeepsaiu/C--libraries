#include<iostream>
#include<stdio.h>
#include "MAP.hpp"
cs540::Map<char, std::string> morse {
    {',', "--..--"},
    {'.', ".-.-.-"},
    {'?', "..--.."},
    {'0', "----- "},
    {'1', ".---- "},
    {'2', "..--- "},
    {'3', "...-- "},
    {'4', "....- "},
    {'5', "..... "},
    {'6', "-.... "},
    {'7', "--... "},
    {'8', "---.. "},
    {'9', "----. "},
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.. "},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-.."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."},
};
int main ()
{
    	cs540::Map<char, std::string> cc_check(morse);
	cs540::Map<char, std::string> cc_check2;

    cs540::Map<int,std::string> morse1;
    cs540::Map<int, int> map;
    morse1.insert(std::make_pair(1, "plus"));
 //	morse1.sk_list.print();

   morse1.insert(std::make_pair(2,"minus"));
//	morse1.sk_list.print();

    morse1.insert(std::make_pair(3, "plus"));
//	morse1.sk_list.print();

    morse1.insert(std::make_pair(4,"minus"));

   morse1.insert(std::make_pair(5, "plus"));
    morse1.insert(std::make_pair(6,"minus"));
    morse1.insert(std::make_pair(7, "plus"));
    morse1.insert(std::make_pair(8,"minus"));
	morse1.sk_list.print();
   morse.sk_list.print();
   cc_check.sk_list.print();	
//  cc_check2(cc_check2);

   return 0;
}

