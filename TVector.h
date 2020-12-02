//Федоров Антон Сергеевич М8О-207Б-19
//вариант 30: фигура - 5-ти угольник, контейнер - динамический массив, аллокатор - список

#include <memory>
#include <algorithm>
#include <iostream>

template <class T, class ALLOCATOR>
class TVector{
private:
    unsigned long long TVectorSize;
    unsigned long long TVectorCapacity;
    std::shared_ptr<T[]> Data;
    using allocator_type = typename ALLOCATOR::template rebind<T>::other;
    static allocator_type& get_allocator() {
        static allocator_type allocator;
        return allocator;
    }
    struct deleter{
        void operator() (void* ptr){
            get_allocator().deallocate((T*)ptr, 1);
        }
    };
    deleter del;
public:
    TVector();
    unsigned long long Size();
    void PushBack(const T elem);
    void PopBack();
    T& operator[] (long long iterator);
    class ForwardIterator{
    private:
        std::shared_ptr<T[]> Iterator;
        unsigned long long index;
        unsigned long long Size;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T ;
        using pointer = T*;
        using reference = T&;
        ForwardIterator(): Iterator(nullptr) {
            index = 0;
        };
        ForwardIterator(const std::shared_ptr<T[]> &shPtr, unsigned long long ind, unsigned long long Size): Iterator(shPtr), Size(Size){
            index = ind;
        };
        T& operator* (){
            return Iterator[index];
        }
        ForwardIterator& operator++(){
            if (index + 1 > Size)
                throw std::out_of_range("Iterator cannot be incremented past the end of range.");
            ++index;
            return *this;
        }
        bool operator != (const ForwardIterator & rhs) {
            return this->index != rhs.index;
        }
        friend class TVector<T,ALLOCATOR>;
    };

    ForwardIterator begin(){
        return ForwardIterator(Data,0,TVectorSize);
    }
    ForwardIterator end(){
        return ForwardIterator(Data,TVectorSize,TVectorSize);
    }
    void Insert(ForwardIterator Iterator, T elem);
    void Erase(ForwardIterator Iterator);
};

template <class T, class ALLOCATOR>
TVector<T,ALLOCATOR>::TVector(){
    TVectorSize = 0;
    TVectorCapacity = 0;
    Data = nullptr;
}
template <class T, class ALLOCATOR>
unsigned long long TVector<T, ALLOCATOR>::Size(){
    return TVectorSize;
}
template <class T, class ALLOCATOR>
void TVector<T, ALLOCATOR>::PushBack(const T elem){
    if (TVectorCapacity == 0){
        TVectorCapacity = 1;
        TVectorSize = 0;
        Data = std::move(std::unique_ptr<T[], deleter>{new(this -> get_allocator().allocate(TVectorCapacity)) T[TVectorCapacity]});
    }
    else if (TVectorCapacity == TVectorSize){
        TVectorCapacity *= 2;
        std::shared_ptr<T[]> newData{new(this -> get_allocator().allocate(TVectorCapacity)) T[TVectorCapacity], deleter()};
        for (unsigned long long i = 0; i < TVectorSize; ++i){
            newData[i] = Data[i];
        }
        Data = newData;
    }
    TVectorSize += 1;
    Data[TVectorSize - 1] = elem;
}
template <class T, class ALLOCATOR>
void TVector<T, ALLOCATOR>::PopBack() {
    if (TVectorSize > 0){
        --TVectorSize;
        if (TVectorSize < TVectorCapacity / 2){
            TVectorCapacity /= 2;
            std::shared_ptr<T[]> newData(new(this -> get_allocator().allocate(TVectorCapacity)) T[TVectorCapacity], deleter());
            for (unsigned long long i = 0; i < TVectorSize; ++i){
                newData[i] = Data[i];
            }
            Data = newData;
        }
    }
}
template <class T, class ALLOCATOR>
void TVector<T, ALLOCATOR>::Insert(ForwardIterator Iterator, T elem){
    unsigned long long pos = Iterator.index;
    if (pos > TVectorSize){
        std::cout << "incorrect position to insrt\n";
        return;
    }
    PushBack(T());
    for (unsigned long long i = TVectorSize - 1; i > pos; --i){
        Data[i] = Data.get()[i-1];
    }
    Data[pos] = elem;
}
template <class T, class ALLOCATOR>
void TVector<T, ALLOCATOR>::Erase(ForwardIterator Iterator){
    unsigned long long pos = Iterator.index;
    if (pos >= TVectorSize){
        throw std::out_of_range("Erase position out of range.");
    }
    for (unsigned long long i = pos; i < TVectorSize - 1; ++i){
        Data[i] = Data[i+1];
    }
    PopBack();
}
template <class T, class ALLOCATOR>
T& TVector<T, ALLOCATOR>::operator[] (const long long iterator){
    return Data[iterator];
}