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

#pragma once

// std
#include <string>
#include <vector>
#include <ctime>
#include <set>

// classes
#include "DWF_Buffer.h"
#include "DWF_Color.h"
#include "DWF_Vector3.h"
#include "DWF_Quaternion.h"
#include "DWF_Matrix4x4.h"
#include "DWF_AnimModelFormat.h"
#include "DWF_Model.h"

namespace DWF_Model
{
    /**
    * FilmBox (.fbx) model loader
    *@author Jean-Milost Reymond
    */
    class FBX : public AnimModelFormat
    {
        public:
            /**
            * FBX data type
            */
            enum class IEDataType
            {
                IE_DT_Unknown = 0,
                IE_DT_Data,
                IE_DT_Int,
                IE_DT_Float,
                IE_DT_String,
                IE_DT_KeySeparator,
                IE_DT_ValueSeparator,
                IE_DT_StartNodeSeparator,
                IE_DT_EndNodeSeparator,
                IE_DT_Comment
            };

            /**
            * FBX data
            */
            struct IFBXData
            {
                IEDataType         m_Type      = IEDataType::IE_DT_Unknown;
                const std::string* m_pData     = nullptr;
                std::size_t        m_Start     = 0;
                std::size_t        m_End       = 0;
                mutable bool       m_IsCounter = false;

                /**
                * Constructor
                *@param pData - data to read from
                */
                IFBXData(const std::string* pData);

                /**
                * Constructor
                *@param type - data type
                *@param pData - data to read from
                *@param start - data start index
                *@param end - data end index
                */
                IFBXData(IEDataType type, const std::string* pData, std::size_t start, std::size_t end);

                /**
                * Gets raw value as a string
                *@return string containing raw value, empty string if not found or on error
                */
                virtual std::string GetRaw() const;

                /**
                * Gets data content as a boolean value
                *@return value, false if not found or on error
                */
                virtual bool GetBool() const;

                /**
                * Gets data content as an integer value
                *@return value, 0 if not found or on error
                */
                virtual std::int32_t GetInt() const;

                /**
                * Gets data content as a long integer value
                *@return value, 0L if not found or on error
                */
                virtual std::int64_t GetLongLong() const;

                /**
                * Gets data content as a float value
                *@return value, 0.0f if not found or on error
                */
                virtual float GetFloat() const;

                /**
                * Gets data content as a double value
                *@return value, 0.0 if not found or on error
                */
                virtual double GetDouble() const;

                /**
                * Gets data content as a string
                *@return string, empty string if not found or on error
                */
                virtual std::string GetStr() const;

                /**
                * Gets data content as a generic value
                *@return value, 0.0 if not found or on error
                */
                template <class T>
                T GetT() const;
            };

            /**
            * FBX dataset
            */
            typedef std::vector<IFBXData*> IFBXDataset;

            /**
            * FBX item
            */
            class IFBXItem
            {
                public:
                    IFBXItem();
                    virtual ~IFBXItem();

                    /**
                    * Sets the item name
                    *@param name - item name
                    */
                    virtual void SetName(const std::string& name);

                    /**
                    * Gets the item name
                    *@return the item name
                    */
                    virtual std::string GetName() const;

                    /**
                    * Sets the item parent
                    *@param pParent - item parent
                    */
                    virtual void SetParent(IFBXItem* pParent);

                    /**
                    * Gets the item parent
                    *@return the item parent
                    */
                    virtual IFBXItem* GetParent() const;

                    /**
                    * Adds a value to a node
                    *@param pValue - value to add
                    *@note The value will be deleted internally, do not delete it from outside
                    */
                    virtual void AddValue(IFBXData* pValue);

                    /**
                    * Gets a value contained in the node
                    *@param index - value index
                    *@return value (as data), nullptr if not found or on error
                    */
                    virtual IFBXData* GetValue(std::size_t index) const;

                    /**
                    * Gets the value count
                    *@return the value count
                    */
                    virtual std::size_t GetValueCount() const;

                private:
                    IFBXItem*   m_pParent = nullptr;
                    IFBXDataset m_Values;
                    std::string m_Name;
            };

            /**
            * FBX items
            */
            typedef std::vector<IFBXItem*> IFBXItems;

