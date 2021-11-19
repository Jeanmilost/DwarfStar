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

#include "DWF_AABBTree.h"

// std
#include <algorithm>

// dwarfstar
#include "Base\DWF_MathHelper.h"
#include "DWF_Line.h"

////---------------------------------------------------------------------------
//// DWF_AABBTree::IIndexedPolygon
////---------------------------------------------------------------------------
//DWF_AABBTree::IIndexedPolygon::IIndexedPolygon()
//{}
////---------------------------------------------------------------------------
//DWF_AABBTree::IIndexedPolygon::~IIndexedPolygon()
//{}
////---------------------------------------------------------------------------
//// DWF_AABBTree::INode
////---------------------------------------------------------------------------
//DWF_AABBTree::INode::INode()
//{}
////---------------------------------------------------------------------------
//DWF_AABBTree::INode::~INode()
//{
//    /*REM
//    for (std::size_t i = 0; i < m_PolygonBuffer.size(); ++i)
//        delete m_PolygonBuffer[i];
//    */
//
//    if (m_pBox)
//        delete m_pBox;
//
//    if (m_pLeft)
//        delete m_pLeft;
//
//    if (m_pRight)
//        delete m_pRight;
//}
////---------------------------------------------------------------------------
//// DWF_AABBTree
////---------------------------------------------------------------------------
//DWF_AABBTree::DWF_AABBTree() :
//    DWF_Object()
//{}
////---------------------------------------------------------------------------
//DWF_AABBTree::~DWF_AABBTree()
//{
//    if (m_pRoot)
//        delete m_pRoot;
//}
////---------------------------------------------------------------------------
//bool DWF_AABBTree::CreateFromIB(const IIndexedPolygonBuffer& ipb, INode* pNode)
//{
//    if (m_pRoot)
//        delete m_pRoot;
//
//    m_pRoot = new INode();
//
//    return CreateFromIB(ipb, m_pRoot);
//}
////---------------------------------------------------------------------------
//bool DWF_AABBTree::CreateFromIB(const IIndexedPolygonBuffer& ipb, INode* pNode)
//{
//    /*REM
//    size_t                    i;
//    size_t                    j;
//    CSR_Box                   leftBox;
//    CSR_Box                   rightBox;
//    CSR_Polygon3              polygon;
//    CSR_IndexedPolygon* pNewPolygons = 0;
//    CSR_IndexedPolygonBuffer* pLeftPolygons = 0;
//    CSR_IndexedPolygonBuffer* pRightPolygons = 0;
//    int                       boxEmpty = 1;
//    int                       insideLeft = 0;
//    int                       insideRight = 0;
//    int                       canResolveLeft = 0;
//    int                       canResolveRight = 0;
//    int                       result = 0;
//    */
//
//    /*REM
//    // no indexed polygon buffer?
//    if (!pIPB)
//        return false;
//    */
//
//    // no node?
//    if (!pNode)
//        return false;
//
//    // initialize node content
//    //REM pNode->m_pParent = 0;
//    //REM pNode->m_pLeft = 0;
//    //REM pNode->m_pRight = 0;
//    pNode->m_pBox = new DWF_Box();
//    //REM FIXME m_pRoot->m_PolygonBuffer = csrIndexedPolygonBufferCreate();
//
//    /*REM
//    // succeeded?
//    if (!m_pRoot->m_pBox || !m_pRoot->m_pPolygonBuffer)
//    {
//        csrAABBTreeNodeContentRelease(pNode);
//        return 0;
//    }
//    */
//
//    /*REM
//    // create the polygon buffers that will contain the divided polygons
//    pLeftPolygons = csrIndexedPolygonBufferCreate();
//    pRightPolygons = csrIndexedPolygonBufferCreate();
//    */
//    // create the polygon buffers that will contain the divided polygons
//    IIndexedPolygonBuffer leftPolygons;
//    IIndexedPolygonBuffer rightPolygons;
//
//    /*REM
//    // succeeded?
//    if (!pLeftPolygons || !pRightPolygons)
//    {
//        csrIndexedPolygonBufferRelease(pLeftPolygons);
//        csrIndexedPolygonBufferRelease(pRightPolygons);
//        csrAABBTreeNodeContentRelease(pNode);
//        return 0;
//    }
//    */
//
//    DWF_PolygonF polygon;
//    bool         boxEmpty = true;
//
//    // iterate through polygons to divide
//    //REM for (i = 0; i < pIPB->m_Count; ++i)
//    for (std::size_t i = 0; i < ipb.size(); ++i)
//    {
//        // using its index, extract the polygon from its vertex buffer
//        polygon = IndexedPolygonToPolygon(ipb[i]);
//
//        // extend the bounding box to include the polygon
//        ExtendBoxToPolygon(polygon, pNode->m_pBox, boxEmpty);
//    }
//
//    DWF_Box leftBox;
//    DWF_Box rightBox;
//
//    // divide the bounding box in 2 sub-boxes
//    pNode->m_pBox->Cut(leftBox, rightBox);
//    //REM csrBoxCut(pNode->m_pBox, &leftBox, &rightBox);
//
//    // iterate again through polygons to divide
//    //REM for (i = 0; i < pIPB->m_Count; ++i)
//    for (std::size_t i = 0; i < ipb.size(); ++i)
//    {
//        // get the concrete polygon (i.e. with physical coordinates, not indexes)
//        polygon = IndexedPolygonToPolygon(ipb[i]);
//
//        std::size_t insideLeft  = 0;
//        std::size_t insideRight = 0;
//
//        // check which box contains the most vertices
//        for (std::uint8_t j = 0; j < 3; ++j)
//            // is vertex inside left or right sub-box?
//            if (leftBox.Inside(polygon.m_Vertex[j]))
//                ++insideLeft;
//            else
//                ++insideRight;
//
//        //REM IIndexedPolygon newPolygons;
//
//        // check at which sub-box the polygon belongs (and thus to which buffer it should be added)
//        if (insideLeft >= insideRight)
//        {
//            /*REM
//            // allocate the memory to add a new polygon in the left polygon buffer
//            pNewPolygons = (CSR_IndexedPolygon*)csrMemoryAlloc(pLeftPolygons->m_pIndexedPolygon,
//                                                               sizeof(CSR_IndexedPolygon),
//                                                               pLeftPolygons->m_Count + 1);
//
//            // succeeded?
//            if (!pNewPolygons)
//            {
//                csrIndexedPolygonBufferRelease(pLeftPolygons);
//                csrIndexedPolygonBufferRelease(pRightPolygons);
//                csrAABBTreeNodeContentRelease(pNode);
//                return 0;
//            }
//
//            // update the buffer content
//            pLeftPolygons->m_pIndexedPolygon = pNewPolygons;
//            ++pLeftPolygons->m_Count;
//
//            // copy the polygon index content in the left buffer
//            pLeftPolygons->m_pIndexedPolygon[pLeftPolygons->m_Count - 1] = pIPB->m_pIndexedPolygon[i];
//            */
//            leftPolygons.push_back(ipb[i]);
//        }
//        else
//        {
//            /*REM
//            // allocate the memory to add a new polygon in the left polygon buffer
//            pNewPolygons = (CSR_IndexedPolygon*)csrMemoryAlloc(pRightPolygons->m_pIndexedPolygon,
//                                                               sizeof(CSR_IndexedPolygon),
//                                                               pRightPolygons->m_Count + 1);
//
//            // succeeded?
//            if (!pNewPolygons)
//            {
//                csrIndexedPolygonBufferRelease(pLeftPolygons);
//                csrIndexedPolygonBufferRelease(pRightPolygons);
//                csrAABBTreeNodeContentRelease(pNode);
//                return 0;
//            }
//
//            // update the buffer content
//            pRightPolygons->m_pIndexedPolygon = pNewPolygons;
//            ++pRightPolygons->m_Count;
//
//            // copy the polygon content inside its buffer
//            pRightPolygons->m_pIndexedPolygon[pRightPolygons->m_Count - 1] = pIPB->m_pIndexedPolygon[i];
//            */
//            rightPolygons.push_back(ipb[i]);
//        }
//    }
//
//    const bool canResolveLeft  = (leftPolygons.size()  && leftPolygons.size()  < ipb.size());
//    const bool canResolveRight = (rightPolygons.size() && rightPolygons.size() < ipb.size());
//
//    // leaf reached?
//    if (!canResolveLeft && !canResolveRight)
//    {
//        // iterate through left polygons to copy to the leaf polygon buffer
//        for (std::size_t i = 0; i < leftPolygons.size(); ++i)
//        {
//            /*REM
//            // allocate the memory to add a new polygon in the leaf node
//            pNewPolygons = (CSR_IndexedPolygon*)csrMemoryAlloc(pNode->m_pPolygonBuffer->m_pIndexedPolygon,
//                                                               sizeof(CSR_IndexedPolygon),
//                                                               pNode->m_pPolygonBuffer->m_Count + 1);
//
//            // succeeded?
//            if (!pNewPolygons)
//            {
//                csrIndexedPolygonBufferRelease(pLeftPolygons);
//                csrIndexedPolygonBufferRelease(pRightPolygons);
//                csrAABBTreeNodeContentRelease(pNode);
//                return 0;
//            }
//
//            // update the buffer content
//            pNode->m_pPolygonBuffer->m_pIndexedPolygon = pNewPolygons;
//            ++pNode->m_pPolygonBuffer->m_Count;
//
//            // copy the polygon content inside the polygon buffer
//            pNode->m_pPolygonBuffer->m_pIndexedPolygon[pNode->m_pPolygonBuffer->m_Count - 1] =
//                pLeftPolygons->m_pIndexedPolygon[i];
//            */
//            pNode->m_PolygonBuffer.push_back(leftPolygons[i]);
//        }
//
//        // iterate through right polygons to copy to the leaf polygon buffer
//        for (std::size_t i = 0; i < rightPolygons.size(); ++i)
//        {
//            /*REM
//            // allocate the memory to add a new polygon in the leaf node
//            pNewPolygons = (CSR_IndexedPolygon*)csrMemoryAlloc(pNode->m_pPolygonBuffer->m_pIndexedPolygon,
//                                                               sizeof(CSR_IndexedPolygon),
//                                                               pNode->m_pPolygonBuffer->m_Count + 1);
//
//            // succeeded?
//            if (!pNewPolygons)
//            {
//                csrIndexedPolygonBufferRelease(pLeftPolygons);
//                csrIndexedPolygonBufferRelease(pRightPolygons);
//                csrAABBTreeNodeContentRelease(pNode);
//                return 0;
//            }
//
//            // update the buffer content
//            pNode->m_pPolygonBuffer->m_pIndexedPolygon = pNewPolygons;
//            ++pNode->m_pPolygonBuffer->m_Count;
//
//            // copy the polygon content inside the polygon buffer
//            pNode->m_pPolygonBuffer->m_pIndexedPolygon[pNode->m_pPolygonBuffer->m_Count - 1] =
//                pRightPolygons->m_pIndexedPolygon[i];
//            */
//            pNode->m_PolygonBuffer.push_back(rightPolygons[i]);
//        }
//
//        /*REM
//        // release the left and right polygon buffers, as they will no longer be used
//        csrIndexedPolygonBufferRelease(pLeftPolygons);
//        csrIndexedPolygonBufferRelease(pRightPolygons);
//        */
//
//        return true;
//    }
//
//    bool result = false;
//
//    // do create left node?
//    if (canResolveLeft)
//    {
//        // create the left node
//        //REM pNode->m_pLeft = (CSR_AABBNode*)malloc(sizeof(CSR_AABBNode));
//        pNode->m_pLeft = new INode();
//
//        // populate it
//        result |= CreateFromIB(leftPolygons, pNode->m_pLeft);
//
//        // set node parent. IMPORTANT must be done after the node is populated (because this value
//        // will be reseted while the node is filled by csrAABBTreeFromIndexedPolygonBuffer())
//        pNode->m_pLeft->m_pParent = pNode;
//
//        // delete left polygon buffer, as it will no longer be used
//        //REM csrIndexedPolygonBufferRelease(pLeftPolygons);
//    }
//
//    // do create right node?
//    if (canResolveRight)
//    {
//        // create the right node
//        //REM pNode->m_pRight = (CSR_AABBNode*)malloc(sizeof(CSR_AABBNode));
//        pNode->m_pRight = new INode();
//
//        // populate it
//        result |= CreateFromIB(rightPolygons, pNode->m_pRight);
//
//        // set node parent. IMPORTANT must be done after the node is populated (because this value
//        // will be reseted while the node is filled by csrAABBTreeFromIndexedPolygonBuffer())
//        pNode->m_pRight->m_pParent = pNode;
//
//        // delete right polygon buffer, as it will no longer be used
//        //REM csrIndexedPolygonBufferRelease(pRightPolygons);
//    }
//
//    return result;
//}
////---------------------------------------------------------------------------
//bool DWF_AABBTree::CreateFromMesh(const DWF_Mesh* pMesh)
//{
//    /*REM
//    CSR_AABBNode* pRoot;
//    int           success;
//    */
//
//    // get indexed polygon buffer from mesh
//    CSR_IndexedPolygonBuffer* pIPB = csrIndexedPolygonBufferFromMesh(pMesh);
//
//    // succeeded?
//    if (!pIPB)
//        return 0;
//
//    // create the root node
//    pRoot = (CSR_AABBNode*)malloc(sizeof(CSR_AABBNode));
//
//    // succeeded?
//    if (!pRoot)
//    {
//        csrIndexedPolygonBufferRelease(pIPB);
//        return 0;
//    }
//
//    // populate the AABB tree
//    success = csrAABBTreeFromIndexedPolygonBuffer(pIPB, pRoot);
//
//    // release the polygon buffer
//    csrIndexedPolygonBufferRelease(pIPB);
//
//    // tree was populated successfully?
//    if (!success)
//    {
//        csrAABBTreeNodeRelease(pRoot);
//        return 0;
//    }
//
//    return pRoot;
//}
////---------------------------------------------------------------------------
//int csrAABBTreeResolve(const CSR_Ray3* pRay,
//                       const CSR_AABBNode* pNode,
//                       size_t              deep,
//                       CSR_Polygon3Buffer* pPolygons)
//{
//    unsigned      i;
//    int           leftResolved = 0;
//    int           rightResolved = 0;
//    CSR_Polygon3* pPolygonBuffer;
//    CSR_Figure3   ray;
//    CSR_Figure3   box;
//
//    // no ray?
//    if (!pRay)
//        return 0;
//
//    // no node to resolve?
//    if (!pNode)
//        return 0;
//
//    // no polygon buffer to contain the result?
//    if (!pPolygons)
//        return 0;
//
//    // is the first iteration?
//    if (!deep)
//    {
//        // ensure the polygon buffer is initialized, otherwise this may cause hard-to-debug bugs
//        pPolygons->m_pPolygon = 0;
//        pPolygons->m_Count = 0;
//    }
//
//    // is leaf?
//    if (!pNode->m_pLeft && !pNode->m_pRight)
//    {
//        // iterate through polygons contained in leaf
//        for (i = 0; i < pNode->m_pPolygonBuffer->m_Count; ++i)
//        {
//            // allocate memory for a new polygon in the buffer
//            pPolygonBuffer = (CSR_Polygon3*)csrMemoryAlloc(pPolygons->m_pPolygon,
//                                                           sizeof(CSR_Polygon3),
//                                                           pPolygons->m_Count + 1);
//
//            // succeeded?
//            if (!pPolygonBuffer)
//                return 0;
//
//            // update the polygon buffer
//            pPolygons->m_pPolygon = pPolygonBuffer;
//            ++pPolygons->m_Count;
//
//            // copy the polygon content
//            if (!csrIndexedPolygonToPolygon(&pNode->m_pPolygonBuffer->m_pIndexedPolygon[i],
//                                            &pPolygons->m_pPolygon[pPolygons->m_Count - 1]))
//                return 0;
//        }
//
//        return 1;
//    }
//
//    // convert ray to geometric figure
//    ray.m_Type = CSR_F3_Ray;
//    ray.m_pFigure = pRay;
//
//    // node contains a left child?
//    if (pNode->m_pLeft)
//    {
//        // convert left box to geometric figure
//        box.m_Type = CSR_F3_Box;
//        box.m_pFigure = pNode->m_pLeft->m_pBox;
//
//        // check if ray intersects the left box
//        if (csrIntersect3(&ray, &box, 0, 0, 0))
//            // resolve left node
//            leftResolved = csrAABBTreeResolve(pRay, pNode->m_pLeft, deep + 1, pPolygons);
//    }
//
//    // node contains a right child?
//    if (pNode->m_pRight)
//    {
//        // convert right box to geometric figure
//        box.m_Type = CSR_F3_Box;
//        box.m_pFigure = pNode->m_pRight->m_pBox;
//
//        // check if ray intersects the right box
//        if (csrIntersect3(&ray, &box, 0, 0, 0))
//            // resolve right node
//            rightResolved = csrAABBTreeResolve(pRay, pNode->m_pRight, deep + 1, pPolygons);
//    }
//
//    return (leftResolved || rightResolved);
//}
////---------------------------------------------------------------------------
///*REM
//void csrAABBTreeNodeContentRelease(CSR_AABBNode* pNode)
//{
//    // release the bounding box
//    if (pNode->m_pBox)
//    {
//        free(pNode->m_pBox);
//        pNode->m_pBox = 0;
//    }
//
//    // release the polygon buffer
//    if (pNode->m_pPolygonBuffer)
//    {
//        // release the polygon buffer content
//        if (pNode->m_pPolygonBuffer->m_pIndexedPolygon)
//            free(pNode->m_pPolygonBuffer->m_pIndexedPolygon);
//
//        free(pNode->m_pPolygonBuffer);
//        pNode->m_pPolygonBuffer = 0;
//    }
//}
//*/
////---------------------------------------------------------------------------
///*REM
//void csrAABBTreeNodeRelease(CSR_AABBNode* pNode)
//{
//    if (!pNode)
//        return;
//
//    // release all children on left side
//    if (pNode->m_pLeft)
//        csrAABBTreeNodeRelease(pNode->m_pLeft);
//
//    // release all children on right side
//    if (pNode->m_pRight)
//        csrAABBTreeNodeRelease(pNode->m_pRight);
//
//    // delete node content
//    csrAABBTreeNodeContentRelease(pNode);
//
//    // delete node
//    free(pNode);
//}
//*/
////---------------------------------------------------------------------------
//// Sliding functions
////---------------------------------------------------------------------------
//void csrSlidingPoint(const CSR_Plane* pSlidingPlane,
//                     const CSR_Vector3* pPosition,
//                     float        radius,
//                     CSR_Vector3* pR)
//{
//    float        distanceToPlane;
//    CSR_Plane    plane;
//    CSR_Vector3  planeRatio;
//    CSR_Vector3  pointBeyondPlane;
//    CSR_Vector3  pointOnPlane;
//    CSR_Segment3 segment;
//    CSR_Figure3  segmentFigure;
//    CSR_Figure3  planeFigure;
//
//    plane = *pSlidingPlane;
//
//    // calculate the distance between the center of the sphere and the plane
//    csrPlaneDistanceTo(pPosition, &plane, &distanceToPlane);
//
//    // check if value is negative
//    if (distanceToPlane < 0.0f)
//    {
//        // invert the plane
//        plane.m_A = -plane.m_A;
//        plane.m_B = -plane.m_B;
//        plane.m_C = -plane.m_C;
//        plane.m_D = -plane.m_D;
//    }
//
//    // calculate the direction of the segment position - plane
//    planeRatio.m_X = radius * plane.m_A;
//    planeRatio.m_Y = radius * plane.m_B;
//    planeRatio.m_Z = radius * plane.m_C;
//
//    // calculate who the segment perpendicular to the plane, from the center
//    // of the sphere, cross the collision sphere. Normally this point is beyond
//    // the plane
//    pointBeyondPlane.m_X = pPosition->m_X - planeRatio.m_X;
//    pointBeyondPlane.m_Y = pPosition->m_Y - planeRatio.m_Y;
//    pointBeyondPlane.m_Z = pPosition->m_Z - planeRatio.m_Z;
//
//    // configure the segment to test
//    segment.m_Start = *pPosition;
//    segment.m_End = pointBeyondPlane;
//
//    // build a figure containing the segment
//    segmentFigure.m_Type = CSR_F3_Segment;
//    segmentFigure.m_pFigure = &segment;
//
//    // build a figure containing the plane
//    planeFigure.m_Type = CSR_F3_Plane;
//    planeFigure.m_pFigure = pSlidingPlane;
//
//    // calculate the point where the segment "center of the sphere - point beyond
//    // the plane" cross the collision plane
//    csrIntersect3(&segmentFigure, &planeFigure, &pointOnPlane, 0, 0);
//
//    // from point calculated below, we add the radius of the sphere, and we
//    // returns the value
//    pR->m_X = pointOnPlane.m_X + planeRatio.m_X;
//    pR->m_Y = pointOnPlane.m_Y + planeRatio.m_Y;
//    pR->m_Z = pointOnPlane.m_Z + planeRatio.m_Z;
//}
////---------------------------------------------------------------------------
//// Ground collision functions
////---------------------------------------------------------------------------
//int csrGroundCollision(const CSR_Sphere* pSphere,
//                       const CSR_Polygon3* pPolygon,
//                       const CSR_Vector3* pGroundDir,
//                       CSR_Vector3* pR)
//{
//    CSR_Ray3    ray;
//    CSR_Vector3 groundDir;
//    CSR_Figure3 rayToCheck;
//    CSR_Figure3 polygonToCheck;
//
//    // validate the inputs
//    if (!pSphere || !pPolygon)
//        return 0;
//
//    // get the ground direction
//    if (pGroundDir)
//        groundDir = *pGroundDir;
//    else
//    {
//        groundDir.m_X = 0.0f;
//        groundDir.m_Y = -1.0f;
//        groundDir.m_Z = 0.0f;
//    }
//
//    // create the ground ray
//    csrRay3FromPointDir(&pSphere->m_Center, &groundDir, &ray);
//
//    // build the ray figure to check
//    rayToCheck.m_Type = CSR_F3_Ray;
//    rayToCheck.m_pFigure = &ray;
//
//    // build the polygon figure to check against
//    polygonToCheck.m_Type = CSR_F3_Polygon;
//    polygonToCheck.m_pFigure = pPolygon;
//
//    // calculate the point where the ground ray hit the polygon
//    if (!csrIntersect3(&rayToCheck, &polygonToCheck, pR, 0, 0))
//        return 0;
//
//    // consider the sphere radius in the result
//    if (pR)
//    {
//        pR->m_X += (pSphere->m_Radius * -groundDir.m_X);
//        pR->m_Y += (pSphere->m_Radius * -groundDir.m_Y);
//        pR->m_Z += (pSphere->m_Radius * -groundDir.m_Z);
//    }
//
//    return 1;
//}
////---------------------------------------------------------------------------
//int csrGroundPosY(const CSR_Sphere* pBoundingSphere,
//                  const CSR_AABBNode* pTree,
//                  const CSR_Vector3* pGroundDir,
//                  CSR_Polygon3* pGroundPolygon,
//                  float* pR)
//{
//    size_t             i;
//    CSR_Ray3           groundRay;
//    CSR_Vector3        groundPos;
//    CSR_Polygon3Buffer polygonBuffer;
//    int                result;
//
//    // validate the inputs
//    if (!pBoundingSphere || !pTree || !pGroundDir)
//        return 0;
//
//    result = 0;
//
//    // create the ground ray
//    csrRay3FromPointDir(&pBoundingSphere->m_Center, pGroundDir, &groundRay);
//
//    // using the ground ray, resolve aligned-axis bounding box tree
//    csrAABBTreeResolve(&groundRay, pTree, 0, &polygonBuffer);
//
//    // initialize the ground position from the bounding sphere center
//    groundPos = pBoundingSphere->m_Center;
//
//    // iterate through polygons to check
//    for (i = 0; i < polygonBuffer.m_Count; ++i)
//        // check if a ground polygon was found, calculate the ground position if yes
//        if (csrGroundCollision(pBoundingSphere, &polygonBuffer.m_pPolygon[i], pGroundDir, &groundPos))
//        {
//            // copy the ground polygon, if required
//            if (pGroundPolygon)
//                *pGroundPolygon = polygonBuffer.m_pPolygon[i];
//
//            result = 1;
//            break;
//        }
//
//    // delete found polygons (no longer needed from now)
//    if (polygonBuffer.m_Count)
//        free(polygonBuffer.m_pPolygon);
//
//    // copy the resulting y value
//    if (pR)
//        *pR = groundPos.m_Y;
//
//    return result;
//}
////---------------------------------------------------------------------------
//DWF_PolygonF DWF_AABBTree::IndexedPolygonToPolygon(const IIndexedPolygon* pIndexedPolygon) const
//{
//    // no indexed polygon to extract from?
//    if (!pIndexedPolygon)
//        return DWF_PolygonF();
//
//    // indexed polygon doesn't contain vertex buffer?
//    if (!pIndexedPolygon->m_pVB)
//        return DWF_PolygonF();
//
//    DWF_PolygonF polygon;
//
//    // iterate through vertices to extract
//    for (std::uint8_t i = 0; i < 3; ++i)
//    {
//        // get the vertex buffer index
//        const std::size_t index = pIndexedPolygon->m_Index[i];
//
//        // is index out of bounds?
//        if (index >= pIndexedPolygon->m_pVB->m_Data.size())
//        {
//            polygon.m_Vertex[i].m_X = 0.0f;
//            polygon.m_Vertex[i].m_Y = 0.0f;
//            polygon.m_Vertex[i].m_Z = 0.0f;
//            continue;
//        }
//
//        // get the polygon vertex from vertex buffer
//        polygon.m_Vertex[i].m_X = pIndexedPolygon->m_pVB->m_Data[index];
//        polygon.m_Vertex[i].m_Y = pIndexedPolygon->m_pVB->m_Data[index + 1];
//        polygon.m_Vertex[i].m_Z = pIndexedPolygon->m_pVB->m_Data[index + 2];
//    }
//
//    return polygon;
//}
////---------------------------------------------------------------------------
//void DWF_AABBTree::ExtendBoxToPolygon(const DWF_PolygonF& polygon,
//                                            DWF_Box*      pBox,
//                                            bool&         empty)
//{
//    // iterate through polygon vertices
//    for (std::uint8_t i = 0; i < 3; ++i)
//    {
//        // is box empty?
//        if (empty)
//        {
//            // initialize bounding box with first vertex
//            pBox->m_Min = polygon.m_Vertex[i];
//            pBox->m_Max = polygon.m_Vertex[i];
//            empty       = false;
//            continue;
//        }
//
//        // search for box min edge
//        pBox->m_Min.m_X = std::min(pBox->m_Min.m_X, polygon.m_Vertex[i].m_X);
//        pBox->m_Min.m_Y = std::min(pBox->m_Min.m_Y, polygon.m_Vertex[i].m_Y);
//        pBox->m_Min.m_Z = std::min(pBox->m_Min.m_Z, polygon.m_Vertex[i].m_Z);
//
//        // search for box max edge
//        pBox->m_Max.m_X = std::max(pBox->m_Max.m_X, polygon.m_Vertex[i].m_X);
//        pBox->m_Max.m_Y = std::max(pBox->m_Max.m_Y, polygon.m_Vertex[i].m_Y);
//        pBox->m_Max.m_Z = std::max(pBox->m_Max.m_Z, polygon.m_Vertex[i].m_Z);
//    }
//}
////---------------------------------------------------------------------------
////REM CSR_IndexedPolygonBuffer* csrIndexedPolygonBufferFromMesh(const CSR_Mesh* pMesh)
//bool DWF_AABBTree::IndexedPolygonBufferFromMesh(const DWF_Mesh* pMesh, IIndexedPolygonBuffer& ipb) const
//{
//    /*REM
//    size_t                    i;
//    size_t                    j;
//    size_t                    index;
//    CSR_IndexedPolygon        indexedPolygon;
//    CSR_IndexedPolygonBuffer* pIPB;
//    */
//
//    // validate the inputs
//    if (!pMesh || !pMesh->m_VBs.size())
//        return false;
//
//    // create an indexed polygon buffer
//    //REM pIPB = csrIndexedPolygonBufferCreate();
//
//    /*REM
//    // succeeded?
//    if (!pIPB)
//        return 0;
//    */
//
//    IIndexedPolygon indexedPolygon;
//
//    // iterate through meshes
//    for (std::size_t i = 0; i < pMesh->m_VBs.size(); ++i)
//    {
//        // is mesh empty?
//        if (!pMesh->m_VBs[i]->m_Data.size())
//            continue;
//
//        // assign the reference to the source vertex buffer
//        indexedPolygon.m_pVB = &pMesh->m_pVB[i];
//
//        // search for vertex type
//        switch (pMesh->m_pVB[i].m_Format.m_Type)
//        {
//            case CSR_VT_Triangles:
//            {
//                // calculate iteration step
//                const unsigned step = (pMesh->m_pVB[i].m_Format.m_Stride * 3);
//
//                // iterate through source vertices
//                for (j = 0; j < pMesh->m_pVB[i].m_Count; j += step)
//                {
//                    // extract polygon from source vertex buffer and add it to polygon buffer
//                    indexedPolygon.m_pIndex[0] = j;
//                    indexedPolygon.m_pIndex[1] = j + pMesh->m_pVB[i].m_Format.m_Stride;
//                    indexedPolygon.m_pIndex[2] = j + (pMesh->m_pVB[i].m_Format.m_Stride * 2);
//                    csrIndexedPolygonBufferAdd(&indexedPolygon, pIPB);
//                }
//
//                continue;
//            }
//
//            case CSR_VT_TriangleStrip:
//            {
//                // calculate length to read in triangle strip buffer
//                const unsigned stripLength =
//                    (unsigned)(pMesh->m_pVB[i].m_Count -
//                               (pMesh->m_pVB[i].m_Format.m_Stride * 2));
//
//                index = 0;
//
//                // iterate through source vertices
//                for (j = 0; j < stripLength; j += pMesh->m_pVB[i].m_Format.m_Stride)
//                {
//                    // extract polygon from source buffer, revert odd polygons
//                    if (!index || !(index % 2))
//                    {
//                        indexedPolygon.m_pIndex[0] = j;
//                        indexedPolygon.m_pIndex[1] = j + pMesh->m_pVB[i].m_Format.m_Stride;
//                        indexedPolygon.m_pIndex[2] = j + (pMesh->m_pVB[i].m_Format.m_Stride * 2);
//                    }
//                    else
//                    {
//                        indexedPolygon.m_pIndex[0] = j + pMesh->m_pVB[i].m_Format.m_Stride;
//                        indexedPolygon.m_pIndex[1] = j;
//                        indexedPolygon.m_pIndex[2] = j + (pMesh->m_pVB[i].m_Format.m_Stride * 2);
//                    }
//
//                    csrIndexedPolygonBufferAdd(&indexedPolygon, pIPB);
//                    ++index;
//                }
//
//                continue;
//            }
//
//            case CSR_VT_TriangleFan:
//            {
//                // calculate length to read in triangle fan buffer
//                const unsigned fanLength =
//                    (unsigned)(pMesh->m_pVB[i].m_Count - pMesh->m_pVB[i].m_Format.m_Stride);
//
//                // iterate through source vertices
//                for (j = pMesh->m_pVB[i].m_Format.m_Stride;
//                     j < fanLength;
//                     j += pMesh->m_pVB[i].m_Format.m_Stride)
//                {
//                    // extract polygon from source buffer
//                    indexedPolygon.m_pIndex[0] = 0;
//                    indexedPolygon.m_pIndex[1] = j;
//                    indexedPolygon.m_pIndex[2] = j + pMesh->m_pVB[i].m_Format.m_Stride;
//                    csrIndexedPolygonBufferAdd(&indexedPolygon, pIPB);
//                }
//
//                continue;
//            }
//
//            case CSR_VT_Quads:
//            {
//                // calculate iteration step
//                const unsigned step = (pMesh->m_pVB[i].m_Format.m_Stride * 4);
//
//                // iterate through source vertices
//                for (j = 0; j < pMesh->m_pVB[i].m_Count; j += step)
//                {
//                    // calculate vertices position
//                    const unsigned v1 = (unsigned)j;
//                    const unsigned v2 = (unsigned)(j + pMesh->m_pVB[i].m_Format.m_Stride);
//                    const unsigned v3 = (unsigned)(j + (pMesh->m_pVB[i].m_Format.m_Stride * 2));
//                    const unsigned v4 = (unsigned)(j + (pMesh->m_pVB[i].m_Format.m_Stride * 3));
//
//                    // extract first polygon from source buffer
//                    indexedPolygon.m_pIndex[0] = v1;
//                    indexedPolygon.m_pIndex[1] = v2;
//                    indexedPolygon.m_pIndex[2] = v3;
//                    csrIndexedPolygonBufferAdd(&indexedPolygon, pIPB);
//
//                    // extract second polygon from source buffer
//                    indexedPolygon.m_pIndex[0] = v3;
//                    indexedPolygon.m_pIndex[1] = v2;
//                    indexedPolygon.m_pIndex[2] = v4;
//                    csrIndexedPolygonBufferAdd(&indexedPolygon, pIPB);
//                }
//
//                continue;
//            }
//
//            case CSR_VT_QuadStrip:
//            {
//                // calculate iteration step
//                const unsigned step = (pMesh->m_pVB[i].m_Format.m_Stride * 2);
//
//                // calculate length to read in triangle strip buffer
//                const unsigned stripLength =
//                    (unsigned)(pMesh->m_pVB[i].m_Count -
//                               (pMesh->m_pVB[i].m_Format.m_Stride * 2));
//
//                // iterate through source vertices
//                for (j = 0; j < stripLength; j += step)
//                {
//                    // calculate vertices position
//                    const unsigned v1 = (unsigned)j;
//                    const unsigned v2 = (unsigned)(j + pMesh->m_pVB[i].m_Format.m_Stride);
//                    const unsigned v3 = (unsigned)(j + (pMesh->m_pVB[i].m_Format.m_Stride * 2));
//                    const unsigned v4 = (unsigned)(j + (pMesh->m_pVB[i].m_Format.m_Stride * 3));
//
//                    // extract first polygon from source buffer
//                    indexedPolygon.m_pIndex[0] = v1;
//                    indexedPolygon.m_pIndex[1] = v2;
//                    indexedPolygon.m_pIndex[2] = v3;
//                    csrIndexedPolygonBufferAdd(&indexedPolygon, pIPB);
//
//                    // extract second polygon from source buffer
//                    indexedPolygon.m_pIndex[0] = v3;
//                    indexedPolygon.m_pIndex[1] = v2;
//                    indexedPolygon.m_pIndex[2] = v4;
//                    csrIndexedPolygonBufferAdd(&indexedPolygon, pIPB);
//                }
//
//                continue;
//            }
//
//            default:
//                continue;
//        }
//    }
//
//    return pIPB;
//}
////---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// DWF_AABBNode
//---------------------------------------------------------------------------
DWF_AABBNode::DWF_AABBNode(DWF_AABBNode* pParent) :
    m_pParent(pParent)
{}
//---------------------------------------------------------------------------
DWF_AABBNode::~DWF_AABBNode()
{
    // delete left node
    if (m_pLeft)
        delete m_pLeft;

    // delete right node
    if (m_pRight)
        delete m_pRight;

    // delete bounding box
    if (m_pBox)
        delete m_pBox;

    // delete and clear the polygon list
    for (DWF_PolygonsF::iterator it = m_Polygons.begin(); it != m_Polygons.end(); ++it)
        delete (*it);
}
//---------------------------------------------------------------------------
// DWF_AABBTree
//---------------------------------------------------------------------------
DWF_AABBTree::DWF_AABBTree()
{}
//---------------------------------------------------------------------------
DWF_AABBTree::~DWF_AABBTree()
{
    // delete entire tree hierarchy
    if (m_pRoot)
        delete m_pRoot;
}
//---------------------------------------------------------------------------
DWF_Box* DWF_AABBTree::GetBoundingBox() const
{
    if (!m_pRoot)
        return nullptr;

    return m_pRoot->m_pBox;
}
//---------------------------------------------------------------------------
std::size_t DWF_AABBTree::GetPolygonCount() const
{
    return m_PolygonCount;
}
//---------------------------------------------------------------------------
bool DWF_AABBTree::Populate(const DWF_PolygonsF& polygons)
{
    m_PolygonCount = polygons.size();

    // tree was already populated?
    if (m_pRoot)
        // clear it first
        delete m_pRoot;

    // create root node
    m_pRoot = new DWF_AABBNode(nullptr);

    // populate tree
    return Populate(m_pRoot, polygons);
}
//---------------------------------------------------------------------------
bool DWF_AABBTree::Resolve(const DWF_RayF* pRay, DWF_PolygonsF& polygons) const
{
    return Resolve(pRay, m_pRoot, polygons);
}
//---------------------------------------------------------------------------
DWF_Vector3F DWF_AABBTree::GetSlidingPoint(const DWF_PlaneF&   slidingPlane,
                                           const DWF_Vector3F& pos,
                                                 float         radius)
{
    DWF_PlaneF plane = slidingPlane;

    // calculate the distance between the center of the sphere and the plane
    const float distanceToPlane = plane.DistanceTo(pos);

    // check if value is negative
    if (distanceToPlane < 0.0f)
        // invert the plane
        plane = -plane;

    // calculate the direction of the line segment position - plane
    const DWF_Vector3F planeRatio(radius * plane.m_A,
                                  radius * plane.m_B,
                                  radius * plane.m_C);

    // calculate who the line segment perpendicular to the plane, from the center
    // of the sphere, cross the collision sphere. Normally this point is beyond
    // the plane
    const DWF_Vector3F pointBeyondPlane(pos.m_X - planeRatio.m_X,
                                        pos.m_Y - planeRatio.m_Y,
                                        pos.m_Z - planeRatio.m_Z);

    // configure the line segment to test
    const DWF_LineF line(pos, pointBeyondPlane);

    DWF_Vector3F pointOnPlane;

    if (!plane.Intersect(line, pointOnPlane))
        return DWF_Vector3F();

    // from point calculated above, add the sphere radius and return the value
    return DWF_Vector3F(pointOnPlane.m_X + planeRatio.m_X,
                        pointOnPlane.m_Y + planeRatio.m_Y,
                        pointOnPlane.m_Z + planeRatio.m_Z);
}
//---------------------------------------------------------------------------
bool DWF_AABBTree::GroundCollision(const DWF_Sphere&   boundingSphere,
                                   const DWF_PolygonF& polygon,
                                   const DWF_Vector3F& groundDir,
                                         DWF_Vector3F& groundPos)
{
    // create the ground ray
    DWF_RayF ray(boundingSphere.m_Center, groundDir);

    // calculate the point where the ground ray hit the polygon
    if (!polygon.Intersect(ray, groundPos))
        return false;

    // consider the sphere radius in the result
    groundPos.m_X += (boundingSphere.m_Radius * -groundDir.m_X);
    groundPos.m_Y += (boundingSphere.m_Radius * -groundDir.m_Y);
    groundPos.m_Z += (boundingSphere.m_Radius * -groundDir.m_Z);

    return true;
}
//---------------------------------------------------------------------------
bool DWF_AABBTree::GroundPosY(const DWF_Sphere&   boundingSphere,
                              const DWF_Vector3F& groundDir,
                                    DWF_PolygonF& groundPolygon,
                                    float&        groundY)
{
    bool result = false;

    // create the ground ray
    DWF_RayF      groundRay(boundingSphere.m_Center, groundDir);
    DWF_PolygonsF polygons;

    // using the ground ray, resolve aligned-axis bounding box tree
    Resolve(&groundRay, polygons);

    // initialize the ground position from the bounding sphere center
    DWF_Vector3F groundPos = boundingSphere.m_Center;

    // iterate through polygons to check
    for (DWF_PolygonsF::iterator it = polygons.begin(); it != polygons.end(); ++it)
        // check if a ground polygon was found, calculate the ground position if yes
        if (GroundCollision(boundingSphere, *(*it), groundDir, groundPos))
        {
            // copy the ground polygon
            groundPolygon = *(*it);

            result = true;
            break;
        }

    // delete and clear the found polygons (no longer required since now)
    for (DWF_PolygonsF::iterator it = polygons.begin(); it != polygons.end(); ++it)
        delete (*it);

    // copy the resulting y value
    groundY = groundPos.m_Y;

    return result;
}
//---------------------------------------------------------------------------
bool DWF_AABBTree::GetPolygons(const DWF_VertexBuffer* pVB, DWF_PolygonsF& polygons)
{
    const std::size_t vertexCount = pVB->m_Data.size();

    // no data to extract from?
    if (!vertexCount)
        return true;

    // search for vertex type
    switch (pVB->m_Format.m_Type)
    {
        case DWF_VertexBuffer::IFormat::IEType::IE_VT_Triangles:
        {
            // calculate iteration step
            const std::size_t step = (pVB->m_Format.m_Stride * 3);

            // iterate through source vertexes
            for (std::size_t i = 0; i < vertexCount; i += step)
                // extract polygon from source buffer
                AddPolygon(*pVB,
                           i,
                           i +  pVB->m_Format.m_Stride,
                           i + (pVB->m_Format.m_Stride * 2),
                           polygons);

            return true;
        }

        case DWF_VertexBuffer::IFormat::IEType::IE_VT_TriangleStrip:
        {
            // calculate length to read in triangle strip buffer
            const std::size_t stripLength = (vertexCount - (pVB->m_Format.m_Stride * 2));
                  std::size_t index       = 0;

            // iterate through source vertexes
            for (std::size_t i = 0; i < stripLength; i += pVB->m_Format.m_Stride)
            {
                // extract polygon from source buffer, revert odd polygons
                if (!index || !(index % 2))
                    AddPolygon(*pVB,
                               i,
                               i +  pVB->m_Format.m_Stride,
                               i + (pVB->m_Format.m_Stride * 2),
                               polygons);
                else
                    AddPolygon(*pVB,
                               i +  pVB->m_Format.m_Stride,
                               i,
                               i + (pVB->m_Format.m_Stride * 2),
                               polygons);

                ++index;
            }

            return true;
        }

        case DWF_VertexBuffer::IFormat::IEType::IE_VT_TriangleFan:
        {
            // calculate length to read in triangle fan buffer
            const std::size_t fanLength = (vertexCount - pVB->m_Format.m_Stride);

            // iterate through source vertexes
            for (std::size_t i = pVB->m_Format.m_Stride; i < fanLength; i += pVB->m_Format.m_Stride)
                // extract polygon from source buffer
                AddPolygon(*pVB,
                           0,
                           i,
                           i + pVB->m_Format.m_Stride,
                           polygons);

            return true;
        }

        case DWF_VertexBuffer::IFormat::IEType::IE_VT_Quads:
        {
            // calculate iteration step
            const std::size_t step = (pVB->m_Format.m_Stride * 4);

            // iterate through source vertexes
            for (std::size_t i = 0; i < vertexCount; i += step)
            {
                // calculate vertexes position
                const std::size_t v1 = i;
                const std::size_t v2 = i +  pVB->m_Format.m_Stride;
                const std::size_t v3 = i + (pVB->m_Format.m_Stride * 2);
                const std::size_t v4 = i + (pVB->m_Format.m_Stride * 3);

                // extract polygons from source buffer
                AddPolygon(*pVB, v1, v2, v3, polygons);
                AddPolygon(*pVB, v3, v2, v4, polygons);
            }

            return true;
        }

        case DWF_VertexBuffer::IFormat::IEType::IE_VT_QuadStrip:
        {
            // calculate iteration step
            const std::size_t step = (pVB->m_Format.m_Stride * 2);

            // calculate length to read in triangle strip buffer
            const std::size_t stripLength = (vertexCount - (pVB->m_Format.m_Stride * 2));

            // iterate through source vertexes
            for (std::size_t i = 0; i < stripLength; i += step)
            {
                // calculate vertexes position
                const std::size_t v1 = i;
                const std::size_t v2 = i +  pVB->m_Format.m_Stride;
                const std::size_t v3 = i + (pVB->m_Format.m_Stride * 2);
                const std::size_t v4 = i + (pVB->m_Format.m_Stride * 3);

                // extract polygons from source buffer
                AddPolygon(*pVB, v1, v2, v3, polygons);
                AddPolygon(*pVB, v3, v2, v4, polygons);
            }

            return true;
        }

        default:
            return false;
    }
}
//---------------------------------------------------------------------------
void DWF_AABBTree::AddPolygonToBoundingBox(const DWF_PolygonF& polygon,
                                                 DWF_Box*      pBox,
                                                 bool&         empty) const
{
    // no box to add to?
    if (!pBox)
        return;

    // iterate through polygon vertices
    for (std::uint8_t i = 0; i < 3; ++i)
    {
        // is box empty?
        if (empty)
        {
            // initialize bounding box with first vertex
            pBox->m_Min = polygon.m_Vertex[i];
            pBox->m_Max = polygon.m_Vertex[i];
            empty       = false;
            continue;
        }

        // search for box min edge
        pBox->m_Min = DWF_Vector3F(std::min(pBox->m_Min.m_X, polygon.m_Vertex[i].m_X),
                                   std::min(pBox->m_Min.m_Y, polygon.m_Vertex[i].m_Y),
                                   std::min(pBox->m_Min.m_Z, polygon.m_Vertex[i].m_Z));

        // search for box max edge
        pBox->m_Max = DWF_Vector3F(std::max(pBox->m_Max.m_X, polygon.m_Vertex[i].m_X),
                                   std::max(pBox->m_Max.m_Y, polygon.m_Vertex[i].m_Y),
                                   std::max(pBox->m_Max.m_Z, polygon.m_Vertex[i].m_Z));
    }
}
//---------------------------------------------------------------------------
bool DWF_AABBTree::Populate(DWF_AABBNode* pNode, const DWF_PolygonsF& polygons)
{
    bool boxEmpty = true;

    // create a collision box
    pNode->m_pBox = new DWF_Box();

    // iterate through polygons to divide
    for (DWF_PolygonsF::const_iterator it = polygons.begin(); it != polygons.end(); ++it)
        // calculate bounding box
        AddPolygonToBoundingBox(*(*it), pNode->m_pBox, boxEmpty);

    // create left and right boxes
    std::unique_ptr<DWF_Box> pLeftBox (new DWF_Box());
    std::unique_ptr<DWF_Box> pRightBox(new DWF_Box());

    // divide box in 2 sub-boxes
    pNode->m_pBox->Cut(*pLeftBox.get(), *pRightBox.get());

    DWF_PolygonsF leftPolygons, rightPolygons;

    // iterate again through polygons to divide
    for (DWF_PolygonsF::const_iterator it = polygons.begin(); it != polygons.end(); ++it)
        for (std::uint8_t i = 0; i < 3; ++i)
            // check if first polygon vertices belongs to left or right sub-box
            if ((*it)->IsBetween((*it)->m_Vertex[i],
                                 pLeftBox->m_Min,
                                 pLeftBox->m_Max,
                                 (float)M_Epsilon))
            {
                // create left polygon
                std::unique_ptr<DWF_PolygonF> pPolygon(new DWF_PolygonF());

                // copy polygon
                for (std::uint8_t j = 0; j < 3; ++j)
                    pPolygon->m_Vertex[j] = (*it)->m_Vertex[j];

                // add polygon to left list
                leftPolygons.push_back(pPolygon.get());
                pPolygon.release();

                break;
            }
            else
            if ((*it)->IsBetween((*it)->m_Vertex[i],
                                 pRightBox->m_Min,
                                 pRightBox->m_Max,
                                 (float)M_Epsilon))
            {
                // create left polygon
                std::unique_ptr<DWF_PolygonF> pPolygon(new DWF_PolygonF());

                // copy polygon
                for (std::uint8_t j = 0; j < 3; ++j)
                    pPolygon->m_Vertex[j] = (*it)->m_Vertex[j];

                // add polygon to left list
                rightPolygons.push_back(pPolygon.get());
                pPolygon.release();

                break;
            }

    const std::size_t polygonCount      = polygons.size();
    const std::size_t leftPolygonCount  = leftPolygons.size();
    const std::size_t rightPolygonCount = rightPolygons.size();
    const bool        canResolveLeft    = ((leftPolygonCount  > 0) && (leftPolygonCount  < polygonCount));
    const bool        canResolveRight   = ((rightPolygonCount > 0) && (rightPolygonCount < polygonCount));

    // leaf reached?
    if (!canResolveLeft && !canResolveRight)
    {
        // iterate through polygons to copy
        for (DWF_PolygonsF::const_iterator it = polygons.begin(); it != polygons.end(); ++it)
        {
            // create left polygon
            std::unique_ptr<DWF_PolygonF> pPolygon(new DWF_PolygonF());

            // copy polygon
            for (std::uint8_t i = 0; i < 3; ++i)
                pPolygon->m_Vertex[i] = (*it)->m_Vertex[i];

            // add polygon to left list
            pNode->m_Polygons.push_back(pPolygon.get());
            pPolygon.release();
        }

        // delete left list, as it will no longer be used
        for (DWF_PolygonsF::iterator it = leftPolygons.begin(); it != leftPolygons.end(); ++it)
            delete (*it);

        // delete right list, as it will no longer be used
        for (DWF_PolygonsF::iterator it = rightPolygons.begin(); it != rightPolygons.end(); ++it)
            delete (*it);

        return true;
    }

    bool result = false;

    // do create left node?
    if (canResolveLeft)
    {
        // create and populate left node
        pNode->m_pLeft = new DWF_AABBNode(pNode);

        try
        {
            result = Populate(pNode->m_pLeft, leftPolygons) || result;
        }
        catch (...)
        {
            // delete current list, as it will no more be used
            for (DWF_PolygonsF::iterator it = leftPolygons.begin(); it != leftPolygons.end(); ++it)
                delete (*it);

            throw;
        }

        // delete current list, as it will no more be used
        for (DWF_PolygonsF::iterator it = leftPolygons.begin(); it != leftPolygons.end(); ++it)
            delete (*it);
    }

    // do create right node?
    if (canResolveRight)
    {
        // create and populate right node
        pNode->m_pRight = new DWF_AABBNode(pNode);

        try
        {
            result = Populate(pNode->m_pRight, rightPolygons) || result;
        }
        catch (...)
        {
            // delete current list, as it will no more be used
            for (DWF_PolygonsF::iterator it = rightPolygons.begin(); it != rightPolygons.end(); ++it)
                delete (*it);

            throw;
        }

        // delete current list, as it will no more be used
        for (DWF_PolygonsF::iterator it = rightPolygons.begin(); it != rightPolygons.end(); ++it)
            delete (*it);
    }

    return result;
}
//---------------------------------------------------------------------------
bool DWF_AABBTree::Resolve(const DWF_RayF* pRay, const DWF_AABBNode* pNode, DWF_PolygonsF& polygons) const
{
    // no node to resolve? (this should never happen, but...)
    if (!pNode)
        return false;

    bool leftResolved  = false;
    bool rightResolved = false;

    // is leaf?
    if (!pNode->m_pLeft && !pNode->m_pRight)
    {
        // iterate through polygons
        for (DWF_PolygonsF::const_iterator it = pNode->m_Polygons.begin();
             it != pNode->m_Polygons.end(); ++it)
        {
            // create polygon
            std::unique_ptr<DWF_PolygonF> pPolygon(new DWF_PolygonF());

            // copy polygon
            for (std::uint8_t i = 0; i < 3; ++i)
                pPolygon->m_Vertex[i] = (*it)->m_Vertex[i];

            // add polygon to result
            polygons.push_back(pPolygon.get());
            pPolygon.release();
        }

        return true;
    }

    // check if ray intersects the left box
    if (pNode->m_pLeft && pNode->m_pLeft->m_pBox->Intersect(*pRay))
        // resolve left node
        leftResolved = Resolve(pRay, pNode->m_pLeft, polygons);

    // check if ray intersects the right box
    if (pNode->m_pRight && pNode->m_pRight->m_pBox->Intersect(*pRay))
        // resolve right node
        rightResolved = Resolve(pRay, pNode->m_pRight, polygons);

    return (leftResolved || rightResolved);
}
//---------------------------------------------------------------------------
