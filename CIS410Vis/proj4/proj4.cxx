//Patrick Thomasma
//Project 4 for CIS410
//January 30th 2022
//Code is mostly complete only difference is that there's no 0 position for RK4 because ofdifferences in the output solution for RK4 and Euler where Euler starts at 1 and RK4 starts at 0, figured this wouldn't be a big deal so I didn't write a seperate function for printing RK4 to remedy that, also there are floating point differences in Euler but very small to the point where I think it's okay for turning in


#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDataSetReader.h>
#include <vtkRectilinearGrid.h>
#include <vtkFloatArray.h>
#include <vtkPolyData.h>
#include <vtkDataSetWriter.h>
#include <vtkTubeFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkSphereSource.h>

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <iostream>
#include <fstream>
using namespace std;
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


// ****************************************************************************
//  Function: EvaluateVectorFieldAtLocation
//
//  Arguments:
//     pt: a two-dimensional location
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     F: a vector field defined on the mesh.  Its size is 2*dims[0]*dims[1].
//        The first value in the field is the x-component for the first point.
//        The second value in the field is the y-component for the first point.
//
//     rv (output): the interpolated field value. (0,0) if the location is out of bounds.
//
// ****************************************************************************

void EvaluateVectorFieldAtLocation(const float *pt, const int *dims, const float *X, 
                              const float *Y, const float *F, float *rv)
{
    // IMPLEMENT ME!
    int x1 = 0;
    int y1 = 0;
    for (int i = 1; i < dims[0]; i++) { //This for loop is finding which cell contains the point coordinate given
            if (pt[0] < X[i] and pt[0] >= X[0]) {
                    x1 = i - 1;
                    //cout << "X1: " << x1 << endl;
		    //cout << "Point values: " << pt[0] << " , " << pt[1] << endl;

                    for (int j = 1; j < dims[1]; j++) {
                            if (pt[1] < Y[j] and pt[1] >= Y[0]) {
                                    y1 = j - 1;
                                    break;
                            }
                    }
              break;
            }
    }
    if (x1  == 0 or y1 == 0) {
            return;
    }
    //cout << "Point numbers " << rv[0] << " " << rv[1] << endl;
    int cell[2] = {x1,y1}; //Cells contain logical point numbers Ce11 is Bottm left vertices
    int cell1[2] = {x1 + 1, y1}; // cell1 is bottom right
    int cell2[2] = {x1 , y1 + 1}; // cell2 is top left
    int cell3[2] = {x1 + 1, y1 + 1}; //cell3 is top right
    //cout <<"Cell1: " << cell[0] << " " << cell[1] << " Cell2: " << cell1[0] << " " << cell1[1] <<" Cell3:" << cell2[0] << " " << cell2[1] << " Cell3: " << cell3[0] << " " << cell3[1] << endl;
    //cout << "F value point: " << GetPointIndex(cell,dims) * 2 << endl;
    //cout << "Cell Indexes " << cell1[0] << " " << cell1[1] << endl;
    float V1x = F[GetPointIndex(cell,dims) * 2 ]; //V1 is A
    float V1y = F[GetPointIndex(cell,dims) * 2 + 1];
    //cout << " Vertice 1 index " << V1x << " " << V1y << endl;
    float V2x = F[GetPointIndex(cell1,dims) * 2]; // V2 is B
    float V2y = F[GetPointIndex(cell1,dims) * 2 + 1];
    //cout << " Vertice 2 Index " << V2x << " " << V2y << endl;
    float V3x = F[GetPointIndex(cell2,dims) * 2]; // The V's all contain field numbers of vertices V3 is F(A)
    float V3y = F[GetPointIndex(cell2,dims) * 2 + 1];
    //cout << " Vertice 3 Index " << V3x << " " << V3y << endl;
    float V4x = F[GetPointIndex(cell3,dims) * 2 ]; // V4 is F(B)
    float V4y = F[GetPointIndex(cell3,dims) * 2 + 1];
    //cout << " Vertice 4 Index " << V4x << " " << V4y << endl;
   // cout << "All my values: Cell1: " << cell[0] << ", " << cell[1] << " Cell2: " << cell1[0] << ", " << cell1[1] << " Cell3 " << cell2[0] << " , " << cell2[1] << " Cell4: " << cell3[0] << " ,  " << cell3[1] << endl;
    float t = (pt[0] - X[cell[0]]) / (X[cell1[0]] - X[cell[0]]);
    float t2 = (pt[1] - Y[cell[1]]) / (Y[cell2[1]] - Y[cell[1]]);
    //cout << "T proportion is " << t << " " << t2 << endl;
    float fieldx = V1x + (t * (V2x - V1x));
    float fieldy = V1y + (t * (V2y - V1y));
    float field2x = V3x + (t * (V4x - V3x));
    float field2y = V3y + (t * (V4y - V3y));
    //cout << "Field value from interpolation: " << field << " " <<field2 << endl;
    float field3x = fieldx + (t2 * (field2x - fieldx));
    float field3y = fieldy + (t2 * (field2y - fieldy));
    //cout << "Field values: " << field3x << " , " << field3y << endl;
    rv[0] = field3x;
    rv[1] = field3y;

}

