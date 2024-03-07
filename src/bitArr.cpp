#include "../include/bitArr.h"
#include <stdlib.h>
#include <climits> 

#define BITS_IN_LONG (sizeof(long) * 8)

BitArray::BitArray(int num_bits, unsigned long value) {
    this->num_bits = num_bits;
    max_bits = num_bits;

    // Вычисляем необходимый размер массива в long-типах (8 битов в байте)
    int num_longs = num_bits / BITS_IN_LONG + 1;

    // Выделяем память для массива
    this->data = new unsigned long[num_longs];

    for (int i = 0; i < num_longs; i++) {
        if (i == 0) data[0] = value;
        else data[i] = 0;
    }
}

BitArray::BitArray(const BitArray &b) {
    *this = b;
}

BitArray::~BitArray() {
    num_bits = 0;
    delete[] data;
    data = NULL;
}

void BitArray::resize(int num_bits, bool value) {
    data = (unsigned long *) realloc(data, num_bits * sizeof(unsigned long));

    if (this->num_bits <= num_bits) {
        max_bits == num_bits ? max_bits *= 2 : max_bits = num_bits;
        data = (unsigned long *) realloc(data, max_bits * sizeof(unsigned long));
        for (int i = this->num_bits; i < num_bits; i++) {
            set(i, value);
        }
        this->num_bits = num_bits;
    } else {
        max_bits = num_bits;
        this->num_bits = num_bits;
        data = (unsigned long *) realloc(data, num_bits * sizeof(unsigned long));
    }

}

bool BitArray::operator[](int i) const {
    int byte = data[i / BITS_IN_LONG], ind = i % BITS_IN_LONG;
    return (byte & (1UL << ind)) != 0;
}

std::string BitArray::to_string() const {
    std::string str = "";
    for (int i = 0; i < num_bits; i++) str.push_back(operator[](i) + '0');
    return str;
}

int BitArray::size() const {
    return num_bits;
}

bool BitArray::empty() const {
    return num_bits == 0 ? true : false;
}

void BitArray::clear() {
    resize(0);
}

//Устанавливает бит с индексом n в значение val.
BitArray &BitArray::set(int n, bool val) {
    reset(n);
    data[n / BITS_IN_LONG] |= val << n % BITS_IN_LONG;
    return *this;
}

//Заполняет массив истиной.
BitArray &BitArray::set() {
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) data[i] = ULONG_MAX;
    return *this;
}

void BitArray::push_back(bool bit) {
    if (num_bits == max_bits) resize(num_bits);
    set(num_bits, bit);
    num_bits++;
}

//Устанавливает бит с индексом n в значение false.
BitArray &BitArray::reset(int n) {
    data[n / BITS_IN_LONG] &= (ULONG_MAX ^ (1UL << n % BITS_IN_LONG));
    return *this;
}

//Заполняет массив ложью.
BitArray &BitArray::reset() {
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) data[i] = 0;
    return *this;
}

//true, если массив содержит истинный бит.
bool BitArray::any() const {
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) if (data[i] > 0) return true;
    return false;
}

//true, если все биты массива ложны.
bool BitArray::none() const {
    return !any();
}

//Битовая инверсия
BitArray BitArray::operator~() const {
    BitArray res = *this;
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) res.data[i] = ~data[i];
    return res;
}

//Подсчитывает количество единичных бит.
int BitArray::count() const {
    int c = 0;
    for (int i = 0; i < num_bits; i++) if (operator[](i)) c++;
    return c;
}

BitArray &BitArray::operator=(const BitArray &b) {
    this->num_bits = b.num_bits;
    this->max_bits = b.max_bits;
    resize(num_bits);
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) data[i] = b.data[i];
    return *this;
}

//Битовые операции над массивами.
//Работают только на массивах одинакового размера.
//Обоснование реакции на параметр неверного размера входит в задачу.
BitArray &BitArray::operator&=(const BitArray &b) {
    if (num_bits != b.num_bits) throw std::runtime_error("Different size of BitArrays");
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) data[i] &= b.data[i];
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if (num_bits != b.num_bits) throw std::runtime_error("Different size of BitArrays");
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) data[i] |= b.data[i];
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if (num_bits != b.num_bits) throw std::runtime_error("Different size of BitArrays");
    for (int i = 0; i < num_bits / BITS_IN_LONG + 1; i++) data[i] ^= b.data[i];
    return *this;
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.num_bits != b.num_bits) throw std::runtime_error("Different size of BitArrays");
    for (int i = 0; i < a.num_bits / BITS_IN_LONG + 1; i++) {
        if (a.data[i] != b.data[i]) return false;
    }
    return true;
}

