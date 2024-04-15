G++ = g++ -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
TEST_LIBS = -lgtest -lgtest_main -pthread
NAME_TESTS = s21_list_test.cc
NAME_EXE = test_list

all: clean test

test: $(NAME_TESTS)
	$(G++) $(CHECKFLAGS) -std=c++17 -o $(NAME_EXE) $(NAME_TESTS) $(TEST_LIBS)
	./$(NAME_EXE)


clean:
	rm -rf *.o *.a a.out *.css *.html *.gch gcov_test *.gcda *.gcno $(NAME_EXE) html_report

format: 
	clang-format -style=google -i *.tpp
	clang-format -style=google -i *.h
	clang-format -style=google -i *.cc

clang-format: 
	clang-format -style=google -n *.tpp
	clang-format -style=google -n *.h
	clang-format -style=google -i *.cc

gcov_report:
	@rm -rf html_report
	@$(G++) $(NAME_TESTS) $(TEST_LIBS)  -fprofile-arcs -ftest-coverage -o gcov_test
#  --coverage  $(TEST_LIBS) -o gcov_test $(shell pkg-config --libs --cflags check)
	@./gcov_test
	@mkdir html_report
	@gcovr --html-details -o html_report/coverage_report.html
	@xdg-open ./html_report/coverage_report.html || gnome-open ./html_report/coverage_report.html || sensible-browser ./html_report/coverage_report.html || google-chrome ./html_report/coverage_report.html || firefox ./html_report/coverage_report.html

valgrind: test
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(NAME_EXE)

