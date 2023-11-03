#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// Constructors:

// Default
TEST(DefaultConstructor, test1) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix();
    EXPECT_EQ(test.GetRows(), 1);
    EXPECT_EQ(test.GetCols(), 1);
  });
}

// Parametrized, correct size
TEST(ParametrizedConstructor, test0) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 4);
    EXPECT_EQ(test.GetRows(), 3);
    EXPECT_EQ(test.GetCols(), 4);
  });
}

// Parametrized, wrong sizes
TEST(ParametrizedConstructor, test1) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(3, 0); });
}

TEST(ParametrizedConstructor, test2) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(2, -2); });
}

TEST(ParametrizedConstructor, test3) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(0, 0); });
}

TEST(ParametrizedConstructor, test4) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(-3, 4); });
}

TEST(ParametrizedConstructor, test5) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(-2, -1); });
}

// Copy
TEST(CopyConstructor, test1) {
  EXPECT_NO_THROW({
    S21Matrix a = S21Matrix(3, 3);
    for (int i = 0; i < a.GetRows(); i++) {
      for (int j = 0; j < a.GetCols(); j++) {
        a(i, j) = i + j;
      }
    }
    S21Matrix b(a);
    for (int i = 0; i < a.GetRows(); i++) {
      for (int j = 0; j < a.GetCols(); j++) {
        EXPECT_EQ(a(i, j), b(i, j));
      }
    }
  });
}

TEST(CopyConstructor, test2) {
  EXPECT_NO_THROW({
    S21Matrix a = S21Matrix(3, 3);
    for (int i = 0; i < a.GetRows(); i++) {
      for (int j = 0; j < a.GetCols(); j++) {
        a(i, j) = i + j;
      }
    }
    S21Matrix b(a);
    a = S21Matrix(a);
    EXPECT_EQ(a.GetRows(), 3);
    EXPECT_EQ(a.GetCols(), 3);
    for (int i = 0; i < a.GetRows(); i++) {
      for (int j = 0; j < a.GetCols(); j++) {
        EXPECT_EQ(a(i, j), b(i, j));
      }
    }
  });
}

// Move
TEST(MoveConstructor, test1) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  S21Matrix b = S21Matrix(3, 3);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      b(i, j) = matrix[i][j];
    }
  }
  S21Matrix a = std::move(b);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_EQ(a(i, j), matrix[i][j]);
    }
  }
  EXPECT_EQ(b.GetRows(), 0);
  EXPECT_EQ(b.GetCols(), 0);
}

// Getters and setters

TEST(Getter, test1) {
  S21Matrix test(1, 1);
  EXPECT_EQ(test.GetRows(), 1);
  EXPECT_EQ(test.GetCols(), 1);
}

TEST(Getter, test2) {
  S21Matrix test(1, 4);
  EXPECT_EQ(test.GetRows(), 1);
  EXPECT_EQ(test.GetCols(), 4);
}

TEST(Getter, test3) {
  S21Matrix test(3, 3);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Getter, test4) {
  S21Matrix test(13, 7);
  EXPECT_EQ(test.GetRows(), 13);
  EXPECT_EQ(test.GetCols(), 7);
}

TEST(Getter, test5) {
  S21Matrix test(100, 100);
  EXPECT_EQ(test.GetRows(), 100);
  EXPECT_EQ(test.GetCols(), 100);
}

TEST(Setter, test1) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(5);
    EXPECT_EQ(test.GetRows(), 5);
  });
}

TEST(Setter, test2) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(2);
    EXPECT_EQ(test.GetRows(), 2);
  });
}

TEST(Setter, test3) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(3);
    EXPECT_EQ(test.GetRows(), 3);
  });
}

TEST(Setter, test4) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(0);
  });
}

TEST(Setter, test5) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(-1);
  });
}

TEST(Setter, test6) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetCols(5);
    EXPECT_EQ(test.GetCols(), 5);
  });
}

TEST(Setter, test7) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetCols(2);
    EXPECT_EQ(test.GetCols(), 2);
  });
}

TEST(Setter, test8) {
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetCols(3);
    EXPECT_EQ(test.GetCols(), 3);
  });
}

TEST(Setter, test9) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetCols(0);
  });
}

TEST(Setter, test10) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetCols(-1);
  });
}

// Operations

TEST(EqMatrixTest, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(mat1.EqMatrix(mat2));
  EXPECT_TRUE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 1}, {4, 3}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalMatrices2) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][2] = {{2, 1}, {4, 3}, {1, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(SumMatrixTest, Addition1) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double result[2][2] = {{6, 8}, {10, 12}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SumMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(SumMatrixTest, Addition2) {
  double matrix1[2][2] = {{0, 1}, {1, 0}};
  double matrix2[2][2] = {{1, 0}, {0, 1}};
  double result[2][2] = {{1, 1}, {1, 1}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SumMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(SumMatrixTest, Addition3) {
  double matrix1[2][3] = {{0, 1, 0}, {1, 0, 1}};
  double matrix2[2][2] = {{1, 0}, {0, 1}};
  double matrix1Copy[2][3] = {{0, 1, 0}, {1, 0, 1}};
  double matrix2Copy[2][2] = {{1, 0}, {0, 1}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_NO_THROW({ mat1.SumMatrix(mat2); });

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), matrix1Copy[i][j]);
    }
  }

  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      EXPECT_EQ(mat2(i, j), matrix2Copy[i][j]);
    }
  }
}

