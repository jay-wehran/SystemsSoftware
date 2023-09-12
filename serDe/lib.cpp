#include <vector>
#include <stdio.h>
#include <iostream>
#include "pack109.hpp"

// BOOLEANS
vec pack109::serialize(bool item)
{
    vec bytes; // declaring a vector
    if (item == true)
    {                                  // if whatever item passed through is true
        bytes.push_back(PACK109_TRUE); // add the true tag to the vector (bytes[0])
    }
    else
    {                                   // if the item is false
        bytes.push_back(PACK109_FALSE); // add the false tag to the vector (bytes[0])
    }
    return bytes; // returning the vector
}

bool pack109::deserialize_bool(vec bytes)
{
    if (bytes.size() < 1)
    { // if the vector is empty, throwing an error
        throw;
    }

    if (bytes[0] == PACK109_TRUE)
    { // if the first element of the vector is the true tag, return true
        return true;
    }
    else if (bytes[0] == PACK109_FALSE)
    { // if the first element of the vector is the false tag, return false
        return false;
    }
    else
    {
        throw;
    }
}

// INTEGERS
//!DONE
vec pack109::serialize(u8 item)
{
    vec bytes;                   // initializing a vector
    bytes.push_back(PACK109_U8); // making bytes[0] the tag
    bytes.push_back(item);       // making bytes[1] the u8 int
    return bytes;
}

u8 pack109::deserialize_u8(vec bytes)
{
    if (bytes.size() < 2)
    { // if the vector doesn't have the tag and value, throw an error
        throw;
    }
    if (bytes[0] == PACK109_U8)
    { // if the tag matches, return the value in bytes[1] (the u8 int)
        return bytes[1];
    }
    else
    {
        throw;
    }
}

vec pack109::serialize(u32 item)
{
    vec bytes;                    // declaring a vector bytes
    bytes.push_back(PACK109_U32); // adding the tag to bytes[0]

    // Loop to break down the 32-bit integer into individual bytes and add to the vector
    for (int i = 3; i >= 0; i--)
    {
        bytes.push_back(static_cast<u8>((item >> (i * 8)) & 0xFF));
    }

    return bytes;
}

u32 pack109::deserialize_u32(vec bytes)
{
    if (bytes.size() < 5)
    {
        throw;
    }

    if (bytes[0] != PACK109_U32)
    {
        throw;
    }

    u32 result = 0;

    // Reconstruction
    for (int i = 1; i <= 4; i++)
    {
        result = (result << 8) | static_cast<u32>(bytes[i]);
    }

    return result;
}

vec pack109::serialize(u64 item)
{
    vec bytes;
    bytes.push_back(PACK109_U64);

    // Break down the 64-bit integer 
    for (int i = 7; i >= 0; i--)
    {
        bytes.push_back(static_cast<u8>((item >> (i * 8)) & 0xFF));
    }

    return bytes;
}

u64 pack109::deserialize_u64(vec bytes)
{
    if (bytes.size() < 9)
    { 
        throw;
    }

    if (bytes[0] != PACK109_U64)
    {
        throw;
    }

    u64 result = 0;

    // Reconstruct 
    for (int i = 1; i <= 8; i++)
    {
        result = (result << 8) | static_cast<u64>(bytes[i]);
    }

    return result;
}

vec pack109::serialize(i8 item)
{
    vec bytes;
    bytes.push_back(PACK109_I8);            
    bytes.push_back(static_cast<u8>(item)); // Convert to u8 and add to bytes
    return bytes;
}
i8 pack109::deserialize_i8(vec bytes)
{
    if (bytes.size() < 2)
    { 
        throw;
    }

    if (bytes[0] != PACK109_I8)
    {
        throw;
    }

    return static_cast<i8>(bytes[1]);
}

vec pack109::serialize(i32 item)
{
    vec bytes;
    bytes.push_back(PACK109_I32); // Add the tag for i32

  
    for (int i = 3; i >= 0; i--)
    {
        bytes.push_back(static_cast<u8>((item >> (i * 8)) & 0xFF));
    }

    return bytes;
}
i32 pack109::deserialize_i32(vec bytes)
{
    if (bytes.size() < 5)
    { 
        throw;
    }

    if (bytes[0] != PACK109_I32)
    {
        throw;
    }

    i32 result = 0;

    // Reconstruction
    for (int i = 1; i <= 4; i++)
    {
        result = (result << 8) | static_cast<i32>(bytes[i]);
    }

    return result;
}