bool operator!=(const BitArray &a, const BitArray &b) {
    if (a.num_bits != b.num_bits) throw std::runtime_error("Different size of BitArrays");
    return !operator==(a, b);
}

BitArray operator&(const BitArray &b1, const BitArray &b2) {
    if (b1.num_bits != b2.num_bits) throw std::runtime_error("Different size of BitArrays");
    BitArray res(b1);
    for (int i = 0; i < b1.num_bits / BITS_IN_LONG + 1; i++) res.data[i] = b1.data[i] & b2.data[i];
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    if (b1.num_bits != b2.num_bits) throw std::runtime_error("Different size of BitArrays");
    BitArray res(b1);
    for (int i = 0; i < b1.num_bits / BITS_IN_LONG + 1; i++) res.data[i] = b1.data[i] | b2.data[i];
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    if (b1.num_bits != b2.num_bits) throw std::runtime_error("Different size of BitArrays");
    BitArray res(b1);
    for (int i = 0; i < b1.num_bits / BITS_IN_LONG + 1; i++) res.data[i] = b1.data[i] ^ b2.data[i];
}

void BitArray::swap(BitArray &b){           //works for BitArray with same sizes
    BitArray temp = *this;
    *this = b;
    b = temp;
}

BitArray& BitArray::operator<<=(int n){
    int intLen = this->num_bits / BITS_IN_LONG + 1;
    for(int i = 0; i < intLen; i++){
        if(i == 0) data[i] = (data[i] >> BITS_IN_LONG - n % BITS_IN_LONG);
        else{
            if (i - n / BITS_IN_LONG >= 0) data[i - n / BITS_IN_LONG] += (data[i] << (n % BITS_IN_LONG));
            data[i] = (data[i] >> BITS_IN_LONG - n % BITS_IN_LONG);
        }
    }
    return *this;
}
BitArray& BitArray::operator>>=(int n){
    int intLen = this->num_bits / BITS_IN_LONG + 1;
    for(int i = intLen - 1; i >= 0; i--){
        if(i == intLen - 1) data[i] = (data[i] << BITS_IN_LONG - n % BITS_IN_LONG);
        else{
            if (i + n / BITS_IN_LONG < intLen) data[i + n / BITS_IN_LONG] += (data[i] >> (n % BITS_IN_LONG));
            data[i] = (data[i] << BITS_IN_LONG - n % BITS_IN_LONG);
        }
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const{
    BitArray resBitArr(*this);
    int intLen = this->num_bits / BITS_IN_LONG + 1;
    for(int i = 0; i < intLen; i++){
        if(i == 0) resBitArr.data[i] = (resBitArr.data[i] >> BITS_IN_LONG - n % BITS_IN_LONG);
        else{
            if (i - n / BITS_IN_LONG >= 0) resBitArr.data[i - n / BITS_IN_LONG] += (resBitArr.data[i] << (n % BITS_IN_LONG));
            resBitArr.data[i] = (resBitArr.data[i] >> BITS_IN_LONG - n % BITS_IN_LONG);
        }
    }
    return resBitArr;
}

BitArray BitArray::operator>>(int n) const{
    BitArray resBitArr(*this);
    int intLen = this->num_bits / BITS_IN_LONG + 1;
    for(int i = intLen - 1; i >= 0; i--){
        if(i == intLen - 1) resBitArr.data[i] = (resBitArr.data[i] << BITS_IN_LONG - n % BITS_IN_LONG);
        else{
            if (i + n / BITS_IN_LONG < intLen) resBitArr.data[i + n / BITS_IN_LONG] += (resBitArr.data[i] >> (n % BITS_IN_LONG));
            resBitArr.data[i] = (resBitArr.data[i] << BITS_IN_LONG - n % BITS_IN_LONG);
        }
    }
    return resBitArr;
}
