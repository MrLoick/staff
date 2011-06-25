/*
 *  Copyright 2009 Utkin Dmitry
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
/* 
 *  This file is part of the WSF Staff project.
 *  Please, visit http://code.google.com/p/staff for more information.
 */

#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

#include "staffcommonexport.h"
#include <string>

typedef struct axiom_attribute axiom_attribute_t;
typedef struct axutil_env axutil_env_t;

namespace staff
{
  class DataObject;
  class Value;
  class QName;

  //! Attribute
  class STAFF_COMMON_EXPORT Attribute
  {
  public:
    //!         constructor
    Attribute();

    //!         initializing constructor
    /*! \param  pDataObject - owner dataobject
        \param  pAxiomAttribute - axiom attribute
        */
    Attribute(DataObject* pDataObject, axiom_attribute_t* pAxiomAttribute);

    //!         ownership transfer operator
    /*! \param  rAttribute - attribute
        */
    Attribute(Attribute& rAttribute);

    //!         axiom_attribute_t* cast operator
    operator axiom_attribute_t*();

    //!         initializing constructor
    /*! \param  sLocalNameInit - local name
        \param  szValue - attribute value as text
        */
    explicit Attribute(const std::string& sLocalNameInit, const char* szValue);

    //!         initializing constructor
    /*! \param  sLocalNameInit - local name
        \param  sValue - attribute value as text
        */
    explicit Attribute(const std::string& sLocalNameInit, const std::string& sValue);

    //!         initializing constructor
    /*! \param  sLocalNameInit - local name
        \param  tValue - attribute value
        */
    Attribute(const std::string& sLocalNameInit, const Value& tValue);

    //!         destructor
    ~Attribute();

    //!         get ownership flag
    /*! \return true - if ownership flag set
        */
    bool IsOwner() const;

    //!         set ownership flag
    /*! \param  bOwner - ownership flag
        */
    void SetOwner(bool bOwner);

    //!         get local name
    /*! \return local name
    */
    std::string GetLocalName() const;

    //!         set local name
    /*! \param  sLocalName - local name
    */
    void SetLocalName(const std::string& sLocalName);

    //!         get attribute value as string
    /*! \return text
    */
    std::string GetText() const;

    //!         set attribute value as string
    /*! \param sText - text
    */
    void SetText(const std::string& sText);

    //!         get attribute value
    /*! \return value
    */
    Value GetValue() const;

    //!         set attribute value
    /*! \param  tValue - value
    */
    void SetValue(const Value& rValue);

    //!         get qname
    /*! \return qname
    */
    const QName GetQName() const;

    //!         get qname
    /*! \return qname
    */
    QName GetQName();

    //!         ownership transfer operation
    /*! \param  rAttribute - source attribute
        \return *this
        */
    Attribute& operator=(Attribute& rAttribute);

    //!         tests a target attribute for equality with a specified attribute
    /*! \param  rAttribute - attribute
        \return true if the attributes are equal
        */
    bool operator==(const Attribute& rAttribute) const;

    //!         tests a target attribute for inequality with a specified attribute
    /*! \param  rAttribute - attribute
        \return true if the attributes are different
        */
    bool operator!=(const Attribute& rAttribute) const;

    //!         member access operator
    /*! \return this
    */
    Attribute* operator->();
    
    //!         member access operator
    /*! \return this
    */
    const Attribute* operator->() const;

  private:
    bool m_bOwner; //!<  ownership flag
    DataObject* m_pDataObject; //!<  owner dataobject
    axiom_attribute_t* m_pAxiomAttribute; //!<  axiom attribute
    static axutil_env_t* m_pEnv; //!<  Axis2/C environment
  };

#ifndef STAFF_NO_DEPRECATED
  typedef Attribute CAttribute STAFF_DEPRECATED(Attribute);
#endif
} // namespace staff

#endif // _ATTRIBUTE_H_
