#include "list.hpp"
#include "json/json.h"
#include "json/json-forwards.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

TodoList::TodoList(const char* file)
{
  this->m_filename = file;
}

void TodoList::readFile()
{
  std::ifstream saveFile;
  saveFile.open(m_filename, std::ifstream::binary);

  Json::Value jsonSave;
  saveFile >> jsonSave;
  m_saveList.clear();

  for (int i = 0; i < jsonSave.size(); i++)
  {
    Task task(jsonSave[i]["description"].asString(), jsonSave[i]["duedate"].asInt(), jsonSave[i]["isfinished"].asBool(), jsonSave[i]["ismissed"].asBool());
    m_saveList.push_back(task);
  }

  saveFile.close();
}

void TodoList::save()
{
  Json::Value jsonSave;

  std::ofstream f;
  f.open(m_filename, std::ofstream::binary);

  for (int i = 0; i < m_saveList.size(); i++)
  {
    jsonSave[i]["description"] = m_saveList.at(i).getDescription();
    jsonSave[i]["duedate"] = m_saveList.at(i).getDate();
    jsonSave[i]["isfinished"] = m_saveList.at(i).isFinished();
    jsonSave[i]["ismissed"] = m_saveList.at(i).isMissed();
  }

  Json::StreamWriterBuilder builder;
  builder["commentStyle"] = "None";
  builder["indentation"] = "  ";

  std::unique_ptr<Json::StreamWriter> outputWriter(builder.newStreamWriter());
  outputWriter->write(jsonSave, &f);

  f.close();
}

int* TodoList::splitDate(int date)
{
  static int dateArr[3];

  dateArr[0] = date / 10000;
  date %= 10000;
  dateArr[1] = date / 100;
  date %= 100;
  dateArr[2] = date;

  return dateArr;
}

void TodoList::display(std::string& option)
{
  readFile();

  std::cout << "\n";

  if (option == "all")
  {
    for (int i = 0; i < m_saveList.size(); i++)
    {
      std::cout << "Due Date: ";

      for (int j = 0; j < 3; j++)
      {
        std::cout << *(splitDate(m_saveList.at(i).getDate()) + j) << " ";
      }
      std::cout << "\nTask description: " << m_saveList.at(i).getDescription() << "\n";

      std::string finished = (m_saveList.at(i).isFinished()) ? "Finished Task\n" : "Not Finished\n";
      std::string late = (m_saveList.at(i).isMissed()) ? "Late\n" : "Not late\n";

      std::cout << finished;
      std::cout << late;
      std::cout << "\n";
    }
  }
  else if (option == "completed")
  {
    for (int i = 0; i < m_saveList.size(); i++)
    {
      if (m_saveList.at(i).isFinished())
      {
        std::cout << "Due Date: ";

        for (int j = 0; j < 3; j++)
        {
          std::cout << *(splitDate(m_saveList.at(i).getDate()) + j) << " ";
        }
        std::cout << "\nTask description: " << m_saveList.at(i).getDescription() << "\n";
        std::cout << "Finished Task\n";
        std::string late = (m_saveList.at(i).isMissed()) ? "Late\n" : "Not late\n";
        std::cout << late;
      }
    }
  }
  else
  {
    for (int i = 0; i < m_saveList.size(); i++)
    {
      if (m_saveList.at(i).isMissed())
      {
        std::cout << "Due Date: ";

        for (int j = 0; j < 3; j++)
        {
          std::cout << *(splitDate(m_saveList.at(i).getDate()) + j) << " ";
        }
        std::cout << "\nTask description: " << m_saveList.at(i).getDescription() << "\n";
        std::string finished = (m_saveList.at(i).isFinished()) ? "Finished Task\n" : "Not Finished\n";
        std::cout << finished;
        std::cout << "Late";
      }
    }
  }
}

void TodoList::add(Task& task)
{
  readFile();
  m_saveList.push_back(task);
  save();
}

void TodoList::completed(Task& task)
{
  readFile();
  for (int i = 0; i < m_saveList.size(); i++)
  {
    if (m_saveList.at(i) == task)
    {
      m_saveList.at(i).finish();
      break;
    }
  }

  save();
}

void TodoList::missed()
{
  readFile();

  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  time_t timepoint = std::chrono::system_clock::to_time_t(now);
  tm local_tm = *(localtime(&timepoint));

  int timeInt = ((local_tm.tm_year + 1900) * 10000) + ((local_tm.tm_mon + 1) * 100) + local_tm.tm_mday;

  for (int i = 0; i < m_saveList.size(); i++)
  {
    if (m_saveList.at(i).getDate() < timeInt)
    {
      m_saveList.at(i).miss();
    }
  }

  save();
}

void TodoList::remove(Task& task)
{
  readFile();
  for (int i = 0; i < m_saveList.size(); i++)
  {
    if (m_saveList.at(i) == task)
    {
      m_saveList.erase(m_saveList.begin() + i);
    }
  }

  save();
}

int TodoList::getCount()
{
  readFile();
  return m_saveList.size();
}