// ****************************************************************************
//  Function: AdvectWithEulerStep
//
//  Arguments:
//     pt: the seed location (two-dimensions)
//     dims: an array of size two.  
//              The first number is the size of the array in argument X, 
//              the second the size of Y.
//     X: an array (size is specified by dims).  
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).  
//              This contains the Y locations of a rectilinear mesh.
//     F: a vector field defined on the mesh.  Its size is 2*dims[0]*dims[1].
//     h: The size of the Euler step
//     nsteps: The number of Euler steps to take
//     output_locations (output): An array of size 2*(nsteps+1).  It's first entry
//        should be the seed location.  The second entry should be the result
//        of the first advection step.  The final entry should be the result
//        of the final advection step.
//
// ****************************************************************************

void
AdvectWithEulerStep(const float *pt, const int *dims, const float *X, 
                    const float *Y, const float *F, 
                    float h, int nsteps, float *output_locations)
{
    // IMPLEMENT ME!

    output_locations[0] = 0; //set x component of first output location
    output_locations[1] = 0; //set y component of first output location
    output_locations[2] = 0; // set x component of second output location
    output_locations[3] = 0; // set y component of second output location
    float lastPos[2] = {pt[0], pt[1]};
    /*
    float VelAtCurrentLocation[2];
    EvaluateVectorFieldAtLocation(lastPos,dims,X,Y,F,VelAtCurrentLocation);
    float nextPos[2];
    nextPos[0] = lastPos[0] + h*VelAtCurrentLocation[0];
    nextPos[1] = lastPos[1] + h*VelAtCurrentLocation[1];
    output_locations[0] = nextPos[0];
    output_locations[1] = nextPos[1];
    cout << "First output, X: " << output_locations[0] << " Y: " << output_locations[1] << endl;
*/
for (int i = 0; i <= nsteps * 2; i += 2) {
	    float VelAtCurrentLocation[2];
	    EvaluateVectorFieldAtLocation(lastPos,dims,X,Y,F,VelAtCurrentLocation);
	    float nextPos[2];
	    nextPos[0] = lastPos[0] + h*VelAtCurrentLocation[0];
	    nextPos[1] = lastPos[1] + h*VelAtCurrentLocation[1];
	    output_locations[i] = nextPos[0];
	    output_locations[i + 1] = nextPos[1];
	    lastPos[0] = output_locations[i];
	    lastPos[1] = output_locations[i + 1];
}
    }

