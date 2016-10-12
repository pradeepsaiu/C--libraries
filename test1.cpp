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
    std::pair<char, std::string> aluetype('a',"bc");

    cs540::Map<char,std::string> morse1;
    cs540::Map<int, int> map;
    morse.insert(std::make_pair('a', "plus"));
    morse.insert(std::make_pair('c',"minus"));
     morse.insert(std::make_pair('d', "plus"));
    morse.insert(std::make_pair('b',"minus"));
   morse.sk_list.print();

   return 0;
}

