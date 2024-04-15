G++ = g++ -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
TEST_SRC = set_tests.cc
TEST_LIBS = -lgtest -lgtest_main -lpthread 

all:

build: 
	@$(G++) $(CHECKFLAGS) main.cc

test: 
	@$(G++) $(CHECKFLAGS) $(TEST_SRC) $(TEST_LIBS) -o test
	@./test

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

format:
	@find .. -type f -name "*.cc" -exec clang-format -style=Google -i {} \;
	@find .. -type f -name "*.h" -exec clang-format -style=Google -i {} \;

format_check:
	find . -type f -name "*.cc" -exec clang-format -style=Google -n {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -n {} \;

#valgrind: build
#	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./a.out
valgrind: test
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
