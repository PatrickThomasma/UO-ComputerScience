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
#include <vtkFloatArray.h>
#include <iomanip>
#include <iostream>


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
//              2 <= idx[2] < dims[2] (or always zero if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z
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
//              2 <= idx[2] < dims[2]-1 (or always zero if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z
//            2D data sets would have Z=1
//
//  Returns:  the cell index
//
// ****************************************************************************

int GetCellIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)*idx[0];
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
//              2 <= idx[2] < dims[2] (or always zero if 2D)
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
//              2 <= idx[2] < dims[2]-1 (or always zero if 2D)
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


// ****************************************************************************
//  Function: EvaluateFieldAtLocation
//
//  Arguments:
//     pt: a two-dimensional location
//     dims: an array of size two.  
//           The first number is the size of the array in argument X, 
//           the second the size of Y.
//     X: an array (size is specified by dims).  
//        This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//        This contains the Y locations of a rectilinear mesh.
//     F: a scalar field defined on the mesh.  
//        Its size is dims[0]*dims[1].
//
//   Returns: the interpolated field value. 0 if the location is out of bounds.
//
// ****************************************************************************

float
EvaluateFieldAtLocation(const float *pt, const int *dims, 
                        const float *X, const float *Y, const float *F)
{
    int x1 = -1;
    int y1 = -1;
    for (int i = 1; i < dims[0]; i++) { //This for loop is finding which cell contains the point coordinate given
	    if (pt[0] < X[i] and pt[0] >= X[0]) {
		    x1 = i - 1;
		    //cout << "X1 becomes " << x1 << endl;

		    for (int j = 1; j < dims[1]; j++) {
			    if (pt[1] < Y[j] and pt[1] >= Y[0]) {
				    y1 = j - 1;
				    break;
			    }
		    }
	      break;
	    }
    }
    //cout << "Point numbers " << x1 << " " << y1 << endl;
    int cell[2] = {x1,y1}; //Cells contain logical point numbers Ce11 is Bottm left vertices
    int cell1[2] = {x1 + 1, y1}; // cell1 is bottom right
    int cell2[2] = {x1, y1 + 1}; // cell2 is top left
    int cell3[2] = {x1 + 1, y1 + 1}; //cell3 is top right
    //cout <<"Cell Index " << cell[0] << " " << cell[1] << endl;
    //cout << "Cell Indexes " << cell1[0] << " " << cell1[1] << endl;
    float V1 = F[GetPointIndex(cell,dims)]; //V1 is A
    //cout << " Vertice 1 index " << V1[0] << " " << V1[1] << endl;
    float V2 = F[GetPointIndex(cell1,dims)]; // V2 is B
    float V3 = F[GetPointIndex(cell2,dims)]; // The V's all contain field numbers of vertices V3 is F(A)
    float V4 = F[GetPointIndex(cell3,dims)]; // V4 is F(B)
    int point = GetPointIndex(cell,dims); //Points contain the 4 Point indexes of the cell
    int point1 = GetPointIndex(cell1,dims);
    int point2 = GetPointIndex(cell2,dims);
    int point3 = GetPointIndex(cell3,dims);
    //cout << "All my values: Cell1: " << cell[0] << ", " << cell[1] << " Cell2: " << cell1[0] << ", " << cell1[1] << " Field 1: " << V1 << " Field 2" << V2 << " Point1: " << point << " Point2: " << point1 << endl;
    float t = (pt[0] - X[cell[0]]) / (X[cell1[0]] - X[cell[0]]);
    float t2 = (pt[1] - Y[cell[1]]) / (Y[cell2[1]] - Y[cell[1]]);
    //cout << "T proportion is " << t << " " << t2 << endl;
    float field = V1 + (t*(V2 - V1));
    float field2 = V3 + (t * (V4-V3));
    //cout << "Field value from interpolation: " << field << " " <<field2 << endl;
    float field3 = field + (t2 * (field2 - field)); 




    return field3;
}