TEST(SumMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_NO_THROW({ mat1.SumMatrix(mat2); });

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), matrix[i][j]);
    }
  }
}

TEST(SubMatrixTest, Subtraction1) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double result[2][2] = {{-4, -4}, {-4, -4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SubMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(SubMatrixTest, Subtraction2) {
  double matrix1[2][2] = {{8, 7}, {6, 5}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};
  double result[2][2] = {{7, 5}, {3, 1}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SubMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(SubMatrixTest, Subtraction3) {
  double matrix1[2][3] = {{0, 1, 0}, {1, 0, 1}};
  double matrix2[2][2] = {{1, 0}, {0, 1}};
  double matrix1Copy[2][3] = {{0, 1, 0}, {1, 0, 1}};
  double matrix2Copy[2][2] = {{1, 0}, {0, 1}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_NO_THROW({ mat1.SubMatrix(mat2); });

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), matrix1Copy[i][j]);
    }
  }

  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      EXPECT_EQ(mat2(i, j), matrix2Copy[i][j]);
    }
  }
}

TEST(SubMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_NO_THROW({ mat1.SubMatrix(mat2); });

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), matrix[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumber1) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 2;
  double expected[2][2] = {{2, 4}, {6, 8}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumber2) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = -2;
  double expected[2][2] = {{-2, -4}, {-6, -8}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumber3) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 0.5;
  double expected[2][2] = {{0.5, 1}, {1.5, 2}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyZero) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 0;
  double expected[2][2] = {{0, 0},
                           {
                               0,
                           }};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixIdentity) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double identity[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix identityMat = S21Matrix(3, 3);
  for (int i = 0; i < identityMat.GetRows(); i++) {
    for (int j = 0; j < identityMat.GetCols(); j++) {
      identityMat(i, j) = identity[i][j];
    }
  }

  mat.MulMatrix(identityMat);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), matrix[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixArbitrary) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{3, 0}, {2, 1}, {0, 1}};
  double expected[2][2] = {{7, 5}, {22, 11}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.MulMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixWrongSize) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[2][3] = {{3, 0, 2}, {0, 1, 2}};
  double matrix1Copy[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2Copy[2][3] = {{3, 0, 2}, {0, 1, 2}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 3);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.MulMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), matrix1Copy[i][j]);
    }
  }

  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      EXPECT_EQ(mat2(i, j), matrix2Copy[i][j]);
    }
  }
}

