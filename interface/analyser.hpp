// <author>Cristóvão B da Cruz e Silva</author>
// <email>c.beirao@cern.ch</email>
// <date>2017-04-10</date>
// <summary>Implementation file for the templates from the Analyser class</summary>
//
// <description>
//  Implementation file with the definitions of the llvvAnalyser class and related classes.
//  The base analyser from which other analyses can be derived from is defined within.
// </description>

#ifndef MY_ANALYSER_HPP
#define MY_ANALYSER_HPP

template<class T>
void EventInfo::OutputValueListHeader(ofstream& file, const ValueWithSystematics<T>& val, const std::string& name) const
{
  std::string metadata = val.GetMetadata("eventlist");
  if(metadata == "true")
  {
    const std::string widthStr = val.GetMetadata("eventlistWidth");
    int width = 15;
    if(widthStr != "")
    {
      std::stringstream tmp;
      tmp << widthStr;
      tmp >> width;
      if(width <= 0)
        width = 15;
    }

    file << std::setw(width) << name << " | ";
  }

  return;
}

template<class T>
void EventInfo::OutputValueList(ofstream& file, const ValueWithSystematics<T>& val) const
{
  std::string metadata = val.GetMetadata("eventlist");
  if(metadata == "true")
  {
    const std::string widthStr = val.GetMetadata("eventlistWidth");
    int width = 15;
    if(widthStr != "")
    {
      std::stringstream tmp;
      tmp << widthStr;
      tmp >> width;
      if(width == 0)
        width = 15;
    }

    file << std::setw(width) << val.Value() << " | ";
  }

  return;
}

template<>
void EventInfo::OutputValueList(ofstream& file, const ValueWithSystematics<bool>& val) const
{
  std::string metadata = val.GetMetadata("eventlist");
  if(metadata == "true")
  {
    const std::string widthStr = val.GetMetadata("eventlistWidth");
    int width = 15;
    if(widthStr != "")
    {
      std::stringstream tmp;
      tmp << widthStr;
      tmp >> width;
      if(width == 0)
        width = 15;
    }

    file << std::setw(width) << (val.Value()?("True"):("False")) << " | ";
  }

  return;
}

template<class T>
void EventInfo::AddBranch(TTree* const tree, ValueWithSystematics<T>& val, std::string name)
{
  std::string metadata = val.GetMetadata("eventtree");
  if(metadata == "true" || metadata == "")
  {
    tree->Branch(name.c_str(), &(val.Value()));

    for(auto& syst: val.Systematics())
    {
      tree->Branch((name + "_" + syst).c_str(), &(val.Systematic(syst)));
    }
  }

  return;
}



template<class T>
void Analyser::loadSystematics(std::vector<std::string>& list, ValueWithSystematics<T> variable)
{
  for(auto& syst: variable.Systematics())
  {
    if(std::find(list.begin(), list.end(), syst) == list.end())
    {
      list.push_back(syst);
    }
  }

  return;
}

#endif


