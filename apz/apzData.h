#pragma once

#include "stdafx.h"
#include "apzStructs.h"
#include "apzUtilities.h"


namespace apz {

  // Immutable type that lets us pass raw data from multiple potential sources
  class Data {
  public:
    Data(const char *tFilePath);
    Data(char *tData, unsigned long tSize);
    ~Data();

    void copyAndAllocate(char **trData, unsigned long *trLen) const;
    void copy(char *trData, unsigned long *trLen, unsigned long tDataSize) const;

  private:
    char *m_data;
    unsigned long m_size;

  };
};