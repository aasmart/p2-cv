// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.hpp"
#include <cmath>
#include <limits>

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(mat);
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  mat->width = width;
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  assert(mat);
  
  os << Matrix_width(mat) << " " << Matrix_height(mat) << std::endl;
  for(int row = 0; row < Matrix_height(mat); row++) {
    for(int col = 0; col < Matrix_width(mat); col++) {
      os << mat->data[row * Matrix_width(mat) + col] << " ";
    }
    os << std::endl;
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  assert(mat);

  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  assert(mat);

  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  assert(mat);
  assert(ptr);

  return floor((ptr - mat->data) / Matrix_width(mat));
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  assert(mat);
  assert(ptr);

  return (ptr - mat->data) % Matrix_width(mat);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(mat);
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  return &(mat->data[column + Matrix_width(mat) * row]);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(mat);
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  return &mat->data[column + Matrix_width(mat) * row];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  assert(mat);

  for(int i = 0; i < Matrix_width(mat) * Matrix_height(mat); i++)
    mat->data[i] = value;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  assert(mat);

  for(int i = 0; i < Matrix_width(mat) * Matrix_height(mat); i++) {
    int row = floor((double)i / Matrix_width(mat));
    int col = (i % Matrix_width(mat));
    if(row == 0 
        || row == Matrix_height(mat) - 1 
        || col == 0 
        || col == Matrix_width(mat) - 1
    ) { 
      mat->data[i] = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  assert(mat);
  
  int max = mat->data[0];
  for(int i = 0; i < Matrix_width(mat) * Matrix_height(mat); i++)
    max = std::max(max, mat->data[i]);
  
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(
  const Matrix* mat, 
  int row,
  int column_start, 
  int column_end
) {
  assert(mat);
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int startPos = row * Matrix_width(mat) + column_start;
  int endPos = row * Matrix_width(mat) + column_end;

  int min = mat->data[startPos];
  int column = startPos;
  for(int i = startPos + 1; i < endPos; i++) {
    if(mat->data[i] < min) {
      min = mat->data[i];
      column = i;
    }
  }

  return column - row * Matrix_width(mat);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(
  const Matrix* mat, 
  int row,
  int column_start, 
  int column_end
) {
  assert(mat);
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);

  int startPos = row * Matrix_width(mat) + column_start;
  int endPos = row * Matrix_width(mat) + column_end;

  int min = mat->data[startPos];
  for(int i = startPos + 1; i < endPos; i++)
    min = std::min(min, mat->data[i]);

  return min;
}