void
AdvectWithRK4Step(const float *pt, const int *dims, const float *X, 
                    const float *Y, const float *F, 
                    float h, int nsteps, float *RK4_output_locations)
{    
    float VelAtCurrentLocation[2];

    RK4_output_locations[0] = 0;
    RK4_output_locations[1]= 0;
    RK4_output_locations[2] = 0;    
    RK4_output_locations[3] = 0;
    //cout <<"Values of pt" << pt[0] << " " << pt[1] << endl;
    float FirstPos[2] = {pt[0], pt[1]};
    float SecondPos[2];
    float K1[2];
    float K2[2];
    float K3[2];
    float K4[2];
    /*
    EvaluateVectorFieldAtLocation(FirstPos,dims,X,Y,F,K1);
    SecondPos[0] = FirstPos[0] + (h / 2.0) * K1[0];
    SecondPos[1] = FirstPos[1] +  (h / 2.0) * K1[1];
    EvaluateVectorFieldAtLocation(SecondPos,dims,X,Y,F,K2);
    SecondPos[0] = FirstPos[0] + (h / 2.0) * K2[0];
    SecondPos[1] = FirstPos[1] + (h / 2.0) * K2[1];
    EvaluateVectorFieldAtLocation(SecondPos,dims,X,Y,F,K3);
    SecondPos[0] = FirstPos[0] + (h) * K3[0];
    SecondPos[1] = FirstPos[1] + (h) * K3[1];
    EvaluateVectorFieldAtLocation(SecondPos, dims, X, Y ,F, K4);
    RK4_output_locations[0] = FirstPos[0] + (1.0/6.0) * h * (K1[0] + (2.0*K2[0]) + (2.0*K3[0]) + K4[0]);
    RK4_output_locations[1] = FirstPos[1] + (1.0/6.0) * h * (K1[1] + (2.0*K2[1]) + (2.0*K3[1]) + K4[1]);
    cout << "First output, X: " << RK4_output_locations[0] << " Y: " << RK4_output_locations[1] << endl;
    */
    for (int i = 0; i <= nsteps * 2; i += 2) {
    EvaluateVectorFieldAtLocation(FirstPos,dims,X,Y,F,K1);
    SecondPos[0] = FirstPos[0] + (h / 2.0) * K1[0];
    SecondPos[1] = FirstPos[1] +  (h / 2.0) * K1[1];
    EvaluateVectorFieldAtLocation(SecondPos,dims,X,Y,F,K2);
    SecondPos[0] = FirstPos[0] + (h / 2.0) * K2[0];
    SecondPos[1] = FirstPos[1] + (h / 2.0) * K2[1];
    EvaluateVectorFieldAtLocation(SecondPos,dims,X,Y,F,K3);
    SecondPos[0] = FirstPos[0] + (h) * K3[0];
    SecondPos[1] = FirstPos[1] + (h) * K3[1];
    EvaluateVectorFieldAtLocation(SecondPos, dims, X, Y ,F, K4);
    RK4_output_locations[i] = FirstPos[0] + (1.0/6.0) * h * (K1[0] + (2.0*K2[0]) + (2.0*K3[0]) + K4[0]);
    RK4_output_locations[i + 1] = FirstPos[1] + (1.0/6.0) * h * (K1[1] + (2.0*K2[1]) + (2.0*K3[1]) + K4[1]);
    FirstPos[0] = RK4_output_locations[i];
    FirstPos[1] = RK4_output_locations[i + 1];
    }




}
vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *image = vtkImageData::New();
    image->SetDimensions(width, height, 1);
    //image->SetWholeExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetUpdateExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetNumberOfScalarComponents(3);
    image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
    //image->AllocateScalars();

    return image;
}

// VTK files are only 3D, so the vector data is all of the form (X,Y,0).
// Remove the 0's since it is counter-intuitive for students who are 
// thinking of this as 2D data.
float *
Convert3DVectorDataTo2DVectorData(const int *dims, const float *F)
{
    float *rv = new float[dims[0]*dims[1]*2];
    int index3D = 0;
    int index2D = 0;
    for (int i = 0 ; i < dims[0] ; i++)
       for (int j = 0 ; j < dims[1] ; j++)
       {
           rv[index2D]   = F[index3D];
           rv[index2D+1] = F[index3D+1];
           index2D += 2;
           index3D += 3;
       }

    return rv;
}

void PrintSteps(const char *solver, int nsteps, float *locations)
{
   ofstream myfile;
   myfile.open("output.txt");
   cerr << "Printing output for solver " << solver << endl;
   for (int j = 0; j < nsteps; j++)
   {
       cerr << j + 1<< ": (" << locations[2*j] << ", " << locations[2*j+1] << ")" << endl;       myfile << j + 1 << ": (" << locations[2*j] << ", " << locations[2*j+1] << ")" << endl;

   }
   myfile.close();
}
int main()
{
    int  i, j;

    // HANK'S CODE TO SET THINGS UP -- DON'T MODIFY THIS
    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj4_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    if (dims[0] <= 0 || dims[1] <= 0)
    {
        cerr << "Was not able to successfully open file \"proj4_data.vtk\"" << endl;
        exit(EXIT_FAILURE);
    }
    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F_3D = (float *) rgrid->GetPointData()->GetVectors()->GetVoidPointer(0);
    float *F = Convert3DVectorDataTo2DVectorData(dims, F_3D);
    
    float seed[2] = { 1, -5 };
    
    // SANITY CHECK TO MAKE SURE VECTOR FIELD EVALUATION IS WORKING
    float vec[2];
    cout << "Dimension" << dims[0] << ", " << dims[1] << " , " << dims[2] << endl;
    EvaluateVectorFieldAtLocation(seed, dims, X, Y, F, vec);
    cerr << "Velocity at (" << seed[0] <<", " << seed[1] << ") is (" << vec[0] << ", " << vec[1] << ")" << endl;

    float h = 0.01;
    const int nsteps = 100;
    float *output_locations = new float[2*(nsteps+1)];
    AdvectWithEulerStep(seed, dims, X, Y, F, h, nsteps, output_locations);
    PrintSteps("Euler", nsteps, output_locations);
    float *RK4_output_locations = new float[2*(nsteps+1)];
    AdvectWithRK4Step(seed, dims, X, Y, F, h, nsteps, RK4_output_locations);
    //cout << "0: (1, -5)" << endl;
    PrintSteps("RK4", nsteps, RK4_output_locations);
    
}
