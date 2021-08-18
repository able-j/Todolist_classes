#include <vector>
#include "task.hpp"

class TodoList
{
public:
  TodoList(const char*);

  void add(Task& task);
  void readFile();
  void display(std::string& option);
  int* splitDate(int date);
  void remove(Task& task);
  void completed(Task& task);
  void save();
  int getCount();
  void missed();

private:
  const char* m_filename;
  std::vector<Task> m_saveList;
};
