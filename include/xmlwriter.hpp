/*
** xmlwriter.h for  in /home/louis/Documents/cpp_indie_studio/include
** 
** Made by louis
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Fri Jun 16 21:51:04 2017 louis
// Last update Fri Jun 16 21:53:21 2017 louis
*/

#ifndef XMLWRITTER_HPP
#define XMLWRITTER_HPP

#include	<iostream>
#include	<string>
#include	<vector>
#include	<stack>


typedef std::stack<std::string> StackStrings;


class xmlwriter
{
 public:
  xmlwriter(std::string sTmp);
  ~xmlwriter();
  void CreateChild(std::string sTag, std::string sValue);
  void Createtag(std::string sTag);
  void CloseLasttag();
  void CloseAlltags();
  void AddAtributes(std::string sAttrName, std::string sAttrvalue);
  void AddComment(std::string sComment);
 private:
  std::string sXmlFile;
  std::vector<std::string> vectAttrData;
  FILE *fp;
  int iLevel;
  StackStrings sTagStack;
};

#endif // xmlwriter_h


