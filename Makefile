CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2
LDFLAGS  = -g3 

gerp: main.o Gerp.o stringProcessing.o StringMap.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o gerp $^

main.o: main.cpp Gerp.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Gerp.o: Gerp.cpp Gerp.h Line.h StringMap.h stringProcessing.h
	$(CXX) $(CXXFLAGS) -c $^

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c $^

StringMap.o: StringMap.cpp StringMap.h
	$(CXX) $(CXXFLAGS) -c StringMap.cpp


# The below rule will be used by unit_test.
unit_test: unit_test_driver.o stringProcessing.o StringMap.o
	$(CXX) $(CXXFLAGS) $^

FSTreeTraversal.o: FSTreeTraversal.cpp
	$(CXX) $(CXXFLAGS) -c FSTreeTraversal.cpp FSTree.h DirNode.h

treeTraversal: FSTreeTraversal.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o treeTraversal $^

## essentially a bash for loop that runs a diff test for each .txt file
DIR=/comp/15/files/proj-gerp-test-dirs/smallGutenberg

test: tests/queries/*.txt
	@for file in $^ ; do \
		echo "Testing file $$(basename $$file)"; \
		./gerp $(DIR) ./tests/my/small-out/$$(basename $$file) < $$file ;\
		./the_gerp $(DIR) ./tests/ref/small-out/$$(basename $$file) < $$file ;\
		sort ./tests/my/small-out/$$(basename $$file) \
			 > ./tests/my/small-out/sort_$$(basename $$file) ;\
		sort ./tests/ref/small-out/$$(basename $$file) \
			 > ./tests/ref/small-out/sort_$$(basename $$file) ;\
		diff ./tests/my/small-out/$$(basename $$file) \
			./tests/ref/small-out/$$(basename $$file) ;\
	done;\