// ****************************************************************************
//  Function: AreaForCell
//
//  Arguments:
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     cellId: a cellIndex (I.e., between 0 and GetNumberOfCells(dims))
//  
//  Returns:  the area of the cell.  Each cell is a rectangle, and the
//            area of a rectangle is width*height.
//            If an invalid cell is specified, then the function should return 0.
//
// ****************************************************************************

float
AreaForCell(const float *X, const float *Y, const int *dims, int cellId)
{
    if (cellId >= GetNumberOfCells(dims)) {
	    return 0;
    }
    int idx[2];
    GetLogicalCellIndex(idx,cellId, dims);
    //cout << "Logical cell index " << idx[0] <<"  "  <<idx[1] << endl;
    int rv1 = idx[0];
    int rv2 = idx[1];
    //cout << "X and Y Points for cell " << rv1 << " " << rv2 << endl;
    float area = ((X[rv1 + 1] - X[rv1]) * (Y[rv2 + 1] - Y[rv2]));

    return area;
}

// ****************************************************************************
//  Function: CountNumberOfCellsWithinThreshold
//
//  Arguments:
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     F: a scalar field defined on the mesh.  Its size is dims[0]*dims[1].
//     min: the minimum range for a threshold
//     max: the maximum range for a threshold
//
//  Returns:  the number of cells within a threshold range.
//
//  Example: assume the desired threshold range is (L, H).  Consider cell C,
//    which has 4 vertices, and assume these 4 vertices have values F1, F2,
//    F3, and F4.
//    Then we define C to be within the threshold range if:
//       L <= F1 <= H  *AND*
//       L <= F2 <= H  *AND*
//       L <= F3 <= H  *AND*
//       L <= F4 <= H 
//
//   Your goal is to count the number of cells that are within the threshold
//   range. 
//
// ****************************************************************************

int
CountNumberOfCellsWithinThreshold(const float *X, const float *Y, const int *dims,
                             const float *F, float L, float H)
{
    int count = 0;
    int check = 0;
    int cellId;
    int counter;
    //int idx[2];
    //int F2[2];
    //int F3[2];
    //int F4[2];
    int point = 0;
    int cellIdx[2];
    int x1 = 0; 
    int x2 = 0;
    //cout << "Two points are: " << x1 << " " << x2 << endl;
    for (int i = 0; i < GetNumberOfCells(dims); i++) {
	    GetLogicalCellIndex(cellIdx, i , dims);
	    x1 = cellIdx[0];
	    x2 = cellIdx[1];
	    int cellIdx1[2] = {x1 + 1, x2};
	    int cellIdx2[2] = {x1, x2 + 1};
	    int cellIdx3[2] = {x1 + 1, x2 + 1};
	    float field = F[GetPointIndex(cellIdx,dims)];
	    float field1 = F[GetPointIndex(cellIdx1,dims)];
	    float field2 = F[GetPointIndex(cellIdx2, dims)];
	    float field3 = F[GetPointIndex(cellIdx3, dims)];
	    //cout << "I value " << i << " " << "Field value " << field  << " " << field1 << " " << field2 << " " << field3 << endl;
	    //cout << "L value is this: " << L << "H value is this "  << H << " Field value is: "<< field  << endl;
	    if ((L <= field) and (field <= H)) {
		    check++;
	    }
	    if ((L <= field1) and (field1 <= H)) {
		    check++;
	    }
	    if ((L <= field2) and (field2<= H)) {
		    check++;
	    }
	    if ((L <= field3) and (field3 <= H)) {
		    check++;
	    }
	    //cout <<"Check value " << check << endl;
	    if (check == 4) {
		    count++;
		    check = 0;
	    }
	    else {
		    check = 0;
	    }
	    
	    
	    
    }

		
             
	   
	    //cout << "Index is: " << cellID << " " << idx[1] << endl;
    

    //GetLogicalPointIndex(idx, 81 ,dims);
//    for (int i = 0; i < dims[0]; i++) {
//	    for (int j = 0; j < dims[1]; j++) {
//		    if (X[i] >= L and X[i] <= H) {
//			    check++;
//		    }
//		    if (X[i + 1] + 1 >= L and X[i + 1] <= H) {
//			    check++;
//		    }
//		    if (Y[j] >= L and Y[j] <= H) {
//			    check++;
//		    }
//		    if (Y[j + 1] >= L and Y[j + 1] <= H) {
//			    check++;
//		    }
//		    if (check == 4) {
//			    count++;
//		    }
//		    else {
//			    check = 0;
//			    continue;
//		    }
//	    }
  //  }

    //cout << "Value of idx at this point "<< idx[0]<< "  " << idx[1]<< endl;
    //cout <<" Value of F2 at this point " << F2[0] << " " << F2[1] << endl;
    //cout <<" Value of F3 at this point " << F3[0] << " " << F3[1] << endl;
    //cout <<" Value of F4 at this point " << F4[0] << " " << F4[1] << endl;
 
//    for (int i = 0; i < GetNumberOfCells(dims); i++) {
//	    cellId = i;
//	    GetLogicalCellIndex(idx, i, dims);
//	    for (int j = 0; j < sizeof(idx) / sizeof(idx[0]); j++) {
//	    	    F4[j] = idx[j] + 1;
//		    if ( j == 0) {
//		    F2[j] = idx[j] + 1;
//		    F3[j] = idx[j];
//		    }
//		    else {
//			    F3[j] = idx[j] + 1;
//			    F2[j] = idx[j];
//		    }
//	    }
	    //cout << "Index " << F4[0] << " " << F4[1] << endl;
//	    if ( L <= F[GetPointIndex(idx,dims)] <= H and L <= F[GetPointIndex(F2,dims)] <= H and L <= F[GetPointIndex(F3,dims)] <= H and L <= F[GetPointIndex(F4,dims)] <= H ) {
//		    count++;
//    }		    

//    }

    return count;
    // IMPLEMENT ME!
}

