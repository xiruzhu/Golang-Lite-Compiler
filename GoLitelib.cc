#include <vector>
#include <memory>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <iostream>

#define GoLiteArray_Error_SliceIndex "slice bounds out of range"
#define GoLiteArray_Error_ArrayIndex "index out of range"

template <typename sliceType, size_t defaultSliceSize = 1L> class GoLiteSlice{
public:
    GoLiteSlice () : mem(new std::vector<std::unique_ptr<sliceType>>(defaultSliceSize)), offset(0L), reachable(0L), capacity(defaultSliceSize) {
        for (typename std::vector<std::unique_ptr<sliceType>>::iterator iter = (*mem).begin(); iter != (*mem).end(); iter++) {
            *iter = std::move(std::unique_ptr<sliceType>(new sliceType()));
        }
    }
    GoLiteSlice (const GoLiteSlice<sliceType>& _cpy) {
        this->mem       = _cpy.mem;
        this->offset    = _cpy.offset;
        this->reachable = _cpy.reachable;
        this->capacity  = _cpy.capacity;
    }
    friend std::ostream& operator<< (std::ostream& _stream, const GoLiteSlice<sliceType>& _obj) {
        _stream << '[';
        for (size_t iter = _obj.offset; iter < _obj.reachable; iter++) {
            _stream<<*(_obj.mem->at(iter));
            if (iter + 1 != _obj.reachable) _stream<<','<<' ';
        }
        _stream << ']';
        return _stream;
    }
    std::unique_ptr<sliceType>& operator[] (size_t _index) {
        if (_index + offset >= reachable) throw std::runtime_error(GoLiteArray_Error_ArrayIndex);
        return this->mem->at(_index + offset);
    }
    friend GoLiteSlice<sliceType> append(GoLiteSlice<sliceType> _target, std::unique_ptr<sliceType> _obj) {
        GoLiteSlice<sliceType> ret = _target;
        if (ret.reachable < ret.capacity) {   // Trivial Case
            ret.mem->at(_target.reachable) = std::move(_obj);
            ret.reachable++;
        } else {                              // copy and append
            size_t newSize = 2*(ret.capacity - ret.offset);
            std::shared_ptr<std::vector<std::unique_ptr<sliceType>>> newMem (new std::vector<std::unique_ptr<sliceType>>(newSize));
            for (size_t iter = 0L; iter < newSize; iter++) {
                newMem->at(iter) = std::move(std::unique_ptr<sliceType>(new sliceType()));
            }
            for (size_t iter = ret.offset; iter < ret.reachable; iter++) {
                sliceType cpy = *(ret.mem->at(iter));
                newMem->at(iter - ret.offset) = std::move(std::unique_ptr<sliceType>(new sliceType(cpy)));
            }
            newMem->at(ret.reachable - ret.offset) = std::move(_obj);
            ret.mem = newMem;
            ret.reachable = ret.reachable+1 - ret.offset;
            ret.offset = 0L;
            ret.capacity = newSize;
        }
        
        return ret;
    }
    GoLiteSlice<sliceType> slice(size_t _begin, size_t _end) {
        if (_begin + offset > reachable)       throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_end   + offset > reachable)       throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_begin > _end)                     throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        GoLiteSlice<sliceType> ret = *this;
        ret.offset    = _begin + offset;
        ret.reachable = _end + offset;
        ret.capacity  = capacity;
        return ret;
    }
    GoLiteSlice<sliceType> slice(size_t _begin, size_t _end, size_t _capacity) {
        if (_begin + offset > reachable)       throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_end   + offset > reachable)       throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_begin > _end)                     throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_capacity + offset > capacity)     throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_end > _capacity)                  throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        GoLiteSlice<sliceType> ret = *this;
        ret.offset    = _begin + offset;
        ret.reachable = _end + offset;
        ret.capacity  = _capacity + offset;
        return ret;
    }
    constexpr size_t length() const {return this->reachable - this->offset;}
    
    std::shared_ptr<std::vector<std::unique_ptr<sliceType>>> mem;
    /*
     *   Example for ([16]int)[4 : 9 : 16]
     *   |<- mem     |<- offset              |<- reachable               |<-capacity
     *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14| 15| 16|
     *   +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     */
    size_t offset;
    size_t reachable;
    size_t capacity;
};
template <typename arrayType, size_t arrarySize> class GoLiteArray{
public:
    GoLiteArray () : mem(new std::vector<std::unique_ptr<arrayType>>(arrarySize)), capacity(arrarySize) {
        for (typename std::vector<std::unique_ptr<arrayType>>::iterator iter = (*mem).begin(); iter != (*mem).end(); iter++) {
            *iter = std::move(std::unique_ptr<arrayType>(new arrayType()));
        }
    }
    GoLiteArray (const GoLiteArray<arrayType, arrarySize>& _obj) : GoLiteArray() {
        for (size_t iter = 0; iter < capacity; iter++) {
            arrayType temp = *(_obj.mem->at(iter));
            this->mem->at(iter) = std::unique_ptr<arrayType>(new arrayType(temp));
        }
    }
    friend std::ostream& operator<< (std::ostream& _stream, const GoLiteArray<arrayType, arrarySize>& _obj) {
        _stream << '[';
        std::vector<std::unique_ptr<arrayType>>& arr = *(_obj.mem);
        for (typename std::vector<std::unique_ptr<arrayType>>::iterator iter = arr.begin(); iter != arr.end(); iter++) {
            _stream << **iter;
            if ((iter+1) != arr.end()) _stream << ',' << ' ';
        }
        _stream << ']';
        return _stream;
    }
    void operator= (const GoLiteArray<arrayType, arrarySize>& _obj) {
        for (size_t iter = 0; iter < capacity; iter++) {
            arrayType temp = *(_obj.mem->at(iter));
            this->mem->at(iter) = std::unique_ptr<arrayType>(new arrayType(temp));
        }
    }
    std::unique_ptr<arrayType>& operator[] (size_t _index) {
        if (_index >= capacity) throw std::runtime_error(GoLiteArray_Error_ArrayIndex);
        return this->mem->at(_index);
    }
    GoLiteSlice<arrayType> slice(size_t _begin, size_t _end) {
        if (_begin >  capacity) throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_end   >  capacity) throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_begin >  _end)     throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        GoLiteSlice<arrayType> ret;
        ret.mem       = mem;
        ret.offset    = _begin;
        ret.reachable = _end;
        ret.capacity  = capacity;
        return ret;
    }
    GoLiteSlice<arrayType> slice(size_t _begin, size_t _end, size_t _capacity) {
        if (_begin > capacity)     throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_end   > capacity)     throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_begin >  _end)        throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_capacity > capacity)  throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        if (_end > capacity)       throw std::runtime_error(GoLiteArray_Error_SliceIndex);
        GoLiteSlice<arrayType> ret;
        ret.mem       = mem;
        ret.offset    = _begin;
        ret.reachable = _end;
        ret.capacity  = _capacity;
        return ret;
    }
    constexpr size_t length() const {return this->capacity;}
private:
    std::shared_ptr<std::vector<std::unique_ptr<arrayType>>> mem;
    size_t capacity = arrarySize;
};
