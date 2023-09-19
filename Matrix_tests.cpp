// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

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

  int width = 3;
  int height = 5;
  int max = 10;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 1);
  *Matrix_at(mat, 1, 1) = max;

  ASSERT_EQUAL(Matrix_max(mat), max);

  delete mat;
}

TEST(test_max_1x1) {
  Matrix* mat = new Matrix;

  int width = 1;
  int height = 1;
  int max = 10;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 1);
  *Matrix_at(mat, 0, 0) = max;

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
    << "3 3 3 3 " << std::endl;

  ASSERT_EQUAL(border_mat.str(), border_mat_correct.str());

  delete mat;
}

TEST(test_fill_1x1) {
  Matrix* mat = new Matrix();
  int width = 1;
  int height = 1;
  int fill = 5;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, fill);

  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), fill);

  delete mat;
}

TEST(test_at_filled_bordered) {
  Matrix* mat = new Matrix();
  int width = 5;
  int height = 3;
  int fill = 3;
  int border = -1;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 3);
  Matrix_fill_border(mat, border);

  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), *Matrix_at(mat, height - 1, width - 1));
  ASSERT_EQUAL(*Matrix_at(mat, 1, 1), fill);

  delete mat;
}

TEST(test_filled_border_1x1) {
  Matrix* mat = new Matrix();
  int width = 1;
  int height = 1;

  Matrix_init(mat, width, height);

  Matrix_fill_border(mat, 5);

  ASSERT_EQUAL(*Matrix_at(mat, 0,0), 5);

  delete mat;
}

TEST(test_filled_border_1xn) {
  Matrix* mat = new Matrix();
  int width = 1;
  int height = 5;

  Matrix_init(mat, width, height);

  Matrix_fill(mat, 1);
  Matrix_fill_border(mat, 5);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      ASSERT_TRUE(col < 1)
      ASSERT_EQUAL(*Matrix_at(mat, row, col), 5);
    }
  }

  delete mat;
}

TEST(test_row_column) {
  Matrix* mat = new Matrix();

  int width = 7;
  int height = 3;

  Matrix_init(mat, width, height);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      int* item = Matrix_at(mat, row, col);
      ASSERT_EQUAL(Matrix_row(mat, item), row);
      ASSERT_EQUAL(Matrix_column(mat, item), col);

      *item = row * width + col;
    }
  }

  std::stringstream matrix;
  Matrix_print(mat, matrix);

  std::stringstream matrix_actual;
  matrix_actual << width << " " << height << std::endl
    << "0 1 2 3 4 5 6 " << std::endl
    << "7 8 9 10 11 12 13 " << std::endl
    << "14 15 16 17 18 19 20 " << std::endl;

  ASSERT_EQUAL(matrix.str(), matrix_actual.str());

  delete mat;
}

TEST(test_row_column_1x1) {
  Matrix* mat = new Matrix();

  int width = 1;
  int height = 1;

  Matrix_init(mat, width, height);

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      int* item = Matrix_at(mat, row, col);
      ASSERT_EQUAL(Matrix_row(mat, item), row);
      ASSERT_EQUAL(Matrix_column(mat, item), col);

      *item = row * width + col;
    }
  }

  std::stringstream matrix;
  Matrix_print(mat, matrix);

  std::stringstream matrix_actual;
  matrix_actual << width << " " << height << std::endl
    << "0 " << std::endl;

  ASSERT_EQUAL(matrix.str(), matrix_actual.str());

  delete mat;
}

TEST(test_min_row) {
  Matrix* mat = new Matrix();

  int width = 7;
  int height = 5;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 5);

  *Matrix_at(mat, 0, 6) = 3;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, width), 3);

  delete mat;
}

TEST(test_min_row_1x1) {
  Matrix* mat = new Matrix();

  int width = 1;
  int height = 1;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 5);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, width), 5);

  delete mat;
}

TEST(test_min_row_1_width) {
  Matrix* mat = new Matrix();

  int width = 3;
  int height = 5;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 3);

  *Matrix_at(mat, 2, 1) = 1;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 1, 2), 1);

  delete mat;
}

TEST(test_min_row_1xN) {
  Matrix* mat = new Matrix();
  int width = 5;
  int height = 1;

  Matrix_init(mat, width, height);

  Matrix_fill(mat, 20);
  *Matrix_at(mat, 0, 2) = 5;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, width), 5);

  delete mat;
}

TEST(test_min_row_Nx1) {
  Matrix* mat = new Matrix();
  int width = 1;
  int height = 5;

  Matrix_init(mat, width, height);

  Matrix_fill(mat, 20);
  *Matrix_at(mat, 2, 0) = 5;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, width), 5);

  delete mat;
}

TEST(test_min_row_extremes) {
  Matrix* mat = new Matrix();
  int width = 5;
  int height = 8;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 10);

  *Matrix_at(mat, 7, 0) = 2;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 7, 0, 5), 2);

  *Matrix_at(mat, 0, 0) = 3;
  *Matrix_at(mat, 0, 4) = 1;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 5), 1);

  *Matrix_at(mat, 1, 0) = 3;
  *Matrix_at(mat, 1, 4) = 5;

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 5), 3);

  delete mat;
}

TEST(test_min_col_in_row) {
  Matrix* mat = new Matrix();

  int width = 4;
  int height = 4;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 2);
  *Matrix_at(mat, 2, 3) = 0;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 4), 3);

  delete mat;
}

TEST(test_min_col_in_row_1x1) {
  Matrix* mat = new Matrix();

  int width = 1;
  int height = 1;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 2);

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, width), 0);

  delete mat;
}

TEST(test_min_row_col_extremes) {
  Matrix* mat = new Matrix();
  int width = 5;
  int height = 8;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, 10);

  *Matrix_at(mat, 7, 0) = 2;

  ASSERT_EQUAL(
    Matrix_column_of_min_value_in_row(mat, 7, 0, 5), 0
  );

  *Matrix_at(mat, 0, 0) = 3;
  *Matrix_at(mat, 0, 4) = 1;

  ASSERT_EQUAL(
    Matrix_column_of_min_value_in_row(mat, 0, 0, 5), 4
  );

  *Matrix_at(mat, 1, 0) = 3;
  *Matrix_at(mat, 1, 4) = 5;

  ASSERT_EQUAL(
    Matrix_column_of_min_value_in_row(mat, 1, 0, 5), 0
  );

  delete mat;
}

TEST(test_init) {
  Matrix* mat = new Matrix();
  Matrix_init(mat, 5, 3);

  ASSERT_EQUAL(Matrix_width(mat), 5);
  ASSERT_EQUAL(Matrix_height(mat), 3)

  delete mat;
}

TEST(test_matrix_print_2) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 1);

  Matrix_fill(mat, 0);
  *Matrix_at(mat, 0, 3) = -5;

  std::stringstream expected;
  expected << "5 1\n"
           << "0 0 0 -5 0 \n";
  std::stringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_width) {
  Matrix* mat = new Matrix();
  int width = 5;
  int height = 3;

  Matrix_init(mat, width, height);

  ASSERT_EQUAL(Matrix_width(mat), width);

  delete mat;
}

TEST(test_height) {
  Matrix* mat = new Matrix();
  int width = 5;
  int height = 3;

  Matrix_init(mat, width, height);

  ASSERT_EQUAL(Matrix_height(mat), height);

  delete mat;
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
