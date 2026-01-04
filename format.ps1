# Reformat all files
Get-ChildItem -Path .\src -Recurse -Include *.cpp,*.h | ForEach-Object -Parallel { clang-format -i -style=file $_.FullName }

Get-ChildItem -Path .\include -Recurse -Include *.cpp,*.h | ForEach-Object -Parallel { clang-format -i -style=file $_.FullName }