CC = g++ -std=c++17 -Wall -Werror -Wextra -Wpedantic
SOURCE = s21_matrix_oop.cc
OBJECT = $(SOURCE:.cc=.o)
CGFLAGS = -fprofile-arcs -ftest-coverage --coverage -O0
TEST_FLAGS =-lgtest -lgcov

all: clean s21_matrix_oop.a

s21_matrix_oop.a: $(SOURCE)
	$(CC) -c $(SOURCE)
	@ar rcs s21_matrix_oop.a $(OBJECT)

test: clean test.cc s21_matrix_oop.a
	$(CC) test.cc s21_matrix_oop.a $(TEST_FLAGS) -o test
	./test

gcov_report: clean test.cc s21_matrix_oop.a
	$(CC) -c $(SOURCE) $(CGFLAGS)
	$(CC) test.cc *.o -o test $(TEST_FLAGS)
	./test
	rm -rf test.gcno test.gcda
	gcovr -r . -s --html --html-details -o ./coverage_report.html
	rm -rf *.gcno *.gcda *.o
	open ./coverage_report.html

style_check:
	clang-format -style=Google -n *.cc  *.h

style_fix:
	clang-format -style=Google -i *.cc  *.h

leaks_check: clean test
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=RESULT_VALGRIND.txt ./test
endif

clean:
	@rm -rf *.o *.a coverage* report RESULT_VALGRIND.txt test