#include "contact_list.h"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>

namespace contact_list {
using number_t = int64_t;
struct storage;
bool add(storage& contacts, std::string_view name, number_t number)
{
    if (name.empty()){
        return false;
    }
    for(unsigned i = 0; i<contacts.names.size(); i++)
    {
       if(contacts.names[i].compare(name) == 0)
       {
        return false;
       }
    }
    contacts.names.push_back(std::string(name));
    contacts.numbers.push_back(number);
    return true;
}

size_t size(const storage& contacts) {
   return contacts.names.size();
}

number_t get_number_by_name(storage& contacts, std::string_view name)
{
    for(unsigned i = 0; i<contacts.names.size(); i++)
    {
       if(contacts.names[i].compare(name) == 0)
       {
        return contacts.numbers[i];
       }
    }
    return -1;
}

std::string to_string(const storage& contacts) {
    std::string ergebnis= "";
    for(unsigned i = 0; i<contacts.names.size(); i++)
    {
        ergebnis = ergebnis + contacts.names[i] + " - " + std::to_string(contacts.numbers[i]) + "\n";
    }
    return ergebnis;
}
bool remove(storage& contacts, std::string_view name)
{
    for(unsigned i = 0; i<contacts.names.size(); i++)
    {
       if(contacts.names[i].compare(name) == 0)
       {
        contacts.names.erase(contacts.names.begin() + i);
        contacts.numbers.erase(contacts.numbers.begin() + i);
        return true;
       }
    }
    return false;
}
void sort(storage& contacts)
{
    for(unsigned i = 0; i<contacts.names.size() - 1; i++)
    {
         for(unsigned n = 0; n<contacts.names.size() - i - 1; n++)
         {
            if(contacts.names[n].compare(contacts.names[n+1])>0)
            {
               std::string tmp1 = contacts.names[n];
               contacts.names[n] = contacts.names[n+1];
               contacts.names[n+1] = tmp1;
               number_t tmp2 = contacts.numbers[n];
               contacts.numbers[n] = contacts.numbers[n+1];
               contacts.numbers[n+1] = tmp2;
            }
         }
    }
}
std::string get_name_by_number(storage& contacts, number_t number)
{
    for(unsigned i = 0; i<contacts.numbers.size(); i++)
    {
       if(contacts.numbers[i] == number){
        return contacts.names[i];
       }
    }
    return "";
}
}
