#include "s21_matrix_oop.h"

// Default constructor
S21Matrix::S21Matrix() : rows_(1), cols_(1) { InitMatrix(); }

// Constructor with parameters
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument(
        "There should be more than 1 row and/or column.");
  }
  InitMatrix();
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (&other != this) {
    CopyMatrix(other);
  }
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  rows_ = std::exchange(other.rows_, 0);
  cols_ = std::exchange(other.cols_, 0);
  matrix_ = std::exchange(other.matrix_, nullptr);
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  S21Matrix result(rows, cols_);
  int lastRow = rows_;
  if (rows < rows_) lastRow = rows;
  CopyExisting(result, lastRow, cols_);
  *this = result;
}

void S21Matrix::SetCols(int cols) {
  S21Matrix result(rows_, cols);
  int lastCol = cols_;
  if (cols < cols_) lastCol = cols;
  CopyExisting(result, rows_, lastCol);
  *this = result;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool status = true;
  if (MatricesMismatch(*this, other))
    status = false;
  else {
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        if (!DoublesEqual(matrix_[i][j], other.matrix_[i][j])) status = false;
      }
    }
  }
  return status;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  try {
    if (MatricesMismatch(*this, other))
      throw std::invalid_argument("The sizes of matrices must match.");
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } catch (std::invalid_argument const &err) {
    std::cout << err.what() << std::endl;
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  try {
    if (MatricesMismatch(*this, other))
      throw std::invalid_argument("The sizes of matrices must match.");
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } catch (std::invalid_argument const &err) {
    std::cout << err.what() << std::endl;
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  try {
    if (cols_ != other.rows_)
      throw std::invalid_argument("Wrong matrices sizes for multiplication.");
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != other.cols_; ++j) {
        for (int k = 0; k != cols_; ++k) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    *this = result;
  } catch (std::invalid_argument const &err) {
    std::cout << err.what() << std::endl;
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i != transposed.rows_; ++i) {
    for (int j = 0; j != transposed.cols_; ++j) {
      transposed.matrix_[i][j] = matrix_[j][i];
    }
  }
  return transposed;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  try {
    if (rows_ != cols_) throw std::invalid_argument("Matrix must be square.");
    if (rows_ == 1)
      throw std::invalid_argument("There must be more than 1 row and column.");
    Complements(result);
  } catch (std::invalid_argument const &err) {
    std::cout << err.what() << std::endl;
    result.DeleteMatrix();
  }
  return result;
}

double S21Matrix::Determinant() {
  double det = 0.0;
  try {
    if (rows_ != cols_) throw std::invalid_argument("Matrix must be square.");
    det = DetHelper();
  } catch (std::invalid_argument const &err) {
    std::cout << err.what() << std::endl;
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix inversed = S21Matrix();
  if (rows_ == 1 && cols_ == 1) {
    inversed(0, 0) = 1 / matrix_[0][0];
  } else {
    inversed = CalcComplements().Transpose();
    try {
      double det = Determinant();
      if (fabs(det) <= 1.0e-7)
        throw std::invalid_argument(
            "Cannot inverse a matrix with 0 determinant.");
      inversed *= (1.0 / det);
    } catch (std::invalid_argument const &err) {
      std::cout << err.what() << std::endl;
      inversed.DeleteMatrix();
    }
  }
  return inversed;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    DeleteMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CopyMatrix(other);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    DeleteMatrix();
    rows_ = std::exchange(other.rows_, 0);
    cols_ = std::exchange(other.cols_, 0);
    matrix_ = std::exchange(other.matrix_, nullptr);
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  CheckIndices(row, col);
  return matrix_[row][col];
}

double &S21Matrix::operator()(int row, int col) const {
  CheckIndices(row, col);
  return matrix_[row][col];
}

// Allocate memory and fill it with 0
void S21Matrix::InitMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i != rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

// Free the memory
void S21Matrix::DeleteMatrix() {
  if (matrix_) {
    for (int i = 0; i != rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  InitMatrix();
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::CopyExisting(S21Matrix &result, int rows, int cols) {
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
}

bool S21Matrix::DoublesEqual(double a, double b) const {
  return (fabs(a - b) >= 1.0e-07) ? false : true;
}

bool S21Matrix::MatricesMismatch(const S21Matrix &a, const S21Matrix &b) const {
  return ((a.rows_ != b.rows_) || (a.cols_ != b.cols_)) ? true : false;
}

void S21Matrix::Complements(S21Matrix &result) {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      S21Matrix minor(rows_ - 1, cols_ - 1);
      Minor(minor, i, j);
      result.matrix_[i][j] = pow(-1, (i + j)) * minor.Determinant();
      minor.DeleteMatrix();
    }
  }
}

void S21Matrix::Minor(S21Matrix &minor, int row, int col) {
  int rowCnt = 0, colCnt = 0;
  for (int i = 0; i != rows_; ++i) {
    if (i != row) {
      colCnt = 0;
      for (int j = 0; j != cols_; ++j) {
        if (j != col) {
          minor.matrix_[rowCnt][colCnt] = matrix_[i][j];
          ++colCnt;
        }
      }
      ++rowCnt;
    }
  }
}

double S21Matrix::DetHelper() {
  double result = 0.0;
  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (int j = 0; j != cols_; ++j) {
      S21Matrix minor(rows_ - 1, cols_ - 1);
      Minor(minor, 0, j);
      result += matrix_[0][j] * pow(-1, j) * minor.DetHelper();
      minor.DeleteMatrix();
    }
  }
  return result;
}

void S21Matrix::CheckIndices(int row, int col) const {
  if (row < 0)
    throw std::invalid_argument("Row index cannot be less than 0.");
  else if (row > rows_)
    throw std::invalid_argument(
        "Row index is greater than actual amount of rows in the matrix.");
  else if (col < 0)
    throw std::invalid_argument("Column index cannot be less than 0.");
  else if (col > cols_)
    throw std::invalid_argument(
        "Column index is greater than actual amount of columns in the "
        "matrix.");
}