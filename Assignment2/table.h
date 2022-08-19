#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table
{
public:
    Table()
    {
    }
    virtual bool update(const std::string& key, const TYPE& value) = 0;
    virtual bool remove(const std::string& key) = 0;
    virtual bool find(const std::string& key, TYPE& value) = 0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table()
    {
    }
};

template <class TYPE>
class SimpleTable :public Table<TYPE>
{

    struct Record
    {
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data)
        {
            key_ = key;          
            data_ = data;        
        }

    };

    Record** records_;  
    int capacity_;     


public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const
    {
        return numRecords() == 0;
    }
    virtual int numRecords() const;
    virtual int capacity() const
    {
        return capacity_;
    }

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const         
{
    int rc = 0; 
    for (int i = 0; records_[i] != nullptr; i++) 
    {
        rc++; 
    }
    return rc; 
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>()        
{
    records_ = new Record * [capacity + 1]; 
    capacity_ = capacity; 
    for (int i = 0; i < capacity_ + 1; i++) 
    {
        records_[i] = nullptr; 
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs)       
{
    records_ = new Record * [rhs.capacity_ + 1];  
    capacity_ = rhs.capacity_;      
    for (int i = 0; i < capacity_ + 1; i++) 
    {
        records_[i] = nullptr;
    }
    for (int i = 0; i < rhs.numRecords(); i++)   
    {
        update(rhs.records_[i]->key_, rhs.records_[i]->data_); 
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs)         
    capacity_ = rhs.capacity_;    
    records_ = rhs.records_;      
    rhs.records_ = nullptr;       
    rhs.capacity_ = 0;             
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const std::string& key, const TYPE& value)                                
{
    int idx = -1;                                                       
    int sz = numRecords();
    bool rc = true; 
    for (int i = 0; i < sz; i++)   
    {
        if (records_[i]->key_ == key)      
        {
            idx = i; 
        }
    }
    if (idx == -1)        
    {
        if (sz < capacity_)       
        {
            records_[numRecords()] = new Record(key, value);
            for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) 
            {
                Record* tmp = records_[i];       
                records_[i] = records_[i - 1];   
                records_[i - 1] = tmp;           
            }
        }
        else
        {
            rc = false;
        }
    }
    else
    {
        records_[idx]->data_ = value;
    }
    return rc;      
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key)    
{
    int idx = -1;       
    for (int i = 0; records_[i] != nullptr; i++)  
    {
        if (records_[i]->key_ == key)    
        {
            idx = i;          
        }
    }
    if (idx != -1)        
    {
        delete records_[idx];    
        int i;
        for (i = idx; i < numRecords() - 1; i++)  
        {
            records_[i] = records_[i + 1];      
        }
       
        records_[i] = nullptr;   
        return true;      
    }
    else
    {
        return false;   
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value)     
{
    int idx = -1;    
    for (int i = 0; i < numRecords(); i++)   
    {
        if (records_[i]->key_ == key)       
        {
            idx = i;          
        }
    }
    if (idx == -1)  
        return false;
    else
    {
        value = records_[idx]->data_; 
        return true; 
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs)       
{
    if (this != &rhs)      
    {
        if (records_)       
        {
            while (numRecords() != 0)     
            {
                remove(records_[0]->key_);
            }
            delete[] records_; 
        }
        records_ = new Record * [rhs.capacity_ + 1]; 
        capacity_ = rhs.capacity_;     
        for (int i = 0; i < capacity_; i++)   
        {
            records_[i] = nullptr; 
        }
        for (int i = 0; i < rhs.numRecords(); i++)  
        {
            update(rhs.records_[i]->key_, rhs.records_[i]->data_); 
        }

    }
    return *this;       
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs)         
{
    if (records_)      
    {
        while (numRecords() != 0)  
        {
            remove(records_[0]->key_);  
        }
        delete[] records_; 
    }
    records_ = rhs.records_; 
    capacity_ = rhs.capacity_;  
    rhs.records_ = nullptr; 
    rhs.capacity_ = 0; 

    return *this;   
}

template <class TYPE>
SimpleTable<TYPE>::~SimpleTable()     
{
    if (records_) 
    {
        int sz = numRecords();
        for (int i = 0; i < sz; i++) 
        {
            remove(records_[0]->key_);
        }
        delete[] records_; 
    }
}

template <class TYPE>
class ChainingTable :public Table<TYPE>
{
    struct Record
    {
        TYPE data_{};
        std::string key_{};
        Record()
        {
        }

        Record(const std::string& key, const TYPE& data)
        {
            key_ = key;
            data_ = data;
        }

        const Record& operator=(const Record& rhs)
        {
            if (this != &rhs)
            {
                key_ = rhs.key_;
                data_ = rhs.data_;
            }
            return *this;
        }

        bool operator==(const Record& other)
        {
            return key_ == other.key_;
        }

        bool operator!=(const Record& other)
        {
            return !(*this == other);
        }

        bool operator<(const Record& other)
        {
            return key_ < other.key_;
        }
    };

    DList<Record>* myList{};
    int capacity_{};
    int numRecs{};
public:
    ChainingTable(int maxExpected);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other)noexcept;
    double loadFactor() const;
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other)noexcept;
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int maxExpected) : Table<TYPE>()         // Constructor. Capacity is the capacity(number of elements for the array) of the table.
{
    myList = new DList<Record>[maxExpected];
    capacity_ = maxExpected;
    numRecs = 0;
    for (int i = 0; i < capacity_; i++)
    {
        myList[i] = DList<Record>();
    }
}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other)        // Copy constructor
{
    myList = new DList<Record>[other.capacity_];
    capacity_ = other.capacity_;
    numRecs = other.numRecs;
    for (int i = 0; i < capacity_; i++)
    {
        myList[i] = other.myList[i];
    }

}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other)noexcept     // Move constructor
{
    myList = other.myList;
    capacity_ = other.capacity_;
    numRecs = other.numRecs;
    other.myList = nullptr;
    other.numRecs = 0;
    other.capacity_ = 0;
}
template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string& key, const TYPE& value)     // If record with matching key already exists, replace value at that key. If no record with that key exists, add it as a new record
{
    size_t hashValue = std::hash<std::string>{}(key);
    int hashIndex = hashValue % capacity_;
    bool toReturn = false;
    Record record = Record(key, value);

    typename DList<Record>::iterator result = myList[hashIndex].search(record);

    if (result != myList[hashIndex].end())
    {
        *result = record;
        toReturn = true;
    }
    else
    {
        myList[hashIndex].push_back(record);
        toReturn = true;
        numRecs++;
    }
    return toReturn;
}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key)        //  If your table contains a record with a matching key, the record (both the key and the value) is removed from the table.
{
    size_t hashValue = std::hash<std::string>{}(key);
    int hashIndex = hashValue % capacity_;
    bool toReturn = true;
    Record record = Record();
    record.key_ = key;


    typename DList<Record>::iterator result = myList[hashIndex].search(record);

    if (result != myList[hashIndex].end())
    {
        myList[hashIndex].erase(result);
        numRecs--;
    }
    else
    {
        toReturn = false;
    }

    return toReturn;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value)         //  If your table contains a record with a matching key, the function returns true, and passes back the value from the record. Else, it returns false.
{
    size_t hashValue = std::hash<std::string>{}(key);
    int hashIndex = hashValue % capacity_;
    bool toReturn = true;
    Record record = Record();
    record.key_ = key;

    typename DList<Record>::iterator result = myList[hashIndex].search(record);
    record = *result;


    if (result != myList[hashIndex].end())
    {
        value = record.data_;
    }
    else
    {
        toReturn = false;
    }

    return toReturn;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other)     // Assignment operator
{

    if (this != &other)
    {
        if (myList)
        {
            delete[] myList;
        }


        myList = new DList<Record>[other.capacity_];
        capacity_ = other.capacity_;
        numRecs = other.numRecs;
        for (int i = 0; i < capacity_; i++)
        {
            myList[i] = other.myList[i];
        }

    }
    return *this;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other)noexcept      // Move operator
{
    if (this != &other)
    {
        if (myList)
        {
            delete[] myList;
        }

        myList = other.myList;
        capacity_ = other.capacity_;
        numRecs = other.numRecs;
        other.myList = nullptr;
        other.capacity_ = 0;
        other.numRecs = 0;
    }
    return *this;
}