vec pack109::serialize(i64 item)
{
    vec bytes;
    bytes.push_back(PACK109_I64); 

    
    for (int i = 7; i >= 0; i--)
    {
        bytes.push_back(static_cast<u8>((item >> (i * 8)) & 0xFF));
    }

    return bytes;
}
i64 pack109::deserialize_i64(vec bytes)
{
    if (bytes.size() < 9)
    { 
        throw;
    }

    if (bytes[0] != PACK109_I64)
    {
        throw;
    }

    i64 result = 0;

    // Reconstruction
    for (int i = 1; i <= 8; i++)
    {
        result = (result << 8) | static_cast<i64>(bytes[i]);
    }

    return result;
}


// FLOATS
vec pack109::serialize(f32 item) {
    vec bytes(sizeof(f32));
  memcpy(&bytes[0], &item, sizeof(f32));
  return bytes;
}
f32 pack109::deserialize_f32(vec bytes) {
    if (bytes.size() < sizeof(f32)) {
    throw;
  }

  f32 result;
  memcpy(&result, &bytes[0], sizeof(f32));
  return result;
}

vec pack109::serialize(f64 item) {
    vec bytes(sizeof(f64));
  memcpy(&bytes[0], &item, sizeof(f64));
  return bytes;
}
f64 pack109::deserialize_f64(vec bytes) {
    if (bytes.size() < sizeof(f64)) {
    throw;
  }

  f64 result;
  memcpy(&result, &bytes[0], sizeof(f64));
  return result;
}


// STRINGS
vec pack109::serialize(string item) {
    vec bytes;

  // Convert the string length to bytes and add to the vector
  if (sizeof(item[0]) == 1) {
    uint16_t length = item.length();
    u8 first8 = static_cast<u8>((length >> 8) & 0xFF);
    u8 second8 = static_cast<u8>((length >> 0) & 0xFF);

    bytes.push_back(PACK109_S16);
    bytes.push_back(static_cast<uint8_t>(first8));
    bytes.push_back(static_cast<uint8_t>(second8));

  } else {
    bytes.push_back(PACK109_S8);
    bytes.push_back(static_cast<uint8_t>(item.size()));
  }
  
  for (char c : item) {
    bytes.push_back(static_cast<u8>(c));
  }

  return bytes;
}

string pack109::deserialize_string(vec bytes) {
    if (bytes.size() < 3) {  // Ensure there are enough bytes for string
    throw;
  }
  unsigned short length = (static_cast<unsigned short>(bytes[1]) << 8) | static_cast<unsigned short>(bytes[2]);
  string result;
  for (int i = 3; i < 3 + length; i++) {
    result += static_cast<char>(bytes[i]);
  }

  return result;
}


// ARRAYS
vec pack109::serialize(std::vector<u8> item) {
    vec bytes;


  u8 length = static_cast<u8>(item.size());
  bytes.push_back(PACK109_A8);
  bytes.push_back(length);


  for (u8 val : item) {
    bytes.push_back(val);
  }

  return bytes;
}
vec pack109::serialize(std::vector<u64> item) {
  vec bytes;

  u8 length = static_cast<u8>(item.size());
  bytes.push_back(PACK109_A8);
  bytes.push_back(length);

  for (u64 val : item) {
    for (int i = 7; i >= 0; --i) {
      bytes.push_back(static_cast<u8>((val >> (i * 8)) & 0xFF));
    }
  }

  return bytes;
}
vec pack109::serialize(std::vector<f64> item) {
  vec bytes;

  u8 length = static_cast<u8>(item.size());
  bytes.push_back(PACK109_A8);
  bytes.push_back(length);

  for (f64 val : item) {
    u64 bits = *reinterpret_cast<u64*>(&val);
    for (int i = 7; i >= 0; --i) {
      bytes.push_back(static_cast<u8>((bits >> (i * 8)) & 0xFF));
    }
  }

  return bytes;
}
vec pack109::serialize(std::vector<string> item) {
    vec bytes;

  u8 length = static_cast<u8>(item.size());
  bytes.push_back(PACK109_A8);
  bytes.push_back(length);

  for (const string& str : item) {
    vec strBytes = serialize(str);
    bytes.insert(bytes.end(), strBytes.begin(), strBytes.end());
  }

  return bytes;
}

