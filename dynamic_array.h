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
    dynamic_array(std::size_t capacity): m_begin(allocate(capacity))
            , m_last(m_begin)
            , m_end(m_begin + capacity)
    {

    }

    dynamic_array():dynamic_array(DEFAULT_CAPACITY){}


    // TODO: copy ctor
    dynamic_array( const dynamic_array& other):dynamic_array(other.capacity())
    {
        for(auto &i:other)
            this->push_back(i);
    }
    T*begin(){
        return m_begin;
    }
    T* end(){

        return m_last;
    }



    // TODO: copy assignment
    dynamic_array& operator=( const dynamic_array &other){
        if(this==&other){
            return *this;
        }
        else{

            delete[]m_begin;///Destroy object and  deallocated memory
            std::swap(*this,dynamic_array<T>(other));
            return *this;

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
            destroy_obj_all();
            ::operator delete[](m_begin);
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
       ::new (m_last) T{val};
        m_last++;
    }


    std::ptrdiff_t size() const { return m_last - m_begin; }
    std::ptrdiff_t capacity() const { return m_end - m_begin; }
    bool empty() const { return m_begin == m_end; }
    void clear() {
        destroy_obj_all();///Destroy objects
        m_last= m_begin;
         }

    const T& operator[](int index) const { return m_begin[index]; }
    T& operator[](int index) { return m_begin[index]; }

    ~dynamic_array() noexcept {
        destroy_obj_all();///Destroy all objects
        ::operator delete[] (m_begin);
        m_begin= nullptr;
        m_last= nullptr;
        m_end= nullptr;

    }
    using iterator = T*;
    using const_iterator = const T*;
    iterator insert(const_iterator pos, T&& value){
        auto new_size=size()+1;
        auto new_cap=capacity();
        if(m_last==m_end){
            new_cap=new_cap*3/2+1;
        }
       auto ptr= allocate(new_cap); ///Allocate memory


       for(int i=0;i!=(pos-m_begin);i++){
               ::new(ptr+i)T{std::move(m_begin[i])};
       }
       ::new(ptr+(pos-m_begin))T{std::move(value)};///Insert value
       for(int i=(pos-m_begin);i<(m_last-m_begin);i++){
           ::new(ptr+i+1)T{std::move(m_begin[i])};
       }


       destroy_obj_all();//Destroy all objects
       ::operator delete[](m_begin);//Deallocate old memory
       m_begin=ptr;
       m_last=ptr+new_size;
       m_end=ptr+new_cap;
       return &m_begin[pos-m_begin];

    }

    iterator insert(const_iterator pos, const T& value){
        auto new_size=size()+1;
        auto new_cap=capacity();
        if(m_last==m_end){
            new_cap=new_cap*3/2+1;
        }
        auto ptr= allocate(new_cap); ///Allocate memory

        for(int i=0;i!=(pos-m_begin);i++){
            ::new(ptr+i)T{m_begin[i]};
        }
        ::new(ptr+(pos-m_begin))T{value};///Insert value
        for(int i=(pos-m_begin);i<(m_last-m_begin);i++){
            ::new(ptr+i+1)T{std::move(m_begin[i])};
        }
        destroy_obj_all();//Destroy all objects
        ::operator delete[](m_begin);//Deallocate old memory
        m_begin=ptr;
        m_last=ptr+new_size;
        m_end=ptr+new_cap;
        return m_begin[pos-m_begin];
    }

    iterator erase( iterator pos ){
        if(pos<m_begin||pos>m_last){
            return m_last;
        }
        else{
           if(pos==m_last){
               m_last--;
               m_last->~T();//Destroy object
           }
           else{
              for(int i=(pos-m_begin);i!=(m_last-m_begin-1);i++){
                  (m_begin+i)->~T();
                  ::new(m_begin+i)T{std::move(m_begin[i+1])};
              }

               m_last--;
               m_last->~T();//Destroy object
           }
           return m_last;
        }
    }
    iterator erase( const_iterator pos ){
        if(pos<m_begin||pos>m_last){
            return m_last;
        }
        else{
            if(pos==m_last){
                m_last--;
                m_last->~T();//Destroy object
            }
            else{
                for(int i=(pos-m_begin);i!=(m_last-m_begin-1);i++){
                    (m_begin+i)->~T();
                    ::new(m_begin+i)T{std::move(m_begin[i+1])};
                }

                m_last--;
                m_last->~T();//Destroy object
            }
            return m_last;
        }
    }
    iterator erase( iterator first, iterator last ){
        if(first<=m_begin && last>m_last ){
            clear();
        }
        else {
            for(int i=0;i!=(last-first);i++){
                erase(first);
            }
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
    ///Function to destroy object
    void destroy_obj_all(){
        if(m_begin== nullptr)
            return;
        ///for(auto obj:this) cannot
        for(auto it=begin();it!=end();it++){
            (*it).~T();
        }
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