template <class TYPE>
ChainingTable<TYPE>::~ChainingTable()       // Destructor
{
    if (myList)
    {
        delete[] myList;
    }
}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const       // Returns true if number of records in the table is 0.
{
    return numRecs == 0;
}

template <class TYPE>
int ChainingTable<TYPE>::numRecords() const     // This function returns the number of records in the table.
{
    return numRecs;
}
template <class TYPE>
int ChainingTable<TYPE>::capacity() const       // This function returns capacity of the table.
{
    return capacity_;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const      // This function returns the load factor of the table. (number of records divided by capacity of table)
{
    return numRecs / capacity_;
}

template <class TYPE>
class LPTable :public Table<TYPE>
{

    struct Record
    {
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data)
        {
            key_ = key;
            data_ = data;
        }

    };

    Record** records_{};
    int capacity_{};
    int numRecs{};

    bool isBetween(int emptyIdx, int currentIdx, int properHashIdx);

public:
    LPTable(int maxExpected);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other)noexcept;
    double loadFactor() const;
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other)noexcept;
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};


template <class TYPE>
LPTable<TYPE>::LPTable(int capacity) : Table<TYPE>()        // Constructor. Capacity is the capacity (number of elements for the array) of the table.
{
    capacity_ = capacity;
    records_ = new Record * [capacity_];
    numRecs = 0;
    for (int i = 0; i < capacity_; i++)
        records_[i] = nullptr;
}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other)      // Copy constructor
{
    records_ = new Record * [other.capacity_];
    capacity_ = other.capacity_;
    numRecs = 0;
    for (int i = 0; i < capacity_; i++)
    {
        records_[i] = nullptr;
    }

    for (int i = 0; i < capacity_; i++)
    {
        if (other.records_[i])
            update(other.records_[i]->key_, other.records_[i]->data_);
    }
}
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other)noexcept       // Move constructor
{
    records_ = other.records_;
    other.records_ = nullptr;
    capacity_ = other.capacity_;
    other.capacity_ = 0;
    numRecs = other.numRecs;
    other.numRecs = 0;
}



