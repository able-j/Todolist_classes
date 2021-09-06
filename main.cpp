#include <iostream>
#include "list.hpp"

void getInput(int& month, int& day, int& year, std::string& description, bool option)
{
  if (option)
  {
    std::cout << "\n\n\n";

    std::cout << "Month: ";
    std::cin >> month;
    std::cout << "\nDay: ";
    std::cin >> day;
    std::cout << "\nYear: ";
    std::cin >> year;
    std::cout << "\nTask description: ";
    std::getline(std::cin >> std::ws, description);
  }
  else
  {
    std::cout << "\n\n\n";

    std::cout << "Enter the Task to mark as completed/delete: ";
    std::getline(std::cin >> std::ws, description);
  }
}

int main()
{
  const char* file = "tasks.json";

  TodoList list(file);

  std::string option;

  int month;
  int day;
  int year;
  std::string description;

  while (true)
  {
	   list.missed();

    std::cout << "\n\n\n\t\t\t\t\tPlease select an option.\n";
    std::cout << "1)   Add new task" << "\n";
    std::cout << "2)   Delete a task" << "\n";
    std::cout << "3)   Mark a task as completed" << "\n";
    std::cout << "4)   Show remaining tasks" << "\n";
    std::cout << "5)   Get Number of remaining tasks" << "\n\n";

    std::cout << "Select an option: ";
    std::cin >> option;

    if (option == "1")
    {
      getInput(month, day, year, description, true);

      Task task(description, month, day, year);
      list.add(task);
    }
    else if (option == "2")
    {
      getInput(month, day, year, description, false);

      Task task(description, month, day, year);
      list.remove(task);

      std::cout << "Successfully deleted.";
    }
    else if (option == "3")
    {
      getInput(month, day, year, description, false);

      Task task(description, month, day, year);
      list.completed(task);
    }
    else if (option == "4")
    {
      std::string taskType;

      std::cout << "Which tasks would you like to display? [all, completed, missed]  ";
      std::cin.ignore();
      taskType = std::cin.get();

      list.display(taskType);
    }
    else if (option == "5")
    {
      std::cout << "Remaining Tasks: " << list.getCount() << "\n\n";
    }
    else
    {
      return 0;
    }
  }

  return 0;
}
