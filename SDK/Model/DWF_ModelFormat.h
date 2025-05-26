/****************************************************************************
 * ==> DWF_ModelFormat -----------------------------------------------------*
 ****************************************************************************
 * Description: Basic model format (e.g. Inter-Quake Model, Quake Model,    *
 *              Wavefront, ...)                                             *
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

// classes
#include "DWF_Buffer.h"
#include "DWF_Model.h"

namespace DWF_Model
{
    /**
    * Model format. It's a base for file formats e.g. Inter-Quake Model, Quake Model, Wavefront, ...
    *@author Jean-Milost Reymond
    */
    class ModelFormat
    {
        public:
            /**
            * Available formats
            */
            enum class IEFormat
            {
                IE_F_Unknown = 0,
                IE_F_FBX,
                IE_F_IQM,
                IE_F_MDL,
                IE_F_Wavefront
            };

            /**
            * Constructor
            *@param format - model format
            */
            ModelFormat(IEFormat format);

            virtual ~ModelFormat();

            /**
            * Clears the model
            */
            virtual void Clear() = 0;

            /**
            * Opens a model from file
            *@param fileName - file to open
            *@return true on success, otherwise false
            */
            virtual bool Open(const std::string& fileName) = 0;

            /**
            * Opens a model from file
            *@param fileName - file to open
            *@return true on success, otherwise false
            */
            virtual bool Open(const std::wstring& fileName) = 0;

            /**
            * Opens a model from buffer
            *@param buffer - buffer containing the model data to open
            *@return true on success, otherwise false
            *@note the buffer should be positioned to the data start
            */
            virtual bool Open(DWF_Buffer::Buffer& buffer) = 0;

            /**
            * Gets the model
            *@return the model, nullptr if no model or on error
            *@note For animated model format, the returned model will always be either the default frame or the first frame of the first
            *      animation set, depending on the model format
            */
            virtual Model* GetModel() const = 0;

            /**
            * Gets model format (e.g. Quake model (.mdl), Inter-Quake model (.iqm), Wavefront model (.obj), ...)
            *@return model format
            */
            virtual inline IEFormat GetFormat() const;

        private:
            IEFormat m_Format;
    };

    //---------------------------------------------------------------------------
    inline ModelFormat::IEFormat ModelFormat::GetFormat() const
    {
        return m_Format;
    }
    //---------------------------------------------------------------------------
}
