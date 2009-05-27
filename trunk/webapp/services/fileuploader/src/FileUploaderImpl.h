// This file generated by staff_codegen
// Service Implementation

#ifndef _FileUploaderImpl_h_
#define _FileUploaderImpl_h_

#include <map>
#include <rise/process/Process.h>
#include "FileUnpacker.h"
#include "FileUploader.h"

namespace webapp
{
  class CFileUploaderImpl: public CFileUploader
  {
  public:
    CFileUploaderImpl();
    virtual ~CFileUploaderImpl();
    virtual void Move(const std::string& sFileName, const std::string& sPathTo);
    virtual void Unpack(const std::string& sFileName, const std::string& sPathTo);
    virtual int GetUnpackingStatus();
    virtual TStringList GetUnpackedFiles(const std::string& sMask);
    virtual void Delete(const std::string& sFileName);

  private:
    void GetUnpackedFiles(const std::string& sMask, TStringList& rFiles, const std::string& sRelativeDir = "");

  private:
    static const std::string m_sUploadDir;
    typedef std::map<std::string, std::string> TStringMap;
    static TStringMap m_mUnpackers;
    std::string m_sLastSaveToDir;
    CFileUnpacker m_tUnpacker;
  };
}


#endif // _FileUploaderImpl_h_
