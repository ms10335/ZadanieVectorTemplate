#pragma once
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

template <typename Vector>
class VectorIterator {
public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

public:
    VectorIterator& operator++() {
        m_ptr++;
        return *this;
    }
    VectorIterator& operator++(int) {
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }
    VectorIterator& operator--() {
        m_ptr--;
        return *this;
    }
    VectorIterator& operator--(int) {
        VectorIterator iterator = *this;
        --(*this);
        return iterator;
    }
    ReferenceType operator[](int index) {
        return *(m_ptr + index);
    }
    PointerType operator->() {
        return m_ptr;
    }
    ReferenceType operator*() {
        return *m_ptr;
    }
    bool operator==(const VectorIterator& other) const {
        return m_ptr == other.m_ptr;
    }
    bool operator!=(const VectorIterator& other) const {
        return !(*this == other);
    }
public:
    VectorIterator(PointerType ptr)
        : m_ptr(ptr) {}

private:
    PointerType m_ptr;
};

template <typename T>
class Vector {
private:
    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;

    void ReAlloc(size_t newCapacity) {
        //1,allo new block of memory
        //2. copy/move old elemnte into new block
        //3. delete

        //1
        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

        //waht if we want to downsize capacity
        if (newCapacity < m_Size) {
            m_Size = newCapacity;
        }

        //2 copy OR move if can
        for (size_t i = 0; i < m_Size; ++i) {
            new (&newBlock[i]) T(std::move(m_Data[i]));
        }
        //delete old assigment
        for (size_t i = 0; i < m_Size; ++i) {
            m_Data[i].~T();
        }

        //3
        //delete[] m_Data;
        ::operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }

public:
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>;

public:
    Vector() {
        //allocate 2 elemnets
        ReAlloc(2);
    }
    void PushBack(const T& value) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }
        m_Data[m_Size++] = value;
    }

    void PushBack(T&& value) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }
        m_Data[m_Size++] = std::move(value);
    }

    //not crate Obj and then move into vector but instead create in allocated in block of memory
    template <typename... Args>
    T& EmplaceBack(Args&&... args) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }
        // MiFu ??!!
        // m_Data[m_Size] = T(std::forward<Args>(args)...);

        //new placement
        new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }

    size_t Size() const { return m_Size; }

    const T& operator[](size_t index) const {
        if (index >= m_Size) {
            assertm(index >= m_Size, "Given index is out of range");
        }
        return m_Data[index];
    }
    //for modifying value from index
    T& operator[](size_t index) {
        if (index >= m_Size) {
            assertm(index >= m_Size, "Given index is out of range");
        }
        return m_Data[index];
    }
    //nice invoke Destructor.
    void PopBack() {
        if (m_Size > 0) {
            m_Size--;
            m_Data[m_Size].~T();
        }
    }
    void Clear() {
        for (size_t i = 0; i < m_Size; ++i) {
            m_Data[i].~T();
        }
        m_Size = 0;
    }
    Iterator begin() {
        return Iterator(m_Data);
    }

    Iterator end() {
        return Iterator(m_Data + m_Size);
    }
    ~Vector() {
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }
};