#include <iostream>
#include "dynamic_array.h"
#include "my_string.h"
#include <string>
int main() {
    // demonstrate dynamic_array
    // finalize dynamic_array: add copy ctor, copy assignment op using swap
    // make dynamic_array generic
    // make the array iterable
    // add basic_tracked_string instances to the dynamic_array
    // check how many copies are being made
    // introduce move semantics
    // prevent copies of basic_tracked_string!
    // rule of 5

   /* dynamic_array<std::string>v_str2;
    v_str2.push_back(std::string{"hello"});
    v_str2.push_back(std::string{"helly"});
    v_str2.push_back(std::string{"hellay"});
    dynamic_array<std::string>v_str3(std::move(v_str2));
    std::cout<<"\nTest iterator v_str3:\n";
    for(const auto&i:v_str3){
        std::cout<<i<<"\n";
    }
    std::cout<<"Test iterator v_str2:\n";
    for(const auto&i:v_str2){
        std::cout<<i<<"\n";
    }*/
  /* dynamic_array<int>v_int;
   v_int.push_back(1);
   v_int.push_back(3);
   v_int.push_back(5);
   v_int.push_back(6);
   v_int.push_back(10);
   v_int.push_back(14);
   v_int.push_back(16);
   v_int.push_back(17);
   v_int.push_back(19);
   v_int.push_back(20);
   v_int.push_back(22);
   std::cout<<"\nBefore insert 2 at begin\n";
   for(const auto&i:v_int){
       std::cout<<i<<" ";
   }
   std::cout<<"\nAfter insert 2 at begin\n";
   v_int.insert(v_int.begin(),std::move(2));
   for(const auto&i:v_int){
        std::cout<<i<<" ";
   }
   v_int.insert(v_int.begin()+3,std::move(4));
   std::cout<<"\nAfter insert 4 at 3rd position\n";
   for(const auto&i:v_int){
       std::cout<<i<<" ";
   }
   std::cout<<"\nAfter insert 12 at the end \n";
   v_int.insert(v_int.end()+2,12);
    for(const auto&i:v_int){
        std::cout<<i<<" ";
    }
    std::cout<<"\nErase 1st element\n";
    v_int.erase(v_int.begin());
    for(const auto&i:v_int){
        std::cout<<i<<" ";
    }
    std::cout<<"\nErase 2 nd element\n";
    v_int.erase(v_int.begin()+1);
    for(const auto&i:v_int){
        std::cout<<i<<" ";
    }
    std::cout<<"\nErase last element\n";
    v_int.erase(v_int.end());
    for(const  auto&i:v_int){
        std::cout<<i<<" ";
    }
    std::cout<<"\nErase range [0:4)\n";
    v_int.erase(v_int.begin(),v_int.begin()+4);
    for(const auto&i: v_int){
        std::cout<<i<<" ";
    }
    std::cout<<"\nErase range [1:4)\n";
    v_int.erase(v_int.begin()+1,v_int.begin()+4);
    for(const auto&i: v_int){
        std::cout<<i<<" ";
    }
    */

    dynamic_array<basic_tracked_string<char>>v_str;
    v_str.push_back(basic_tracked_string<char>("Hello1"));
    v_str.push_back(basic_tracked_string("Hello2"));
    v_str.push_back(basic_tracked_string("Hello3"));
    v_str.push_back(basic_tracked_string("Hello4"));
    v_str.push_back(std::move(basic_tracked_string("Hello5")));
   dynamic_array<basic_tracked_string<char>>v_str2;
    v_str2.push_back(basic_tracked_string("World1"));
    v_str2.push_back(basic_tracked_string("World2"));
    v_str2.push_back(basic_tracked_string("World3"));
    v_str2.push_back(basic_tracked_string("World4"));
    v_str2.push_back(std::move(basic_tracked_string("World5")));
/*
    std::cout<<"\n List of words: ";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }

    v_str.insert(v_str.begin(),basic_tracked_string("Hello0"));
    std::cout<<"\nInsert at 1st array\n";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }

    v_str.insert(v_str.begin()+3, basic_tracked_string("Hello9"));
    std::cout<<"\nInsert at 3rd element\n";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }

    v_str.insert(v_str.end(), basic_tracked_string("Hello10"));
    std::cout<<"\nInsert at last  element\n";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }

    v_str.erase(v_str.begin());
    std::cout<<"\nErase at 1st element\n";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }
    v_str.erase(v_str.begin()+3);
    std::cout<<"\nErase at 3rd element\n";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }

    v_str.erase(v_str.end());
    std::cout<<"\nErase at last element\n";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }

    v_str.erase(v_str.begin(),v_str.begin()+4);
    std::cout<<"\nErase at [0:4) elements\n";
    for(const auto&i:v_str){
        std::cout<<i<<" ";
    }*/
    v_str = v_str2;


    return 0;
}
