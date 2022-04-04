/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SpecularSpheres.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This examples demonstrates the effect of specular lighting.
//
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"
#include <vtkPNGWriter.h>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkDataSetReader.h>
#include <vtkContourFilter.h>
#include <vtkRectilinearGrid.h>

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>


// ****************************************************************************
//  Function: GetNumberOfPoints
//
//  Arguments:
//     dims: an array of size 3 with the number of points in X, Y, and Z.
//           2D data sets would have Z=1
//
//  Returns:  the number of points in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfPoints(const int *dims)
{
    // 3D
    //return dims[0]*dims[1]*dims[2];
    // 2D
    return dims[0]*dims[1];
}

// ****************************************************************************
//  Function: GetNumberOfCells
//
//  Arguments:
//
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the number of cells in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfCells(const int *dims)
{
    // 3D
    //return (dims[0]-1)*(dims[1]-1)*(dims[2]-1);
    // 2D
    return (dims[0]-1)*(dims[1]-1);
}


// ****************************************************************************
//  Function: GetPointIndex
//
//  Arguments:
//      idx:  the logical index of a point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the point index
//
// ****************************************************************************

int GetPointIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
    // 2D
    return idx[1]*dims[0]+idx[0];
}


// ****************************************************************************
//  Function: GetCellIndex
//
//  Arguments:
//      idx:  the logical index of a cell.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the cell index
//
// ****************************************************************************

int GetCellIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)+idx[0];
    // 2D
    return idx[1]*(dims[0]-1)+idx[0];
}

