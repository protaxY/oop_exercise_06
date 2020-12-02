//Федоров Антон Сергеевич М8О-207Б-19
//вариант 30: фигура - 5-ти угольник, контейнер - динамический массив, аллокатор - список

#include <iostream>
#include <memory>
#include <functional>
#include <list>

template <class T, std::size_t BLOCK_SIZE>
class Allocator
{
private:
    T* buffer;
    std::list<T*> list;
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;

    Allocator() noexcept: list(), buffer(){
        static_assert(BLOCK_SIZE > 0);
    }

    Allocator(const Allocator<T, BLOCK_SIZE> &other): Allocator(){
        buffer = new T[BLOCK_SIZE];
        for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
            buffer[i] = other.buffer[i];
            list.push_back(&buffer[i]);
        }
    }

    ~Allocator(){
        delete[] buffer;
    }

    T* allocate(std::size_t quantity){
        if (buffer == nullptr){
            buffer = new T[BLOCK_SIZE];
            for (int i = 0; i < BLOCK_SIZE; ++i) {
                list.push_back(&buffer[i]);
            }
            std::cout << list.size() << " memory blocks left" << "\n";
        }
        if (quantity > list.size()){
            std::cout << list.size() << " memory blocks left" << "\n";
            throw (std::bad_alloc());
        } else {
            T* ticket = list.front();
            for (int i = 0; i < quantity; ++i){
                list.pop_front();
            }
            std::cout << list.size() << " memory blocks left" << "\n";
            return ticket;
        }
    }

    void deallocate(pointer, size_t) {
        std::cout << "Deallocating\n";
    }

    template <class U>
    struct rebind {
        using other = Allocator<U, BLOCK_SIZE>;
    };
};