template <class TYPE>
bool LPTable<TYPE>::update(const std::string& key, const TYPE& value)  // If record with matching key already exists, replace value at that key. If no record with that key exists, add it as a new record
{                                                                      // The table can only hold capacity - 1 records (must have one open spot minimum).
    size_t hashValue = std::hash<std::string>{}(key);
    int hashIndex = hashValue % capacity_;
    bool recordFound = false, boolReturned = true;
    int idx = -1;
    int i;
    for (i = hashIndex; !recordFound && records_[i]; i = (i + 1) % capacity_)
    {
        if (records_[i]->key_ == key)
        {
            recordFound = true;
            idx = i;
        }
    }

    if (idx == -1)
    {
        if (numRecs < capacity_ - 1)
        {
            records_[i] = new Record(key, value);
            numRecs++;
        }
        else
            boolReturned = false;
    }
    else
    {
        records_[idx]->data_ = value;
    }
    return boolReturned;
}

template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key)      //  If your table contains a record with a matching key, the record (both the key and the value) is removed from the table.
{
    size_t hashValue = std::hash<std::string>{}(key);
    int hashIndex = hashValue % capacity_;
    bool recordFound = false, boolReturned = false;
    int idx = -1;
    int nextIdx = -1;
    for (int i = hashIndex; !recordFound && records_[i]; i = (i + 1) % capacity_)
    {
        if (records_[i]->key_ == key)
        {
            recordFound = true;
            idx = i;
        }
    }

    if (idx != -1)
    {
        records_[idx] = nullptr;
        nextIdx = idx + 1;
        numRecs--;
        while (records_[nextIdx])
        {
            hashValue = std::hash<std::string>{}(records_[nextIdx]->key_);
            hashIndex = hashValue % capacity_;
            if (isBetween(idx, nextIdx, hashIndex))
            {
                records_[idx] = records_[nextIdx];
                records_[nextIdx] = nullptr;
                idx = nextIdx;
            }
            nextIdx = (nextIdx + 1) % capacity_;
        }

        boolReturned = true;

    }

    return boolReturned;
}

