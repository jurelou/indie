//
// xmlwriter.cpp for  in /home/louis/Documents/cpp_indie_studio/wmlwriter_src
// 
// Made by louis
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Fri Jun 16 21:48:24 2017 louis
// Last update Fri Jun 16 21:54:02 2017 louis
//

#include	"xmlwriter.hpp"
#include	<stdarg.h>

xmlwriter::xmlwriter(std::string sTmp)
{
  sXmlFile = sTmp;
  fp = NULL;
  iLevel = 0;
  fp = fopen(sXmlFile.c_str(),"w");

  if (fp == NULL)
    {
      std::cout<<"Unable to open output file";
      return;
    }
  else
    fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\" \?>");
}

xmlwriter::~xmlwriter()
{
  if (fp != NULL)
    fclose(fp);
  vectAttrData.clear();
}


void		xmlwriter::Createtag(std::string sTag)
{
  fprintf(fp,"\n");
  for (int iTmp =0;iTmp<iLevel;iTmp++)
    fprintf(fp,"\t");
  fprintf(fp,"<%s",sTag.c_str());
  while (0 < vectAttrData.size()/2)
    {
      std::string sTmp = vectAttrData.back();
      fprintf(fp," %s=", sTmp.c_str());
      vectAttrData.pop_back();
      sTmp = vectAttrData.back();
      fprintf(fp,"\"%s\"", sTmp.c_str());
      vectAttrData.pop_back();
    }
  vectAttrData.clear();
  fprintf(fp,">");
  sTagStack.push(sTag);
  iLevel++; 
}

void		xmlwriter::CloseLasttag()
{
  fprintf(fp,"\n");
  iLevel--;
  for (int iTmp =0;iTmp<iLevel;iTmp++)
    fprintf(fp,"\t");
  fprintf(fp,"</%s>",sTagStack.top().c_str());
  sTagStack.pop();
  return;
}

void		xmlwriter::CloseAlltags()
{
  while (sTagStack.size() != 0)
    {
      fprintf(fp,"\n");
      iLevel--;
      for (int iTmp =0;iTmp<iLevel;iTmp++)
	fprintf(fp,"\t");
      fprintf(fp,"</%s>",sTagStack.top().c_str());
      sTagStack.pop();
    }
  return;
}

void		xmlwriter::CreateChild(std::string sTag,std::string sValue)
{
  fprintf(fp,"\n");
  for (int iTmp =0;iTmp<iLevel;iTmp++)
    fprintf(fp,"\t");
  fprintf(fp,"<%s",sTag.c_str());
  while (0 < vectAttrData.size()/2)
    {
      std::string sTmp = vectAttrData.back();
      fprintf(fp," %s=", sTmp.c_str());
      vectAttrData.pop_back();
      sTmp = vectAttrData.back();
      fprintf(fp,"\"%s\"", sTmp.c_str());
      vectAttrData.pop_back();
    }
  vectAttrData.clear();
  fprintf(fp,">%s</%s>",sValue.c_str(),sTag.c_str());
}

void		xmlwriter::AddAtributes(std::string sKey, std::string sVal)
{
  vectAttrData.push_back(sVal);
  vectAttrData.push_back(sKey);
}


void		xmlwriter::AddComment(std::string sComment)
{
  fprintf(fp,"\n");
  for (int iTmp =0;iTmp<iLevel;iTmp++)
    fprintf(fp,"\t");
  fprintf(fp,"<!--%s-->",sComment.c_str());
}
