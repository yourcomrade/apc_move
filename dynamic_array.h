//
// Created by rgr24 on 28/10/2022.
//

#ifndef MOVE_SEMANTICS_DYNAMIC_ARRAY_H
#define MOVE_SEMANTICS_DYNAMIC_ARRAY_H
#include <cstring>
#include <utility>

template<typename T>
class dynamic_array {
public:


    static const std::size_t DEFAULT_CAPACITY{1};
    dynamic_array(std::size_t capacity): m_begin(allocate())
            , m_last(m_begin)
            , m_end(m_begin + capacity)
    {

    }

    dynamic_array():dynamic_array(DEFAULT_CAPACITY){}


    // TODO: copy ctor
    dynamic_array(const dynamic_array&other):dynamic_array(other.capacity())
    {
        for(int i=0;i<=other.size();i++){
            this->push_back(other.m_begin[i]);
        }
    }
    T*begin(){
        return m_begin;
    }
    T* end(){

        return m_last;
    }

    ///Function to destroy object
    void destroy_obj_all(){
        if(m_begin== nullptr)
            return;
        ///for(auto obj:this) cannot
        for(auto it=begin();it!=end();it++){
            (*it).~T();
        }
    }

    // TODO: copy assignment
    dynamic_array& operator=(const dynamic_array&other){
        if(this==&other){
            return *this;
        }
        else{
            destroy_obj_all();//Destroy all objects stored in memory
            delete[]m_begin;//Deallocated memory
            return *this=dynamic_array<T>(other);
        }
    }
    ///Move contructor
    dynamic_array(dynamic_array&&other)noexcept:
    m_begin(std::exchange(other.m_begin, nullptr)),
    m_last(std::exchange(other.m_last, nullptr)),
    m_end(std::exchange(other.m_end, nullptr))
    {}
    ///Move assignment
    dynamic_array& operator=(dynamic_array&&other)noexcept{
        if(&other==this){
            return *this;
        }
        else{
          //  destroy_obj_all();
            delete[]m_begin;
            m_begin=std::exchange(other.m_begin, nullptr);
            m_last=std::exchange(other.m_last, nullptr);
            m_end=std::exchange(other.m_end, nullptr);
            return *this;
        }
    }

   void push_back(T&& val) {
       adjust_capacity();
       ::new (m_last) T{std::move(val)};
       m_last++;
   }
    void push_back(const T& val) {
        adjust_capacity();
       ::new (m_last) T{std::move(val)};
        m_last++;
    }


    std::ptrdiff_t size() const { return m_last - m_begin; }
    std::ptrdiff_t capacity() const { return m_end - m_begin; }
    bool empty() const { return m_begin == m_end; }
    void clear() {
        destroy_obj_all();///Destroy objects
        delete[]m_begin;
        m_begin= nullptr;
        m_last= nullptr;
        m_end = m_begin; }

    const T& operator[](int index) const { return m_begin[index]; }
    T& operator[](int index) { return m_begin[index]; }

    ~dynamic_array() noexcept {
        destroy_obj_all();///Destroy all objects
        delete[] m_begin;
        m_begin= nullptr;
        m_last= nullptr;
        m_end= nullptr;

    }
    using iterator = T*;
    using const_iterator = const T*;
    iterator insert(const_iterator pos, const T& value){

        auto cur_size=size()+1;
        auto cur_cap=cur_size*3/2+1;
        auto ptr=new T[cur_cap];
        T*cur_pos= nullptr;
        if(pos==m_begin){
            ptr[0]=value;
            cur_pos=&ptr[0];
            std::memcpy(&ptr[1],&m_begin[0],sizeof(m_begin[0])*size());
        }
        else if(pos>m_begin && pos <=m_last){
            std::memcpy(&ptr[0],&m_begin[0],sizeof(m_begin[0])*(pos-m_begin));
            ptr[pos-m_begin]=value;
            cur_pos=&ptr[pos-m_begin];
            std::memcpy(&ptr[pos-m_begin+1],&m_begin[pos-m_begin],sizeof(m_begin[0])*(m_end-pos));
        }
        else{
            std::memcpy(&ptr[0],&m_begin[0],sizeof(m_begin[0])*size());
            ptr[size()]=value;
            cur_pos=&ptr[size()];
        }
        destroy_obj_all(); ///Destroy all objects
        delete[]m_begin;
        m_begin=&ptr[0];
        m_last=m_begin+cur_size;
        m_end=m_begin+cur_cap;
        return cur_pos;
    }
    iterator insert(const_iterator pos, T&& value){

        auto cur_size=size()+1;
        auto cur_cap=cur_size*3/2+1;
        auto ptr=new T[cur_cap];
        T*cur_pos= nullptr;
        if(pos==m_begin){
            ptr[0]=std::move(value);
            cur_pos=&ptr[0];
            std::memmove(&ptr[1],&m_begin[0],sizeof(m_begin[0])*size());
        }
        else if(pos>m_begin && pos <=m_last){
            std::memmove(&ptr[0],&m_begin[0],sizeof(m_begin[0])*(pos-m_begin));
            ptr[pos-m_begin]=std::move(value);
            cur_pos=&ptr[pos-m_begin];
            std::memmove(&ptr[pos-m_begin+1],&m_begin[pos-m_begin],sizeof(m_begin[0])*(m_end-pos));
        }
        else{
            std::memmove(&ptr[0],&m_begin[0],sizeof(m_begin[0])*size());
            ptr[size()]=std::move(value);
            cur_pos=&ptr[size()];
        }
        destroy_obj_all();///Destroy all objects
        delete[]m_begin;
        m_begin=&ptr[0];
        m_last=m_begin+cur_size;
        m_end=m_begin+cur_cap;
        return cur_pos;
    }

    iterator erase( iterator pos ){
        if(pos<m_begin||pos>m_last){
            return m_last;
        }
        else{
           if(pos==m_last){
               m_last->~T();//Destroy object
               m_last--;
           }
           else{
              for(int i=(pos-m_begin);i!=(m_last-pos);i++){
                  m_begin[i]=std::move(m_begin[i+1]);
              }
               m_last->~T();//Destroy object
               m_last--;
           }
           return m_last;
        }
    }
    iterator erase( const_iterator pos ){
        return erase(pos);
    }
    iterator erase( iterator first, iterator last ){
        if(first<=m_begin && last>m_last ){
            destroy_obj_all();///Destroy all objects
            delete[]m_begin;
            m_begin = nullptr;
            m_last = nullptr;
            m_end = nullptr;
        }
        else{
           int j=first-m_begin;
           for(int i=(last-m_begin);i!=(m_last-first+1);i++){
               m_begin[j]=std::move(m_begin[i]);
               j++;
           }
           for(auto i=last;i<=m_last;i++){
               i->~T();///Destroy object
           }
           m_last-=(last-first);
        }
        return m_last;
    }
    iterator erase( const_iterator pos, const_iterator last ){
        return erase(pos,last);
    }
private:
    ///Allocate memory for object
    T*allocate(std::size_t n=DEFAULT_CAPACITY){
        return static_cast<T*>( operator new[](sizeof(T) * n) );
    }

    void adjust_capacity() {
        if (m_last == m_end) {
            // reallocate
            auto current_size = size();
            auto new_size = current_size * 3 / 2 + 1;
            dynamic_array<T>other(new_size);
            for(auto &i:*this){
                other.push_back(std::move(i));
            }
            *this=std::move(other);
        }
    }




    T *m_begin;
    T *m_last;
    T *m_end;
};


#endif //MOVE_SEMANTICS_DYNAMIC_ARRAY_H