            /**
            * FBX property type
            */
            enum class IEPropType
            {
                IE_PT_Unknown = 0,
                IE_PT_Bool,
                IE_PT_Int,
                IE_PT_Double,
                IE_PT_ULongLong,
                IE_PT_String,
                IE_PT_Number,
                IE_PT_Color,
                IE_PT_ColorRGB,
                IE_PT_Vector,
                IE_PT_Vector3D,
                IE_PT_Time,
                IE_PT_DateTime,
                IE_PT_Enum,
                IE_PT_LclTranslation,
                IE_PT_LclRotation,
                IE_PT_LclScaling,
                IE_PT_Visibility,
                IE_PT_VisibilityInheritance,
                IE_PT_Compound,
                IE_PT_Object,
                IE_PT_Array
            };

            /**
            * FBX property
            */
            class IFBXProperty : public IFBXItem
            {
                public:
                    /**
                    * Constructor
                    *@param propType - property type
                    */
                    IFBXProperty(IEPropType propType);

                    virtual ~IFBXProperty();

                    /**
                    * Gets the item name
                    *@return the item name, empty string if not found or on error
                    */
                    virtual std::string GetPropName() const;

                    /**
                    * Gets the property type
                    *@return the property type
                    */
                    virtual IEPropType GetType() const;

                protected:
                    mutable bool m_Cached = false;

                private:
                    mutable std::string m_PropName;
                    IEPropType          m_PropType = IEPropType::IE_PT_Unknown;
            };

            /**
            * FBX properties
            */
            typedef std::vector<IFBXProperty*> IFBXProperties;

            /**
            * FBX unknown property
            */
            class IFBXUnknownProperty : public IFBXProperty
            {
                public:
                    IFBXUnknownProperty();
                    virtual ~IFBXUnknownProperty();
            };

            /**
            * FBX boolean property
            */
            class IFBXBoolProperty : public IFBXProperty
            {
                public:
                    IFBXBoolProperty();
                    virtual ~IFBXBoolProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual bool Get() const;

                private:
                    mutable bool m_Value = false;
            };

            /**
            * FBX integer property
            */
            class IFBXIntProperty : public IFBXProperty
            {
                public:
                    IFBXIntProperty();
                    virtual ~IFBXIntProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::int32_t Get() const;

                private:
                    mutable std::int32_t m_Value = 0;
            };

            /**
            * FBX double property
            */
            class IFBXDoubleProperty : public IFBXProperty
            {
                public:
                    IFBXDoubleProperty();
                    virtual ~IFBXDoubleProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual double Get() const;

                private:
                    mutable double m_Value = 0.0;
            };

            /**
            * FBX long long property
            */
            class IFBXLongLongProperty : public IFBXProperty
            {
                public:
                    IFBXLongLongProperty();
                    virtual ~IFBXLongLongProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::int64_t Get() const;

                private:
                    mutable std::int64_t m_Value = 0L;
            };

            /**
            * FBX string property
            */
            class IFBXStringProperty : public IFBXProperty
            {
                public:
                    IFBXStringProperty();
                    virtual ~IFBXStringProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::string Get() const;

                private:
                    mutable std::string m_Value;
            };

            /**
            * FBX number property
            */
            class IFBXNumberProperty : public IFBXProperty
            {
                public:
                    IFBXNumberProperty();
                    virtual ~IFBXNumberProperty();

                    /**
                    * Gets the value
                    *@param index - the value index
                    *@return the value, 0.0 if not found or on error
                    */
                    virtual double Get(std::size_t index) const;

                    /**
                    * Gets the value count
                    *@return the value count
                    */
                    virtual std::size_t GetCount() const;

                private:
                    mutable std::vector<double> m_Values;

                    /**
                    * Gets and caches all the values
                    */
                    void GetValues() const;
            };

            /**
            * FBX color property
            */
            class IFBXColorProperty : public IFBXProperty
            {
                public:
                    IFBXColorProperty();
                    virtual ~IFBXColorProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual ColorF Get() const;

                private:
                    mutable ColorF m_Value;
            };

            /**
            * FBX color RGB property
            */
            class IFBXColorRGBProperty : public IFBXProperty
            {
                public:
                    IFBXColorRGBProperty();
                    virtual ~IFBXColorRGBProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual ColorF Get() const;

