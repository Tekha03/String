#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class String {
 public:
  String();

  String(size_t size, char character = '?');

  String(const char* str);

  String(const String& other);

  String& operator=(const String& str);

  void Clear();

  void PushBack(char character);

  void PopBack();

  void Resize(size_t new_size);

  void Resize(size_t new_size, char character);

  void Reserve(size_t new_cap);

  void ShrinkToFit();

  void Swap(String& other);

  char& operator[](size_t index);

  const char& operator[](size_t index) const;

  char& Front();

  const char& Front() const;

  char& Back();

  const char& Back() const;

  char* Data();

  const char* Data() const;

  bool Empty() const;

  size_t Size() const;

  size_t Capacity() const;

  String& operator+=(const String& str);

  String& operator*=(size_t n);

  std::vector<String> Split(const String& delim = " ");

  String Join(const std::vector<String>& strings);

  ~String();

 private:
  char* str_;
  size_t size_;
  size_t capacity_;
};

String operator+(const String& str1, const String& str2);

bool operator==(const String& str1, const String& str2);

bool operator!=(const String& str1, const String& str2);

bool operator<(const String& str, const String& str2);

bool operator<=(const String& str1, const String& str2);

bool operator>(const String& str1, const String& str2);

bool operator>=(const String& str1, const String& str2);

String operator*(const String& str, size_t n);

std::istream& operator>>(std::istream& input, String& str);

std::ostream& operator<<(std::ostream& output, const String& str);

String::String() { size_ = capacity_ = 0; }

String::String(size_t size, char character)
    : str_(new char[size + 1]), size_(size), capacity_(size) {
  memset(str_, character, size);
  str_[size_] = '\0';
}

String::String(const char* str) {
  size_ = strlen(str);
  capacity_ = size_;
  str_ = new char[size_ + 1];
  for (size_t i = 0; i < size_; i++) {
    str_[i] = str[i];
  }
  str_[size_] = '\0';
}

String::String(const String& other) { *this = other; }

String& String::operator=(const String& str) {
  size_ = str.size_;
  capacity_ = str.capacity_;
  delete[] str_;
  str_ = new char[capacity_ + 1];
  if (str.str_ != nullptr) {
    memcpy(str_, str.str_, size_);
  }
  str_[size_] = '\0';
  return *this;
}

void String::Clear() { size_ = 0; }

void String::PushBack(char character) {
  if (size_ >= capacity_) {
    Reserve(2 * size_ + 1);
  }
  str_[size_++] = character;
  str_[size_] = '\0';
}

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  str_[--size_] = '\0';
}

void String::Resize(size_t new_size) {
  if (new_size > capacity_) {
    Reserve(new_size);
  }
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  size_t siz = size_;
  Resize(new_size);
  for (size_t i = size_ - 1; i >= siz; i--) {
    str_[i] = character;
  }
  str_[size_] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (new_cap <= capacity_) {
    return;
  }
  char* copy = new char[new_cap + 1];
  if (str_ != nullptr) {
    memcpy(copy, str_, size_);
  }
  copy[size_] = '\0';
  delete[] str_;
  str_ = copy;
  capacity_ = new_cap;
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    char* copy = new char[size_ + 1];
    memcpy(copy, str_, size_);
    copy[size_] = '\0';
    delete[] str_;
    str_ = copy;
    capacity_ = size_;
  }
}

void String::Swap(String& other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

char& String::operator[](size_t index) { return str_[index]; }

const char& String::operator[](size_t index) const { return str_[index]; }

char& String::Front() { return str_[0]; }

const char& String::Front() const { return str_[0]; }

char& String::Back() { return str_[size_ - 1]; }

const char& String::Back() const { return str_[size_ - 1]; }

char* String::Data() { return &str_[0]; }

const char* String::Data() const { return &str_[0]; }

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

String& String::operator+=(const String& str) {
  String copy = str;
  Reserve(size_ + copy.Size());
  memcpy(str_ + size_, copy.str_, copy.Size());
  size_ += copy.Size();
  str_[size_] = '\0';
  return *this;
}

String operator+(const String& str1, const String& str2) {
  String copy("");
  copy += str1;
  copy += str2;
  return copy;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> result;
  String curr("");
  for (size_t i = 0; i < size_; i++) {
    if (i + delim.Size() <= size_) {
      String copy(delim.Size());
      for (size_t j = 0; j < delim.Size(); j++) {
        copy.str_[j] = str_[i + j];
      }
      if (copy == delim) {
        i += delim.Size() - 1;
        curr.str_[curr.size_] = '\0';
        result.push_back(curr);
        curr.Clear();
        continue;
      }
    }
    curr.PushBack(str_[i]);
  }
  curr.str_[curr.size_] = '\0';
  result.push_back(curr);
  return result;
}

String String::Join(const std::vector<String>& strings) {
  String result("");
  for (size_t i = 0; i < strings.size(); i++) {
    for (size_t j = 0; j < strings[i].Size(); j++) {
      result.PushBack(strings[i][j]);
    }
    if (i < strings.size() - 1) {
      result += str_;
    }
  }
  return result;
}

String::~String() { delete[] str_; }

bool operator==(const String& str1, const String& str2) {
  if (str1.Size() != str2.Size()) {
    return false;
  }
  for (size_t i = 0; i < str1.Size(); i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& str1, const String& str2) {
  return !(str1 == str2);
}

bool operator<(const String& str1, const String& str2) {
  size_t mini = str1.Size();
  if (str2.Size() < mini) {
    mini = str2.Size();
  }
  for (size_t i = 0; i < mini; i++) {
    if (str1[i] < str2[i]) {
      return true;
    }
    if (str1[i] > str2[i]) {
      return false;
    }
  }
  return str1.Size() < str2.Size();
}

bool operator<=(const String& str1, const String& str2) {
  return str1 == str2 ? true : str1 < str2;
}

bool operator>(const String& str1, const String& str2) {
  return !(str1 <= str2);
}

bool operator>=(const String& str1, const String& str2) {
  return str1 == str2 ? true : str1 > str2;
}

String operator*(const String& str, size_t n) {
  String result(str.Size() * n);
  int ind = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < str.Size(); j++) {
      result[ind++] = str[j];
    }
  }
  return result;
}

String& String::operator*=(size_t numb) {
  String copy = *this;
  copy = copy * numb;
  Swap(copy);
  return *this;
}

std::istream& operator>>(std::istream& input, String& str) {
  char character;
  str.Clear();
  while (input >> character) {
    str.PushBack(character);
  }
  return input;
}

std::ostream& operator<<(std::ostream& output, const String& str) {
  for (size_t i = 0; i < str.Size(); i++) {
    output << str[i];
  }
  return output;
}
