$ErrorActionPreference = "Stop"

Write-Host "Building application..."
gcc src\main.c src\student.c src\storage.c -Iinclude -Wall -Wextra -Werror -pedantic -std=c11 -o student-system.exe

Write-Host "Building tests..."
gcc tests\test_student.c src\student.c src\storage.c -Iinclude -Wall -Wextra -Werror -pedantic -std=c11 -o test-student.exe

Write-Host "Running tests..."
.\test-student.exe

Write-Host "Build and tests completed successfully."
