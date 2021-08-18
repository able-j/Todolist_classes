#include <string>

class Task
{
public:
  Task(std::string, int, bool, bool);
  Task(std::string, int, int, int);

  std::string getDescription();
  int& getDate();
  void finish();
  bool isFinished();
  bool isMissed();
  void miss();

  bool operator==(Task& task);

private:
  std::string m_description;
  int m_dueDate;
  bool m_isFinished;
  bool m_isMissed;
};