std::vector<u8> pack109::deserialize_vec_u8(vec bytes) {
    if (bytes.size() < 2) {
    throw;
  }

  if (bytes[0] != PACK109_A8) {
    throw;
  }

  u8 length = bytes[1];

  if (bytes.size() < 2 + length) {
    throw;
  }

  // Reconstruct
  std::vector<u8> result;
  for (int i = 2; i < 2 + length; i++) {
    result.push_back(bytes[i]);
  }

  return result;
}
std::vector<u64> pack109::deserialize_vec_u64(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }

  if (bytes[0] != PACK109_A8) {
    throw;
  }

  // Reconstruct 
  u8 length = bytes[1];

  if (bytes.size() < 2 + length * 8) {
    throw;
  }

  // Reconstruct 
  std::vector<u64> result;
  for (int i = 2; i < 2 + length * 8; i += 8) {
    u64 val = 0;
    for (int j = 0; j < 8; ++j) {
      val |= static_cast<u64>(bytes[i + j]) << ((7 - j) * 8);
    }
    result.push_back(val);
  }

  return result;
}

std::vector<f64> pack109::deserialize_vec_f64(vec bytes) {
    if (bytes.size() < 2) {
    throw;
  }

  if (bytes[0] != PACK109_A8) {
    throw;
  }

  // Reconstruct
  u8 length = bytes[1];

  if (bytes.size() < 2 + length * 8) {
    throw;
  }

  // Reconstruct the vector elements from bytes
  std::vector<f64> result;
  for (int i = 2; i < 2 + length * 8; i += 8) {
    u64 bits = (static_cast<u64>(bytes[i]) << 56) |
               (static_cast<u64>(bytes[i + 1]) << 48) |
               (static_cast<u64>(bytes[i + 2]) << 40) |
               (static_cast<u64>(bytes[i + 3]) << 32) |
               (static_cast<u64>(bytes[i + 4]) << 24) |
               (static_cast<u64>(bytes[i + 5]) << 16) |
               (static_cast<u64>(bytes[i + 6]) << 8) |
               static_cast<u64>(bytes[i + 7]);
    f64 val = *reinterpret_cast<f64*>(&bits);
    result.push_back(val);
  }

  return result;
}
std::vector<string> pack109::deserialize_vec_string(vec bytes) {
    if (bytes.size() < 2) {
    throw;
  }

  if (bytes[0] != PACK109_A8) {
    throw;
  }

  // Reconstruct 
  u8 length = bytes[1];

  if (bytes.size() < 2 + length) {
    throw;
  }

  // Reconstruct the vector elements from bytes
  std::vector<string> result;
  int currentIndex = 2;
  for (int i = 0; i < length; ++i) {
    vec strBytes(bytes.begin() + currentIndex, bytes.begin() + currentIndex + sizeof(u32));
    string str = deserialize_string(strBytes);
    result.push_back(str);
    currentIndex += strBytes.size();
  }

  return result;
}

// MAPS
vec pack109::serialize(struct Person item){
  vec bytes;

  // age
  bytes.push_back(PACK109_U8);
  bytes.push_back(item.age);

  // height
  vec heightBytes(sizeof(f32));
  ::memcpy(&heightBytes[0], &item.height, sizeof(f32));
  bytes.insert(bytes.end(), heightBytes.begin(), heightBytes.end());

  // name
  vec nameBytes = serialize(item.name);
  bytes.insert(bytes.end(), nameBytes.begin(), nameBytes.end());

  return bytes;
}

struct Person pack109::deserialize_person(vec bytes){
    struct Person person;

  if (bytes.size() < sizeof(u8) + sizeof(f32)) {
    throw;
  }
  
  if (bytes[0] != PACK109_U8) {
    throw;
  }

  person.age = bytes[1];

  //height 
  if (bytes.size() < sizeof(u8) + sizeof(f32) + 2) {
    throw;
  }
  
  f32 height;
  memcpy(&height, &bytes[sizeof(u8)], sizeof(f32));
  person.height = height;

  // name 
  vec nameBytes(bytes.begin() + sizeof(u8) + sizeof(f32) + 2, bytes.end());
  
  person.name = deserialize_string(nameBytes);

  return person;
}




// HELPER METHOD
void pack109::printVec(vec &bytes)
{
    printf("[ ");
    for (int i = 0; i < bytes.size(); i++)
    {
        printf("%x ", bytes[i]);
    }
    printf("]\n");
}