                private:
                    mutable ColorF m_Value;
            };

            /**
            * FBX vector property
            */
            class IFBXVectorProperty : public IFBXProperty
            {
                public:
                    IFBXVectorProperty();
                    virtual ~IFBXVectorProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual DWF_Math::Vector3F Get() const;

                private:
                    mutable DWF_Math::Vector3F m_Value;
            };

            /**
            * FBX vector 3D property
            */
            class IFBXVector3DProperty : public IFBXProperty
            {
                public:
                    IFBXVector3DProperty();
                    virtual ~IFBXVector3DProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual DWF_Math::Vector3F Get() const;

                private:
                    mutable DWF_Math::Vector3F m_Value;
            };

            /**
            * FBX time property
            */
            class IFBXTimeProperty : public IFBXProperty
            {
                public:
                    IFBXTimeProperty();
                    virtual ~IFBXTimeProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::time_t Get() const;

                private:
                    mutable std::time_t m_Value = 0;
            };

            /**
            * FBX date and time property
            */
            class IFBXDateTimeProperty : public IFBXProperty
            {
                public:
                    IFBXDateTimeProperty();
                    virtual ~IFBXDateTimeProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::string Get() const;

                private:
                    mutable std::string m_Value;
            };

            /**
            * FBX enumerated value property
            */
            class IFBXEnumProperty : public IFBXProperty
            {
                public:
                    IFBXEnumProperty();
                    virtual ~IFBXEnumProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::int32_t Get() const;

                private:
                    mutable std::int32_t m_Value = 0;
            };

            /**
            * FBX local translation property
            */
            class IFBXLclTranslationProperty : public IFBXProperty
            {
                public:
                    IFBXLclTranslationProperty();
                    virtual ~IFBXLclTranslationProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual DWF_Math::Vector3F Get() const;

                private:
                    mutable DWF_Math::Vector3F m_Value;
            };

            /**
            * FBX local rotation property
            */
            class IFBXLclRotationProperty : public IFBXProperty
            {
                public:
                    IFBXLclRotationProperty();
                    virtual ~IFBXLclRotationProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual DWF_Math::QuaternionF Get() const;

                private:
                    mutable DWF_Math::QuaternionF m_Value;
            };

            /**
            * FBX local scaling property
            */
            class IFBXLclScalingProperty : public IFBXProperty
            {
                public:
                    IFBXLclScalingProperty();
                    virtual ~IFBXLclScalingProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual DWF_Math::Vector3F Get() const;

                private:
                    mutable DWF_Math::Vector3F m_Value = DWF_Math::Vector3F(1.0f, 1.0f, 1.0f);
            };

            /**
            * FBX visibility property
            */
            class IFBXVisibilityProperty : public IFBXProperty
            {
                public:
                    IFBXVisibilityProperty();
                    virtual ~IFBXVisibilityProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual bool Get() const;

                private:
                    mutable bool m_Value = false;
            };

            /**
            * FBX visibility inheritance property
            */
            class IFBXVisibilityInheritanceProperty : public IFBXProperty
            {
                public:
                    IFBXVisibilityInheritanceProperty();
                    virtual ~IFBXVisibilityInheritanceProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual bool Get() const;

                private:
                    mutable bool m_Value = false;
            };

            /**
            * FBX compound property
            */
            class IFBXCompoundProperty : public IFBXProperty
            {
                public:
                    IFBXCompoundProperty();
                    virtual ~IFBXCompoundProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::string Get() const;

                private:
                    mutable std::string m_Value;
            };

            /**
            * FBX object property
            */
            class IFBXObjectProperty : public IFBXProperty
            {
                public:
                    IFBXObjectProperty();
                    virtual ~IFBXObjectProperty();

                    /**
                    * Gets the value
                    *@return the value
                    */
                    virtual std::string Get() const;

                private:
                    mutable std::string m_Value;
            };

            /**
            * FBX array property
            */
            template <class T>
            class IFBXArrayProperty : public IFBXProperty
            {
                public:
                    /**
                    * Constructor
                    *@param capacity - array capacity, ignored if 0
                    */
                    IFBXArrayProperty(std::size_t capacity);

                    virtual ~IFBXArrayProperty();

