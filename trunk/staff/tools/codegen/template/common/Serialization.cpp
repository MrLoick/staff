namespace staff
{
#ifneq($(Interface.Enums.$Count),0)
///////////////////////////////////////////////////////////////////////////////////////////////////////
// enums
#foreach $(Interface.Enums)
#ifeq($(Enum.Extern),0) // do not serialize extern type
#cginclude "EnumSerialization.cpp"
#ifeqend
#end

#ifeqend // enums
#ifneq($(Interface.Structs.$Count),0)
///////////////////////////////////////////////////////////////////////////////////////////////////////
// struct serializators/deserializators
#foreach $(Interface.Structs)
#cginclude "StructSerialization.cpp"
#end

#ifeqend
#ifneq($(Interface.Typedefs.$Count),0)
///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef serializators
#foreach $(Interface.Typedefs)
#ifeq($(Typedef.Extern),0) // do not serialize extern type

DataObject& SerializeTypedef_$(Typedef.NsName.!mangle)(DataObject& rdoParam, const $(Typedef.NsName)& rtType)
{
#var bUseParentElement $(Typedef.Options.*useParentElement)
#context $(Typedef.DataType)
#var sParam rtType
#var sdoParam rdoParam
#cginclude "TypeSerialization.cpp"
#contextend
  return rdoParam;
}

#ifeqend //ifeq($(Typedef.Extern),0) // do not serialize extern type
#end // foreach $(Interface.Structs)
#ifeqend

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef deserializators
#foreach $(Interface.Typedefs)
#ifeq($(Typedef.Extern),0)
const DataObject& DeserializeTypedef_$(Typedef.NsName.!mangle)\
(const DataObject& rdoParam, $(Typedef.NsName)& rtType)
{
#var bUseParentElement $(Typedef.Options.*useParentElement)
#context $(Typedef.DataType)
#var sParam rtType
#var sdoParam rdoParam
#cginclude "TypeDeserialization.cpp"
#contextend
  return rdoParam;
}

#ifeqend // ifeq($(Typedef.Extern),0) // do not serialize extern type
#end
}
