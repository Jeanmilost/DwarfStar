/****************************************************************************
 * ==> TGeometricDocument3D ------------------------------------------------*
 ****************************************************************************
 * Description : This module provides a geometric 3D shapes document        *
 * Developer   : Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar Engine                                           *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sublicense, and/or sell copies of the Software, and to       *
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

#ifndef TGeometricDocument3DH
#define TGeometricDocument3DH

// std
#include <vector>

// dwarfstar engine
#include "DWF_Common_Types.h"
#include "DWF_Graphics_Color.h"
#include "DWF_Geometry_Shape.h"
#include "DWF_Geometry_Matrix.h"
#include "DWF_Geometry_Rect.h"
#include "DWF_OpenGL_Renderer.h"
#include "DWF_OpenGL_Shader.h"

// interface
#include "TGeometricDocument.h"

// windows
#include <Windows.h>

// xml library
#include "sxmlc.h"

using namespace DWF_Geometry;
using namespace DWF_Graphics;
using namespace DWF_OpenGL;

/**
* Geometric document for 3D shapes
*@author Jean-Milost Reymond
*/
class TGeometricDocument3D : public TGeometricDocument
{
    public:
        /**
        * Constructor
        *@param hWnd - application Windows handle
        */
        TGeometricDocument3D(HWND hWnd);

        /**
        * Destructor
        */
        virtual ~TGeometricDocument3D();

        /**
        * Adds a line to the document
        *@param point - a point on the line
        *@param dir - the line direction
        */
        virtual void AddLine(const DWF_Vector3DR& point, const DWF_Vector3DR& dir);

        /**
        * Adds a line to the document
        *@param point - the point where the ray starts
        *@param dir - the ray direction
        */
        virtual void AddRay(const DWF_Vector3DR& point, const DWF_Vector3DR& dir);

        /**
        * Adds a line segment to the document
        *@param start - the point where the line segment starts
        *@param end - the point where the line segment ends
        */
        virtual void AddSegment(const DWF_Vector3DR& start, const DWF_Vector3DR& end);

        /**
        * Adds a polygon to the document
        *@param v1 - the first polygon vertex
        *@param v2 - the second polygon vertex
        *@param v3 - the third polygon vertex
        */
        virtual void AddPolygon(const DWF_Vector3DR& v1,
                                const DWF_Vector3DR& v2,
                                const DWF_Vector3DR& v3);

        /**
        * Adds a plane to the document
        *@param point - a point on the plane
        *@param normal - the plane normal
        */
        virtual void AddPlane(const DWF_Vector3DR& point, const DWF_Vector3DR& normal);

        /**
        * Adds a sphere to the document
        *@param center - the center of the sphere
        *@param radius - the sphere radius
        */
        virtual void AddSphere(const DWF_Vector3DR& center, M_Real radius);

        /**
        * Adds a box to the document
        *@param min - the box min corner
        *@param max - the box max corner
        */
        virtual void AddBox(const DWF_Vector3DR& min, const DWF_Vector3DR& max);

        /**
        * Adds a disk to the document
        *@param center - the center of the disk
        *@param normal - the disk normal
        *@param radius - the disk radius
        */
        virtual void AddDisk(const DWF_Vector3DR& center,
                             const DWF_Vector3DR& normal,
                                   M_Real         radius);

        /**
        * Adds a cylinder to the document
        *@param start - the point where the cylinder starts
        *@param end - the point where the cylinder ends
        *@param radius - the cylinder radius
        */
        virtual void AddCylinder(const DWF_Vector3DR& start, const DWF_Vector3DR& end, M_Real radius);

        /**
        * Selects the shape at index
        *@param index - index
        *@param selected - if true, the shape is selected, unselected otherwise
        */
        virtual void Select(std::size_t index, bool selected) const;

        /**
        * Resets the shape at index
        *@param index - index
        */
        virtual void Reset(std::size_t index) const;

