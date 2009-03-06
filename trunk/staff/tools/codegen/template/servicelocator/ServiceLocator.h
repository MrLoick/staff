// This file generated by staff_codegen
// DO NOT EDIT

#ifndef _SERVICELOCATOR_H_
#define _SERVICELOCATOR_H_

#include <rise/string/String.h>

namespace staff
{
  //!  класс для получения обьекта для работы с сервисом по имени
  class CServiceLocator
  {
  public:
    //!         получить ссылку на обьект локатора
    /*! \return ссылка на обьект локатора
    */
    static CServiceLocator& Inst();
    
    //!         получить указатель на обьект для работы с сервисом
    /*! \param  sServiceName - имя сервиса
        \param  sID - идентификатор
        */
    void* LocateService(const rise::CString& sServiceName, const rise::CString& sID);

  protected:
    //!        конструктор по умолчанию
    CServiceLocator();
    
    //!        деструктор
    ~CServiceLocator();
  
  private:
    class CServiceLocatorImpl;
    CServiceLocatorImpl* m_pImpl;
    static CServiceLocator* m_pInst;
  };
}

#endif // _SERVICELOCATOR_H_