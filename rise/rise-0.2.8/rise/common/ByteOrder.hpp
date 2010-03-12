#ifndef _BYTEORDER_HPP_
#define _BYTEORDER_HPP_

#include <rise/common/ExceptionTemplate.h>
#include <rise/string/String.h>

namespace rise
{
//   template<typename TDATA>
//   TDATA CByteOrder::SwapBytesN(TDATA tData)  // VC++ 2005 не находит символы при линковке
//   {                                     // если поместить реализацию в hpp файл
//     TDATA tDataRet; 
//     byte uchSize = sizeof(tData);
//     const byte* pSrc = reinterpret_cast<const byte*>(&tData);
//     byte* pDst = reinterpret_cast<byte*>(&tDataRet) + uchSize - 1;
//     while(uchSize-- != 0)
//       *pDst-- = *pSrc++;
//     return tDataRet;
//   }

  //////////////////////////////////////////////////////////////////////////////
  //    FUNCTION:       ToBigEndian
  //    DESCRIPTION:    преобразование кодировки в BigEndian
  //    PARAMETRS:      tData - данные для преобразования
  //    RETURN:         преобразованные данные
  //    EXCEPTIONS:     none
  //    COMMENT:        none
  //////////////////////////////////////////////////////////////////////////////
  template<typename TDATA>
  TDATA CByteOrder::ToBigEndian( const TDATA& tData )
  {
    return 
#if (__BYTE_ORDER == __BIG_ENDIAN) // MIPS
      tData;
#elif (__BYTE_ORDER == __LITTLE_ENDIAN) // Intel
      SwapBytes(tData);
#else
#error "UNKNOWN __BYTE_ORDER" __LINE__ " " __FILE__
#endif
  }

  //////////////////////////////////////////////////////////////////////////////
  //    FUNCTION:       ToLittleEndian
  //    DESCRIPTION:    преобразование кодировки в LittleEndian
  //    PARAMETRS:      tData - данные для преобразования
  //    RETURN:         преобразованные данные
  //    EXCEPTIONS:     none
  //    COMMENT:        none
  //////////////////////////////////////////////////////////////////////////////
  template<typename TDATA>
  TDATA CByteOrder::ToLittleEndian( const TDATA& tData )
  {
    return 
#if (__BYTE_ORDER == __BIG_ENDIAN) // MIPS
      SwapBytes(tData);
#elif (__BYTE_ORDER == __LITTLE_ENDIAN) // Intel
      tData;
#else
#error "UNKNOWN __BYTE_ORDER" __LINE__ " " __FILE__
#endif
  }

  //////////////////////////////////////////////////////////////////////////////
  //    FUNCTION:       ToByteOrder
  //    DESCRIPTION:    преобразование кодировки в указанную
  //    PARAMETRS:      tData - данные для преобразования
  //                    eByteOrder - кодировка
  //    RETURN:         преобразованные данные
  //    EXCEPTIONS:     none
  //    COMMENT:        none
  //////////////////////////////////////////////////////////////////////////////
  template<typename TDATA>
  TDATA CByteOrder::ToByteOrder( const TDATA& tData, CByteOrder::EByteOrder eByteOrder )
  {
    switch(eByteOrder)
    {
    case EBO_BIG_ENDIAN:
      return ToBigEndian(tData);
    case EBO_LITTLE_ENDIAN:
      return ToLittleEndian(tData);
    default:
      RISE_THROWS(CLogicFormatException, "Неизвестный порядок байт: " + rise::ToStr(eByteOrder));
    }
  }

} // namespace rise

#endif // _BYTEORDER_HPP_