        /**
        * Resets the shape
        *@param pShape - shape
        */
        virtual void Reset(void* pShape) const;

        /**
        * Enables or disabled the inside simulator
        *@param value - if true, the simulator is enabled on this document, disabled otherwise
        */
        void EnableInsideSimulator(bool value);

        /**
        * Gets the inside simulator point position
        *@return inside simulator point in the document
        */
        DWF_Vector3DR GetInsideSimulatorPoint() const;

        /**
        * Gets the shape at the current index
        *@param index - index
        *@return shape at current index, NULL if not found or on error
        */
        virtual void* GetShape(std::size_t index) const;

        /**
        * Gets the shape count on the document
        *@return the shape count on the document
        */
        virtual std::size_t GetShapeCount() const;

        /**
        * Gets the currently focused shape
        *@return the currently focused shape
        */
        virtual DWF_Shape3D<M_Real>* GetFocused() const;

        /**
        * Gets the simulator test point
        *@return the simulator test point
        */
        virtual DWF_Vector3DR GetPoint() const;

        /**
        * Sets the simulator test point
        *@param point - point
        */
        virtual void SetPoint(const DWF_Vector3DR& point);

        /**
        * Resizes the document
        *@param width - new document width
        *@param height - new document height
        */
        virtual void CreateViewport(int width, int height);

        /**
        * Applies an arcball movement to the camera around the scene
        *@param offsetX - shifting value around the x axis
        *@param offsetY - shifting value around the y axis
        *@param offsetRadius - shifting value to apply to the radius
        */
        virtual void MoveCamera(M_Real offsetX, M_Real offsetY, M_Real offsetRadius);

        /**
        * Inflates or deflates the currently focused shape
        *@param offsetX - inflating offset on the X axis, on negative value the shape will be deflated
        *@param offsetY - inflating offset on the Y axis, on negative value the shape will be deflated
        *@param offsetZ - inflating offset on the Z axis, on negative value the shape will be deflated
        */
        virtual void InflateFocused(M_Real offsetX, M_Real offsetY, M_Real offsetZ);

        /**
        * Moves the currently focused shape
        *@param offsetX - moving offset on the X axis
        *@param offsetY - moving offset on the Y axis
        *@param offsetZ - moving offset on the Z axis
        */
        virtual void MoveFocused(M_Real offsetX, M_Real offsetY, M_Real offsetZ);

        /**
        * Rotates the currently focused shape
        *@param offsetX - rotating offset on the X axis
        *@param offsetY - rotating offset on the Y axis
        *@param offsetZ - rotating offset on the Z axis
        */
        virtual void RotateFocused(M_Real offsetX, M_Real offsetY, M_Real offsetZ);

        /**
        * Draws the document content on the canvas
        *@param rect - rectangle surrounding the document to draw
        *@param pCanvas - canvas to draw on
        */
        virtual void Draw(const TRect& rect, TCanvas* pCanvas) const;

    protected:
        /**
        * Called when the content of a document should be read
        *@param doc - xml document root node to read from
        *@return true on success, otherwise false
        */
        virtual bool DoReadContent(XMLNode* pNode);

        /**
        * Called when the content of a document should be written
        *@param doc - xml document to write to
        *@return true on success, otherwise false
        */
        virtual bool DoWriteContent(XMLDoc& doc) const;

    private:
        /**
        * OpenGL objects enumeration
        */
        enum IEGLObject
        {
            IE_GO_Plane,
            IE_GO_Sphere,
            IE_GO_Box,
            IE_GO_Disk,
            IE_GO_Cylinder
        };

        /**
        * Shape on the document
        */
        struct IShape
        {
            DWF_Shape3D<M_Real>* m_pShape;
            DWF_Color            m_Color;
            DWF_Vector3DR        m_VirtualCoord;
            float                m_FadeOffset;
            float                m_FadeValue;
            bool                 m_Selected;

            IShape();
            ~IShape();
        };

