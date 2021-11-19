/****************************************************************************
 * ==> DWF_AABBTree --------------------------------------------------------*
 ****************************************************************************
 * Description:  Aligned-Axis Bounding Box tree                             *
 * Contained in: Core                                                       *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar engine                                           *
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

// dwarfstar
#include "DWF_Object.h"
#include "DWF_Polygon.h"
#include "DWF_Ray.h"
#include "DWF_Box.h"
#include "DWF_Sphere.h"

///**
//* Aligned-Axis Bounding Box tree
//*@author Jean-Milost Reymond
//*/
//class DWF_AABBTree : public DWF_Object
//{
//    public:
//        /**
//        * Indexed polygon
//        */
//        struct IIndexedPolygon
//        {
//            const DWF_VertexBuffer* m_pVB = nullptr;
//            std::size_t             m_Index[3];
//
//            IIndexedPolygon();
//            virtual ~IIndexedPolygon();
//        };
//
//        typedef std::vector<IIndexedPolygon*> IIndexedPolygonBuffer;
//
//        /**
//        * Tree node
//        */
//        struct INode
//        {
//            INode*                m_pParent = nullptr;
//            INode*                m_pLeft   = nullptr;
//            INode*                m_pRight  = nullptr;
//            DWF_Box*              m_pBox    = nullptr;
//            IIndexedPolygonBuffer m_PolygonBuffer;
//
//            INode();
//            virtual ~INode();
//        };
//
//        typedef std::vector<DWF_PolygonF*> IPolygonBuffer;
//
//        /**
//        * Called when a vertex color should be get
//        *@param pVB - vertex buffer that will contain the vertex for which the color should be get
//        *@param pNormal - vertex normal
//        *@param groupIndex - the vertex group index (e.g. the inner and outer vertices of a ring)
//        *@return RGBA color to apply to the vertex
//        *@note This callback will be called only if the per-vertex color option is activated in the vertex
//        *      buffer
//        */
//        typedef unsigned (*CSR_fOnGetVertexColor)(const DWF_VertexBuffer* pVB,
//                                                  const DWF_Vector3F*     pNormal,
//                                                        std::size_t       groupIndex);
//
//        INode* m_pRoot = nullptr;
//
//        DWF_AABBTree();
//        virtual ~DWF_AABBTree();
//
//        /**
//        * Creates the AABB tree from an indexed polygon buffer
//        *@param ipb - indexed polygon buffer from which the tree should be created
//        *@param[in, out] pNode - root or parent node to create from, populated node on function ends
//        *@return true on success, otherwise false
//        */
//        virtual bool CreateFromIB(const IIndexedPolygonBuffer& ipb);
//        virtual bool CreateFromIB(const IIndexedPolygonBuffer& ipb, INode* pNode);
//
//        /**
//        * Creates an AABB tree from a mesh
//        *@param pMesh - mesh from which the tree should be created
//        *@return true on success, otherwise false
//        */
//        bool CreateFromMesh(const DWF_Mesh* pMesh);
//
//        /**
//        * Resolves AABB tree
//        *@param pRay - ray against which tree items will be tested
//        *@param pNode - root or parent node to resolve
//        *@param deep - tree deep level, used internally, should be set to 0
//        *@param[out] pPolygons - polygons belonging to boxes hit by ray
//        *@return true on success, otherwise false
//        */
//        bool Resolve(const DWF_RayF* pRay, std::size_t deep, IPolygonBuffer* pPolygons);
//
//        /**
//        * Gets the next position while sliding on a plane
//        *@param slidingPlane - sliding plane
//        *@param pos - current position
//        *@param radius - radius around the current position
//        *@return resulting position
//        */
//        DWF_Vector3F GetSlidingPoint(const DWF_PlaneF& slidingPlane, const DWF_Vector3F& pos, float radius);
//
//        /**
//        * Calculates the position where a model or a point of view is placed on the ground
//        *@param boundingSphere - bounding sphere surrounding the point of view or model
//        *@param polygon - polygon belonging to the model showing the ground of a scene
//        *@param groundDir - ground direction. If 0, a default direction of [0, -1, 0] will be used
//        *@param[out] groundPos - resulting position where the bounding sphere surrounding the point of
//        *                        view or model will be placed on the ground. Ignored if 0
//        *@return true if the bounding sphere is above the ground polygon, otherwise false
//        *@note The bounding sphere should be in the same coordinate system as the polygon. This
//        *      means that any transformation should be applied to the sphere before calling this
//        *      function
//        */
//        bool GroundCollision(const DWF_Sphere&   boundingSphere,
//                             const DWF_PolygonF& polygon,
//                             const DWF_Vector3F& groundDir,
//                                   DWF_Vector3F& groundPos);
//
//        /**
//        * Calculates the y axis position where to place the point of view to stay above the ground
//        *@param boundingSphere - sphere surrounding the point of view or model
//        *@param groundDir - ground direction
//        *@param[out] groundPolygon - polygon on which the ground was hit, ignored if 0
//        *@param[out] groundY - resulting position on the y axis where to place the point of view or model
//        *@return true if a ground polygon was found, otherwise false
//        *@note The bounding sphere should be in the same coordinate system as the model. This means
//        *      that any transformation should be applied to the sphere before calling this function
//        */
//        bool GroundPosY(const DWF_Sphere&   boundingSphere,
//                        const DWF_Vector3F& groundDir,
//                              DWF_PolygonF& groundPolygon,
//                              float&        groundY);
//
//    private:
//        /**
//        * Converts an indexed polygon to a polygon
//        *@param pIndexedPolygon - indexed polygon to convert
//        *@return converted polygon
//        */
//        DWF_PolygonF IndexedPolygonToPolygon(const IIndexedPolygon* pIndexedPolygon) const;
//
//        /**
//        * Extends a box to encompass a polygon
//        *@param polygon - polygon to encompass in the box
//        *@param[in, out] pBox - bounding box that will encompass the polygon
//        *@param[out] pEmpty - if true, box is empty and still not contains any polygon
//        */
//        void ExtendBoxToPolygon(const DWF_PolygonF& polygon,
//                                      DWF_Box*      pBox,
//                                      bool&         empty);
//
//        /**
//        * Gets an indexed polygon buffer from a mesh
//        *@param pMesh - mesh
//        *@param ipb - indexed polygon buffer to fill
//        *@return true on success, otherwise false
//        *@note The indexed polygon buffer must be released when no longer used, see
//        *      csrIndexedPolygonBufferRelease()
//        *@note BE CAREFUL, the indexed polygon buffer is valid as long as its source mesh is valid.
//        *      If the mesh is released, the indexed polygon buffer should be released together.
//        *      However the indexed polygon buffer may be released after the mesh
//        */
//        bool IndexedPolygonBufferFromMesh(const DWF_Mesh* pMesh, IIndexedPolygonBuffer& ipb) const;
//};

