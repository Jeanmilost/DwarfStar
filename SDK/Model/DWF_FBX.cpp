/****************************************************************************
 * ==> DWF_FBX -------------------------------------------------------------*
 ****************************************************************************
 * Description: Filmbox .fbx model                                          *
 * Developer:   Jean-Milost Reymond                                         *
 ****************************************************************************
 * MIT License - DwarfStar Game Engine                                      *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

#include "DWF_FBX.h"

// std
#include <algorithm>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <sstream>

// classes
#include "DWF_StdFileBuffer.h"

using namespace DWF_Model;

//---------------------------------------------------------------------------
// FBX::IFBXData
//---------------------------------------------------------------------------
FBX::IFBXData::IFBXData(const std::string* pData) :
    m_pData(pData)
{}
//---------------------------------------------------------------------------
FBX::IFBXData::IFBXData(IEDataType type, const std::string* pData, std::size_t start, std::size_t end) :
    m_Type(type),
    m_pData(pData),
    m_Start(start),
    m_End(end)
{}
//---------------------------------------------------------------------------
std::string FBX::IFBXData::GetRaw() const
{
    if (!m_pData)
        return "";

    const std::size_t length = m_pData->length();

    if (!length)
        return "";

    const std::size_t start = std::min(m_Start, length - 1);
    const std::size_t end   = std::min(m_End,   length - 1);

    if (start > end)
        return "";

    return m_pData->substr(start, end - start);
}
//---------------------------------------------------------------------------
bool FBX::IFBXData::GetBool() const
{
    // get raw value
    const std::string str = GetRaw();

    // found it?
    if (str.empty())
        return false;

    // convert raw data to boolean
    return IFBXHelper::StrToBool(str);
}
//---------------------------------------------------------------------------
std::int32_t FBX::IFBXData::GetInt() const
{
    // contains an integer value?
    if (m_Type != IEDataType::IE_DT_Int)
        return 0;

    // get raw value
    std::string str = GetRaw();

    // found it?
    if (str.empty())
        return 0;

    // is a counter?
    if (str[0] == '*')
    {
        // remove the counter marker from string
        str = str.substr(1, str.length() - 1);

        // still not empty?
        if (str.empty())
            return 0;

        // mark the value as a counter
        m_IsCounter = true;
    }

    // convert raw data to integer
    std::int32_t value;
    std::istringstream sstr(str);
    sstr >> value;

    // full string must be converted for success
    if (sstr.rdstate() == std::ios_base::eofbit)
        return value;

    return 0;
}
//---------------------------------------------------------------------------
std::int64_t FBX::IFBXData::GetLongLong() const
{
    // get raw value
    const std::string str = GetRaw();

    // found it?
    if (str.empty())
        return 0L;

    // convert raw data to long long
    std::int64_t value;
    std::istringstream sstr(str);
    sstr >> value;

    // full string must be converted for success
    if (sstr.rdstate() == std::ios_base::eofbit)
        return value;

    return 0L;
}
//---------------------------------------------------------------------------
float FBX::IFBXData::GetFloat() const
{
    // contains a floating point value?
    if (m_Type != IEDataType::IE_DT_Float)
        return 0.0f;

    // get raw value
    const std::string str = GetRaw();

    // found it?
    if (str.empty())
        return 0.0f;

    // convert raw data to float
    float value;
    std::istringstream sstr(str);
    sstr >> value;

    // full string must be converted for success
    if (sstr.rdstate() == std::ios_base::eofbit)
        return value;

    return 0.0f;
}
//---------------------------------------------------------------------------
double FBX::IFBXData::GetDouble() const
{
    // contains a floating point value?
    if (m_Type != IEDataType::IE_DT_Float)
        return 0.0;

    // get raw value
    const std::string str = GetRaw();

    // found it?
    if (str.empty())
        return 0.0;

    // convert raw data to double
    double value;
    std::istringstream sstr(str);
    sstr >> value;

    // full string must be converted for success
    if (sstr.rdstate() == std::ios_base::eofbit)
        return value;

    return 0.0;
}
//---------------------------------------------------------------------------
std::string FBX::IFBXData::GetStr() const
{
    // contains a string value?
    if (m_Type != IEDataType::IE_DT_String)
        return "";

    return GetRaw();
}
//---------------------------------------------------------------------------
// FBX::IFBXItem
//---------------------------------------------------------------------------
FBX::IFBXItem::IFBXItem()
{}
//---------------------------------------------------------------------------
FBX::IFBXItem::~IFBXItem()
{
    for (IFBXDataset::iterator it = m_Values.begin(); it != m_Values.end(); ++it)
        delete (*it);
}
//---------------------------------------------------------------------------
void FBX::IFBXItem::SetName(const std::string& name)
{
    m_Name = name;
}
//---------------------------------------------------------------------------
std::string FBX::IFBXItem::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void FBX::IFBXItem::SetParent(IFBXItem* pParent)
{
    m_pParent = pParent;
}
//---------------------------------------------------------------------------
FBX::IFBXItem* FBX::IFBXItem::GetParent() const
{
    return m_pParent;
}
//---------------------------------------------------------------------------
void FBX::IFBXItem::AddValue(IFBXData* pValue)
{
    if (!pValue)
        return;

    m_Values.push_back(pValue);
}
//---------------------------------------------------------------------------
FBX::IFBXData* FBX::IFBXItem::GetValue(std::size_t index) const
{
    if (index >= m_Values.size())
        return nullptr;

    return m_Values[index];
}
//---------------------------------------------------------------------------
std::size_t FBX::IFBXItem::GetValueCount() const
{
    return m_Values.size();
}
//---------------------------------------------------------------------------
// FBX::IFBXProperty
//---------------------------------------------------------------------------
FBX::IFBXProperty::IFBXProperty(IEPropType propType) :
    IFBXItem(),
    m_PropType(propType)
{}
//---------------------------------------------------------------------------
FBX::IFBXProperty::~IFBXProperty()
{}
//---------------------------------------------------------------------------
std::string FBX::IFBXProperty::GetPropName() const
{
    // is prop name already cached?
    if (m_PropName.empty())
    {
        // no available value?
        if (!GetValueCount())
            return "";

        // force the const constraint just this time to cache the property name
        m_PropName = GetValue(0)->GetRaw();
    }

    return m_PropName;
}
//---------------------------------------------------------------------------
FBX::IEPropType FBX::IFBXProperty::GetType() const
{
    return m_PropType;
}
//---------------------------------------------------------------------------
// FBX::IFBXUnknownProperty
//---------------------------------------------------------------------------
FBX::IFBXUnknownProperty::IFBXUnknownProperty() :
    IFBXProperty(IEPropType::IE_PT_Unknown)
{}
//---------------------------------------------------------------------------
FBX::IFBXUnknownProperty::~IFBXUnknownProperty()
{}
//---------------------------------------------------------------------------
// FBX::IFBXBoolProperty
//---------------------------------------------------------------------------
FBX::IFBXBoolProperty::IFBXBoolProperty() :
    IFBXProperty(IEPropType::IE_PT_Bool)
{}
//---------------------------------------------------------------------------
FBX::IFBXBoolProperty::~IFBXBoolProperty()
{}
//---------------------------------------------------------------------------
bool FBX::IFBXBoolProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return false;

    // already cached?
    if (m_Cached)
        return m_Value;

    // convert raw data to boolean and cache it
    m_Value  = GetValue(4)->GetBool();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXIntProperty
//---------------------------------------------------------------------------
FBX::IFBXIntProperty::IFBXIntProperty() :
    IFBXProperty(IEPropType::IE_PT_Int)
{}
//---------------------------------------------------------------------------
FBX::IFBXIntProperty::~IFBXIntProperty()
{}
//---------------------------------------------------------------------------
std::int32_t FBX::IFBXIntProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return 0;

    // already cached?
    if (m_Cached)
        return m_Value;

    // cache value
    m_Value  = GetValue(4)->GetInt();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXDoubleProperty
//---------------------------------------------------------------------------
FBX::IFBXDoubleProperty::IFBXDoubleProperty() :
    IFBXProperty(IEPropType::IE_PT_Double)
{}
//---------------------------------------------------------------------------
FBX::IFBXDoubleProperty::~IFBXDoubleProperty()
{}
//---------------------------------------------------------------------------
double FBX::IFBXDoubleProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return 0.0;

    // already cached?
    if (m_Cached)
        return m_Value;

    // cache value
    m_Value  = GetValue(4)->GetDouble();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXLongLongProperty
//---------------------------------------------------------------------------
FBX::IFBXLongLongProperty::IFBXLongLongProperty() :
    IFBXProperty(IEPropType::IE_PT_ULongLong)
{}
//---------------------------------------------------------------------------
FBX::IFBXLongLongProperty::~IFBXLongLongProperty()
{}
//---------------------------------------------------------------------------
std::int64_t FBX::IFBXLongLongProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return 0L;

    // already cached?
    if (m_Cached)
        return m_Value;

    // cache value
    m_Value  = GetValue(4)->GetLongLong();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXStringProperty
//---------------------------------------------------------------------------
FBX::IFBXStringProperty::IFBXStringProperty() :
    IFBXProperty(IEPropType::IE_PT_String)
{}
//---------------------------------------------------------------------------
FBX::IFBXStringProperty::~IFBXStringProperty()
{}
//---------------------------------------------------------------------------
std::string FBX::IFBXStringProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return "";

    // already cached?
    if (m_Cached)
        return m_Value;

    // convert raw data to string and cache it
    m_Value  = GetValue(4)->GetRaw();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXNumberProperty
//---------------------------------------------------------------------------
FBX::IFBXNumberProperty::IFBXNumberProperty() :
    IFBXProperty(IEPropType::IE_PT_Number)
{}
//---------------------------------------------------------------------------
FBX::IFBXNumberProperty::~IFBXNumberProperty()
{}
//---------------------------------------------------------------------------
double FBX::IFBXNumberProperty::Get(std::size_t index) const
{
    // already cached?
    if (!m_Cached)
        GetValues();

    // is index out of bounds?
    if (index >= m_Values.size())
        return 0.0;

    return m_Values[index];
}
//---------------------------------------------------------------------------
std::size_t FBX::IFBXNumberProperty::GetCount() const
{
    // already cached?
    if (!m_Cached)
        GetValues();

    return m_Values.size();
}
//---------------------------------------------------------------------------
void FBX::IFBXNumberProperty::GetValues() const
{
    // already cached?
    if (m_Cached)
        return;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return;

    // read and cache values
    for (std::size_t i = 4; i < count; ++i)
        m_Values.push_back(GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetDouble());

    m_Cached = true;
}
//---------------------------------------------------------------------------
// FBX::IFBXColorProperty
//---------------------------------------------------------------------------
FBX::IFBXColorProperty::IFBXColorProperty() :
    IFBXProperty(IEPropType::IE_PT_Color)
{}
//---------------------------------------------------------------------------
FBX::IFBXColorProperty::~IFBXColorProperty()
{}
//---------------------------------------------------------------------------
ColorF FBX::IFBXColorProperty::Get() const
{
    // already cached?
    if (m_Cached)
        return m_Value;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return ColorF();

    // read and cache color components
    for (std::size_t i = 4; i < count; ++i)
        switch (i)
        {
            case 4: m_Value.m_R = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 5: m_Value.m_G = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 6: m_Value.m_B = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
        }

    m_Value.m_A = 1.0f;
    m_Cached    = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXColorRGBProperty
//---------------------------------------------------------------------------
FBX::IFBXColorRGBProperty::IFBXColorRGBProperty() :
    IFBXProperty(IEPropType::IE_PT_ColorRGB)
{}
//---------------------------------------------------------------------------
FBX::IFBXColorRGBProperty::~IFBXColorRGBProperty()
{}
//---------------------------------------------------------------------------
ColorF FBX::IFBXColorRGBProperty::Get() const
{
    // already cached?
    if (m_Cached)
        return m_Value;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return ColorF();

    // read and cache color components
    for (std::size_t i = 4; i < count; ++i)
        switch (i)
        {
            case 4: m_Value.m_R = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 5: m_Value.m_G = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 6: m_Value.m_B = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
        }

    m_Value.m_A = 1.0f;
    m_Cached    = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXVectorProperty
//---------------------------------------------------------------------------
FBX::IFBXVectorProperty::IFBXVectorProperty() :
    IFBXProperty(IEPropType::IE_PT_Vector)
{}
//---------------------------------------------------------------------------
FBX::IFBXVectorProperty::~IFBXVectorProperty()
{}
//---------------------------------------------------------------------------
DWF_Math::Vector3F FBX::IFBXVectorProperty::Get() const
{
    // already cached?
    if (m_Cached)
        return m_Value;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return DWF_Math::Vector3F();

    // read and cache vector components
    for (std::size_t i = 4; i < count; ++i)
        switch (i)
        {
            case 4: m_Value.m_X = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 5: m_Value.m_Y = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 6: m_Value.m_Z = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
        }

    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXVector3DProperty
//---------------------------------------------------------------------------
FBX::IFBXVector3DProperty::IFBXVector3DProperty() :
    IFBXProperty(IEPropType::IE_PT_Vector3D)
{}
//---------------------------------------------------------------------------
FBX::IFBXVector3DProperty::~IFBXVector3DProperty()
{}
//---------------------------------------------------------------------------
DWF_Math::Vector3F FBX::IFBXVector3DProperty::Get() const
{
    // already cached?
    if (m_Cached)
        return m_Value;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return DWF_Math::Vector3F();

    // read and cache vector components
    for (std::size_t i = 4; i < count; ++i)
        switch (i)
        {
            case 4: m_Value.m_X = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 5: m_Value.m_Y = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 6: m_Value.m_Z = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
        }

    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXTimeProperty
//---------------------------------------------------------------------------
FBX::IFBXTimeProperty::IFBXTimeProperty() :
    IFBXProperty(IEPropType::IE_PT_Time)
{}
//---------------------------------------------------------------------------
FBX::IFBXTimeProperty::~IFBXTimeProperty()
{}
//---------------------------------------------------------------------------
std::time_t FBX::IFBXTimeProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return 0;

    // already cached?
    if (m_Cached)
        return m_Value;

    // get raw value
    const std::string str = GetValue(4)->GetRaw();

    // found it?
    if (str.empty())
        return 0;

    // convert raw data to time_t
    std::time_t value;
    std::istringstream sstr(str);
    sstr >> value;

    // full string must be converted for success
    if (sstr.rdstate() == std::ios_base::eofbit)
    {
        // cache value
        m_Value  = value;
        m_Cached = true;

        return m_Value;
    }

    return 0;
}
//---------------------------------------------------------------------------
// FBX::IFBXDateTimeProperty
//---------------------------------------------------------------------------
FBX::IFBXDateTimeProperty::IFBXDateTimeProperty() :
    IFBXProperty(IEPropType::IE_PT_DateTime)
{}
//---------------------------------------------------------------------------
FBX::IFBXDateTimeProperty::~IFBXDateTimeProperty()
{}
//---------------------------------------------------------------------------
std::string FBX::IFBXDateTimeProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return "";

    // already cached?
    if (m_Cached)
        return m_Value;

    // convert raw data to string and cache it
    m_Value  = GetValue(4)->GetRaw();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXEnumProperty
//---------------------------------------------------------------------------
FBX::IFBXEnumProperty::IFBXEnumProperty() :
    IFBXProperty(IEPropType::IE_PT_Enum)
{}
//---------------------------------------------------------------------------
FBX::IFBXEnumProperty::~IFBXEnumProperty()
{}
//---------------------------------------------------------------------------
std::int32_t FBX::IFBXEnumProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return 0;

    // already cached?
    if (m_Cached)
        return m_Value;

    // cache value
    m_Value  = GetValue(4)->GetInt();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXLclTranslationProperty
//---------------------------------------------------------------------------
FBX::IFBXLclTranslationProperty::IFBXLclTranslationProperty() :
    IFBXProperty(IEPropType::IE_PT_LclTranslation)
{}
//---------------------------------------------------------------------------
FBX::IFBXLclTranslationProperty::~IFBXLclTranslationProperty()
{}
//---------------------------------------------------------------------------
DWF_Math::Vector3F FBX::IFBXLclTranslationProperty::Get() const
{
    // already cached?
    if (m_Cached)
        return m_Value;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return DWF_Math::Vector3F();

    // read and cache vector components
    for (std::size_t i = 4; i < count; ++i)
        switch (i)
        {
            case 4: m_Value.m_X = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 5: m_Value.m_Y = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 6: m_Value.m_Z = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
        }

    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXLclRotationProperty
//---------------------------------------------------------------------------
FBX::IFBXLclRotationProperty::IFBXLclRotationProperty() :
    IFBXProperty(IEPropType::IE_PT_LclRotation)
{}
//---------------------------------------------------------------------------
FBX::IFBXLclRotationProperty::~IFBXLclRotationProperty()
{}
//---------------------------------------------------------------------------
DWF_Math::QuaternionF FBX::IFBXLclRotationProperty::Get() const
{
    // already cached?
    if (m_Cached)
        return m_Value;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return DWF_Math::QuaternionF();

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    // read quaternion components
    for (std::size_t i = 4; i < count; ++i)
        switch (i)
        {
            case 4: x = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 5: y = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 6: z = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
        }

    const float degToRad = (float)(M_PI / 180.0f);

    DWF_Math::QuaternionF qx;
    DWF_Math::QuaternionF qy;
    DWF_Math::QuaternionF qz;

    // calculate quaternion based on the x, y and z Euler angles
    qx.FromAxis(-x * degToRad, DWF_Math::Vector3F(1.0f, 0.0f, 0.0f));
    qy.FromAxis(-y * degToRad, DWF_Math::Vector3F(0.0f, 1.0f, 0.0f));
    qz.FromAxis(-z * degToRad, DWF_Math::Vector3F(0.0f, 0.0f, 1.0f));

    // build the final rotation matrix and cache it
    m_Value  = qx.Multiply(qy).Multiply(qz).Normalize();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXLclScalingProperty
//---------------------------------------------------------------------------
FBX::IFBXLclScalingProperty::IFBXLclScalingProperty() :
    IFBXProperty(IEPropType::IE_PT_LclScaling)
{}
//---------------------------------------------------------------------------
FBX::IFBXLclScalingProperty::~IFBXLclScalingProperty()
{}
//---------------------------------------------------------------------------
DWF_Math::Vector3F FBX::IFBXLclScalingProperty::Get() const
{
    // already cached?
    if (m_Cached)
        return m_Value;

    const std::size_t count = GetValueCount();

    // no available value?
    if (count <= 4)
        return DWF_Math::Vector3F(1.0f, 1.0f, 1.0f);

    // read and cache vector components
    for (std::size_t i = 4; i < count; ++i)
        switch (i)
        {
            case 4: m_Value.m_X = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 5: m_Value.m_Y = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
            case 6: m_Value.m_Z = GetValue(i)->m_Type == IEDataType::IE_DT_Int ? (float)GetValue(i)->GetInt() : GetValue(i)->GetFloat(); continue;
        }

    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXVisibilityProperty
//---------------------------------------------------------------------------
FBX::IFBXVisibilityProperty::IFBXVisibilityProperty() :
    IFBXProperty(IEPropType::IE_PT_Visibility)
{}
//---------------------------------------------------------------------------
FBX::IFBXVisibilityProperty::~IFBXVisibilityProperty()
{}
//---------------------------------------------------------------------------
bool FBX::IFBXVisibilityProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return false;

    // already cached?
    if (m_Cached)
        return m_Value;

    // convert raw data to boolean and cache it
    m_Value  = GetValue(4)->GetBool();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXVisibilityInheritanceProperty
//---------------------------------------------------------------------------
FBX::IFBXVisibilityInheritanceProperty::IFBXVisibilityInheritanceProperty() :
    IFBXProperty(IEPropType::IE_PT_VisibilityInheritance)
{}
//---------------------------------------------------------------------------
FBX::IFBXVisibilityInheritanceProperty::~IFBXVisibilityInheritanceProperty()
{}
//---------------------------------------------------------------------------
bool FBX::IFBXVisibilityInheritanceProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return false;

    // already cached?
    if (m_Cached)
        return m_Value;

    // get raw value
    const std::string str = GetValue(4)->GetRaw();

    // found it?
    if (str.empty())
        return false;

    // convert raw data to boolean and cache it
    m_Value  = IFBXHelper::StrToBool(str);
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXCompoundProperty
//---------------------------------------------------------------------------
FBX::IFBXCompoundProperty::IFBXCompoundProperty() :
    IFBXProperty(IEPropType::IE_PT_Compound)
{}
//---------------------------------------------------------------------------
FBX::IFBXCompoundProperty::~IFBXCompoundProperty()
{}
//---------------------------------------------------------------------------
std::string FBX::IFBXCompoundProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return "";

    // already cached?
    if (m_Cached)
        return m_Value;

    // convert raw data to boolean and cache it
    m_Value  = GetValue(4)->GetRaw();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXObjectProperty
//---------------------------------------------------------------------------
FBX::IFBXObjectProperty::IFBXObjectProperty() :
    IFBXProperty(IEPropType::IE_PT_Object)
{}
//---------------------------------------------------------------------------
FBX::IFBXObjectProperty::~IFBXObjectProperty()
{}
//---------------------------------------------------------------------------
std::string FBX::IFBXObjectProperty::Get() const
{
    // no available value?
    if (GetValueCount() <= 4)
        return "";

    // already cached?
    if (m_Cached)
        return m_Value;

    // convert raw data to boolean and cache it
    m_Value  = GetValue(4)->GetRaw();
    m_Cached = true;

    return m_Value;
}
//---------------------------------------------------------------------------
// FBX::IFBXNode
//---------------------------------------------------------------------------
FBX::IFBXNode::IFBXNode() :
    IFBXItem()
{}
//---------------------------------------------------------------------------
FBX::IFBXNode::~IFBXNode()
{
    for (IFBXItems::iterator it = m_Props.begin(); it != m_Props.end(); ++it)
        delete (*it);

    for (IFBXItems::iterator it = m_Children.begin(); it != m_Children.end(); ++it)
        delete (*it);
}
//---------------------------------------------------------------------------
void FBX::IFBXNode::AddProp(IFBXProperty* pProp)
{
    if (!pProp)
        return;

    m_Props.push_back(pProp);
}
//---------------------------------------------------------------------------
FBX::IFBXProperty* FBX::IFBXNode::GetProp(std::size_t index) const
{
    if (index >= m_Props.size())
        return nullptr;

    return static_cast<IFBXProperty*>(m_Props[index]);
}
//---------------------------------------------------------------------------
std::size_t FBX::IFBXNode::GetPropCount() const
{
    return m_Props.size();
}
//---------------------------------------------------------------------------
void FBX::IFBXNode::AddChild(IFBXNode* pChild)
{
    if (!pChild)
        return;

    m_Children.push_back(pChild);
}
//---------------------------------------------------------------------------
FBX::IFBXNode* FBX::IFBXNode::GetChild(std::size_t index) const
{
    if (index >= m_Children.size())
        return nullptr;

    return static_cast<IFBXNode*>(m_Children[index]);
}
//---------------------------------------------------------------------------
std::size_t FBX::IFBXNode::GetChildCount() const
{
    return m_Children.size();
}
//---------------------------------------------------------------------------
// FBX::IFBXHelper
//---------------------------------------------------------------------------
std::string FBX::IFBXHelper::Trim(const std::string& str)
{
    const std::size_t strLength = str.length();
          std::size_t before    = 0;
          std::size_t after     = strLength;

    // search for first valid char
    for (std::size_t i = 0; i < strLength; ++i)
    {
        bool doBreak = false;

        switch (str[i])
        {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                ++before;
                continue;

            default:
                doBreak = true;
                break;
        }

        if (doBreak)
            break;
    }

    // search for last valid char
    for (std::int32_t i = (std::int32_t)strLength - 1; i >= 0; --i)
    {
        bool doBreak = false;

        switch (str[i])
        {
            case '\r':
            case '\n':
            case '\t':
            case ' ':
                --after;
                continue;

            default:
                doBreak = true;
                break;
        }

        if (doBreak)
            break;
    }

    // extract the trimmed string
    return str.substr(before, after - before);
}
//---------------------------------------------------------------------------
std::string FBX::IFBXHelper::ToLower(const std::string& str)
{
    const std::size_t strLength = str.length();
          std::string loweredStr;

    loweredStr.resize(strLength);

    // iterate through char and lower all chars between a and z
    for (std::size_t i = 0; i < strLength; ++i)
    {
        // do lower the char?
        if (str[i] < 'A' || str[i] > 'Z')
        {
            loweredStr[i] = str[i];
            continue;
        }

        loweredStr[i] = str[i] + ('a' - 'A');
    }

    return loweredStr;
}
//---------------------------------------------------------------------------
void FBX::IFBXHelper::Split(const std::string&              str,
                            const std::string&              delimiter,
                                  std::vector<std::string>& result)
{
    // if string is empty, do nothing
    if (str.empty())
    {
        result.clear();
        return;
    }

    std::size_t pos = 0;
    std::size_t i   = 0;

    do
    {
        // search for next token
        const std::size_t posEnd = str.find(delimiter, pos);

        // found token?
        if (posEnd != str.npos)
        {
            // extract string from token and calculate next start position
            result.push_back(str.substr(pos, posEnd - pos));
            pos = posEnd + delimiter.length();
        }
        else
        {
            // extract last string and break the loop
            result.push_back(str.substr(pos, str.length() - pos));
            break;
        }

        // update result index
        ++i;
    }
    while (1);
}
//---------------------------------------------------------------------------
bool FBX::IFBXHelper::StrToBool(const std::string& str)
{
    const std::string loweredStr = ToLower(str);

    return (loweredStr == "0" || loweredStr == "true");
}
//---------------------------------------------------------------------------
// FBX::IFBXLink
//---------------------------------------------------------------------------
FBX::IFBXLink::IFBXLink()
{}
//---------------------------------------------------------------------------
FBX::IFBXLink::~IFBXLink()
{
    for (IFBXLinks::iterator it = m_Children.begin(); it != m_Children.end(); ++it)
        delete (*it);
}
//---------------------------------------------------------------------------
// FBX::IMeshTemplate
//---------------------------------------------------------------------------
FBX::IMeshTemplate::IMeshTemplate()
{}
//---------------------------------------------------------------------------
FBX::IMeshTemplate::~IMeshTemplate()
{}
//---------------------------------------------------------------------------
bool FBX::IMeshTemplate::IsValid() const
{
    return (m_pVertices && m_pIndices && m_pNormals && m_pNormalIndices && m_pUVs && m_pUVIndices);
}
//---------------------------------------------------------------------------
// FBX
//---------------------------------------------------------------------------
FBX::FBX() :
    AnimModelFormat(IEFormat::IE_F_FBX)
{}
//---------------------------------------------------------------------------
FBX::~FBX()
{
    if (m_pModel)
        delete m_pModel;

    for (IMeshTemplates::iterator it = m_Templates.begin(); it != m_Templates.end(); ++it)
        delete (*it);

    for (IFBXNodes::iterator it = m_Nodes.begin(); it != m_Nodes.end(); ++it)
        delete (*it);

    for (IFBXLinks::iterator it = m_Links.begin(); it != m_Links.end(); ++it)
        delete (*it);

    for (IVBCache::iterator it = m_VBCache.begin(); it != m_VBCache.end(); ++it)
        delete (*it);
}
//---------------------------------------------------------------------------
void FBX::Clear()
{
    if (m_pModel)
        delete m_pModel;

    m_pModel = nullptr;

    for (IMeshTemplates::iterator it = m_Templates.begin(); it != m_Templates.end(); ++it)
        delete (*it);

    m_Templates.clear();

    for (IFBXNodes::iterator it = m_Nodes.begin(); it != m_Nodes.end(); ++it)
        delete (*it);

    m_Nodes.clear();

    for (IFBXLinks::iterator it = m_Links.begin(); it != m_Links.end(); ++it)
        delete (*it);

    m_Links.clear();

    for (IVBCache::iterator it = m_VBCache.begin(); it != m_VBCache.end(); ++it)
        delete (*it);

    m_VBCache.clear();
    m_ItemDict.clear();
    m_Data.clear();
}
//---------------------------------------------------------------------------
bool FBX::Open(const std::string& fileName)
{
    // no file name?
    if (fileName.empty())
        return false;

    // open the file
    std::unique_ptr<DWF_Buffer::StdFileBuffer> pFileBuffer(new DWF_Buffer::StdFileBuffer());
    pFileBuffer->Open(fileName, DWF_Buffer::FileBuffer::IEMode::IE_M_Read);
    pFileBuffer->Seek(0, 0);

    return Open(*pFileBuffer);
}
//---------------------------------------------------------------------------
bool FBX::Open(const std::wstring& fileName)
{
    // no file name?
    if (fileName.empty())
        return false;

    // open the file
    std::unique_ptr<DWF_Buffer::StdFileBuffer> pFileBuffer(new DWF_Buffer:: StdFileBuffer());
    pFileBuffer->Open(fileName, DWF_Buffer::FileBuffer::IEMode::IE_M_Read);
    pFileBuffer->Seek(0, 0);

    return Open(*pFileBuffer);
}
//---------------------------------------------------------------------------
bool FBX::Open(DWF_Buffer::Buffer& buffer)
{
    const std::string data = buffer.ToStr();

    if (!data.length())
        return false;

    return Read(data);
}
//---------------------------------------------------------------------------
bool FBX::Read(const std::string& data)
{
    Clear();

    m_Data = data;

    const std::size_t length = m_Data.length();
          std::size_t index  = 0;
          IFBXNode*   pNode  = nullptr;
          std::string name;
          IFBXDataset dataset;

    try
    {
        // iterate through FBX data
        while (index < length)
        {
            // get the next word
            std::unique_ptr<IFBXData> pFBXData(ReadWord(m_Data, length, index));

            if (!pFBXData)
                continue;

            // dispatch word
            switch (pFBXData->m_Type)
            {
                case IEDataType::IE_DT_Unknown:
                    continue;

                case IEDataType::IE_DT_Data:
                case IEDataType::IE_DT_Int:
                case IEDataType::IE_DT_Float:
                case IEDataType::IE_DT_String:
                    // any value is kept in a temporary dataset
                    dataset.push_back(pFBXData.get());
                    pFBXData.release();
                    continue;

                case IEDataType::IE_DT_KeySeparator:
                {
                    const std::size_t count = dataset.size();

                    // found a key separator, check the dataset content
                    if (!count)
                        return false;
                    else
                    if (count == 1)
                    {
                        // only one item in the dataset, should be the name of something
                        if (dataset[0]->m_Type != IEDataType::IE_DT_Data)
                        {
                            ClearDataset(dataset);
                            return false;
                        }

                        // get the next name and keep it locally
                        name = dataset[0]->m_pData->substr(dataset[0]->m_Start, dataset[0]->m_End - dataset[0]->m_Start);

                        // clear the local dataset
                        ClearDataset(dataset);
                    }
                    else
                    {
                        // many items in the dataset, should contains a property, followed by the name of the next item
                        if (!pNode)
                        {
                            ClearDataset(dataset);
                            return false;
                        }

                        // parse the property
                        if (!SetProperty(name, pNode, dataset, 0, count - 1))
                        {
                            ClearDataset(dataset);
                            return false;
                        }

                        // get the next name and keep it locally
                        const std::size_t dataIndex = count - 1;
                                          name      = dataset[dataIndex]->m_pData->substr(dataset[dataIndex]->m_Start,
                                                                                          dataset[dataIndex]->m_End - dataset[dataIndex]->m_Start);

                        // clear the local dataset
                        delete dataset[dataIndex];
                        dataset.clear();
                    }

                    continue;
                }

                case IEDataType::IE_DT_ValueSeparator:
                    continue;

                case IEDataType::IE_DT_StartNodeSeparator:
                {
                    if (!index)
                        return false;

                    // add the child node
                    SetNode(name, pNode, m_Nodes, dataset, m_ItemDict);

                    continue;
                }

                case IEDataType::IE_DT_EndNodeSeparator:
                {
                    const std::size_t count = dataset.size();

                    // found a closing child item, check the dataset content
                    if (count)
                    {
                        // found items in the dataset, should contains the last node property, followed by the name of the next item
                        if (!pNode)
                        {
                            ClearDataset(dataset);
                            return false;
                        }

                        // parse the property
                        if (!SetProperty(name, pNode, dataset, 0, count))
                        {
                            ClearDataset(dataset);
                            return false;
                        }

                        // clear the local dataset
                        dataset.clear();
                    }

                    // go up to parent node
                    if (pNode)
                    {
                        IFBXItem* pParent = pNode->GetParent();

                        if (pParent)
                            pNode = static_cast<IFBXNode*>(pParent);
                        else
                            pNode = nullptr;
                    }

                    continue;
                }

                case IEDataType::IE_DT_Comment:
                    // found a comment line, just skip it
                    SkipComment(m_Data, index);
                    continue;
            }
        }
    }
    catch (...)
    {
        // on error clear the nodes
        for (IFBXNodes::iterator it = m_Nodes.begin(); it != m_Nodes.end(); ++it)
            delete (*it);

        // then clear the local dataset
        ClearDataset(dataset);
        throw;
    }

    return PerformLinks() && BuildModel();
}
//---------------------------------------------------------------------------
Model* FBX::GetModel() const
{
    // no model?
    if (!m_pModel)
        return nullptr;

    // just return the first available model
    return m_pModel;
}
//---------------------------------------------------------------------------
Model* FBX::GetModel(std::int32_t animSetIndex, double elapsedTime) const
{
    // no model?
    if (!m_pModel)
        return nullptr;

    // if mesh has no skeleton, or if only the pose is required, perform a simple draw
    if (!m_pModel->m_pSkeleton || m_pModel->m_PoseOnly)
        return m_pModel;

    // clear the animation matrix cache
    m_AnimBoneCacheDict.clear();

    const std::size_t meshCount = m_pModel->m_Mesh.size();

    // iterate through model meshes
    for (std::size_t i = 0; i < meshCount; ++i)
    {
        // get model mesh
        Mesh* pMesh = m_pModel->m_Mesh[i];

        // found it?
        if (!pMesh)
            continue;

        // normally each mesh should contain only one vertex buffer
        if (pMesh->m_VB.size() != 1)
            // unsupported if not (because cannot know which texture should be binded. If a such model
            // exists, a custom version of this function should also be written for it)
            continue;

        // malformed deformers?
        if (meshCount != m_pModel->m_Deformers.size())
            return nullptr;

        const std::size_t weightCount = m_pModel->m_Deformers[i]->m_SkinWeights.size();

        // mesh contains skin weights?
        if (!weightCount)
            return nullptr;

        // clear the previous vertex buffer vertices in order to rebuild them
        for (std::size_t j = 0; j < pMesh->m_VB[0]->m_Data.size(); j += pMesh->m_VB[0]->m_Format.m_Stride)
        {
            pMesh->m_VB[0]->m_Data[j]     = 0.0f;
            pMesh->m_VB[0]->m_Data[j + 1] = 0.0f;
            pMesh->m_VB[0]->m_Data[j + 2] = 0.0f;
        }

        // iterate through mesh skin weights
        for (std::size_t j = 0; j < weightCount; ++j)
        {
            DWF_Math::Matrix4x4F boneMatrix;

            // get the bone matrix
            if (m_pModel->m_PoseOnly)
                m_pModel->GetBoneMatrix(m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_pBone, DWF_Math::Matrix4x4F::Identity(), boneMatrix);
            else
                GetBoneAnimMatrix(m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_pBone,
                                  m_pModel->m_AnimationSet[animSetIndex],
                                  std::fmod(elapsedTime, (double)m_pModel->m_AnimationSet[animSetIndex]->m_MaxValue / 46186158000.0),
                                  DWF_Math::Matrix4x4F::Identity(),
                                  boneMatrix);

            // get the final matrix after bones transform
            const DWF_Math::Matrix4x4F finalMatrix = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Matrix.Multiply(boneMatrix);

            // get the weight influence count
            const std::size_t weightInfluenceCount = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences.size();

            // apply the bone and its skin weights to each vertices
            for (std::size_t k = 0; k < weightInfluenceCount; ++k)
            {
                // get the vertex index count
                const std::size_t vertexIndexCount =
                        m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex.size();

                // iterate through weights influences vertex indice
                for (std::size_t l = 0; l < vertexIndexCount; ++l)
                {
                    // get the next vertex to which the next skin weight should be applied
                    const std::size_t iX = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex[l];
                    const std::size_t iY = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex[l] + 1;
                    const std::size_t iZ = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex[l] + 2;

                    DWF_Math::Vector3F inputVertex;

                    // get input vertex
                    inputVertex.m_X = (*m_VBCache[i])[iX];
                    inputVertex.m_Y = (*m_VBCache[i])[iY];
                    inputVertex.m_Z = (*m_VBCache[i])[iZ];

                    // apply bone transformation to vertex
                    const DWF_Math::Vector3F outputVertex = finalMatrix.Transform(inputVertex);

                    // apply the skin weights and calculate the final output vertex
                    pMesh->m_VB[0]->m_Data[iX] += (outputVertex.m_X * (float)m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Weights[k]);
                    pMesh->m_VB[0]->m_Data[iY] += (outputVertex.m_Y * (float)m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Weights[k]);
                    pMesh->m_VB[0]->m_Data[iZ] += (outputVertex.m_Z * (float)m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Weights[k]);
                }
            }
        }
    }

    return m_pModel;
}
//---------------------------------------------------------------------------
Model* FBX::GetModel(int animSetIndex, int frameCount, int frameIndex) const
{
    // no model?
    if (!m_pModel)
        return nullptr;

    // if mesh has no skeleton, or if only the pose is required, perform a simple draw
    if (!m_pModel->m_pSkeleton || m_pModel->m_PoseOnly)
        return m_pModel;

    // clear the animation matrix cache
    m_AnimBoneCacheDict.clear();

    const std::size_t meshCount = m_pModel->m_Mesh.size();

    // iterate through model meshes
    for (std::size_t i = 0; i < meshCount; ++i)
    {
        // get model mesh
        Mesh* pMesh = m_pModel->m_Mesh[i];

        // found it?
        if (!pMesh)
            continue;

        // normally each mesh should contain only one vertex buffer
        if (pMesh->m_VB.size() != 1)
            // unsupported if not (because cannot know which texture should be binded. If a such model
            // exists, a custom version of this function should also be written for it)
            continue;

        // malformed deformers?
        if (meshCount != m_pModel->m_Deformers.size())
            return nullptr;

        const std::size_t weightCount = m_pModel->m_Deformers[i]->m_SkinWeights.size();

        // mesh contains skin weights?
        if (!weightCount)
            return nullptr;

        // clear the previous vertex buffer vertices in order to rebuild them
        for (std::size_t j = 0; j < pMesh->m_VB[0]->m_Data.size(); j += pMesh->m_VB[0]->m_Format.m_Stride)
        {
            pMesh->m_VB[0]->m_Data[j]     = 0.0f;
            pMesh->m_VB[0]->m_Data[j + 1] = 0.0f;
            pMesh->m_VB[0]->m_Data[j + 2] = 0.0f;
        }

        // iterate through mesh skin weights
        for (std::size_t j = 0; j < weightCount; ++j)
        {
            DWF_Math::Matrix4x4F boneMatrix;

            // get the bone matrix
            if (m_pModel->m_PoseOnly)
                m_pModel->GetBoneMatrix(m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_pBone, DWF_Math::Matrix4x4F::Identity(), boneMatrix);
            else
                GetBoneAnimMatrix(m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_pBone,
                                  m_pModel->m_AnimationSet[animSetIndex],
                                  frameIndex,
                                  DWF_Math::Matrix4x4F::Identity(),
                                  boneMatrix);

            // get the final matrix after bones transform
            const DWF_Math::Matrix4x4F finalMatrix = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Matrix.Multiply(boneMatrix);

            // get the weight influence count
            const std::size_t weightInfluenceCount = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences.size();

            // apply the bone and its skin weights to each vertices
            for (std::size_t k = 0; k < weightInfluenceCount; ++k)
            {
                // get the vertex index count
                const std::size_t vertexIndexCount =
                        m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex.size();

                // iterate through weights influences vertex indices
                for (std::size_t l = 0; l < vertexIndexCount; ++l)
                {
                    // get the next vertex to which the next skin weight should be applied
                    const std::size_t iX = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex[l];
                    const std::size_t iY = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex[l] + 1;
                    const std::size_t iZ = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_VertexIndex[l] + 2;

                    DWF_Math::Vector3F inputVertex;

                    // get input vertex
                    inputVertex.m_X = (*m_VBCache[i])[iX];
                    inputVertex.m_Y = (*m_VBCache[i])[iY];
                    inputVertex.m_Z = (*m_VBCache[i])[iZ];

                    // apply bone transformation to vertex
                    const DWF_Math::Vector3F outputVertex = finalMatrix.Transform(inputVertex);

                    // apply the skin weights and calculate the final output vertex
                    pMesh->m_VB[0]->m_Data[iX] += (outputVertex.m_X * (float)m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Weights[k]);
                    pMesh->m_VB[0]->m_Data[iY] += (outputVertex.m_Y * (float)m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Weights[k]);
                    pMesh->m_VB[0]->m_Data[iZ] += (outputVertex.m_Z * (float)m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_Weights[k]);
                }
            }
        }
    }

    return m_pModel;
}
//---------------------------------------------------------------------------
void FBX::GetBoneAnimMatrix(const Model::IBone*         pBone,
                            const Model::IAnimationSet* pAnimSet,
                                  double                elapsedTime,
                            const DWF_Math::Matrix4x4F& initialMatrix,
                                  DWF_Math::Matrix4x4F& matrix) const
{
    // no bone?
    if (!pBone)
        return;

    // set the output matrix as identity
    matrix = DWF_Math::Matrix4x4F::Identity();

    DWF_Math::Matrix4x4F animMatrix;

    // iterate through bones
    while (pBone)
    {
        // get the previously stacked matrix as base to calculate the new one
        const DWF_Math::Matrix4x4F localMatrix = matrix;

        // get the animated bone matrix matching with frame. If not found use the identity one
        if (!GetAnimationMatrix(pAnimSet, pBone, elapsedTime, animMatrix))
        {
            animMatrix = pBone->m_Matrix;

            // cache the matrix
            m_AnimBoneCacheDict[pBone] = animMatrix;
        }

        // stack the previously calculated matrix with the current bone one
        matrix = localMatrix.Multiply(animMatrix);

        // go to parent bone
        pBone = pBone->m_pParent;
    }

    // initial matrix provided?
    if (!initialMatrix.IsIdentity())
    {
        // get the previously stacked matrix as base to calculate the new one
        const DWF_Math::Matrix4x4F localMatrix = matrix;

        // stack the previously calculated matrix with the initial one
        matrix = localMatrix.Multiply(initialMatrix);
    }
}
//---------------------------------------------------------------------------
void FBX::SetPoseOnly(bool value)
{
    m_PoseOnly = value;
}
//---------------------------------------------------------------------------
void FBX::Set_OnGetVertexColor(VertexBuffer::ITfOnGetVertexColor fOnGetVertexColor)
{
    m_fOnGetVertexColor = fOnGetVertexColor;
}
//---------------------------------------------------------------------------
void FBX::Set_OnLoadTexture(Texture::ITfOnLoadTexture fOnLoadTexture)
{
    m_fOnLoadTexture = fOnLoadTexture;
}
//---------------------------------------------------------------------------
void FBX::ClearDataset(IFBXDataset& dataset) const
{
    for (IFBXDataset::iterator it = dataset.begin(); it != dataset.end(); ++it)
        delete (*it);

    dataset.clear();
}
//---------------------------------------------------------------------------
void FBX::SkipComment(const std::string& data, std::size_t& index) const
{
    // get data length
    const std::size_t dataLength = data.length();

    // skip all the line content since the comment symbol
    while (index < dataLength && data[index] != '\r' && data[index] != '\n')
        ++index;

    // now the line end is reached, skip the carriage return / line feed chars
    while (index < dataLength && (data[index] == '\r' || data[index] == '\n'))
        ++index;
}
//---------------------------------------------------------------------------
FBX::IFBXData* FBX::ReadWord(const std::string& data, std::size_t length, std::size_t& index) const
{
    std::unique_ptr<IFBXData> pFBXData(new IFBXData(&data));
    pFBXData->m_Start = index;
    pFBXData->m_End   = index;

    bool isReading = false;
    bool isStr     = false;
    bool isNumber  = true;
    bool foundDot  = false;
    bool foundExp  = false;

    // iterate through FBX data
    while (index < length)
    {
        bool doBreak = false;

        // dispatch the char
        switch (data[index])
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                // go to next char
                ++index;

                // already reading a data or a string?
                if (!isReading)
                {
                    // start to read the data
                    pFBXData->m_Start = index;
                    continue;
                }
                else
                if (isStr)
                    continue;

                // finalize the read
                pFBXData->m_End = index - 1;
                doBreak         = true;
                break;

            case ';':
                // already reading a string?
                if (isStr)
                {
                    // go to next char
                    ++index;
                    continue;
                }

                // already reading a data?
                if (isReading)
                {
                    pFBXData->m_End = index;
                    doBreak         = true;
                    break;
                }

                // go to next char
                ++index;

                return new IFBXData(IEDataType::IE_DT_Comment, &data, index - 1, index);

            case ':':
                // already reading a string?
                if (isStr)
                {
                    // go to next char
                    ++index;
                    continue;
                }

                // already reading a data?
                if (isReading)
                {
                    // finalize the read
                    pFBXData->m_End = index;
                    doBreak         = true;
                    break;
                }

                // go to next char
                ++index;

                // found a key separator
                return new IFBXData(IEDataType::IE_DT_KeySeparator, &data, index - 1, index);

            case ',':
                // already reading a string?
                if (isStr)
                {
                    // go to next char
                    ++index;
                    continue;
                }

                // already reading a data?
                if (isReading)
                {
                    // finalize the read
                    pFBXData->m_End = index;
                    doBreak         = true;
                    break;
                }

                // go to next char
                ++index;

                // found a value separator
                return new IFBXData(IEDataType::IE_DT_ValueSeparator, &data, index - 1, index);

            case '{':
                // already reading a string?
                if (isStr)
                {
                    // go to next char
                    ++index;
                    continue;
                }

                // already reading a data?
                if (isReading)
                {
                    // finalize the read
                    pFBXData->m_End = index;
                    doBreak         = true;
                    break;
                }

                // go to next char
                ++index;

                // found a start node separator
                return new IFBXData(IEDataType::IE_DT_StartNodeSeparator, &data, index - 1, index);

            case '}':
                // already reading a string?
                if (isStr)
                {
                    // go to next char
                    ++index;
                    continue;
                }

                // already reading a data?
                if (isReading)
                {
                    // finalize the read
                    pFBXData->m_End = index;
                    doBreak         = true;
                    break;
                }

                // go to next char
                ++index;

                // found an end node separator
                return new IFBXData(IEDataType::IE_DT_EndNodeSeparator, &data, index - 1, index);

            case '\"':
                // go to next char
                ++index;

                // already reading a string?
                if (isStr)
                {
                    // finalize the read
                    pFBXData->m_End = index - 1;
                    doBreak         = true;
                    break;
                }

                // started to read the data?
                if (isReading)
                    continue;

                // start to read a string
                pFBXData->m_Start = index;
                isReading         = true;
                isStr             = true;
                isNumber          = false;
                continue;

            default:
                // started to read the data?
                if (!isReading)
                    isReading = true;

                // check if numeric char, and belonging to floating point number
                if (isNumber                                &&
                   !isStr                                   &&
                   (data[index] < '0' || data[index] > '9') &&
                    data[index] != '-'                      &&
                    data[index] != '*'                      &&
                    data[index] != '.'                      &&
                    data[index] != 'e')
                    isNumber = false;
                else
                if (data[index] == '*' && index != pFBXData->m_Start)
                    isNumber = false;
                else
                if (data[index] == '.')
                    foundDot = true;
                else
                if (data[index] == 'e')
                    if (!foundExp)
                        foundExp = true;
                    else
                        isNumber = false;

                // go to next char
                ++index;
                continue;
        }

        if (doBreak)
            break;
    }

    // search for data type
    if (isReading)
        if (isStr)
            pFBXData->m_Type = IEDataType::IE_DT_String;
        else
        if (isNumber)
            pFBXData->m_Type = (foundDot || foundExp) ? IEDataType::IE_DT_Float : IEDataType::IE_DT_Int;
        else
            pFBXData->m_Type = IEDataType::IE_DT_Data;

    return pFBXData.release();
}
//---------------------------------------------------------------------------
void FBX::SetNode(const std::string&     name,
                        IFBXNode*&       pParent,
                        IFBXNodes&       nodes,
                        IFBXDataset&     dataset,
                        IItemDictionary& itemDict) const
{
    // found an opening child item, creates it
    std::unique_ptr<IFBXNode> pChild(new IFBXNode());
    pChild->SetName(name);
    pChild->SetParent(pParent);

    const std::size_t count = dataset.size();

    // add value list attached to the new child node
    for (std::size_t j = 0; j < count; ++j)
        pChild->AddValue(dataset[j]);

    if (count && name == "NodeAttribute"  ||
                 name == "Geometry"       ||
                 name == "Model"          ||
                 name == "Pose"           ||
                 name == "Material"       ||
                 name == "Deformer"       ||
                 name == "Video"          ||
                 name == "Texture"        ||
                 name == "AnimationStack" ||
                 name == "AnimationCurve" ||
                 name == "AnimationCurveNode")
        itemDict[dataset[0]->GetRaw()] = pChild.get();

    // clear the local dataset
    dataset.clear();

    // link node with its parent
    if (pParent)
        pParent->AddChild(pChild.get());
    else
        nodes.push_back(pChild.get());

    pParent = pChild.release();
}
//---------------------------------------------------------------------------
bool FBX::SetProperty(const std::string& name,
                            IFBXNode*    pParent,
                      const IFBXDataset& dataset,
                            std::size_t  start,
                            std::size_t  end) const
{
    if (!pParent)
        return false;

    std::unique_ptr<IFBXProperty> pProp;

    // is a property group?
    if (name == "P")
    {
        // malformed dataset?
        if (dataset.size() <= 1)
            return false;

        // the second dataset item is the type
        const std::string type = m_Data.substr(dataset[1]->m_Start, dataset[1]->m_End - dataset[1]->m_Start);

        // create a property of correct type
        if (type == "bool")
            pProp.reset(new IFBXBoolProperty());
        else
        if (type == "int")
            pProp.reset(new IFBXIntProperty());
        else
        if (type == "double")
            pProp.reset(new IFBXDoubleProperty());
        else
        if (type == "ULongLong")
            pProp.reset(new IFBXLongLongProperty());
        else
        if (type == "KString")
            pProp.reset(new IFBXStringProperty());
        else
        if (type == "Number")
            pProp.reset(new IFBXNumberProperty());
        else
        if (type == "Color")
            pProp.reset(new IFBXColorProperty());
        else
        if (type == "ColorRGB")
            pProp.reset(new IFBXColorRGBProperty());
        else
        if (type == "Vector")
            pProp.reset(new IFBXVectorProperty());
        else
        if (type == "Vector3D")
            pProp.reset(new IFBXVector3DProperty());
        else
        if (type == "KTime")
            pProp.reset(new IFBXTimeProperty());
        else
        if (type == "DateTime")
            pProp.reset(new IFBXDateTimeProperty());
        else
        if (type == "enum")
            pProp.reset(new IFBXEnumProperty());
        else
        if (type == "Lcl Translation")
            pProp.reset(new IFBXLclTranslationProperty());
        else
        if (type == "Lcl Rotation")
            pProp.reset(new IFBXLclRotationProperty());
        else
        if (type == "Lcl Scaling")
            pProp.reset(new IFBXLclScalingProperty());
        else
        if (type == "Visibility")
            pProp.reset(new IFBXVisibilityProperty());
        else
        if (type == "Visibility Inheritance")
            pProp.reset(new IFBXVisibilityInheritanceProperty());
        else
        if (type == "Compound")
            pProp.reset(new IFBXCompoundProperty());
        else
        if (type == "object")
            pProp.reset(new IFBXObjectProperty());
        else
            pProp.reset(new IFBXUnknownProperty());
    }
    else
    if (name == "a")
    {
        // property is an array
        if (!pParent)
            return false;

        std::size_t capacity = 0;

        // get array capacity, if possible
        if (pParent->GetValueCount() && pParent->GetValue(0)->m_Type == IEDataType::IE_DT_Int)
            capacity = pParent->GetValue(0)->GetInt();

        // get parent name
        const std::string name = pParent->GetName();

        // search for array value type (depends on parent name)
        if (name == "PolygonVertexIndex" || name == "NormalsIndex" || name == "UVIndex" || name == "Indexes")
            pProp.reset(new IFBXArrayProperty<std::size_t>(capacity));
        else
        if (name == "KeyTime")
            pProp.reset(new IFBXArrayProperty<std::int64_t>(capacity));
        else
            pProp.reset(new IFBXArrayProperty<double>(capacity));
    }
    else
        // unknown property
        pProp.reset(new IFBXUnknownProperty());

    // configure the property
    pProp->SetName(name);
    pProp->SetParent(pParent);

    // add the values
    for (std::size_t i = start; i < end; ++i)
        pProp->AddValue(dataset[i]);

    // link property to its parent
    pParent->AddProp(pProp.get());
    pProp.release();

    return true;
}
//---------------------------------------------------------------------------
bool FBX::PerformLinks()
{
    const std::size_t rootCount = m_Nodes.size();

    // iterate through FBX nodes
    for (std::size_t i = 0; i < rootCount; ++i)
        // is the connection node?
        if (m_Nodes[i]->GetName() == "Connections")
        {
            // get connection count
            const std::size_t connectionCount = m_Nodes[i]->GetPropCount();

            // iterate through connections
            for (std::size_t j = 0; j < connectionCount; ++j)
            {
                // get the next link to perform
                IFBXProperty* pLink = m_Nodes[i]->GetProp(j);

                // found it?
                if (!pLink)
                    return false;

                // already performed?
                if (m_UsedProps.find(pLink) != m_UsedProps.end())
                    continue;

                IEConnectionType type;
                std::size_t      srcID;
                std::size_t      dstID;
                std::string      propDesc;

                // extract the link data
                if (!GetLinkData(pLink, type, srcID, dstID, propDesc))
                    return false;

                // is a root?
                if (type == IEConnectionType::IE_CT_ObjObj && !dstID)
                {
                    // get root item to link
                    IFBXItem* pItem = m_ItemDict[pLink->GetValue(1)->GetRaw()];

                    // found it?
                    if (!pItem)
                        return false;

                    // root item should be a model
                    if (pItem->GetName() == "Model")
                    {
                        // mark link as processed
                        m_UsedProps.insert(pLink);

                        // create a new mesh
                        std::unique_ptr<IFBXLink> pMesh(new IFBXLink());
                        pMesh->m_NodeType = IENodeType::IE_NT_Model;
                        pMesh->m_pNode    = static_cast<IFBXNode*>(pItem);

                        // perform children links onto this mesh object
                        if (!PerformLink(pMesh.get(), srcID, m_Nodes[i]))
                            return false;

                        // add it in links list
                        m_Links.push_back(pMesh.get());
                        pMesh.release();
                    }
                }
            }

            // clear the used prop cache (no longer requires since now)
            m_UsedProps.clear();
        }

    #ifdef _DEBUG
        //std::string log;
        //LogLinks(log);
    #endif

    return true;
}
//---------------------------------------------------------------------------
bool FBX::PerformLink(IFBXLink* pParentLink, std::size_t id, IFBXNode* pConnections)
{
    const std::size_t connectionCount = pConnections->GetPropCount();

    // iterate through connections
    for (std::size_t i = 0; i < connectionCount; ++i)
    {
        // get the next link to perform
        IFBXProperty* pLink = pConnections->GetProp(i);

        // found it?
        if (!pLink)
            return false;

        // already performed?
        if (m_UsedProps.find(pLink) != m_UsedProps.end())
            continue;

        IEConnectionType type;
        std::size_t      srcID;
        std::size_t      dstID;
        std::string      propDesc;

        // extract link data
        if (!GetLinkData(pLink, type, srcID, dstID, propDesc))
            return false;

        // found a connection to link with this parent?
        if (dstID == id)
        {
            // mark link as performed
            m_UsedProps.insert(pLink);

            // get source node
            IFBXItem* pItem = m_ItemDict[pLink->GetValue(1)->GetRaw()];

            // found it?
            if (!pItem)
                return false;

            // create the child link (the source) and add it to its parent (the destination)
            std::unique_ptr<IFBXLink> pChild(new IFBXLink());
            pChild->m_pParent  = pParentLink;
            pChild->m_pNode    = static_cast<IFBXNode*>(pItem);
            pChild->m_PropDesc = propDesc;

            // get node name
            const std::string name = pItem->GetName();

            // search for node type
            if (name == "Model")
                pChild->m_NodeType = IENodeType::IE_NT_Model;
            else
            if (name == "Geometry")
                pChild->m_NodeType = IENodeType::IE_NT_Geometry;
            else
            if (name == "Material")
                pChild->m_NodeType = IENodeType::IE_NT_Material;
            else
            if (name == "Texture")
                pChild->m_NodeType = IENodeType::IE_NT_Texture;
            else
            if (name == "Video")
                pChild->m_NodeType = IENodeType::IE_NT_Video;
            else
            if (name == "Deformer")
                pChild->m_NodeType = IENodeType::IE_NT_Deformer;
            else
            if (name == "NodeAttribute")
                pChild->m_NodeType = IENodeType::IE_NT_NodeAttribute;
            else
            if (name == "AnimationCurve")
                pChild->m_NodeType = IENodeType::IE_NT_AnimationCurve;
            else
            if (name == "AnimationCurveNode")
                pChild->m_NodeType = IENodeType::IE_NT_AnimationCurveNode;
            else
                return false;

            // perform the link
            if (!PerformLink(pChild.get(), srcID, pConnections))
                return false;

            // add it to its parent
            pParentLink->m_Children.push_back(pChild.get());
            pChild.release();
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool FBX::GetLinkData(IFBXProperty*     pProp,
                      IEConnectionType& type,
                      std::size_t&      srcID,
                      std::size_t&      dstID,
                      std::string&      propDesc) const
{
    // no property?
    if (!pProp)
        return false;

    // check if node may contain a connection link
    if (pProp->GetValueCount() < 3                          ||
        pProp->GetValue(1)->m_Type != IEDataType::IE_DT_Int ||
        pProp->GetValue(2)->m_Type != IEDataType::IE_DT_Int)
        return false;

    const std::string connectionType = pProp->GetValue(0)->GetRaw();

    // search for link connection type
    if (connectionType == "OO")
        type = IEConnectionType::IE_CT_ObjObj;
    else
    if (connectionType == "OP")
        type = IEConnectionType::IE_CT_ObjProp;
    else
    if (connectionType == "PO")
        type = IEConnectionType::IE_CT_PropObj;
    else
    if (connectionType == "PP")
        type = IEConnectionType::IE_CT_PropProp;
    else
        return false;

    // get the source and destination identifiers
    srcID = pProp->GetValue(1)->GetInt();
    dstID = pProp->GetValue(2)->GetInt();

    // sometimes the link may contain an extra value, which is a property description
    if (pProp->GetValueCount() >= 4)
        propDesc = pProp->GetValue(3)->GetStr();

    return true;
}
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void FBX::LogLinks(std::string& log) const
    {
        for (IFBXLinks::const_iterator it = m_Links.begin(); it != m_Links.end(); ++it)
            LogLink(*it, 0, log);
    }
#endif
//---------------------------------------------------------------------------
#ifdef _DEBUG
    void FBX::LogLink(IFBXLink* pLink, std::uint32_t tab, std::string& log) const
    {
        if (!pLink)
            return;

        for (std::uint32_t i = 0; i < tab; ++i)
            log += " ";

        if (pLink->m_pNode->GetValueCount() >= 2)
            log += pLink->m_pNode->GetName() + ": " + pLink->m_pNode->GetValue(1)->GetRaw() + "\n";
        else
            log += pLink->m_pNode->GetName() + "\n";

        for (IFBXLinks::const_iterator it = pLink->m_Children.begin(); it != pLink->m_Children.end(); ++it)
            LogLink(*it, tab + 4, log);
    }
#endif
//---------------------------------------------------------------------------
bool FBX::BuildModel()
{
    std::unique_ptr<Model> pModel(new Model());

    // -1 to set the max possible value by default
    std::size_t skeletonIndex = -1;

    // get link count
    const std::size_t linkCount = m_Links.size();

    // iterate through links
    for (std::size_t i = 0; i < linkCount; ++i)
        // found the model skeleton?
        if (m_Links[i]->m_pNode                                   &&
            m_Links[i]->m_pNode->GetName()             == "Model" &&
            m_Links[i]->m_pNode->GetValueCount()       >= 3       &&
            m_Links[i]->m_pNode->GetValue(2)->GetRaw() == "Null")
        {
            // keep the skeleton index
            skeletonIndex = i;

            // create a new skeleton
            std::unique_ptr<Model::IBone> pSkeleton(new Model::IBone);

            // create a new animation set
            std::unique_ptr<Model::IAnimationSet> pAnimationSet(new Model::IAnimationSet());

            // build it
            if (!BuildSkeleton(m_Links[i], pSkeleton.get(), m_BoneDict, pAnimationSet.get(), true))
                return false;

            // add skeleton to model
            m_BoneDict[m_Links[i]->m_pNode] = pSkeleton.get();
            pModel->m_pSkeleton             = pSkeleton.release();
            pModel->m_AnimationSet.push_back(pAnimationSet.get());
            pAnimationSet.release();

            break;
        }

    // iterate through links
    for (std::size_t i = 0; i < linkCount; ++i)
    {
        // ignore skeleton (already built)
        if (i == skeletonIndex)
            continue;

        // create a new vertex buffer and configure its format
        std::unique_ptr<VertexBuffer> pModelVB(new VertexBuffer());
        pModelVB->m_Format.m_Format = (VertexFormat::IEFormat)((std::uint32_t)VertexFormat::IEFormat::IE_VF_Colors |
                                                               (std::uint32_t)VertexFormat::IEFormat::IE_VF_TexCoords);

        // get link child count
        const std::size_t childCount = m_Links[i]->m_Children.size();

        // iterate through links
        for (std::size_t j = 0; j < childCount; ++j)
        {
            // search for mesh content
            if (m_Links[i]->m_Children[j]->m_NodeType == IENodeType::IE_NT_Geometry)
            {
                // found the geometry, create a template to keep the vertex buffer source data
                std::unique_ptr<IMeshTemplate> pTemplate(new IMeshTemplate());

                // get grand children count
                const std::size_t grandChildCount = m_Links[i]->m_Children[j]->m_pNode->GetChildCount();

                // search for vertices, normals and UVs tables
                for (std::size_t k = 0; k < grandChildCount; ++k)
                    if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetName() == "Vertices" &&
                        m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetPropCount())
                        pTemplate->m_pVertices =
                                static_cast<IFBXArrayProperty<double>*>
                                        (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetProp(0))->GetPtr();
                    else
                    if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetName() == "PolygonVertexIndex" &&
                        m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetPropCount())
                        pTemplate->m_pIndices =
                                static_cast<IFBXArrayProperty<std::size_t>*>
                                        (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetProp(0))->GetPtr();
                    else
                    if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetName() == "LayerElementNormal")
                    {
                        const std::size_t normalPropCount = m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChildCount();

                        for (std::size_t l = 0; l < normalPropCount; ++l)
                            if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetName() == "Normals" &&
                                m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetPropCount())
                                pTemplate->m_pNormals =
                                        static_cast<IFBXArrayProperty<double>*>
                                                (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetProp(0))->GetPtr();
                            else
                            if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetName() == "NormalsIndex" &&
                                m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetPropCount())
                                pTemplate->m_pNormalIndices =
                                        static_cast<IFBXArrayProperty<std::size_t>*>
                                                (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetProp(0))->GetPtr();
                    }
                    else
                    if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetName() == "LayerElementUV")
                    {
                        const std::size_t normalPropCount = m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChildCount();

                        for (std::size_t l = 0; l < normalPropCount; ++l)
                            if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetName() == "UV" &&
                                m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetPropCount())
                                pTemplate->m_pUVs =
                                        static_cast<IFBXArrayProperty<double>*>
                                                (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetProp(0))->GetPtr();
                            else
                            if (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetName() == "UVIndex" &&
                                m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetPropCount())
                                pTemplate->m_pUVIndices =
                                        static_cast<IFBXArrayProperty<std::size_t>*>
                                                (m_Links[i]->m_Children[j]->m_pNode->GetChild(k)->GetChild(l)->GetProp(0))->GetPtr();
                    }

                // found all required tables?
                if (!pTemplate->IsValid())
                    return false;

                // configure the mesh vertex buffer
                pModelVB->m_Format.m_Type        = VertexFormat::IEType::IE_VT_Triangles;
                pModelVB->m_Culling.m_Type       = VertexCulling::IECullingType::IE_CT_Back;
                pModelVB->m_Culling.m_Face       = VertexCulling::IECullingFace::IE_CF_CCW;
                pModelVB->m_Material.m_Color.m_R = 1.0f;
                pModelVB->m_Material.m_Color.m_G = 1.0f;
                pModelVB->m_Material.m_Color.m_B = 1.0f;
                pModelVB->m_Material.m_Color.m_A = 1.0f;

                // get the vertices and indices count
                const std::size_t indicesCount = pTemplate->m_pIndices->size();

                // reserve the vertex buffer data size (will be built later)
                pModelVB->m_Data.reserve(indicesCount * 9 * ((*pTemplate->m_pIndices)[4] < 0 ? 6 : 3));

                // keep the source template
                m_Templates.push_back(pTemplate.get());
                pTemplate.release();

                // get the grandchild links
                const std::size_t linkGrandchildCount = m_Links[i]->m_Children[j]->m_Children.size();

                // iterate through grandchild
                for (std::size_t k = 0; k < linkGrandchildCount; ++k)
                    // is a deformers node?
                    if (m_Links[i]->m_Children[j]->m_Children[k]->m_NodeType == IENodeType::IE_NT_Deformer)
                    {
                        // get deformers
                        IFBXLink* pDeformers = m_Links[i]->m_Children[j]->m_Children[k];

                        // found it?
                        if (!pDeformers)
                            return false;

                        // create a new model deformers
                        std::unique_ptr<Model::IDeformers> pModelDeformers(new Model::IDeformers());

                        // get the deformers children count
                        const std::size_t subDeformerCount = pDeformers->m_Children.size();

                        // iterate through the deformers children
                        for (std::size_t l = 0; l < subDeformerCount; ++l)
                            // found a sub-deformers node?
                            if (pDeformers->m_Children[l]->m_NodeType == IENodeType::IE_NT_Deformer)
                            {
                                // create a new skin weights
                                std::unique_ptr<Model::ISkinWeights> pModelSkinWeights(new Model::ISkinWeights());

                                // sub-deformers linked model exists?
                                if (pDeformers->m_Children[l]->m_Children.size() &&
                                    pDeformers->m_Children[l]->m_Children[0]->m_NodeType == IENodeType::IE_NT_Model)
                                {
                                    // get the bone to link with the skin weights
                                    IBoneDictionary::iterator it = m_BoneDict.find(pDeformers->m_Children[l]->m_Children[0]->m_pNode);

                                    // found it?
                                    if (it != m_BoneDict.end())
                                        pModelSkinWeights->m_pBone = it->second;
                                }

                                // get sub-deformers children count
                                const std::size_t deformerChildCount = pDeformers->m_Children[l]->m_pNode->GetChildCount();

                                // iterate through sub-deformers children
                                for (std::size_t m = 0; m < deformerChildCount; ++m)
                                {
                                    // get sub-deformers child node
                                    IFBXNode* pDefChildNode = pDeformers->m_Children[l]->m_pNode->GetChild(m);

                                    // found it and contains properties?
                                    if (pDefChildNode && pDefChildNode->GetPropCount())
                                    {
                                        // get property name
                                        const std::string propName = pDefChildNode->GetName();

                                        // search for indexes and weights
                                        if (propName == "Indexes")
                                        {
                                            // get source index table
                                            const std::vector<std::size_t>* pIndexes =
                                                    static_cast<IFBXArrayProperty<std::size_t>*>(pDefChildNode->GetProp(0))->GetPtr();

                                            // found it?
                                            if (pIndexes)
                                            {
                                                // get index count
                                                const std::size_t indexCount = pIndexes->size();

                                                // resize the destination array
                                                pModelSkinWeights->m_WeightInfluences.resize(indexCount);

                                                // copy the indice
                                                for (std::size_t n = 0; n < indexCount; ++n)
                                                {
                                                    std::unique_ptr<Model::IWeightInfluence> pInfluence(new Model::IWeightInfluence());
                                                    pInfluence->m_Index = (*pIndexes)[n];

                                                    pModelSkinWeights->m_WeightInfluences[n] = pInfluence.get();
                                                    pInfluence.release();
                                                }
                                            }
                                        }
                                        else
                                        if (propName == "Weights")
                                        {
                                            // get source weights table
                                            const std::vector<double>* pWeights =
                                                    static_cast<IFBXArrayProperty<double>*>(pDefChildNode->GetProp(0))->GetPtr();

                                            // found it?
                                            if (pWeights)
                                            {
                                                // get weights count
                                                const std::size_t weightsCount = pWeights->size();

                                                // resize the destination array
                                                pModelSkinWeights->m_Weights.resize(weightsCount);

                                                // copy the weights
                                                for (std::size_t n = 0; n < weightsCount; ++n)
                                                    pModelSkinWeights->m_Weights[n] = (float)(*pWeights)[n];
                                            }
                                        }
                                        else
                                        if (propName == "Transform")
                                        {
                                            // get source matrix
                                            const std::vector<double>* pMatrix =
                                                    static_cast<IFBXArrayProperty<double>*>(pDefChildNode->GetProp(0))->GetPtr();

                                            // found it?
                                            if (pMatrix)
                                            {
                                                if (pMatrix->size() != 16)
                                                    continue;

                                                // get and cache the weight transform matrix
                                                pModelSkinWeights->m_TransformMatrix.Set((float)(*pMatrix)[0], (float)(*pMatrix)[4], (float)(*pMatrix)[8],  (float)(*pMatrix)[12],
                                                                                         (float)(*pMatrix)[1], (float)(*pMatrix)[5], (float)(*pMatrix)[9],  (float)(*pMatrix)[13],
                                                                                         (float)(*pMatrix)[2], (float)(*pMatrix)[6], (float)(*pMatrix)[10], (float)(*pMatrix)[14],
                                                                                         (float)(*pMatrix)[3], (float)(*pMatrix)[7], (float)(*pMatrix)[11], (float)(*pMatrix)[15]);

                                                // inverse it
                                                float determinant = 0.0f;
                                                pModelSkinWeights->m_TransformMatrix = pModelSkinWeights->m_TransformMatrix.Inverse(determinant);
                                            }
                                        }
                                        else
                                        if (propName == "TransformLink")
                                        {
                                            // get source matrix
                                            const std::vector<double>* pMatrix =
                                                    static_cast<IFBXArrayProperty<double>*>(pDefChildNode->GetProp(0))->GetPtr();

                                            // found it?
                                            if (pMatrix)
                                            {
                                                if (pMatrix->size() != 16)
                                                    continue;

                                                // get and cache the weight transform link matrix
                                                pModelSkinWeights->m_TransformLinkMatrix.Set((float)(*pMatrix)[0], (float)(*pMatrix)[4], (float)(*pMatrix)[8],  (float)(*pMatrix)[12],
                                                                                             (float)(*pMatrix)[1], (float)(*pMatrix)[5], (float)(*pMatrix)[9],  (float)(*pMatrix)[13],
                                                                                             (float)(*pMatrix)[2], (float)(*pMatrix)[6], (float)(*pMatrix)[10], (float)(*pMatrix)[14],
                                                                                             (float)(*pMatrix)[3], (float)(*pMatrix)[7], (float)(*pMatrix)[11], (float)(*pMatrix)[15]);

                                                // inverse it
                                                float determinant = 0.0f;
                                                pModelSkinWeights->m_TransformLinkMatrix =
                                                        pModelSkinWeights->m_TransformLinkMatrix.Inverse(determinant);
                                            }
                                        }
                                    }
                                }

                                // get the weight bone name
                                if (pDeformers->m_Children[l]->m_pNode->GetValueCount() >= 2)
                                    pModelSkinWeights->m_BoneName = pDeformers->m_Children[l]->m_pNode->GetValue(1)->GetStr();

                                // get the weight matrix to apply
                                pModelSkinWeights->m_Matrix = pModelSkinWeights->m_TransformLinkMatrix;

                                // add model skin weights to model deformers
                                pModelDeformers->m_SkinWeights.push_back(pModelSkinWeights.get());
                                pModelSkinWeights.release();
                            }

                        // add model deformers to model
                        pModel->m_Deformers.push_back(pModelDeformers.get());
                        pModelDeformers.release();
                    }
            }
            else
            if (m_Links[i]->m_Children[j]->m_NodeType == IENodeType::IE_NT_Material)
            {
                // get grandchildren count
                const std::size_t grandChildCount = m_Links[i]->m_Children[j]->m_Children.size();

                // iterate through grandchildren
                for (std::size_t k = 0; k < grandChildCount; ++k)
                    // is a texture?
                    if (m_Links[i]->m_Children[j]->m_Children[k]->m_NodeType == IENodeType::IE_NT_Texture)
                    {
                        // get texture node
                        IFBXNode* pTextureNode = m_Links[i]->m_Children[j]->m_Children[k]->m_pNode;

                        // found it?
                        if (!pTextureNode)
                            continue;

                        // get texture node properties count
                        const std::size_t texPropCount = pTextureNode->GetPropCount();

                        // iterate through texture node properties
                        for (std::size_t l = 0; l < texPropCount; ++l)
                            // is a file name?
                            if (pTextureNode->GetProp(l)->GetName() == "FileName" && pTextureNode->GetProp(l)->GetValueCount())
                                // load texture callback defined?
                                if (m_fOnLoadTexture)
                                {
                                    // let the caller load and create the texture
                                    std::unique_ptr<Texture> pTexture(m_fOnLoadTexture(pTextureNode->GetProp(l)->GetValue(0)->GetStr(), true));

                                    // successfully created?
                                    if (pTexture)
                                        // add it to model
                                        pModelVB->m_Material.m_pTexture = pTexture.release();
                                }
                    }
            }
        }

        // link the built vertex buffer to its mesh
        std::unique_ptr<Mesh> pMesh(new Mesh());
        pMesh->m_VB.push_back(pModelVB.get());
        pModelVB.release();

        // link the built mesh to its model
        pModel->m_Mesh.push_back(pMesh.get());
        pMesh.release();
    }

    // keep the built model
    m_pModel = pModel.release();

    // to show only the pose without animation
    m_pModel->m_PoseOnly = m_PoseOnly;

    const std::size_t meshCount = m_pModel->m_Mesh.size();

    if (meshCount != m_Templates.size())
        return false;

    // should take care of the pose only?
    if (!m_pModel->m_PoseOnly)
        m_VBCache.resize(meshCount);

    // iterate through model meshes
    for (std::size_t i = 0; i < meshCount; ++i)
    {
        // get model mesh
        Mesh* pMesh = m_pModel->m_Mesh[i];

        // found it?
        if (!pMesh)
            continue;

        IIndexToInflDict indexToInfl;

        // should take care of the pose only?
        if (!m_pModel->m_PoseOnly)
        {
            const std::size_t weightCount = m_pModel->m_Deformers[i]->m_SkinWeights.size();

            // iterate through mesh skin weights
            for (std::size_t j = 0; j < weightCount; ++j)
            {
                // get the weight influence count
                const std::size_t weightInfluenceCount = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences.size();

                // iterate through weights influences
                for (std::size_t k = 0; k < weightInfluenceCount; ++k)
                {
                    // get weight index
                    const std::size_t weightIndex = m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]->m_Index;

                    // search for existing index in the dictionary
                    IIndexToInflDict::iterator it = indexToInfl.find(weightIndex);

                    // found it?
                    if (it == indexToInfl.end())
                    {
                        // create a new weight influence reference
                        Model::IWeightInfluences weightInfluences;
                        weightInfluences.push_back(m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]);

                        // add the index to the dictionary
                        indexToInfl[weightIndex] = weightInfluences;
                    }
                    else
                        // add the weight influence to the index
                        it->second.push_back(m_pModel->m_Deformers[i]->m_SkinWeights[j]->m_WeightInfluences[k]);
                }
            }
        }

        // populate the vertex buffer
        if (!PopulateVertexBuffer(m_Templates[i], pMesh->m_VB[0], &indexToInfl))
            return false;

        // should take care of the pose only?
        if (!m_pModel->m_PoseOnly)
        {
            // cache the vertex buffer
             m_VBCache[i] = new VertexBuffer::IData();
            *m_VBCache[i] = pMesh->m_VB[0]->m_Data;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool FBX::BuildSkeleton(IFBXLink*             pLink,
                        Model::IBone*         pBone,
                        IBoneDictionary&      boneDict,
                        Model::IAnimationSet* pAmimationSet,
                        bool                  isRoot) const
{
    if (!pLink)
        return false;

    if (!pBone)
        return false;

    // populate the bone
    if (!PopulateBone(pLink->m_pNode, pBone))
        return false;

    // get link child count
    const std::size_t childCount = pLink->m_Children.size();

    // iterate through link children
    for (std::size_t i = 0; i < childCount; ++i)
        if (pLink->m_Children[i]->m_NodeType == IENodeType::IE_NT_Model)
        {
            // found a model node, create a new child bone
            std::unique_ptr<Model::IBone> pChildBone(new Model::IBone);
            pChildBone->m_pParent = pBone;

            // add it to bone dictionary
            boneDict[pLink->m_Children[i]->m_pNode] = pChildBone.get();

            // build child bone children
            if (!BuildSkeleton(pLink->m_Children[i], pChildBone.get(), boneDict, pAmimationSet, false))
                return false;

            // add child bone to skeleton
            pBone->m_Children.push_back(pChildBone.get());
            pChildBone.release();
        }
        else
        if (pLink->m_Children[i]->m_NodeType == IENodeType::IE_NT_AnimationCurveNode)
        {
            // found an animation node, create a new animation and animation keys container
            std::unique_ptr<Model::IAnimation>     pAnimation    (new Model::IAnimation());
            std::unique_ptr<Model::IAnimationKeys> pAnimationKeys(new Model::IAnimationKeys());

            // animation node contains enough properties?
            if (pLink->m_Children[i]->m_pNode->GetValueCount() >= 2)
            {
                // get animation type
                const std::string type = pLink->m_Children[i]->m_pNode->GetValue(1)->GetStr();

                // animation type was declared?
                if (type.length())
                {
                    // get the last char
                    const std::size_t lastIndex = type.length() - 1;

                    // search for animation type
                    if (type[lastIndex] == 'T')
                        pAnimationKeys->m_Type = Model::IEAnimKeyType::IE_KT_Position;
                    else
                    if (type[lastIndex] == 'R')
                        pAnimationKeys->m_Type = Model::IEAnimKeyType::IE_KT_Rotation;
                    else
                    if (type[lastIndex] == 'S')
                        pAnimationKeys->m_Type = Model::IEAnimKeyType::IE_KT_Scale;
                    else
                        continue;
                }
            }

            // get animation child count
            const std::size_t nodeChildCount = pLink->m_Children[i]->m_Children.size();

            // iterate through animation children
            for (std::size_t j = 0; j < nodeChildCount; ++j)
                // found an animation curve?
                if (pLink->m_Children[i]->m_Children[j]->m_NodeType == IENodeType::IE_NT_AnimationCurve)
                {
                    // get animation curve
                    IFBXNode* pAnimationCurve = pLink->m_Children[i]->m_Children[j]->m_pNode;

                    // found it?
                    if (!pAnimationCurve)
                        continue;

                    IFBXArrayProperty<std::int64_t>* pKeys   = nullptr;
                    IFBXArrayProperty<double>*       pValues = nullptr;

                    // get animation curve child count
                    const std::size_t animCurveChildCount = pAnimationCurve->GetChildCount();

                    // iterate through animation curve children
                    for (std::size_t k = 0; k < animCurveChildCount; ++k)
                    {
                        // get animation curve property
                        IFBXNode* pAnimCurveChildNode = pAnimationCurve->GetChild(k);

                        // found a key time or key value array?
                        if (pAnimCurveChildNode && pAnimCurveChildNode->GetPropCount())
                            if (pAnimCurveChildNode->GetName() == "KeyTime")
                                pKeys = static_cast<IFBXArrayProperty<std::int64_t>*>(pAnimCurveChildNode->GetProp(0));
                            else
                            if (pAnimCurveChildNode->GetName() == "KeyValueFloat")
                                pValues = static_cast<IFBXArrayProperty<double>*>(pAnimCurveChildNode->GetProp(0));
                    }

                    // both keys and values should be found
                    if (!pKeys || !pValues)
                        continue;

                    // also the both arrays should have the same length
                    if (pKeys->GetCount() != pValues->GetCount())
                        continue;

                    // get animation value count
                    const std::size_t valueCount = pValues->GetCount();

                    // iterate through animation values
                    for (std::size_t k = 0; k < valueCount; ++k)
                    {
                        std::unique_ptr<Model::IAnimationKey> pNewAnimationKey;
                        Model::IAnimationKey*                 pAnimationKey;

                        // first curve?
                        if (!j)
                        {
                            // create a new animation key ans set its time stamp
                            pNewAnimationKey.reset(new Model::IAnimationKey());
                            pAnimationKey              = pNewAnimationKey.get();
                            pAnimationKey->m_TimeStamp = pKeys->Get(k);
                            pAmimationSet->m_MaxValue  = std::max(pAnimationKey->m_TimeStamp, pAmimationSet->m_MaxValue);
                        }
                        else
                            pAnimationKey = pAnimationKeys->m_Keys[k];

                        // set animation value
                        pAnimationKey->m_Values.push_back((float)pValues->Get(k));

                        // first curve?
                        if (!j)
                        {
                            // add key to animation key list
                            pAnimationKeys->m_Keys.push_back(pNewAnimationKey.get());
                            pNewAnimationKey.release();
                        }
                    }
                }

            // add animation key to animation
            pAnimation->m_Keys.push_back(pAnimationKeys.get());
            pAnimationKeys.release();

            // get the bone linked with the model
            IBoneDictionary::const_iterator it = m_BoneDict.find(pLink->m_pNode);

            // found it?
            if (it != m_BoneDict.end())
            {
                // link the bone to the animation
                pAnimation->m_BoneName = it->second->m_Name;
                pAnimation->m_pBone    = it->second;
            }

            // add the animation to the animation set
            pAmimationSet->m_Animations.push_back(pAnimation.get());
            pAnimation.release();
        }

    return true;
}
//---------------------------------------------------------------------------
bool FBX::PopulateBone(IFBXNode* pNode, Model::IBone* pBone) const
{
    if (!pNode)
        return false;

    if (!pBone)
        return false;

    std::string boneName;

    // get bone name, if any
    if (pNode->GetValueCount() >= 2)
        pBone->m_Name = pNode->GetValue(1)->GetStr();

    // get node child count
    const std::size_t count = pNode->GetChildCount();

    // iterate through child nodes
    for (std::size_t i = 0; i < count; ++i)
    {
        // get child
        IFBXNode* pChild = pNode->GetChild(i);

        // found it?
        if (!pChild)
            return false;

        // get properties set containing the bone data
        if (pChild->GetName() == "Properties70")
        {
            // get property count
            const std::size_t propCount = pChild->GetPropCount();

            DWF_Math::Vector3F    translation;
            DWF_Math::Vector3F    scaling(1.0f, 1.0f, 1.0f);
            DWF_Math::QuaternionF rotation;

            // iterate through properties
            for (std::size_t j = 0; j < propCount; ++j)
            {
                // get property
                IFBXProperty* pProp = pChild->GetProp(j);

                // found it?
                if (!pProp)
                    return false;

                // property contains values?
                if (pProp->GetValueCount())
                {
                    // get property name
                    const std::string name = pProp->GetValue(0)->GetRaw();

                    // search for local translation, rotation and scaling
                    if (name == "Lcl Translation")
                    {
                        IFBXLclTranslationProperty* pLclTransProp = static_cast<IFBXLclTranslationProperty*>(pProp);

                        if (!pLclTransProp)
                            return false;

                        translation = pLclTransProp->Get();
                    }
                    else
                    if (name == "Lcl Rotation")
                    {
                        IFBXLclRotationProperty* pLclRotatProp = static_cast<IFBXLclRotationProperty*>(pProp);

                        if (!pLclRotatProp)
                            return false;

                        rotation = pLclRotatProp->Get();
                    }
                    else
                    if (name == "Lcl Scaling")
                    {
                        IFBXLclScalingProperty* pLclScalingProp = static_cast<IFBXLclScalingProperty*>(pProp);

                        if (!pLclScalingProp)
                            return false;

                        scaling = pLclScalingProp->Get();
                    }
                }
            }

            // create the translation matrix
            DWF_Math::Matrix4x4F transMat = DWF_Math::Matrix4x4F::Identity();
            transMat.m_Table[3][0]        = translation.m_X;
            transMat.m_Table[3][1]        = translation.m_Y;
            transMat.m_Table[3][2]        = translation.m_Z;

            // get the rotation matrix
            const DWF_Math::Matrix4x4F rotMat = rotation.ToMatrix();

            // create the scale matrix
            DWF_Math::Matrix4x4F scaleMat = DWF_Math::Matrix4x4F::Identity();
            scaleMat.m_Table[0][0]        = scaling.m_X;
            scaleMat.m_Table[1][1]        = scaling.m_Y;
            scaleMat.m_Table[2][2]        = scaling.m_Z;

            // build the bone matrix
            pBone->m_Matrix = rotMat.Multiply(transMat).Multiply(scaleMat);

            // keep the source node as custom data, in order to reuse it later
            pBone->m_pCustom = pNode;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool FBX::PopulateVertexBuffer(const IMeshTemplate*    pMeshTemplate,
                                     VertexBuffer*     pModelVB,
                               const IIndexToInflDict* pIndexToInfl) const
{
    if (!pMeshTemplate)
        return false;

    if (!pModelVB)
        return false;

    DWF_Math::Vector3F vertex;
    DWF_Math::Vector3F normal;
    DWF_Math::Vector2F uv;

    // get the index count
    const std::size_t indicesCount = pMeshTemplate->m_pIndices->size();

    std::vector<std::int32_t> indices;
    indices.reserve(4);

    std::vector<std::int32_t> normalIndices;
    normalIndices.reserve(4);

    std::vector<std::int32_t> uvIndices;
    uvIndices.reserve(4);

    // iterate through indice
    for (std::size_t i = 0; i < indicesCount; ++i)
    {
        // get index
        const std::int32_t indice = (std::int32_t)(*pMeshTemplate->m_pIndices)[i];

        // is the last index of a group?
        if (indice >= 0)
        {
            // no, keep it
            indices.push_back(indice);
            normalIndices.push_back((std::int32_t)(*pMeshTemplate->m_pNormalIndices)[i]);
            uvIndices.push_back((std::int32_t)(*pMeshTemplate->m_pUVIndices)[i]);
        }
        else
        {
            // yes, calculate and keep the last index
            indices.push_back(std::abs(indice) - 1);
            normalIndices.push_back(std::abs((std::int32_t)(*pMeshTemplate->m_pNormalIndices)[i]));
            uvIndices.push_back(std::abs((std::int32_t)(*pMeshTemplate->m_pUVIndices)[i]));

            // is surface a polygon or a quad?
            switch (indices.size())
            {
                case 3:
                    // polygon, extract it
                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[0] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[0] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[0] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[0] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[0] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[0] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[0] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[0] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[0], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[1] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[1] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[1] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[1] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[1] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[1] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[1] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[1] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[1], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[2] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[2] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[2] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[2] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[2] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[2] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[2] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[2] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[2], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    break;

                case 4:
                    // quad, extract the first polygon...
                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[0] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[0] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[0] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[0] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[0] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[0] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[0] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[0] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[0], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[1] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[1] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[1] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[1] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[1] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[1] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[1] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[1] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[1], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[2] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[2] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[2] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[2] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[2] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[2] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[2] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[2] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[2], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    // ...and the second
                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[0] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[0] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[0] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[0] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[0] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[0] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[0] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[0] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[0], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[2] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[2] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[2] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[2] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[2] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[2] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[2] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[2] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[2], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    vertex.m_X = (float)(*pMeshTemplate->m_pVertices)[ (std::size_t)indices[3] * 3];
                    vertex.m_Y = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[3] * 3) + 1];
                    vertex.m_Z = (float)(*pMeshTemplate->m_pVertices)[((std::size_t)indices[3] * 3) + 2];

                    normal.m_X = (float)(*pMeshTemplate->m_pNormals)[ (std::size_t)normalIndices[3] * 3];
                    normal.m_Y = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[3] * 3) + 1];
                    normal.m_Z = (float)(*pMeshTemplate->m_pNormals)[((std::size_t)normalIndices[3] * 3) + 2];

                    uv.m_X     = (float)(*pMeshTemplate->m_pUVs)[ (std::size_t)uvIndices[3] * 2];
                    uv.m_Y     = (float)(*pMeshTemplate->m_pUVs)[((std::size_t)uvIndices[3] * 2) + 1];

                    AddWeightInfluence(pIndexToInfl, indices[3], pModelVB);
                    pModelVB->Add(&vertex, &normal, &uv, 0, m_fOnGetVertexColor);

                    break;
            }

            // clear the index table for the next round
            indices.clear();
            normalIndices.clear();
            uvIndices.clear();
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool FBX::GetAnimationMatrix(const Model::IAnimationSet* pAnimSet,
                             const Model::IBone*         pBone,
                                   double                elapsedTime,
                                   DWF_Math::Matrix4x4F& matrix) const
{
    // no animation set?
    if (!pAnimSet)
        return false;

    // no bone?
    if (!pBone)
        return false;

    // search for matrix in cache
    IAnimBoneCacheDict::const_iterator it = m_AnimBoneCacheDict.find(pBone);

    // found it?
    if (it != m_AnimBoneCacheDict.end())
    {
        // reuse it
        matrix = it->second;
        return true;
    }

    // iterate through animations
    for (std::size_t i = 0; i < pAnimSet->m_Animations.size(); ++i)
    {
        // found the animation matching with the bone for which the matrix should be get?
        if (pAnimSet->m_Animations[i]->m_pBone != pBone)
            continue;

        double                rotFrame       = 0.0;
        double                nextRotFrame   = 0.0;
        double                posFrame       = 0.0;
        double                nextPosFrame   = 0.0;
        double                scaleFrame     = 0.0;
        double                nextScaleFrame = 0.0;
        DWF_Math::Vector3F    rotation;
        DWF_Math::Vector3F    nextRotation;
        DWF_Math::QuaternionF finalRotation;
        DWF_Math::Vector3F    position;
        DWF_Math::Vector3F    nextPosition;
        DWF_Math::Vector3F    finalPosition;
        DWF_Math::Vector3F    scaling     (1.0f, 1.0f, 1.0f);
        DWF_Math::Vector3F    nextScaling (1.0f, 1.0f, 1.0f);
        DWF_Math::Vector3F    finalScaling(1.0f, 1.0f, 1.0f);

        bool foundTrans = false;
        bool foundRot   = false;
        bool foundScale = false;

        // iterate through animation keys
        for (std::size_t j = 0; j < pAnimSet->m_Animations[i]->m_Keys.size(); ++j)
        {
            std::size_t keyIndex = 0;

            // iterate through animation key items
            for (std::size_t k = 0; k < pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys.size(); ++k)
            {
                // the time unit in FBX (FbxTime) is 1/46186158000 of one second
                const double frameTime = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[k]->m_TimeStamp / 46186158000.0;

                if (elapsedTime >= frameTime)
                    keyIndex = k;
                else
                    break;
            }

            // search for keys type
            switch (pAnimSet->m_Animations[i]->m_Keys[j]->m_Type)
            {
                case Model::IEAnimKeyType::IE_KT_Position:
                    if (pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values.size() != 3)
                        return false;

                    // get the position values at index
                    position.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[0];
                    position.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[1];
                    position.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[2];
                    posFrame     = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_TimeStamp / 46186158000.0;

                    // get the next rotation quaternion
                    if (keyIndex + 1 >= pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys.size())
                    {
                        nextPosition.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[0];
                        nextPosition.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[1];
                        nextPosition.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[2];
                        nextPosFrame     = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_TimeStamp / 46186158000.0;
                    }
                    else
                    {
                        nextPosition.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[0];
                        nextPosition.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[1];
                        nextPosition.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[2];
                        nextPosFrame     = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_TimeStamp / 46186158000.0;
                    }

                    foundTrans = true;
                    continue;

                case Model::IEAnimKeyType::IE_KT_Rotation:
                    if (pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values.size() != 3)
                        return false;

                    // get the rotation quaternion at index
                    rotation.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[0];
                    rotation.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[1];
                    rotation.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[2];
                    rotFrame     = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_TimeStamp / 46186158000.0;

                    // get the next rotation quaternion
                    if (keyIndex + 1 >= pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys.size())
                    {
                        nextRotation.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[0];
                        nextRotation.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[1];
                        nextRotation.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[2];
                        nextRotFrame     = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_TimeStamp / 46186158000.0;
                    }
                    else
                    {
                        nextRotation.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[0];
                        nextRotation.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[1];
                        nextRotation.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[2];
                        nextRotFrame     = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_TimeStamp / 46186158000.0;
                    }

                    foundRot = true;
                    continue;

                case Model::IEAnimKeyType::IE_KT_Scale:
                    if (pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values.size() != 3)
                        return false;

                    // get the scale values at index
                    scaling.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[0];
                    scaling.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[1];
                    scaling.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_Values[2];
                    scaleFrame  = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex]->m_TimeStamp / 46186158000.0;

                    // get the next rotation quaternion
                    if (keyIndex + 1 >= pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys.size())
                    {
                        nextScaling.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[0];
                        nextScaling.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[1];
                        nextScaling.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_Values[2];
                        nextScaleFrame  = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[0]->m_TimeStamp / 46186158000.0;
                    }
                    else
                    {
                        nextScaling.m_X =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[0];
                        nextScaling.m_Y =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[1];
                        nextScaling.m_Z =         pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_Values[2];
                        nextScaleFrame  = (double)pAnimSet->m_Animations[i]->m_Keys[j]->m_Keys[keyIndex + 1]->m_TimeStamp / 46186158000.0;
                    }

                    foundScale = true;
                    continue;

                default:
                    continue;
            }
        }

        // process the translation
        if (foundTrans)
        {
            // calculate the frame delta, the frame length and the interpolation for the position
            float frameDelta    = (float)(elapsedTime - posFrame);
            float frameLength   = (float)(nextPosFrame - posFrame);
            float interpolation = frameLength ? frameDelta / frameLength : 0.0f;

            // interpolate the position
            finalPosition.m_X = (position.m_X + ((nextPosition.m_X - position.m_X) * interpolation)) * 1.0f;
            finalPosition.m_Y = (position.m_Y + ((nextPosition.m_Y - position.m_Y) * interpolation)) * 1.0f;
            finalPosition.m_Z = (position.m_Z + ((nextPosition.m_Z - position.m_Z) * interpolation)) * 1.0f;
        }
        else
        {
            // get the original position from the bone matrix
            finalPosition.m_X = pBone->m_Matrix.m_Table[3][0];
            finalPosition.m_Y = pBone->m_Matrix.m_Table[3][1];
            finalPosition.m_Z = pBone->m_Matrix.m_Table[3][2];
        }

        // process the rotation
        if (foundRot)
        {
            // calculate the frame delta, the frame length and the interpolation for the rotation
            float frameDelta    = (float)(elapsedTime  - rotFrame);
            float frameLength   = (float)(nextRotFrame - rotFrame);
            float interpolation = frameLength ? frameDelta / frameLength : 0.0f;

            // degree to radians conversion constant
            const float degToRad = (float)(M_PI / 180.0f);

            DWF_Math::QuaternionF qx;
            DWF_Math::QuaternionF qy;
            DWF_Math::QuaternionF qz;

            // build the quaternion from current rotation
            qx.FromAxis(-rotation.m_X * degToRad, DWF_Math::Vector3F(1.0f, 0.0f, 0.0f));
            qy.FromAxis(-rotation.m_Y * degToRad, DWF_Math::Vector3F(0.0f, 1.0f, 0.0f));
            qz.FromAxis(-rotation.m_Z * degToRad, DWF_Math::Vector3F(0.0f, 0.0f, 1.0f));

            DWF_Math::QuaternionF q = qx.Multiply(qy).Multiply(qz).Normalize();

            // build the quaternion from next rotation
            qx.FromAxis(-nextRotation.m_X * degToRad, DWF_Math::Vector3F(1.0f, 0.0f, 0.0f));
            qy.FromAxis(-nextRotation.m_Y * degToRad, DWF_Math::Vector3F(0.0f, 1.0f, 0.0f));
            qz.FromAxis(-nextRotation.m_Z * degToRad, DWF_Math::Vector3F(0.0f, 0.0f, 1.0f));

            DWF_Math::QuaternionF nq = qx.Multiply(qy).Multiply(qz).Normalize();

            bool error = false;

            // interpolate the rotation
            finalRotation = q.Slerp(nq, interpolation, error);
        }
        else
        {
            const IFBXNode*             pSrcNode = static_cast<IFBXNode*>(pBone->m_pCustom);
                  DWF_Math::QuaternionF srcRot;

            if (pSrcNode)
            {
                // get node child count
                const std::size_t count = pSrcNode->GetChildCount();

                // iterate through child nodes
                for (std::size_t i = 0; i < count; ++i)
                {
                    // get child
                    IFBXNode* pChild = pSrcNode->GetChild(i);

                    // found it?
                    if (!pChild)
                        return false;

                    // get properties set containing the bone data
                    if (pChild->GetName() == "Properties70")
                    {
                        // get property count
                        const std::size_t propCount = pChild->GetPropCount();

                        // iterate through properties
                        for (std::size_t j = 0; j < propCount; ++j)
                        {
                            // get property
                            IFBXProperty* pProp = pChild->GetProp(j);

                            // found it?
                            if (!pProp)
                                return false;

                            // property contains values?
                            if (pProp->GetValueCount())
                            {
                                // get property name
                                const std::string name = pProp->GetValue(0)->GetRaw();

                                // search for local rotation
                                if (name == "Lcl Rotation")
                                {
                                    IFBXLclRotationProperty* pLclRotatProp = static_cast<IFBXLclRotationProperty*>(pProp);

                                    if (!pLclRotatProp)
                                        return false;

                                    srcRot = pLclRotatProp->Get();
                                }
                            }
                        }
                    }
                }
            }

            finalRotation = srcRot;
        }

        // process the scaling
        if (foundScale)
        {
            // calculate the frame delta, the frame length and the interpolation for the scaling
            float frameDelta    = (float)(elapsedTime    - scaleFrame);
            float frameLength   = (float)(nextScaleFrame - scaleFrame);
            float interpolation = frameLength ? frameDelta / frameLength : 0.0f;

            // interpolate the scaling
            finalScaling.m_X = scaling.m_X + ((nextScaling.m_X - scaling.m_X) * interpolation);
            finalScaling.m_Y = scaling.m_Y + ((nextScaling.m_Y - scaling.m_Y) * interpolation);
            finalScaling.m_Z = scaling.m_Z + ((nextScaling.m_Z - scaling.m_Z) * interpolation);
        }
        else
        {
            finalScaling.m_X = 1.0f;
            finalScaling.m_Y = 1.0f;
            finalScaling.m_Z = 1.0f;
        }

        // create the translation matrix
        DWF_Math::Matrix4x4F translateMatrix = DWF_Math::Matrix4x4F::Identity();
        translateMatrix.m_Table[3][0]        = finalPosition.m_X;
        translateMatrix.m_Table[3][1]        = finalPosition.m_Y;
        translateMatrix.m_Table[3][2]        = finalPosition.m_Z;

        // get the rotation matrix
        const DWF_Math::Matrix4x4F rotateMatrix = finalRotation.ToMatrix();

        // create the scale matrix
        DWF_Math::Matrix4x4F scaleMatrix = DWF_Math::Matrix4x4F::Identity();
        scaleMatrix.m_Table[0][0]        = finalScaling.m_X;
        scaleMatrix.m_Table[1][1]        = finalScaling.m_Y;
        scaleMatrix.m_Table[2][2]        = finalScaling.m_Z;

        // build the final matrix
        matrix = rotateMatrix.Multiply(translateMatrix).Multiply(scaleMatrix);

        // cache the matrix
        m_AnimBoneCacheDict[pBone] = matrix;

        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void FBX::AddWeightInfluence(const IIndexToInflDict* pIndexToInfl, std::size_t indice, VertexBuffer* pModelVB) const
{
    if (!pIndexToInfl)
        return;

    IIndexToInflDict::const_iterator it = pIndexToInfl->find(indice);

    if (it != pIndexToInfl->end())
    {
        const std::size_t weightInflCount = it->second.size();

        for (std::size_t j = 0; j < weightInflCount; ++j)
            it->second[j]->m_VertexIndex.push_back(pModelVB->m_Data.size());
    }
}
//---------------------------------------------------------------------------