TEST(TransposeTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, RectangularMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double expected[3][2] = {{1, 4}, {2, 5}, {3, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, SingleElementMatrix) {
  double matrix[1][1] = {{21}};
  double expected[1][1] = {{21}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  S21Matrix transposed = mat.Transpose();

  EXPECT_EQ(transposed.GetRows(), 1);
  EXPECT_EQ(transposed.GetCols(), 1);
  EXPECT_EQ(transposed(0, 0), expected[0][0]);
}

TEST(CalcComplementsTest, SquareMatrix1) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double expected[2][2] = {{4, -3}, {-2, 1}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix complements = mat.CalcComplements();

  for (int i = 0; i < complements.GetRows(); i++) {
    for (int j = 0; j < complements.GetCols(); j++) {
      EXPECT_EQ(complements(i, j), expected[i][j]);
    }
  }
}

TEST(CalcComplementsTest, SquareMatrix2) {
  double matrix[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double expected[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix complements = mat.CalcComplements();

  for (int i = 0; i < complements.GetRows(); i++) {
    for (int j = 0; j < complements.GetCols(); j++) {
      EXPECT_EQ(complements(i, j), expected[i][j]);
    }
  }
}

TEST(CalcComplementsTest, NonSquareMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {3, 4, 5}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix complements = mat.CalcComplements();

  for (int i = 0; i < complements.GetRows(); i++) {
    for (int j = 0; j < complements.GetCols(); j++) {
      EXPECT_EQ(complements(i, j), matrix[i][j]);
    }
  }
}

TEST(CalcComplementsTest, 1x1Matrix) {
  double matrix[1][1] = {{1}};

  S21Matrix mat = S21Matrix(1, 1);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix complements = mat.CalcComplements();

  for (int i = 0; i < complements.GetRows(); i++) {
    for (int j = 0; j < complements.GetCols(); j++) {
      EXPECT_EQ(complements(i, j), matrix[i][j]);
    }
  }
}

TEST(DeterminantTest, 1x1Matrix) {
  double matrix[1][1] = {{42}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  double determinant = mat.Determinant();

  EXPECT_EQ(determinant, matrix[0][0]);
}

TEST(DeterminantTest, 2x2Matrix) {
  double matrix[2][2] = {{-3, 2}, {12, 4}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();
  EXPECT_EQ(determinant, -36);
}

TEST(DeterminantTest, 3x3Matrix) {
  double matrix[3][3] = {{-3, 2, -5}, {10, 4, 7}, {6, -8, -9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();
  EXPECT_EQ(determinant, 724);
}

TEST(DeterminantTest, NonSquareMatrix) {
  double matrix[2][3] = {{42, 21, 42}, {1, 2, 1}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), matrix[i][j]);
    }
  }
  EXPECT_EQ(determinant, 0);
}

TEST(InverseTest, 1x1Matrix) {
  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = 2.0;

  S21Matrix inversed = mat.InverseMatrix();

  EXPECT_EQ(inversed(0, 0), 0.5);
}

TEST(InverseTest, 3x3Matrix) {
  double matrix[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double result[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix inversed = mat.InverseMatrix();

  for (int i = 0; i < inversed.GetRows(); i++) {
    for (int j = 0; j < inversed.GetCols(); j++) {
      EXPECT_EQ(inversed(i, j), result[i][j]);
    }
  }
}

TEST(InverseTest, 3x3MatrixZeroDeterminant) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix inversed = mat.InverseMatrix();

  EXPECT_EQ(inversed.GetRows(), 0);
  EXPECT_EQ(inversed.GetCols(), 0);
}

// Operators

TEST(AssignmentOperator, test1) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(3, 4);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix();
    result = check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check(i, j));
      }
    }
  });
}

TEST(AdditionOperator, Addition) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double expected[2][2] = {{6, 8}, {10, 12}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  S21Matrix result = S21Matrix(2, 2);
  result = mat1 + mat2;

  for (int i = 0; i < result.GetRows(); i++) {
    for (int j = 0; j < result.GetCols(); j++) {
      EXPECT_EQ(result(i, j), expected[i][j]);
    }
  }
}

TEST(SubtractionOperator, Subtraction) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double expected[2][2] = {{-4, -4}, {-4, -4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  S21Matrix result = S21Matrix(2, 2);
  result = mat1 - mat2;

  for (int i = 0; i < result.GetRows(); i++) {
    for (int j = 0; j < result.GetCols(); j++) {
      EXPECT_EQ(result(i, j), expected[i][j]);
    }
  }
}

TEST(MultiplicationOperator, MultiplyNumber) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 2;
  double expected[2][2] = {{2, 4}, {6, 8}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix result = S21Matrix(2, 2);
  result = mat * num;

  for (int i = 0; i < result.GetRows(); i++) {
    for (int j = 0; j < result.GetCols(); j++) {
      EXPECT_EQ(result(i, j), expected[i][j]);
    }
  }
}

TEST(MultiplicationOperator, MultiplyMatrixArbitrary) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{3, 0}, {2, 1}, {0, 1}};
  double expected[2][2] = {{7, 5}, {22, 11}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  S21Matrix result = S21Matrix(2, 2);
  result = mat1 * mat2;

  for (int i = 0; i < result.GetRows(); i++) {
    for (int j = 0; j < result.GetCols(); j++) {
      EXPECT_EQ(result(i, j), expected[i][j]);
    }
  }
}

TEST(EqualityOperator, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(mat1 == mat2);
  EXPECT_TRUE(mat2 == mat1);
}

TEST(AddAssignOperator, AdditionAndAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double expected[2][2] = {{6, 8}, {10, 12}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1 += mat2;

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(SubAssignOperator, SubtractionAndAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double expected[2][2] = {{-4, -4}, {-4, -4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1 -= mat2;

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(MulAssignOperator, MultiplyNumberAndAssign) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 2;
  double expected[2][2] = {{2, 4}, {6, 8}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat *= num;

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulAssignOperator, MultiplyMatrixArbitraryAndAssign) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{3, 0}, {2, 1}, {0, 1}};
  double expected[2][2] = {{7, 5}, {22, 11}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1 *= mat2;

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(IndexationOperator, Indexation_Proper_Bounds_Const) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{3, 0}, {2, 1}, {0, 1}};
  double expected[2][2] = {{7, 5}, {22, 11}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1 *= mat2;

  const S21Matrix mat_result = mat1;

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat_result(i, j), expected[i][j]);
    }
  }
}

TEST(IndexationOperator, Indexation_Improper_Bounds) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  EXPECT_ANY_THROW(mat1(3, 1) = 0);
  EXPECT_ANY_THROW(mat1(1, 5) = 0);
}

TEST(IndexationOperator, Indexation_Improper_Bounds_Const) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }
  const S21Matrix mat_const = mat1;

  EXPECT_ANY_THROW(mat_const(3, 1) = 0);
  EXPECT_ANY_THROW(mat_const(1, 5) = 0);
  EXPECT_ANY_THROW(mat_const(-3, 1) = 0);
  EXPECT_ANY_THROW(mat_const(1, -5) = 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}