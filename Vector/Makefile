G++ = g++ -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
TEST_SRC = s21_vector_test.cc
TEST_LIBS = -lgtest -lgtest_main -lpthread 

all:

build: 
	$(G++) $(CHECKFLAGS) $(TEST_SRC) $(TEST_LIBS) -o test

test: 
	@$(G++) $(CHECKFLAGS) $(TEST_SRC) $(TEST_LIBS) -o test
	@./test
	@rm test

clean:
	@rm -rf *.o *.a a.out *.css *.html gcov_test *.gcda *.gcno test 

gcov_report:
	@rm -rf html_report
	@$(G++) $(TEST_SRC) $(TEST_LIBS)  -fprofile-arcs -ftest-coverage -o gcov_test
#  --coverage  $(TEST_LIBS) -o gcov_test $(shell pkg-config --libs --cflags check)
	@./gcov_test
	@mkdir html_report
	@gcovr --html-details -o html_report/coverage_report.html
	@open -a "Google Chrome" ./html_report/coverage_report.html

style: 
	clang-format -style=google -i *.cc
	clang-format -style=google -i *.h

clang-format: 
	clang-format -style=google -n *.cc
	clang-format -style=google -n *.h

valgrind: build
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
