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

#include "DWF_BezierCurve.h"

using namespace DWF_Math;

//---------------------------------------------------------------------------
// BezierCurve
//---------------------------------------------------------------------------
BezierCurve::BezierCurve()
{}
//---------------------------------------------------------------------------
BezierCurve::~BezierCurve()
{}
//---------------------------------------------------------------------------
Vector2F BezierCurve::GetQuadraticBezierPoint(const Vector2F& start, const Vector2F& end, const Vector2F& control, float position)
{
    // point p0p1 is the point on the line formed by the start position and the control point, and
    // point p1p2 is the point on the line formed by the control point and the line end
    const Vector2F p0p1 = GetPointOnLine(start, control, position);
    const Vector2F p1p2 = GetPointOnLine(control, end, position);

    // the resulting point is the point found on the intermediate segment (p0p1 to p1p2)
    return GetPointOnLine(p0p1, p1p2, position);
}
//---------------------------------------------------------------------------
Vector3F BezierCurve::GetQuadraticBezierPoint(const Vector3F& start, const Vector3F& end, const Vector3F& control, float position)
{
    // point p0p1 is the point on the line formed by the start position and the control point, and
    // point p1p2 is the point on the line formed by the control point and the line end
    const Vector3F p0p1 = GetPointOnLine(start, control, position);
    const Vector3F p1p2 = GetPointOnLine(control, end, position);

    // the resulting point is the point found on the intermediate segment (p0p1 to p1p2)
    return GetPointOnLine(p0p1, p1p2, position);
}
//---------------------------------------------------------------------------
Vector2F BezierCurve::GetCubicBezierPoint(const Vector2F& start, const Vector2F& end, const Vector2F& control1, const Vector2F& control2, float position)
{
    // point p0p1 is the point on the line formed by the start position and the first control point,
    // point p1p2 is the point on the line formed by the first control point and the second control
    // point, and point p2p3 is the point on the line formed by the second control point and the
    // line end
    const Vector2F p0p1 = GetPointOnLine(start, control1, position);
    const Vector2F p1p2 = GetPointOnLine(control1, control2, position);
    const Vector2F p2p3 = GetPointOnLine(control2, end, position);

    // the resulting point is the quadratic bezier point found on the intermediate segments (p0p1 to
    // p1p2 and p1p2 to p2p3)
    return GetQuadraticBezierPoint(p0p1, p2p3, p1p2, position);
}
//---------------------------------------------------------------------------
Vector3F BezierCurve::GetCubicBezierPoint(const Vector3F& start, const Vector3F& end, const Vector3F& control1, const Vector3F& control2, float position)
{
    // point p0p1 is the point on the line formed by the start position and the first control point,
    // point p1p2 is the point on the line formed by the first control point and the second control
    // point, and point p2p3 is the point on the line formed by the second control point and the
    // line end
    const Vector3F p0p1 = GetPointOnLine(start, control1, position);
    const Vector3F p1p2 = GetPointOnLine(control1, control2, position);
    const Vector3F p2p3 = GetPointOnLine(control2, end, position);

    // the resulting point is the quadratic bezier point found on the intermediate segments (p0p1 to
    // p1p2 and p1p2 to p2p3)
    return GetQuadraticBezierPoint(p0p1, p2p3, p1p2, position);
}
//---------------------------------------------------------------------------