/**
* Aligned-axis bounding box tree node
*@author Jean-Milost Reymond
*/
struct DWF_AABBNode
{
    DWF_AABBNode* m_pParent = nullptr;
    DWF_AABBNode* m_pLeft   = nullptr;
    DWF_AABBNode* m_pRight  = nullptr;
    DWF_Box*      m_pBox    = nullptr;
    DWF_PolygonsF m_Polygons;

    /**
    * Constructor
    *@param pParent - parent node
    */
    DWF_AABBNode(DWF_AABBNode* pParent);

    virtual ~DWF_AABBNode();
};

/**
* Aligned-axis bounding box tree
*@author Jean-Milost Reymond
*/
class DWF_AABBTree
{
    public:
        DWF_AABBTree();
        virtual ~DWF_AABBTree();

        /**
        * Gets the bounding box surrounding the tree data
        *@return the bounding box, NULL if not found or on error
        */
        virtual DWF_Box* GetBoundingBox() const;

        /**
        * Gets the polygon count
        *@return the polygon count
        */
        virtual std::size_t GetPolygonCount() const;

        /**
        * Populates AABB tree
        *@param polygons - source polygon array
        *@return true on success, otherwise false
        */
        virtual bool Populate(const DWF_PolygonsF& polygons);

        /**
        * Resolves AABB tree
        *@param pRay - ray against which tree boxes will be tested
        *@param[in, out] polygons - polygons belonging to boxes hit by ray
        *@return true on success, otherwise false
        *@note Polygon list content should be deleted when useless
        */
        virtual bool Resolve(const DWF_RayF* pRay, DWF_PolygonsF& polygons) const;

        /**
        * Gets the next position while sliding on a plane
        *@param slidingPlane - sliding plane
        *@param pos - current position
        *@param radius - radius around the current position
        *@return resulting position
        */
        virtual DWF_Vector3F GetSlidingPoint(const DWF_PlaneF&   slidingPlane,
                                             const DWF_Vector3F& pos,
                                                   float         radius);