int main()
{
    int  i;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj2_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    float ranges[10] = { -1, 1, -1, 0, 0, 1, -0.75, -0.25, 0.25, 0.75 };
    for (int i = 0; i < 5; i++)
    {
        int numCells = CountNumberOfCellsWithinThreshold(X, Y, dims, F, ranges[2*i], ranges[2*i+1]);
        cerr << "The number of cells between " << ranges[2*i] << " and " << ranges[2*i+1] << " is " << numCells << endl;
    }

    const int ncells = 5;
    int cellIds[ncells] = { 0, 50, 678, 1000, 1200 };
    for (i = 0 ; i < ncells ; i++)
    {
        float area = AreaForCell(X, Y, dims, cellIds[i]);
        cerr << "The area for cell " << cellIds[i] << " is " << area << endl;
    }

    const int npts = 11;
    float pt[npts][3] = 
         {
            {1.01119, 0.122062, 0},
            {0.862376, 1.33829, 0},
            {0.155026, 0.126123, 0},
            {0.69736, 0.0653565, 0},
            {0.2, 0.274117, 0},
            {0.893699, 1.04111, 0},
            {0.608791, -0.0533753, 0},
            {1.00543, 0.158024, 0},
            {0.384158, -0.0768977, 0},
            {0.666757, 0.60259, 0},
	    {1.0, -5.0, 0},
         };

    

    for (i = 0; i < 11; i++)
    {
        float f = EvaluateFieldAtLocation(pt[i], dims, X, Y, F);
        cerr << "Evaluated field at (" << pt[i][0] <<"," << pt[i][1] << ") as "
             << f << endl;
    }
    
   
    cerr << "Infinite loop here, else Windows people may have the terminal "
         << "disappear before they see the output."
         << " Remove these lines if they annoy you." << endl;
    cerr << "(press Ctrl-C to exit program)" << endl;
    while (1) ; 
}




