/****************************************************************************
 * ==> DWF_BezierCurve -----------------------------------------------------*
 ****************************************************************************
 * Description: Provides functions to calculate Bezier curves               *
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
#include "DWF_Vector2.h"
#include "DWF_Vector3.h"

namespace DWF_Math
{
    /**
    * Bezier curve
    *@author Jean-Milost Reymond
    */
    class BezierCurve
    {
        public:
            BezierCurve();
            virtual ~BezierCurve();

            /**
            * Calculates a point on a quadratic Bezier curve
            *@param start - Bezier curve start coordinate
            *@param end - Bezier curve end coordinate
            *@param control - Bezier curve control point coordinate
            *@param position - position of the point to find in percent (between 0.0f and 1.0f)
            *@return quadratic Bezier point coordinate matching with position
            */
            static Vector2F GetQuadraticBezierPoint(const Vector2F& start, const Vector2F& end, const Vector2F& control, float position);

            /**
            * Calculates a point on a quadratic Bezier curve
            *@param start - Bezier curve start coordinate
            *@param end - Bezier curve end coordinate
            *@param control - Bezier curve control point coordinate
            *@param position - position of the point to find in percent (between 0.0f and 1.0f)
            *@return quadratic Bezier point coordinate matching with position
            */
            static Vector3F GetQuadraticBezierPoint(const Vector3F& start, const Vector3F& end, const Vector3F& control, float position);

            /**
            * Calculates a point on a cubic Bezier curve
            *@param start - Bezier curve start coordinate
            *@param end - Bezier curve end coordinate
            *@param control1 - first Bezier curve control point coordinate
            *@param control2 - second Bezier curve control point coordinate
            *@param position - position of the point to find in percent (between 0.0f and 1.0f)
            *@return cubic Bezier point coordinate matching with position
            */
            static Vector2F GetCubicBezierPoint(const Vector2F& start,
                                                const Vector2F& end,
                                                const Vector2F& control1,
                                                const Vector2F& control2,
                                                      float     position);

            /**
            * Calculates a point on a cubic Bezier curve
            *@param start - Bezier curve start coordinate
            *@param end - Bezier curve end coordinate
            *@param control1 - first Bezier curve control point coordinate
            *@param control2 - second Bezier curve control point coordinate
            *@param position - position of the point to find in percent (between 0.0f and 1.0f)
            *@return cubic Bezier point coordinate matching with position
            */
            static Vector3F GetCubicBezierPoint(const Vector3F& start,
                                                const Vector3F& end,
                                                const Vector3F& control1,
                                                const Vector3F& control2,
                                                      float     position);

            /**
            * Calculates a point on a line
            *@param start - line start coordinate
            *@param end - line end coordinate
            *@param position - position of the point to find in percent (between 0.0f and 1.0f)
            *@return point coordinates on the line
            */
            static inline Vector2F GetPointOnLine(const Vector2F& start, const Vector2F& end, float position);

            /**
            * Calculates a point on a line
            *@param start - line start coordinate
            *@param end - line end coordinate
            *@param position - position of the point to find in percent (between 0.0f and 1.0f)
            *@return point coordinates on the line
            */
            static inline Vector3F GetPointOnLine(const Vector3F& start, const Vector3F& end, float position);
    };

    //---------------------------------------------------------------------------
    // BezierCurve
    //---------------------------------------------------------------------------
    inline Vector2F BezierCurve::GetPointOnLine(const Vector2F& start, const Vector2F& end, float position)
    {
        return (start + ((end - start) * position));
    }
    //---------------------------------------------------------------------------
    inline Vector3F BezierCurve::GetPointOnLine(const Vector3F& start, const Vector3F& end, float position)
    {
        return (start + ((end - start) * position));
    }
    //---------------------------------------------------------------------------
}