                    /**
                    * Gets the value at index
                    *@param index - the value index
                    *@return the value, 0 if not found or on error
                    */
                    virtual T Get(std::size_t index) const;

                    /**
                    * Gets the value count
                    *@return the value count
                    */
                    virtual std::size_t GetCount() const;

                    /**
                    * Gets the values array pointer
                    *@return the values array pointer
                    */
                    const std::vector<T>* GetPtr() const;

                private:
                    mutable std::vector<T> m_Values;
                    std::size_t            m_Capacity = 0;

                    /**
                    * Gets and caches all the values
                    */
                    void GetValues() const;
            };

            /**
            * FBX node
            */
            class IFBXNode : public IFBXItem
            {
                public:
                    IFBXNode();
                    virtual ~IFBXNode();

                    /**
                    * Adds a property to a node
                    *@param pProp - property to add
                    *@note The property will be deleted internally, do not delete it from outside
                    */
                    virtual void AddProp(IFBXProperty* pProp);

                    /**
                    * Gets a property contained in the node
                    *@param index - property index
                    *@return property, nullptr if not found or on error
                    */
                    virtual IFBXProperty* GetProp(std::size_t index) const;

                    /**
                    * Gets the property count
                    *@return the property count
                    */
                    virtual std::size_t GetPropCount() const;

                    /**
                    * Adds a child to a node
                    *@param pChild - child to add
                    *@note The child will be deleted internally, do not delete it from outside
                    */
                    virtual void AddChild(IFBXNode* pChild);

                    /**
                    * Gets a child contained in the node
                    *@param index - child index
                    *@return child, nullptr if not found or on error
                    */
                    virtual IFBXNode* GetChild(std::size_t index) const;

                    /**
                    * Gets the child count
                    *@return the child count
                    */
                    virtual std::size_t GetChildCount() const;

                private:
                    IFBXItems m_Props;
                    IFBXItems m_Children;
            };

            /**
            * FBX nodes
            */
            typedef std::vector<IFBXNode*> IFBXNodes;

            FBX();
            virtual ~FBX();

            /**
            * Clears the model
            */
            virtual void Clear();

            /**
            * Opens a FBX model from a file
            *@param fileName - FBX file name to open
            *@return true on success, otherwise false
            */
            virtual bool Open(const std::string&  fileName);
            virtual bool Open(const std::wstring& fileName);

            /**
            * Opens a FBX model from a buffer
            *@param buffer - buffer containing FBX file to open
            *@return true on success, otherwise false
            */
            virtual bool Open(DWF_Buffer::Buffer& fileName);

            /**
            * Reads a FBX data
            *@param data - FBX data to open
            *@return true on success, otherwise false
            */
            virtual bool Read(const std::string& data);

            /**
            * Gets the default model
            *@return the model, nullptr if no model or on error
            */
            virtual Model* GetModel() const;

            /**
            * Gets the model
            *@param animSetIndex - animation set index
            *@param elapsedTime - elapsed time in milliseconds
            *@return a ready-to-draw copy of the model, nullptr on error
            *@note The model will be deleted internally, do not delete it from outside
            */
            virtual Model* GetModel(std::int32_t animSetIndex, double elapsedTime) const;

            /**
            * Gets the model
            *@param animSetIndex - animation set index
            *@param frameCount - frame count
            *@param frameInex - frame index
            *@return a ready-to-draw copy of the model, nullptr on error
            *@note The model will be deleted internally, do not delete it from outside
            */
            virtual Model* GetModel(int animSetIndex, int frameCount, int frameIndex) const;

            /**
            * Gets the bone animation matrix
            *@param pBone - skeleton root bone
            *@param pAnimSet - animation set containing the animation to get
            *@param elapsedTime - elapsed time in milliseconds
            *@param initialMatrix - the initial matrix
            *@param[out] matrix - animation matrix
            */
            virtual void GetBoneAnimMatrix(const Model::IBone*         pBone,
                                           const Model::IAnimationSet* pAnimSet,
                                                 double                elapsedTime,
                                           const DWF_Math::Matrix4x4F& initialMatrix,
                                                 DWF_Math::Matrix4x4F& matrix) const;

            /**
            * Sets if only the pose should be rendered, without animation
            *@param value - if true, only the pose will be rendered
            *@note This function should be called before open the model
            */
            virtual void SetPoseOnly(bool value);

