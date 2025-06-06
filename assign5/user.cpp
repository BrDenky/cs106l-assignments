#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}


// 1 Part
std::ostream& operator<<(std::ostream& os, const User& user) {
  os << "User(name=" << user._name << ", friends=[";
  for (size_t i = 0; i < user._size; ++i) {
    os << user._friends[i];
    if (i < user._size - 1) {
      os << ", ";
    }
  }
  os << "])";
  return os;
}

//Destructor
User::~User() {
  delete[] _friends;
}

//Copy constructor
User::User(const User& user) 
  : _name(user._name)
  , _size(user._size)
  , _capacity(user._capacity)
  , _friends(nullptr)
{
  if (user._capacity > 0) {
    _friends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      _friends[i] = user._friends[i];
    }
  }
}

// Copy assignment operator
User& User::operator=(const User& user) {
  if (this != &user) {

    delete[] _friends;

    _name = user._name;
    _size = user._size;
    _capacity = user._capacity;

    if (_capacity > 0) {
      _friends = new std::string[_capacity];
      for (size_t i = 0; i < _size; ++i) {
        _friends[i] = user._friends[i];
      }
    } else {
      _friends = nullptr;
    }
  }
  return *this;
}

// Operator += to add friends symmetrically
User& User::operator+=(User& rhs) {

  this->add_friend(rhs._name);

  rhs.add_friend(this->_name);
  
  return *this;
}

// Operator < to compare users alphabetically
bool User::operator<(const User& rhs) const {
  return _name < rhs._name;
}