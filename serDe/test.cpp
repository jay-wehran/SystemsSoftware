#include <stdexcept>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include"pack109.hpp"

template <class T>
int test(const char* label, T lhs, T rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    std::cout << "Failed\n" << "\n";
    std::cout << "lhs=" << lhs << "\n";
    std::cout << "rhs=" << rhs << "\n";
    exit(1);
  }
}

int testvec(const char* label, vec lhs, vec rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs="); pack109::printVec(lhs); printf("\n");
    printf("  rhs="); pack109::printVec(rhs); printf("\n");
    exit(1);
  }
}


int main() {

  // Test bool

  // True
  vec v1{0xa0};
  vec bytes1 = pack109::serialize(true);
  testvec("Test 1 - true ser", bytes1, v1);

  bool bool_true = pack109::deserialize_bool(bytes1);
  test("Test 2 - true de", bool_true, true);
 

  // False
  vec v2{0xa1};
  vec bytes2 = pack109::serialize(false);
  testvec("Test 3 - false ser", bytes2, v2);

  bool bool_false = pack109::deserialize_bool(bytes2); 
  test("Test 4 - false de", bool_false, false);

// Test Integers

 // u8
u8 item1 = 0x42; // had to switch "memory" with "item1" in the second line in the second element of the vec
vec v3{0xa2, item1}; //!
vec bytes3 = pack109::serialize(item1);
testvec("Test 5 - u8 ser", bytes3, v3);
  
  u8 int_u8 = pack109::deserialize_u8(bytes3);  
  test("Test 6 - u8 de", int_u8, item1);

  //u32

  u32 item_u32 = 0x12345678;
  vec v4{0xa3, 0x12, 0x34, 0x56, 0x78}; // Expected serialized bytes
  vec bytes4 = pack109::serialize(item_u32);
  testvec("Test 7 - u32 ser", bytes4, v4);
  
  u32 int_u32 = pack109::deserialize_u32(bytes4);
  test("Test 8 - u32 de", int_u32, item_u32);


  //u64
  u64 item_u64 = 0x0123456789abcdef;
  vec v5{0xa4, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef}; // Expected serialized bytes
  vec bytes5 = pack109::serialize(item_u64);
  testvec("Test 9 - u64 ser", bytes5, v5);
  
  u64 int_u64 = pack109::deserialize_u64(bytes5);
  test("Test 10 - u64 de", int_u64, item_u64);


  //i8
  i8 item_i8 = -42;
  vec v6{0xa5, static_cast<u8>(item_i8)}; // Expected serialized bytes
  vec bytes6 = pack109::serialize(item_i8);
  testvec("Test 11 - i8 ser", bytes6, v6);
  
  i8 int_i8 = pack109::deserialize_i8(bytes6);
  test("Test 12 - i8 de", int_i8, item_i8);

    // i32
  i32 item_i32 = -12345678;
  vec v7{0xa6}; // Initialize the expected serialized bytes vector

  // Serialize i32
  for (int i = 24; i >= 0; i -= 8) {
    v7.push_back(static_cast<u8>((item_i32 >> i) & 0xFF));
  }
  vec bytes7 = pack109::serialize(item_i32);
  testvec("Test 13 - i32 ser", bytes7, v7);

  // Deserialize i32
  i32 int_i32 = 0;
  for (size_t i = 1; i < bytes7.size(); i++) {
    int_i32 |= (static_cast<i32>(bytes7[i]) << (24 - (8 * (i - 1))));
  }
  test("Test 14 - i32 de", int_i32, item_i32);

   // i64
  i64 item_i64 = -1234567890123456LL;
  vec v9{0xa7}; // Initialize the expected serialized bytes vector

  // Serialize i64
  for (int i = 56; i >= 0; i -= 8) {
    v9.push_back(static_cast<u8>((item_i64 >> i) & 0xFF));
  }
  vec bytes9 = pack109::serialize(item_i64);
  testvec("Test 17 - i64 ser", bytes9, v9);

  // Deserialize i64
  i64 int_i64 = 0;
  for (size_t i = 1; i < bytes9.size(); i++) {
    int_i64 |= (static_cast<i64>(bytes9[i]) << (56 - (8 * (i - 1))));
  }
  test("Test 18 - i64 de", int_i64, item_i64);



  // Test Floats

  // f32
  f32 item_f32 = 3.14159f;
  vec bytes11 = pack109::serialize(item_f32);
  f32 result_f32 = pack109::deserialize_f32(bytes11);
  test("Test 19 - f32 ser/de", result_f32, item_f32);


  // f64
  f64 item_f64 = 2.71828;
  vec bytes12 = pack109::serialize(item_f64);
  f64 result_f64 = pack109::deserialize_f64(bytes12);
  test("Test 20 - f64 ser/de", result_f64, item_f64);


  // Test string
  // Test string serialization and deserialization
  string item_str = "Hello, World!";
  vec v10{PACK109_S16, 0x00, 0x0D}; // Expected serialized bytes
  for (char c : item_str) {
    v10.push_back(static_cast<u8>(c));
  }
  vec bytes10 = pack109::serialize(item_str);
  testvec("Test 21 - string ser", bytes10, v10);

  string result_str = pack109::deserialize_string(bytes10);
  test("Test 22 - string de", result_str, item_str);


  // // Test Arrays

  // // u8
  std::vector<u8> item_vec_u8 = {0x11, 0x22, 0x33, 0x44};
  vec bytes13 = pack109::serialize(item_vec_u8);
  std::vector<u8> result_vec_u8 = pack109::deserialize_vec_u8(bytes13);
  testvec("Test 23 - u8 vector ser/de", result_vec_u8, item_vec_u8);


  vec v1 = {0xa1};
  // // Test Map

  // // Person Test 
  //   // Test struct Person serialization and deserialization
  struct Person item_person = {21, 173.3f, "Jason"};
  vec bytes14 = pack109::serialize(item_person);
  struct Person result_person = pack109::deserialize_person(bytes14);
  test("Test 24 - struct Person ser/de - age", result_person.age, item_person.age);
  test("Test 25 - struct Person ser/de - height", result_person.height, item_person.height);
  test("Test 26 - struct Person ser/de - name", result_person.name, item_person.name);

}