// ****************************************************************************
//  Function: GetLogicalPointIndex
//
//  Arguments:
//      idx (output):  the logical index of the point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1] 
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      pointId:  a number between 0 and (GetNumberOfPoints(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************



void GetLogicalPointIndex(int *idx, int pointId, const int *dims)
{
    // 3D
    // idx[0] = pointId%dim[0];
    // idx[1] = (pointId/dims[0])%dims[1];
    // idx[2] = pointId/(dims[0]*dims[1]);

    // 2D
    idx[0] = pointId%dims[0];
    idx[1] = pointId/dims[0];
}


// ****************************************************************************
//  Function: GetLogicalCellIndex
//
//  Arguments:
//      idx (output):  the logical index of the cell index.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1 
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      cellId:  a number between 0 and (GetNumberOfCells(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalCellIndex(int *idx, int cellId, const int *dims)
{
    // 3D
    // idx[0] = cellId%(dims[0]-1);
    // idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
    // idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    idx[0] = cellId%(dims[0]-1);
    idx[1] = cellId/(dims[0]-1);
}
class SegmentList
{
   public:
                   SegmentList() { maxSegments = 10000; segmentIdx = 0; pts = new float[4*maxSegments]; };
     virtual      ~SegmentList() { delete [] pts; };

     void          AddSegment(float X1, float Y1, float X2, float Y2);
     vtkPolyData  *MakePolyData(void);

   protected:
     float        *pts;
     int           maxSegments;
     int           segmentIdx;
};

void
SegmentList::AddSegment(float X1, float Y1, float X2, float Y2)
{
    pts[4*segmentIdx+0] = X1;
    pts[4*segmentIdx+1] = Y1;
    pts[4*segmentIdx+2] = X2;
    pts[4*segmentIdx+3] = Y2;
    segmentIdx++;
}

vtkPolyData *
SegmentList::MakePolyData(void)
{
    int nsegments = segmentIdx;
    int numPoints = 2*(nsegments);
    vtkPoints *vtk_pts = vtkPoints::New();
    vtk_pts->SetNumberOfPoints(numPoints);
    int ptIdx = 0;
    vtkCellArray *lines = vtkCellArray::New();
    lines->EstimateSize(numPoints,2);
    for (int i = 0 ; i < nsegments ; i++)
    {
        double pt[3];
        pt[0] = pts[4*i];
        pt[1] = pts[4*i+1];
        pt[2] = 0.;
        vtk_pts->SetPoint(ptIdx, pt);
        pt[0] = pts[4*i+2];
        pt[1] = pts[4*i+3];
        pt[2] = 0.;
        vtk_pts->SetPoint(ptIdx+1, pt);
        vtkIdType ids[2] = { ptIdx, ptIdx+1 };
        lines->InsertNextCell(2, ids);
        ptIdx += 2;
    }

    vtkPolyData *pd = vtkPolyData::New();
    pd->SetPoints(vtk_pts);
    pd->SetLines(lines);
    lines->Delete();
    vtk_pts->Delete();

    return pd;
}

int main()
{
    int  i, j;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj5.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    // Add 4 segments that put a frame around your isolines.  This also
    // documents how to use "AddSegment".
    SegmentList sl;
    sl.AddSegment(-10, -10, +10, -10); // Add segment (-10,-10) -> (+10, -10)
    sl.AddSegment(-10, +10, +10, +10);
    sl.AddSegment(-10, -10, -10, +10);
    sl.AddSegment(+10, -10, +10, +10);
    int numsegments[16];
    for (int i = 0; i < sizeof(numsegments) / sizeof(numsegments[0]); i++) {
	    if (i == 0 or i == 15) {
		    numsegments[i] = 0;
	    }
	    else if (i == 6 or i == 9) {
		    numsegments[i] = 2;
	    }
	    else {
		    numsegments[i] = 1;
	    }
    }
    float pt[2]; 
    float pt1[2];
    int lup[16][4]; //lookup table for line segments and which edges each segment hits on the cell
/*
 
    Vertex 1   Edge 2  Vertex 3
         |--------------|
	 |		|
	 |		|
 Edge 1	 |		|  Edge 3
	 |		|
	 |		|
	 |		|
	 |--------------|
     Vertex 0   edge 0    Vertex 2
*/




    lup[0][0] = lup[0][1] = lup[0][2] = lup[0][3] = -1; // case 1
    lup[1][0] = 1;lup[1][1] = 0; lup[1][2] = -1;lup[1][3] = -1; //case 2

    lup[2][0] = 1;lup[2][1] = 2;lup[2][2] = -1;lup[2][3] = -1; // case 3
    lup[3][0] = 2;lup[3][1] = 0;lup[3][2] = -1 ;lup[3][3] = -1; // case 4
    lup[4][0] =  3; lup[4][1] =  0; lup[4][2] = -1; lup[4][3] = -1; // case 5
    lup[5][0] = 1; lup[5][1] = 3; lup[5][2] = -1; lup[5][3] = -1; // case 6
    lup[6][0] = 1;lup[6][1] = 2;lup[6][2] = 0; lup[6][3] = 3; // case 7 
    lup[7][0] = 2;lup[7][1] = 3;lup[7][2] = -1;lup[7][3] = -1; // case 8 
    lup[8][0] = 2;lup[8][1] = 3;lup[8][2] = -1;lup[8][3] = -1; // case 9
    lup[9][0] = 1;lup[9][1] = 0;lup[9][2] = 2;lup[9][3] = 3; // case 10
    lup[10][0] = 1; lup[10][1] = 3; lup[10][2] = -1; lup[10][3] = -1; // case 11
    lup[11][0] = 0;lup[11][1] = 3;lup[11][2] = -1;lup[11][3] = -1; // case 12
    lup[12][0] = 2;lup[12][1] = 0;lup[12][2] = -1;lup[12][3] = -1; // case 13
    lup[13][0] = 1;lup[13][1] = 2;lup[13][2] = -1;lup[13][3] = -1; // case 14 
    lup[14][0] = 1;lup[14][1] = 0;lup[14][2] = -1;lup[14][3] = -1; // case 15
    lup[15][0] = lup[15][1] = lup[15][2] = lup[15][3] = -1; // case 16 

    int x,y = 0;
    for (int j = 0; j < GetNumberOfCells(dims) - 1; j++) {
        int cellidx0[2];
    	GetLogicalCellIndex(cellidx0, j , dims);
	int casenum = 0;
    	x = cellidx0[0];
    	y = cellidx0[1];
//following convention of bottom left is V0, top left is V1, Top right is V3, bottomright is V2
    	int cellidx2[2] = {x + 1, y};
    	int cellidx1[2] = {x, y + 1};
    	int cellidx3[2] = {x + 1 , y + 1};
//These are out of number because of changing convention after writing code but it should follow above comment on the convention
    	float V0 = F[GetPointIndex(cellidx0,dims)]; 
    	float V2 = F[GetPointIndex(cellidx2,dims)];
    	float V3 = F[GetPointIndex(cellidx3,dims)];
    	float V1 = F[GetPointIndex(cellidx1,dims)];
//Get field values of each vertices to compare with ISO value
    	if (V0 > 3.2) {
	    	casenum += 1;
    	}
    	if (V1 > 3.2) {
	    	casenum += 2;
    	}
    	if (V2 > 3.2) {
	    	casenum += 4;
    	}
    	if (V3 > 3.2) {
	    	casenum += 8;
    	}
//Since convention is V3V2V1V0 which is binary then we add appropriate binary values to casenum 
//EX:
//Following Field values are V0 = 2, V1 = 3, V2 = 4, V3 = 5. Since V2 and V3 are bigger than ISO value than the casenumber would be 12 which is 1100 (The 1's are where V3 and V2 would be)
    	int nsegments = numsegments[casenum];
	cout <<"casenum: " << casenum << endl;
    	for (int i = 0; i < nsegments; i++) {
//Probably a better way to do this (Pre computing these edges would've been more organized ) But basically whatever edge that one endpoint of line segment equals we will find the two vertices it is in between of and find t based off field values then interpolate the X or Y to find where in the edge the isovalue lies on
	    	int edge1 = lup[casenum][2*i];
	    	if (edge1 == 1) { 
		    float t = (3.2 - V0) / (V1 - V0); //t is found based off field values
		    float y = Y[cellidx0[1]] + t * (Y[cellidx1[1]] - Y[cellidx0[1]]); //Then interpolate based on X or Y values
		    pt[0] = X[cellidx0[0]]; //Since edge 1 is between V0 and V1 there is no need to interpolate X as it will be the same point as V0 and V1, only point to find is the y
		    pt[1] = y;
	    	}
	    	if (edge1 == 3) {
                    float t = (3.2 - V2) / (V3 - V2);
                    float y = Y[cellidx2[1]] + t * (Y[cellidx3[1]] - Y[cellidx2[1]]);
                    pt[0] = X[cellidx3[0]];
		    pt[1] = y;
	    	}
	    	if (edge1 == 2) {
		    float t = (3.2 - V1) / (V3 - V1);
		    float x = X[cellidx1[0]] + t * (X[cellidx3[0]] - X[cellidx1[0]]);
		    pt[0] = x;
		    pt[1] = Y[cellidx1[1]];
//Since edge 2 is between V1 and V3 we interpolate to find X but Y should remain constant
	    	}
	    	if (edge1 == 0) {
                    float t = (3.2 - V0) / (V2 - V0);
                    float x = X[cellidx0[0]] + t * (X[cellidx2[0]] - X[cellidx0[0]]);
                    pt[0] = x;
		    pt[1] = Y[cellidx2[1]];
	    	}
//The Edge1 steps are repeated for edge2
//This will find the second endpoint for the linesegment
	    	int edge2 = lup[casenum][2*i+1];
            	if (edge2 == 1) {
                    float t = (3.2 - V0) / (V1 - V0);
                    float y = Y[cellidx0[1]] + t * (Y[cellidx1[1]] - Y[cellidx0[1]]);
                    pt1[0] = X[cellidx0[0]];
		    pt1[1] = y;
            	}
            	if (edge2 == 3) {
                    float t = (3.2 - V2) / (V3 - V2);
                    float y = Y[cellidx2[1]] + t * (Y[cellidx3[1]] - Y[cellidx2[1]]);
                    pt1[0] = X[cellidx3[0]];
		    pt1[1] = y;
            	}
            	if (edge2 == 2) {
                    float t = (3.2 - V1) / (V3 - V1);
                    float x = X[cellidx1[0]] + t * (X[cellidx3[0]] - X[cellidx1[0]]);
                    pt1[0] = x;
		    pt1[1] = Y[cellidx1[1]];
            	}
            	if (edge2 == 0) {
                    float t = (3.2 - V0) / (V2 - V0);
                    float x = X[cellidx0[0]] + t * (X[cellidx2[0]] - X[cellidx0[0]]);
                    pt1[0] = x;
		    pt1[1] = Y[cellidx2[1]];
            	}
//Once both endpoints are found we draw a line according to AddSegment in between the two
	    	sl.AddSegment(pt[0],pt[1],pt1[0],pt1[1]);
    	}
    }

// YOUR CODE TO GENERATE ISOLINES SHOULD GO HERE!

    vtkPolyData *pd = sl.MakePolyData();

    //This can be useful for debugging
/*
    vtkDataSetWriter *writer = vtkDataSetWriter::New();
    writer->SetFileName("paths.vtk");
    writer->SetInputData(pd);
    writer->Write();
 */

    vtkSmartPointer<vtkDataSetMapper> win1Mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    win1Mapper->SetInputData(pd);
    win1Mapper->SetScalarRange(0, 0.15);

    vtkSmartPointer<vtkActor> win1Actor =
      vtkSmartPointer<vtkActor>::New();
    win1Actor->SetMapper(win1Mapper);

    vtkSmartPointer<vtkRenderer> ren1 =
      vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    ren1->AddActor(win1Actor);
    ren1->SetBackground(0.0, 0.0, 0.0);
    renWin->SetSize(800, 800);

    ren1->GetActiveCamera()->SetFocalPoint(0,0,0);
    ren1->GetActiveCamera()->SetPosition(0,0,50);
    ren1->GetActiveCamera()->SetViewUp(0,1,0);
    ren1->GetActiveCamera()->SetClippingRange(20, 120);
    ren1->GetActiveCamera()->SetDistance(30);

    // This starts the event loop and invokes an initial render.
    //
    iren->Initialize();
    iren->Start();

    pd->Delete();
}
