G++ = g++ -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
TEST_LIBS = -lgtest -lgtest_main -pthread
NAME_TESTS = test.cc
NAME_EXE = test

all: clean test

test:
	$(G++) $(CHECKFLAGS) */*$(NAME_TESTS) -o $(NAME_EXE) $(TEST_LIBS)
	./$(NAME_EXE)


clean:
	@rm -rf *.o *.a a.out *.css *.html *.gch gcov_test *.gcda *.gcno $(NAME_EXE) html_report

format:
	@find . -type f -name "*.cc" -exec clang-format -style=Google -i {} \;
	@find . -type f -name "*.h" -exec clang-format -style=Google -i {} \;
	@find . -type f -name "*.tpp" -exec clang-format -style=Google -i {} \;

format_check:
	find . -type f -name "*.cc" -exec clang-format -style=Google -n {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -n {} \;
	
gcov_report:
	@rm -rf html_report
	@$(G++) */*$(NAME_TESTS) $(TEST_LIBS)  -fprofile-arcs -ftest-coverage -o gcov_test
	@./gcov_test
	@mkdir html_report
	@gcovr --html-details -o html_report/coverage_report.html
	@open -a "Google Chrome" ./html_report/coverage_report.html || xdg-open ./html_report/coverage_report.html || gnome-open ./html_report/coverage_report.html || sensible-browser ./html_report/coverage_report.html || google-chrome ./html_report/coverage_report.html || firefox ./html_report/coverage_report.html

valgrind: test
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(NAME_EXE)