        /**
        * Graphic shape
        */
        struct IGraphicShape
        {
            DWF_Shape3D<M_Real>* m_pShape;
            IEGLObject           m_GLObject;
            DWF_Color            m_Color;
            DWF_Vector3DR        m_VirtualCoord;
            bool                 m_Focused;

            IGraphicShape();
            ~IGraphicShape();
        };

        /**
        * Camera arcball
        */
        struct IArcBall
        {
            M_Real m_AngleX;
            M_Real m_AngleY;
            M_Real m_Radius;

            IArcBall();
            ~IArcBall();
        };

        typedef std::vector<IShape*>                         IShapes;
        typedef std::vector<IGraphicShape*>                  IGraphicShapes;
        typedef std::map<IEGLObject, DWF_Modeling::DWF_Mesh> IMeshDictionary;

        HWND            m_hWnd;
        DWF_Renderer    m_Renderer;
        DWF_Shader      m_Shader;
        IShapes         m_Shapes;
        IMeshDictionary m_Meshes;
        IArcBall        m_Arcball;
        DWF_Matrix4x4R  m_Projection;
        DWF_Matrix4x4R  m_View;
        DWF_Matrix4x4R  m_Model;
        DWF_Vector3DR   m_Point;
        M_Real          m_MaxAngle;
        bool            m_InsideSimEnabled;

        /**
        * Initializes the document
        *@return true on success, otherwise false
        */
        bool Initialize();

        /**
        * Generates and cache a plane model
        */
        void GeneratePlaneModel();

        /**
        * Generates and cache a sphere model
        */
        void GenerateSphereModel();

        /**
        * Generates and cache a box model
        */
        void GenerateBoxModel();

        /**
        * Generates and cache a disk model
        */
        void GenerateDiskModel();

        /**
        * Generates and cache a cylinder model
        */
        void GenerateCylinderModel();

        /**
        * Reads a vector content from a XML node
        *@param pNode - node containing the vector to read
        *@return read vector
        */
        DWF_Vector3DR ReadVectorFromXML(XMLNode* pNode) const;

        /**
        * Adds a tag containing a vector in a document
        *@param pParent - parent node in document to add to
        *@param name - vector name
        *@param vector - vector containing the values to write
        *@return true on success, otherwise false
        */
        bool AddTag(XMLNode* pParent, const std::string& name, const DWF_Vector3DR& vector) const;

        /**
        * Loads and links the shader
        *@param vertex - vertex program to load
        *@param fragment - fragment program to load
        *@return true on success, otherwise false
        */
        bool LoadShader(const std::string& vertex, const std::string& fragment);

        /**
        * Gets the arcball matrix to apply to the camera
        *@param arcball - arcball values
        */
        DWF_Matrix4x4R GetArcBallMatrix(const IArcBall& arcball);

        /**
        * Draws the background
        *@param rect - background rectangle
        */
        void DrawBackground(const DWF_RectR& rect) const;

        /**
        * Selects a color to use to draw a shape
        *@param color - color to use
        *@returns true on success, otherwise false
        */
        bool SelectColor(const DWF_Color& color) const;

        /**
        * Builds the model matrix
        *@param position - model position
        *@param xRotation - model rotation on the x axis
        *@param yRotation - model rotation on the y axis
        *@param zRotation - model rotation on the z axis
        *@param scaleFactor - model scale factor
        */
        DWF_Matrix4x4R BuildModelMatrix(const DWF_Vector3DR& position,
                                              float          xRotation,
                                              float          yRotation,
                                              float          zRotation,
                                        const DWF_Vector3DR& scaleFactor) const;

        /**
        * Fades in or out the color in a shape
        *@param pShape - shape for which color should be faded in or out
        */
        void FadeColor(IShape* pShape) const;

        /**
        * Compare graphic shapes
        *@param pLeft - graphic shape to compare
        *@param pRight - graphic shape to compare with
        */
        static bool OnCompareShapes(const IGraphicShape* pLeft, const IGraphicShape* pRight);
};

#endif
