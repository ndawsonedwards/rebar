#include "gtest/gtest.h"

extern "C" {
#include "mapping.h" 
}

TEST(MappingTest, LinearMapInt32_Normal) {
  int32_t input = 50;
  int32_t inputMin = 0; 
  int32_t inputMax = 100;
  int32_t outputMin = 10;
  int32_t outputMax = 20;

  int32_t output;
  Error err = Mapping_LinearMapInt32(input, &output, inputMin, inputMax, outputMin, outputMax);

  EXPECT_EQ(err, Error_None);
  EXPECT_EQ(output, 15);
}

TEST(MappingTest, LinearMapInt32_InputMin) {
  int32_t input = 0;
  int32_t inputMin = 0;
  int32_t inputMax = 100;
  int32_t outputMin = 10; 
  int32_t outputMax = 20;

  int32_t output;
  Error err = Mapping_LinearMapInt32(input, &output, inputMin, inputMax, outputMin, outputMax);

  EXPECT_EQ(err, Error_None);
  EXPECT_EQ(output, 10);
}

TEST(MappingTest, LinearMapInt32_InputMax) {
  // Test input exceeding max
  int32_t input = 120;
  int32_t inputMin = 0;
  int32_t inputMax = 100;
  int32_t outputMin = 10;
  int32_t outputMax = 20;

  int32_t output;
  Error err = Mapping_LinearMapInt32(input, &output, inputMin, inputMax, outputMin, outputMax);

  EXPECT_EQ(err, Error_None);
  EXPECT_EQ(output, 20);
}

TEST(MappingTest, LinearMapInt32_BadParams) {
  // Test invalid input params
  int32_t input = 50;
  int32_t inputMin = 10;
  int32_t inputMax = 0;
  int32_t outputMin = 20;
  int32_t outputMax = 10;

  int32_t output;
  Error err = Mapping_LinearMapInt32(input, &output, inputMin, inputMax, outputMin, outputMax);

  EXPECT_EQ(err, Error_BadParameter);
}

TEST(MappingTest, LinearMapInt32_IllegalPointer) {
  // Test null output pointer
  int32_t input = 50;
  int32_t inputMin = 0;
  int32_t inputMax = 100;
  int32_t outputMin = 10;
  int32_t outputMax = 20;

  int32_t* output = NULL;
  Error err = Mapping_LinearMapInt32(input, output, inputMin, inputMax, outputMin, outputMax);

  EXPECT_EQ(err, Error_IllegalPointer);  
}

TEST(MappingTest, LinearMapInt32_Negative) {
  int32_t input = -100;
  int32_t output;
  int32_t inputMin = -1000;
  int32_t inputMax = 1000; 
  int32_t outputMin = -500;
  int32_t outputMax = 500;

  Error err = Mapping_LinearMapInt32(input, &output, inputMin, inputMax, outputMin, outputMax);

  ASSERT_EQ(err, Error_None);
  ASSERT_EQ(output, -50);
}