template<class TYPE>
bool LPTable<TYPE>::isBetween(int emptyIdx, int currentIdx, int properHashIdx)      // checks to see if indexes are in their correct spots
{
    bool toReturn = false;

    if (emptyIdx >= properHashIdx && emptyIdx < currentIdx)
    {
        toReturn = true;
    }
    if (properHashIdx > currentIdx && emptyIdx >= properHashIdx) // empty >= currentIdx also
    {
        toReturn = true;
    }
    if (properHashIdx > currentIdx && currentIdx >= emptyIdx)
    {
        toReturn = true;
    }
    return toReturn;
}

template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value)       //  If your table contains a record with a matching key, the function returns true, and passes back the value from the record. Else, it returns false.
{
    size_t hashValue = std::hash<std::string>{}(key);
    int hashIndex = hashValue % capacity_;

    bool recordFound = false;


    for (int i = hashIndex; !recordFound && records_[i]; i = (i + 1) % capacity_)
    {

        if (records_[i]->key_ == key)
        {
            value = records_[i]->data_;
            recordFound = true;
        }

    }

    return recordFound;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other)       // Assignment operator
{

    if (this != &other)
    {
        if (records_)
        {
            for (int i = 0; i < capacity_; i++)
            {
                delete records_[i];
            }
            delete[] records_;
        }
        records_ = new Record * [other.capacity_];
        capacity_ = other.capacity_;
        numRecs = 0;

        for (int i = 0; i < capacity_; i++)
        {
            records_[i] = nullptr;
        }

        for (int i = 0; i < capacity_; i++)
        {
            if (other.records_[i])
                update(other.records_[i]->key_, other.records_[i]->data_);
        }
    }
    return *this;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other)noexcept        // Move operator
{

    if (this != &other)
    {

        if (records_)
        {
            for (int i = 0; i < capacity_; i++)
            {
                delete records_[i];
            }
            delete[] records_;
        }

        records_ = other.records_;
        capacity_ = other.capacity_;
        numRecs = other.numRecs;
        other.records_ = nullptr;
        other.capacity_ = 0;
        other.numRecs = 0;

    }
    return *this;

}

template <class TYPE>
LPTable<TYPE>::~LPTable()       // Destructor
{
    if (records_)
    {
        for (int i = 0; i < numRecs; i++)
        {
            delete records_[i];
        }
        delete[] records_;
    }
}

template <class TYPE>
bool LPTable<TYPE>::isEmpty() const         // Returns true if number of records in the table is 0.
{
    return numRecs == 0;
}

template <class TYPE>
int LPTable<TYPE>::numRecords() const       // This function returns the number of records in the table.
{
    return numRecs;
}
template <class TYPE>
int LPTable<TYPE>::capacity() const         // This function returns capacity of the table.
{
    return capacity_;
}
template <class TYPE>
double LPTable<TYPE>::loadFactor() const
{
    return numRecs / capacity_;             // This function returns the load factor of the table. (number of records divided by capacity of table)
}

