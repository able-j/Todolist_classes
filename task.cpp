#include "task.hpp"

Task::Task(std::string task, int month, int day, int year)
{
  this->m_description = task;
  this->m_dueDate = (year * 10000) + (month * 100) + day;
  this->m_isFinished = false;
  this->m_isMissed = false;
}

Task::Task(std::string task, int dateInt, bool finished, bool missed)
{
  this->m_description = task;
  this->m_dueDate = dateInt;
  this->m_isFinished = finished;
  this->m_isMissed = missed;
}

bool Task::operator==(Task& task)
{
  return m_description == task.getDescription();
}

std::string Task::getDescription()
{
  return m_description;
}

int& Task::getDate()
{
  return m_dueDate;
}

bool Task::isFinished()
{
  return m_isFinished;
}

bool Task::isMissed()
{
  return m_isMissed;
}

void Task::finish()
{
  m_isFinished = true;
}

void Task::miss()
{
  m_isMissed = true;
}
