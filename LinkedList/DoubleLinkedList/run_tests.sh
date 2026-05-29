#!/bin/bash

function run_test() {
  name=$1
  if [ -f "$name" ]; then
    echo "Compiling $name..."
    g++ -std=c++20 -fsanitize=address -g "$name" -o "${name%.cpp}"
    if [ $? -eq 0 ]; then
      echo "Running $name..."
      "./${name%.cpp}"
      test_result=$?
      rm -f "${name%.cpp}"
      if [ $test_result -ne 0 ]; then
        echo -e "\033[0;31mTest failed!\033[0m"
        exit 1
      fi
    else
      echo -e "\033[0;31mTest is unsuccessful. Be sure that you implemented all methods required in test!\033[0m"
      echo -e "\033[0;31mFollow \"Undefined symbol\" error message. That means that you are missing implementation of that method that is specified!\033[0m"
      exit 1
    fi
  else
    echo -e "\033[0;31mTest file $name not found.\033[0m"
    exit 1
  fi
}

if [ $# -gt 1 ]; then
  echo -e "\033[0;31mInvalid number of arguments!\033[0m"
  exit 1
fi

dir="tests/"

# run specific test
if [ $# -eq 1 ]; then
  filename="Test$1.cpp"
  run_test "$dir$filename"
# run all tests
else
  # Get all test files sorted numerically
  test_files=$(ls "$dir"Test*.cpp 2>/dev/null | sort -V)
  
  if [ -z "$test_files" ]; then
    echo -e "\033[0;31mNo test files found in $dir\033[0m"
    exit 1
  fi
  
  total=0
  passed=0
  
  for file in $test_files; do
    total=$((total + 1))
    echo ""
    echo "=========================================="
    run_test "$file"
    if [ $? -eq 0 ]; then
      passed=$((passed + 1))
    fi
  done
  
  echo ""
  echo "=========================================="
  echo "Test Summary: $passed/$total tests passed"
  echo "=========================================="
  
  if [ $passed -ne $total ]; then
    exit 1
  fi
fi
