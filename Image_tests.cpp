// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  std::ostringstream s;
  Image_print(img, s);

  // Correct output
  std::ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_print_1x1) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};

  Image_init(img, 1, 1);
  Image_set_pixel(img, 0, 0, red);

  // Capture our output
  std::ostringstream s;
  Image_print(img, s);

  // Correct output
  std::ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "255 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_img_init) {
  Image* img = new Image();

  Image_init(img, 3, 5);

  ASSERT_EQUAL(Image_width(img), 3);
  ASSERT_EQUAL(Image_height(img), 5);
  
  Pixel pixel{0, 5, 10};

  Image_fill(img, pixel);
  
  for(int row = 0; row < Image_height(img); row++) {
    for(int col = 0; col < Image_width(img); col++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, row, col), pixel));
    }
  }

  delete img;
}

TEST(test_img_init_1x1) {
  Image* img = new Image();

  Image_init(img, 1, 1);

  ASSERT_EQUAL(Image_width(img), 1);
  ASSERT_EQUAL(Image_height(img), 1);
  
  Pixel pixel{0, 5, 10};

  Image_fill(img, pixel);
  
  for(int row = 0; row < Image_height(img); row++) {
    for(int col = 0; col < Image_width(img); col++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, row, col), pixel));
    }
  }

  delete img;
}

TEST(test_img_ppm) {
  Image* img = new Image();

  std::string inFileName = "dog.ppm";
  std::ifstream inputStream;
  inputStream.open(inFileName);

  ASSERT_TRUE(inputStream.is_open());

  Image_init(img, inputStream);

  ASSERT_EQUAL(Image_width(img), 5);
  ASSERT_EQUAL(Image_height(img), 5);

  std::ostringstream imagePrint;
  Image_print(img, imagePrint);

  std::ostringstream imageCorrect;
  imageCorrect 
    << "P3\n"
    << "5 5\n"
    << "255\n"
    << "0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n"
    << "255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n"
    << "126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n"
    << "255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n"
    << "255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";

  ASSERT_EQUAL(imagePrint.str(), imageCorrect.str());

  delete img;
}

TEST(test_img_fill) {
  Image* img = new Image();
  int width = 2;
  int height = 3;
  Image_init(img, width, height);

  Pixel pixel{6, 8, 3};
  Image_fill(img, pixel);
  Image_set_pixel(img, 0, 1, Pixel{10, 0, 5});

  std::stringstream correct;
  correct 
    << "P3" << std::endl 
    << Image_width(img) << " " << Image_height(img) << std::endl 
    << "255" << std::endl
    << "6 8 3 10 0 5 " << std::endl
    << "6 8 3 6 8 3 " << std::endl
    << "6 8 3 6 8 3 " << std::endl;

  std::stringstream out;
  Image_print(img, out);

  ASSERT_EQUAL(out.str(), correct.str());

  delete img;
}

TEST(test_img_fill_1x1) {
  Image* img = new Image();
  int width = 1;
  int height = 1;
  Image_init(img, width, height);

  Pixel pixel{6, 8, 3};
  Image_fill(img, pixel);

  for(int row = 0; row < Image_height(img); row++) {
    for(int col = 0; col < Image_width(img); col++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, row, col), pixel));
    }
  }

  delete img;
}

TEST(test_set_pixel) {
  Image* img = new Image();
  int width = 5;
  int height = 3;
  Image_init(img, width, height);

  Pixel pixel {30, 50, 255};

  Image_set_pixel(img, 2, 4, pixel);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 4), pixel));

  delete img;
}

TEST(test_set_pixel_2) {
  Image* img = new Image();
  int width = 5;
  int height = 3;
  Image_init(img, width, height);

  Pixel pixel {30, 50, 255};

  Image_set_pixel(img, 1, 2, pixel);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 2), pixel));

  delete img;
}

TEST(test_set_pixel_1x1) {
  Image* img = new Image();
  int width = 1;
  int height = 1;
  Image_init(img, width, height);

  Pixel pixel {30, 50, 255};

  Image_set_pixel(img, 0, 0, pixel);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), pixel));

  delete img;
}

TEST(image_height) {
  Image* img = new Image();
  int width = 4;
  int height = 7;

  Image_init(img, width, height);
  ASSERT_EQUAL(Image_height(img), height);

  delete img;
}

TEST(image_width) {
  Image* img = new Image();
  int width = 4;
  int height = 7;

  Image_init(img, width, height);
  ASSERT_EQUAL(Image_width(img), width);

  delete img;
}

TEST(image_height_1x1) {
  Image* img = new Image();
  int width = 1;
  int height = 1;

  Image_init(img, width, height);
  ASSERT_EQUAL(Image_height(img), height);

  delete img;
}

TEST(image_width_1x1) {
  Image* img = new Image();
  int width = 1;
  int height = 1;

  Image_init(img, width, height);
  ASSERT_EQUAL(Image_width(img), width);

  delete img;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
