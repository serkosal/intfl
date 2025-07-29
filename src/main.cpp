#include <iostream>
#include <filesystem>

int main() {
  std::filesystem::path dirpath = ".";

  if (std::filesystem::exists(dirpath)
      && std::filesystem::is_directory(dirpath))
    for (const auto& entry : std::filesystem::directory_iterator(dirpath))
    {        
      std::cout << "File: " << entry.path() << "\n";
      
    }

  else
    std::cerr << "Directory not found!\n";
  
  std::cout << "Initial commit\n";
  return 0;
}
