#include "stdafx.h"
#include "apzData.h"

using namespace apz;

Data::Data(const char *tFilePath) {

  std::ifstream File(tFilePath, std::ios_base::binary | std::ios_base::in);

  if(!File.good()){
    CRITICAL_ERROR("No such file exists!");
  }

  File.seekg(0, std::ios_base::end);
  unsigned long pos = File.tellg();
  File.seekg(0, std::ios_base::beg);

  m_size = pos;
  m_data = new char[m_size];

  File.read(m_data, m_size);

  File.close();
}

Data::Data(char *tData, unsigned long tSize) {
  m_size = tSize;
  m_data = new char[m_size];

  memcpy((void *)m_data, (void *)tData, m_size);
}

Data::~Data() {
  delete m_data;
}


void Data::copyAndAllocate(char **trData, unsigned long *trLen) const {
  *trLen = m_size;
  *trData = new char[m_size];

  memcpy(*trData, m_data, m_size);
}

void Data::copy(char *trData, unsigned long *trLen, unsigned long tDataSize) const {
  if(tDataSize > m_size) tDataSize = m_size;

  *trLen = tDataSize;
  memcpy(trData, m_data, tDataSize);
}
