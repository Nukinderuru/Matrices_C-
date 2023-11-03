#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  // Helper functions
  void InitMatrix();
  void DeleteMatrix();
  void CopyMatrix(const S21Matrix &other);
  void CopyExisting(S21Matrix &result, int rows, int cols);
  bool DoublesEqual(double a, double b) const;
  bool MatricesMismatch(const S21Matrix &a, const S21Matrix &b) const;
  void Complements(S21Matrix &result);
  void Minor(S21Matrix &minor, int rows, int cols);
  double DetHelper();
  void CheckIndices(int row, int col) const;

 public:
  // Constructors and a destructor
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  // Getters and setters for private fields
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  // Operations
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Operators
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  double &operator()(int row, int col);
  double &operator()(int row, int col) const;
};

#endif  // S21_MATRIX_OOP_H