        /**
        * Calculates the position where a model or a point of view is placed on the ground
        *@param boundingSphere - bounding sphere surrounding the point of view or model
        *@param polygon - polygon belonging to the model showing the ground of a scene
        *@param groundDir - ground direction. If 0, a default direction of [0, -1, 0] will be used
        *@param[out] groundPos - resulting position where the bounding sphere surrounding the point of
        *                        view or model will be placed on the ground. Ignored if 0
        *@return true if the bounding sphere is above the ground polygon, otherwise false
        *@note The bounding sphere should be in the same coordinate system as the polygon. This
        *      means that any transformation should be applied to the sphere before calling this
        *      function
        */
        virtual bool GroundCollision(const DWF_Sphere&   boundingSphere,
                                     const DWF_PolygonF& polygon,
                                     const DWF_Vector3F& groundDir,
                                           DWF_Vector3F& groundPos);

        /**
        * Calculates the y axis position where to place the point of view to stay above the ground
        *@param boundingSphere - sphere surrounding the point of view or model
        *@param groundDir - ground direction
        *@param[out] groundPolygon - polygon on which the ground was hit, ignored if 0
        *@param[out] groundY - resulting position on the y axis where to place the point of view or model
        *@return true if a ground polygon was found, otherwise false
        *@note The bounding sphere should be in the same coordinate system as the model. This means
        *      that any transformation should be applied to the sphere before calling this function
        */
        virtual bool GroundPosY(const DWF_Sphere&   boundingSphere,
                                const DWF_Vector3F& groundDir,
                                      DWF_PolygonF& groundPolygon,
                                      float&        groundY);

        /**
        * Gets polygons from vertex
        *@param pVertex - source vertex descriptor, contains buffer to get from
        *@param polygonType - polygon type to generate
        *@param[out] polygons - polygon list to populate
        *@return true on success, otherwise false
        *@note Polygon list content should be deleted when useless
        */
        static bool GetPolygons(const DWF_VertexBuffer* pVB, DWF_PolygonsF& polygons);

    private:
        DWF_AABBNode* m_pRoot        = nullptr;
        std::size_t   m_PolygonCount = 0;

        /**
        * Adds a polygon inside an existing bounding box
        *@param polygon - polygon to add
        *@param box - bounding box in which polygon should be added
        *@param[in, out] empty - if true, box is empty an still no contains any polygon
        */
        void AddPolygonToBoundingBox(const DWF_PolygonF& polygon,
                                           DWF_Box*      pBox,
                                           bool&         empty) const;

        /**
        * Populates AABB tree
        *@param pNode - root or parent node to create from
        *@param polygons - source polygon array
        *@return true on success, otherwise false
        */
        bool Populate(DWF_AABBNode* pNode, const DWF_PolygonsF& polygons);

        /**
        * Resolves AABB tree
        *@param pRay - ray against which tree boxes will be tested
        *@param pNode - root or parent node to resolve
        *@param[in, out] polygons - polygons belonging to boxes hit by ray
        *@return true on success, otherwise false
        *@note Polygon list content should be deleted when useless
        */
        bool Resolve(const DWF_RayF*      pRay,
                     const DWF_AABBNode*  pNode,
                           DWF_PolygonsF& polygons) const;

        /**
        * Adds polygon to array
        *@param vb - source vertex buffer
        *@param v1 - first polygon vertex index in vertex buffer
        *@param v2 - second polygon vertex index in vertex buffer
        *@param v3 - third polygon vertex index in vertex buffer
        *@param[in, out] polygons - polygon array that contains generated polygons
        *@note Generated polygons should be deleted when useless
        */
        static inline void AddPolygon(const DWF_VertexBuffer& vb,
                                            std::size_t       v1,
                                            std::size_t       v2,
                                            std::size_t       v3,
                                            DWF_PolygonsF&    polygons);
};

//---------------------------------------------------------------------------
inline void DWF_AABBTree::AddPolygon(const DWF_VertexBuffer& vb,
                                           std::size_t       v1,
                                           std::size_t       v2,
                                           std::size_t       v3,
                                           DWF_PolygonsF&    polygons)
{
    std::unique_ptr<DWF_PolygonF> pPolygon(new DWF_PolygonF());

    // copy polygon from source buffer
    pPolygon->m_Vertex[0] = DWF_Vector3F(vb.m_Data[v1], vb.m_Data[v1 + 1], vb.m_Data[v1 + 2]);
    pPolygon->m_Vertex[1] = DWF_Vector3F(vb.m_Data[v2], vb.m_Data[v2 + 1], vb.m_Data[v2 + 2]);
    pPolygon->m_Vertex[2] = DWF_Vector3F(vb.m_Data[v3], vb.m_Data[v3 + 1], vb.m_Data[v3 + 2]);

    // add polygon to list
    polygons.push_back(pPolygon.get());
    pPolygon.release();
}
//---------------------------------------------------------------------------
