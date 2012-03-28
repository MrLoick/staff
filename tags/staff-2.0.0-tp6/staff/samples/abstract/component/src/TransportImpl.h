// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#ifndef _TransportImpl_h_
#define _TransportImpl_h_

#include "Transport.h"

namespace samples
{
namespace abstract
{

  //! implementation of Transport
  class TransportImpl: public Transport
  {
  public:
    TransportImpl();
    virtual ~TransportImpl();
    virtual void OnCreate();
    virtual void OnDestroy();
    virtual TransportInfo GetTransport(TransportType eTransport);
    virtual staff::Abstract<Vehicle> Echo(const staff::Abstract<Vehicle>& rtpVehicle);
  };
}
}


#endif // _TransportImpl_h_