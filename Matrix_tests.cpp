// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// Creates a 10x20 matrix and checks that the
// matrix is of the correct size
TEST(test_dimensions) {
  Matrix* mat = new Matrix;

  int width = 10;
  int height = 20;

  Matrix_init(mat, width, height);
  ASSERT_EQUAL(Matrix_width(mat), width);
  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
}

TEST(test_max) {
  Matrix* mat = new Matrix;

  int width = 5;
  int height = 5;
  int max = 10;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 1);
  *Matrix_at(mat, 1, 1) = max;

  ASSERT_EQUAL(Matrix_max(mat), max);

  delete mat;
}

TEST(test_max_equal) {
  Matrix* mat = new Matrix;

  int width = 5;
  int height = 5;
  int max = 1;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, max);

  ASSERT_EQUAL(Matrix_max(mat), max);

  delete mat;
}

TEST(test_fill_border) {
  Matrix* mat = new Matrix;

  int width = 4;
  int height = 5;
  int fill = 0;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, fill);
  Matrix_fill_border(mat, 3);

  std::stringstream border_mat;
  Matrix_print(mat, border_mat);

  std::stringstream border_mat_correct;
  border_mat_correct 
    << width << " " << height << std::endl
    << "3 3 3 3 " << std::endl 
    << "3 0 0 3 " << std::endl
    << "3 0 0 3 " << std::endl
    << "3 0 0 3 " << std::endl
    << "3 3 3 3 ";

  ASSERT_EQUAL(border_mat.str(), border_mat_correct.str());
}

// TEST(test_at) {
//   Matrix* mat = new Matrix;
//   int width = 3;
//   int height = 5;
//   int fill = 25;
//   Matrix_init(mat, width, height);
//   Matrix_fill(mat, fill);

//   int row = 2;
//   int column = 2;

//   Matrix_at(mat, row, column);
// }

// TEST(test_mat_row) {
//   Matrix *mat = new Matrix;

//   int width = 5;
//   int height = 3;

//   Matrix_init(mat, width, height);
  
// }

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