            /**
            * Sets the OnGetVertexColor callback
            *@param fOnGetVertexColor - callback function handle
            */
            void Set_OnGetVertexColor(VertexBuffer::ITfOnGetVertexColor fOnGetVertexColor);

            /**
            * Sets the OnLoadTexture callback
            *@param fOnLoadTexture - callback function handle
            */
            void Set_OnLoadTexture(Texture::ITfOnLoadTexture fOnLoadTexture);

        private:
            /**
            * Unique IDs to items dictionary
            */
            typedef std::map<std::string, IFBXItem*> IItemDictionary;

            /**
            * FBX helper functions
            */
            class IFBXHelper
            {
                public:
                    /**
                    * Trims all unused chars before and after a string
                    *@param str - string to trim
                    @return trimmed string
                    */
                    static std::string Trim(const std::string& str);

                    /**
                    * Forces all the chars between a and z to be in lower case
                    *@param str - string to lower
                    *@return lowered string
                    */
                    static std::string ToLower(const std::string& str);

                    /**
                    * Splits a string by delimiter
                    *@param str - string to split
                    *@param delimiter - delimiter
                    *@param[out] result - vector containing split strings
                    */
                    static void Split(const std::string&              str,
                                      const std::string&              delimiter,
                                            std::vector<std::string>& result);

                    /**
                    * Converts a string to a boolean value
                    *@param str - string to convert
                    *@return converted boolean value
                    */
                    static bool StrToBool(const std::string& str);
            };

            /**
            * Connection types
            */
            enum class IEConnectionType
            {
                IE_CT_ObjObj,  // object to object (OO) connection
                IE_CT_ObjProp, // object to property (OP) connection
                IE_CT_PropObj, // property to object (PO) connection
                IE_CT_PropProp // property to property (PP) connection
            };

            /**
            * Node types
            */
            enum class IENodeType
            {
                IE_NT_Model,
                IE_NT_Geometry,
                IE_NT_Material,
                IE_NT_Texture,
                IE_NT_Video,
                IE_NT_Deformer,
                IE_NT_NodeAttribute,
                IE_NT_AnimationCurve,
                IE_NT_AnimationCurveNode
            };

            struct IFBXLink;

            /**
            * FBX link list
            */
            typedef std::vector<IFBXLink*> IFBXLinks;

            /**
            * FBX link
            */
            struct IFBXLink
            {
                IENodeType  m_NodeType = IENodeType::IE_NT_Model;
                IFBXNode*   m_pNode    = nullptr;
                IFBXLink*   m_pParent  = nullptr;
                IFBXLinks   m_Children;
                std::string m_PropDesc;

                IFBXLink();
                ~IFBXLink();
            };

            /**
             * Mesh template, contains the source data to use to generate the model meshes vertex buffers
             */
            struct IMeshTemplate
            {
                const std::vector<double>*      m_pVertices      = nullptr;
                const std::vector<std::size_t>* m_pIndices       = nullptr;
                const std::vector<double>*      m_pNormals       = nullptr;
                const std::vector<std::size_t>* m_pNormalIndices = nullptr;
                const std::vector<double>*      m_pUVs           = nullptr;
                const std::vector<std::size_t>* m_pUVIndices     = nullptr;

                IMeshTemplate();
                ~IMeshTemplate();

                /**
                * Checks if mesh template is valid
                *@return true if mesh template is valid, otherwise false
                */
                bool IsValid() const;
            };

            typedef std::vector<IMeshTemplate*> IMeshTemplates;

            /**
            * Used properties set
            */
            typedef std::set<IFBXProperty*> IUsedProps;

            /**
            * Index to weight influence dictionary
            */
            typedef std::map<std::size_t, Model::IWeightInfluences> IIndexToInflDict;

            /**
            * Bone dictionary
            */
            typedef std::map<IFBXNode*, Model::IBone*> IBoneDictionary;

            /**
            * Animated bone cache dictionary
            */
            typedef std::map<const Model::IBone*, DWF_Math::Matrix4x4F> IAnimBoneCacheDict;

            /**
            * Source vertex buffer cache
            */
            typedef std::vector<VertexBuffer::IData*> IVBCache;

