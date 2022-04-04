#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDataSetReader.h>
#include <vtkRectilinearGrid.h>
#include <vtkFloatArray.h>


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
//  Function: EvaluateFieldAtLocation
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
//     F: a scalar field defined on the mesh.  Its size is dims[0]*dims[1].
//
//   Returns: the interpolated field value. 0 if the location is out of bounds.
//
// ****************************************************************************

float EvaluateFieldAtLocation(const float *pt, const int *dims, const float *X, 
                              const float *Y, const float *F)
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
    if (x1  == -1 or y1 == -1) {
            return 0;
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


void
WriteImage(vtkImageData *img, const char *filename)
{
    std::string full_filename = filename;
    full_filename += ".png";
    vtkPNGWriter *writer = vtkPNGWriter::New();
    writer->SetInputData(img);
    writer->SetFileName(full_filename.c_str());
    writer->Write();
    writer->Delete();
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

// ****************************************************************************
//  Function: ApplyBlueHotColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0<=F<=1) to a color using the blue 
//     hot color map.
//
//     The blue hot color map has:
//        F=0: (0,0,0.5) 
//        F=1: (1.0,1.0,1.0) 
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//      
//  Note: color map is in float (0 to 1) and output is in unsigned char
//        (0 to 255), so the floating point values you calculate for 
//        the three color channels need to be multiplied by 255 when
//        being assigned to RGB.
//
// ****************************************************************************

void ApplyBlueHotColorMap(float F, unsigned char *RGB)
{
	float f1 = 0.0 + F*(1.0 - 0.0);
	float f2 = 0.0 + F*(1.0 - 0.0);
	float f3 = 0.5 + F*(1.0 - 0.5);
	RGB[0] = f1 * 255;
	RGB[1] = f2 * 255;
	RGB[2] = f3 * 255;





}


// ****************************************************************************
//  Function: ApplyDifferenceColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0<=F<=1) to a color 
//     using a difference colormap.
//
//     The difference color map has:
//        F=0: (0,0,0.5) 
//        F=0.5: (1.0,1.0,1.0) 
//        F=1: (0.5, 0, 0)
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//      
//  Note: color map is in float (0 to 1) and output is in unsigned char
//        (0 to 255), so the floating point values you calculate for 
//        the three color channels need to be multiplied by 255 when
//        being assigned to RGB.
//
// ****************************************************************************

void ApplyDifferenceColorMap(float F, unsigned char *RGB)
{
	float f1,f2,f3;
	if (F < 0.5) {
		float t = F / 0.5;
		RGB[0] = (t * 1.0) * 255.0;
		RGB[1] = (t * 1.0) * 255.0;
		RGB[2] = (t * (1.0 - 0.5) + 0.5) * 255.0;
	}
	else if(F > 0.5) {
		float t = (F - 0.5) / 0.5;
		RGB[0] = (t * (0.5 - 1.0) + 1.0) * 255.0;
		RGB[1] = t * -255.0 + 255.0;
		RGB[2] = t * -255.0 + 255.0;
	}
	else {
		RGB[0] = 255.0;
		RGB[1] = 255.0;
		RGB[2] = 255.0;
	}
}

// ****************************************************************************
//  Function: ApplyHSVColorMap
//
//  Purpose: 
//     Maps a normalized scalar value F (0 <= F <= 1) to a color using 
//     an HSV rainbow colormap.
//
//     The rainbow colormap uses a saturation = 1.0, value = 1.0, 
//     and interpolates hue from 0 to 360 degrees.
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1  
//       RGB (output):  the location to store the color
//      
//  Note: as with the first two functions, make sure to multiple by 255 
//        when converting floats to unsigned chars.
//
// ****************************************************************************

void ApplyHSVColorMap(float F, unsigned char *RGB)  
{
	//cout << "F is: " << F << endl;
	//Referenced hanks slides from lecture 5 slide 35
    float hue = F * 6.0;
    int i = floor(hue);
    float f = hue - i;
    float p = 1.0 * (1.0 - 1.0); 
    float q = 1.0 * (1.0 - 1.0 * f);
    float t = 1.0 * (1.0 - 1.0 * (1.0 - f));
    //cout << "q is: " << q << " t is: " << t << " i is: "<< i << endl;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    switch(i) {
        case 0: r = 1.0; g = t; b = p; break;
        case 1: r = q; g = 1.0; b = p; break;
        case 2: r = p; g = 1.0; b = t; break;
        case 3: r = p; g = q; b = 1.0; break;
        case 4: r = t; g = p; b = 1.0; break;
	case 5: r = 1.0; g = p; b = q; break;
    }
    RGB[0] = r * 255.0;
    RGB[1] = g * 255.0;
    RGB[2] = b * 255.0;
}



int main()
{
    int  i, j;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj3_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);
    
    int nx = 500;
    int ny = 500;
    //float test = (249.0 - 0) / (499.0 - 0);
    //float inter = -9 + test * (X[49] - X[0]);
    //cout << "T value is " << test << endl;
    //cout << "Inter value is " << inter << endl;

    vtkImageData *images[3];
    unsigned char *buffer[3];
    for (i = 0 ; i < 3 ; i++)
    {
        images[i] = NewImage(nx, ny);
        buffer[i] = (unsigned char *) images[i]->GetScalarPointer(0,0,0);
    }

    for (i = 0 ; i < 3 ; i++)
       for (j = 0 ; j < 3*nx*ny ; j++)
            buffer[i][j] = 0;

    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++)
        {
            // ITERATE OVER PIXELS
            float pt[2];
	    //cout << "j is " << j << "ny is " << ny << endl;
            pt[0] = -9.0 + ((i / 499.0) * (9.0 - (-9.0)));
            pt[1] = -9.0 + ((j / 499.0) * (9.0 - (-9.0)));
	    //pt[0] = i / ((float)nx - 1.0)* 18.0 - 9.0;
	    //pt[1] = j / ((float)ny - 1.0) * 18.0 - 9.0;

	    //cout << "pt0 is " << pt[0] << " pt1 is " << pt[1] << endl;
	    //pt[1] is showing up as 5 instead of 0
            float f = EvaluateFieldAtLocation(pt,dims,X,Y,F);
	    //cout <<" Field values " << f << endl;
            float normalizedF = (f - 1.2) / (5.02 - 1.2); //...; see step 5 re 1.2->5.02
	    //cout << "Normalized field values " << normalizedF << endl;
            
            // I TAKE OVER HERE
            int offset = 3*(j*nx+i);
	    //cout <<"Offset value " << offset << " Buffer value: " << buffer << endl;
            ApplyBlueHotColorMap(normalizedF, buffer[0]+offset);
            ApplyDifferenceColorMap(normalizedF, buffer[1]+offset);
            ApplyHSVColorMap(normalizedF, buffer[2]+offset);
        }
    }
    float pt[2];
    pt[0] = 1.0;
    pt[1] = -5.0;
    float t = EvaluateFieldAtLocation(pt, dims,X,Y,F);
    cout << "Evalute field: " << t << endl;

    WriteImage(images[0], "bluehot");
    WriteImage(images[1], "difference");
    WriteImage(images[2], "hsv");
}
