#ifndef Wektor_H
#define Wektor_H

template<typename T>
class Wektor
{
private:
    int capacity;
    int current;
    std::shared_ptr<T>* ptr;

public:
    Wektor() : capacity(10), current(0), ptr(new std::shared_ptr<T>[10]) {}

    Wektor(int a) : capacity(a), current(0), ptr(new std::shared_ptr<T>[a]) {}

    Wektor(const Wektor& A) : capacity(A.capacity), current(A.current), ptr(new std::shared_ptr<T>[A.capacity]) {
        for (int i = 0; i < capacity; i++) {
            ptr[i] = A.ptr[i];
        }
    }

    Wektor(Wektor&& oldvector) : capacity(oldvector.capacity), current(oldvector.current), ptr(oldvector.ptr) {
        oldvector.capacity = 0;
        oldvector.current = 0;
        oldvector.ptr = nullptr;
    }

    ~Wektor() {
        delete[] ptr;
    }

    T& operator[](const int pozycja) { return *ptr[pozycja]; };

    bool operator!=(const Wektor& other) { return ptr != other.ptr; }

    bool operator==(const Wektor& other) { return ptr == other.ptr; }

    Wektor& operator=(Wektor& other) {
        if (this != &other) {
            delete[] ptr;
            capacity = other.capacity;
            current = other.current;
            ptr = new std::shared_ptr<T>[capacity];
            for (int i = 0; i < current; i++) {
                ptr[i] = other.ptr[i];
            }
        }
        return *this;
    }

    void push_back(T arg) {
        if (current == capacity) {
            capacity *= 2;
            std::shared_ptr<T>* temporary = new std::shared_ptr<T>[capacity];
            for (int i = 0; i < current; i++) {
                temporary[i] = ptr[i];
            }
            delete[] ptr;
            ptr = temporary;
        }
        ptr[current++] = std::make_shared<T>(arg);
    }

    void assign(int position, T arg) {
        if (position > capacity) {
            capacity = position + 1;
            std::shared_ptr<T>* temporary = new std::shared_ptr<T>[capacity];
            for (int i = 0; i < current; i++) {
                temporary[i] = ptr[i];
            }
            delete[] ptr;
            ptr = temporary;
        }
        ptr[position] = std::make_shared<T>(arg);
        if (position >= current) {
            current = position + 1;
        }
    }

    T at(int position) {
        if (position >= 0 && position < current) {
            return *ptr[position];
        }
        // Rzucanie wyj¹tku lub zwracanie wartoœci domyœlnej by³oby lepsze
        return -1;
    }

    class Iterator : public Wektor
    {
        friend class Wektor;
    private:
        std::shared_ptr<T>* adres;

    public:
        Iterator() : adres(nullptr) {};
        Iterator(std::shared_ptr<T>* adres) : adres(adres) {};
        ~Iterator() {};
        bool operator!=(Iterator other) { return adres != other.adres; }
        bool operator==(Iterator other) { return adres == other.adres; }
        Iterator& operator++()
        {
            adres++;
            return *this;
        }

        Iterator& operator++(int)
        {
            Iterator buf(*this);
            adres++;
            return buf;
        }

        T operator*() { return static_cast<T>(*adres->get()); }
    };

    Iterator begin()
    {
        return Iterator(ptr);
    }

    Iterator end()
    {
        if (current == 0)
            return Iterator(ptr);
        return Iterator(ptr + current);
    }

    int getcapacity() { return capacity; };
    int getcurrent() { return current; };
    std::shared_ptr<T> getptr() { return ptr; };
};
#endif