            IFBXNodes                         m_Nodes;
            IFBXLinks                         m_Links;
            IMeshTemplates                    m_Templates;
            IUsedProps                        m_UsedProps;
            IItemDictionary                   m_ItemDict;
            IBoneDictionary                   m_BoneDict;
            mutable IAnimBoneCacheDict        m_AnimBoneCacheDict;
            IVBCache                          m_VBCache;
            Model*                            m_pModel            = nullptr;
            std::string                       m_Data;
            bool                              m_PoseOnly          = false;
            VertexBuffer::ITfOnGetVertexColor m_fOnGetVertexColor = nullptr;
            Texture::ITfOnLoadTexture         m_fOnLoadTexture    = nullptr;

            /**
            * Clears a dataset
            *@param dataset - dataset to clear
            */
            void ClearDataset(IFBXDataset& dataset) const;

            /**
            * Skips a comment line
            *@param data - FBX data to read from
            *@param[in, out] index - index where comment starts, index after the comment line on function ends
            */
            void SkipComment(const std::string& data, std::size_t& index) const;

            /**
            * Reads a word in the FBX data
            *@param data - data to read in
            *@param length - data length
            *@param[in, out] index - index to start from, index after last read word on function ends
            *@return FBX data containing the word
            */
            IFBXData* ReadWord(const std::string& data, std::size_t length, std::size_t& index) const;

            /**
            * Sets a child node in a parent node
            *@param name - node name
            *@param[in, out] pParent - parent node, new parent node on function ends
            *@param nodes - root node list
            *@param dataset - dataset containing the node data
            *@param itemDict - item dictionary
            */
            void SetNode(const std::string&     name,
                               IFBXNode*&       pParent,
                               IFBXNodes&       nodes,
                               IFBXDataset&     dataset,
                               IItemDictionary& itemDict) const;

            /**
            * Sets a property in a parent node
            *@param name - property name
            *@param pParent - parent node
            *@param dataset - dataset containing the property data
            *@param start - property data start index in the dataset
            *@param end - property data end index in the dataset
            *@return true on success, otherwise false
            */
            bool SetProperty(const std::string& name,
                                   IFBXNode*    pParent,
                             const IFBXDataset& dataset,
                                   std::size_t  start,
                                   std::size_t  end) const;

            /**
            * Performs the model links
            *@return true on success, otherwise false
            */
            bool PerformLinks();

            /**
            * Performs the link between 2 FBX objects
            *@param pParentLink - parent link in which the link will be added
            *@param id - parent link identifier
            *@param pConnections - connection list containing all the links to perform
            *@return true on success, otherwise false
            */
            bool PerformLink(IFBXLink* pParentLink, std::size_t id, IFBXNode* pConnections);

            /**
            * Gets the link data
            *@param pProp - property containing the link
            *@param[out] type - connection type
            *@param[out] srcID - source identifier (i.e. object id which belongs to destination object)
            *@param[out] dstID - destination identifier (i.e. object which will contain the source object)
            *@param[out] propDesc - property description (optional, empty if destination isn't a property)
            *@return true on success, otherwise false
            */
            bool GetLinkData(IFBXProperty*     pProp,
                             IEConnectionType& type,
                             std::size_t&      srcID,
                             std::size_t&      dstID,
                             std::string&      propDesc) const;

            /**
            * Logs the links hierarchy
            *@param[out] log - log content
            */
            #ifdef _DEBUG
                void LogLinks(std::string& log) const;
            #endif

            /**
            * Logs a link and its children
            *@param pLink - link to log
            *@param tab - tabulation
            *@param[out] log - log content
            */
            #ifdef _DEBUG
                void LogLink(IFBXLink* pLink, std::uint32_t tab, std::string& log) const;
            #endif

            /**
            * Builds the model
            *@return true on success, otherwise false
            */
            bool BuildModel();

            /**
            * Builds the skeleton
            *@param pLink - link containing the bone data
            *@param pBone - if true, link contains the skeleton root node
            *@param boneDict - bone dictionary
            *@param pAmimationSet - mesh animation set
            *@param isRoot - if true, the bone represents the root bone, i.e the skeleton itself
            *@return true on success, otherwise false
            */
            bool BuildSkeleton(IFBXLink*             pLink,
                               Model::IBone*         pBone,
                               IBoneDictionary&      boneDict,
                               Model::IAnimationSet* pAmimationSet,
                               bool                  isRoot) const;

            /**
            * Populates a bone
            *@param pNode - node containing the bone data
            *@param pBone - if true, link contains the skeleton root node
            *@param boneDict - bone dictionary
            *@return true on success, otherwise false
            */
            bool PopulateBone(IFBXNode* pNode, Model::IBone* pBone) const;

            /**
            * Populates the vertex buffer
            *@param pMeshTemplate - mesh templates to use to populate the vertex buffer
            *@param pModelVB - model vertex buffer to populate
            *@param pIndexToInfl - index to influence dictionary, ignored if nullptr
            *@return true on success, otherwise false
            */
            bool PopulateVertexBuffer(const IMeshTemplate*    pMeshTemplate,
                                            VertexBuffer*     pModelVB,
                                      const IIndexToInflDict* pIndexToInfl) const;

            /**
            * Gets the animation matrix
            *@param pAnimSet - animation set containing the animation to search
            *@param pBone - skeleton root bone
            *@param elapsedTime - elapsed time in milliseconds
            *@param[out] matrix - animation matrix
            *@return true on success, otherwise false
            */
            bool GetAnimationMatrix(const Model::IAnimationSet* pAnimSet,
                                    const Model::IBone*         pBone,
                                          double                elapsedTime,
                                          DWF_Math::Matrix4x4F& matrix) const;

            /**
            * Add a weight influence for a vertex buffer
            *@param pIndexToInfl - index to influence dictionary
            *@param indice - vertex indice in the source buffer
            *@param pModelVB - model vertex buffer in which the weight influence index should be added
            */
            void AddWeightInfluence(const IIndexToInflDict* pIndexToInfl, std::size_t indice, VertexBuffer* pModelVB) const;
    };

    //---------------------------------------------------------------------------
    // FBX::IFBXData
    //---------------------------------------------------------------------------
    template <class T>
    T FBX::IFBXData::GetT() const
    {
        // get raw value
        const std::string str = GetRaw();

        // found it?
        if (str.empty())
            return (T)0;

        // convert raw data to double
        T value = (T)0;
        std::istringstream sstr(str);
        sstr >> value;

        // full string must be converted for success
        if (sstr.rdstate() == std::ios_base::eofbit)
            return value;

        return (T)0;
    }
    //---------------------------------------------------------------------------
    // FBX::IFBXArrayProperty
    //---------------------------------------------------------------------------
    template <class T>
    FBX::IFBXArrayProperty<T>::IFBXArrayProperty(std::size_t capacity) :
        IFBXProperty(IEPropType::IE_PT_Array),
        m_Capacity(capacity)
    {}
    //---------------------------------------------------------------------------
    template <class T>
    FBX::IFBXArrayProperty<T>::~IFBXArrayProperty()
    {}
    //---------------------------------------------------------------------------
    template <class T>
    T FBX::IFBXArrayProperty<T>::Get(std::size_t index) const
    {
        // already cached?
        if (!m_Cached)
            GetValues();

        // is index out of bounds?
        if (index >= m_Values.size())
            return (T)0;

        return m_Values[index];
    }
    //---------------------------------------------------------------------------
    template <class T>
    std::size_t FBX::IFBXArrayProperty<T>::GetCount() const
    {
        // already cached?
        if (!m_Cached)
            GetValues();

        return m_Values.size();
    }
    //---------------------------------------------------------------------------
    template <class T>
    const std::vector<T>* FBX::IFBXArrayProperty<T>::GetPtr() const
    {
        // already cached?
        if (!m_Cached)
            GetValues();

        return &m_Values;
    }
    //---------------------------------------------------------------------------
    template <class T>
    void FBX::IFBXArrayProperty<T>::GetValues() const
    {
        // already cached?
        if (m_Cached)
            return;

        const std::size_t count = GetValueCount();

        // no available value?
        if (!count)
            return;

        // reserve memory for numbers
        if (m_Capacity)
            m_Values.reserve(m_Capacity);

        // get the numbers
        for (std::size_t i = 0; i < count; ++i)
            m_Values.push_back(GetValue(i)->GetT<T>());

        // notify that values were cached
        m_Cached = true;
    }
    //---------------------------------------------------------------------------
}
