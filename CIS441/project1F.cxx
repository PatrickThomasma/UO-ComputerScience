#include <iostream>
#include <algorithm>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <cmath>
#include <string>
#include <algorithm>
#define NORMALS

using std::sort;
using std::cerr;
using std::endl;

using namespace std;


double RC[1000][1000];


double ceil__441(double f)
{
    return ceil(f-0.00001);
}

double floor__441(double f)
{
    return floor(f+0.00001);
}

void Normalize(double *point) {
	double magnitude = sqrt(point[0]*point[0] + point[1]*point[1] + point[2]*point[2]);
	for (int i = 0; i < 3; ++i) {
		point[i] = point[i] / magnitude;
	}
}

double *Normalize(double x, double y, double z) {
	double *vec = new double[3];
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	Normalize(vec);
	return vec;
}


vtkImageData *
NewImage(int height, int width)
{
    vtkImageData *img = vtkImageData::New();
    img->SetDimensions(width, height, 1);
    img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

    return img;
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

void CrossProduct(double *left , double *right, double *result) {
	result[0] = left[1]*right[2] - left[2]*right[1];
	result[1] = left[2] * right[0] - left[0]*right[2];
	result[2] = left[0] * right[1] - left[1] *right[0];
}

double DotProduct(double *left, double *right) 
{
	double result = 0;
	for (int i = 0; i < 3; ++i) {
		result += left[i] * right[i];
	}
	return result;
}

class Matrix
{
  public:
    double          A[4][4];  // A[i][j] means row i, column j

    void            TransformPoint(const double *ptIn, double *ptOut);
    static Matrix   ComposeMatrices(const Matrix &, const Matrix &);
    void            Print(ostream &o);
};

void
Matrix::Print(ostream &o)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        char str[256];
        sprintf(str, "(%.7f %.7f %.7f %.7f)\n", A[i][0], A[i][1], A[i][2], A[i][3]);
        o << str;
    }
}

Matrix
Matrix::ComposeMatrices(const Matrix &M1, const Matrix &M2)
{
    Matrix rv;
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++)
        {
            rv.A[i][j] = 0;
            for (int k = 0 ; k < 4 ; k++)
                rv.A[i][j] += M1.A[i][k]*M2.A[k][j];
        }
    }
    return rv;
}

void
Matrix::TransformPoint(const double *ptIn, double *ptOut)
{
    ptOut[0] = ptIn[0]*A[0][0]
             + ptIn[1]*A[1][0]
             + ptIn[2]*A[2][0]
             + ptIn[3]*A[3][0];
    ptOut[1] = ptIn[0]*A[0][1]
             + ptIn[1]*A[1][1]
             + ptIn[2]*A[2][1]
             + ptIn[3]*A[3][1];
    ptOut[2] = ptIn[0]*A[0][2]
             + ptIn[1]*A[1][2]
             + ptIn[2]*A[2][2]
             + ptIn[3]*A[3][2];
    ptOut[3] = ptIn[0]*A[0][3]
             + ptIn[1]*A[1][3]
             + ptIn[2]*A[2][3]
             + ptIn[3]*A[3][3];
}

class Camera
{
  public:
    double          near, far;
    double          angle;
    double          position[3];
    double          focus[3];
    double          up[3];

    Matrix          ViewTransform();
    Matrix          CameraTransform();
    Matrix          DeviceTransform();
};



Matrix Camera::CameraTransform()
{
	double u[3], v[3], w[3] , O[3];

	for (int i = 0; i < 3; ++i)
	{
		O[i] = position[i];
		w[i] = position[i] - focus[i];
		v[i] = up[i];
	}
	CrossProduct(v,w,u);
	CrossProduct(w,u,v);

	Normalize(u);
	Normalize(v);
	Normalize(w);

	Matrix cameraTransform;
	cameraTransform.A[3][3] = 1;
	for (int i = 0; i < 3; ++i) {
		cameraTransform.A[i][3] = 0;
	}
	for (int i = 0; i < 3; ++i) {
		int j = 0;
		cameraTransform.A[i][j++] = u[i];
		cameraTransform.A[i][j++] = v[i];
		cameraTransform.A[i][j] = w[i];
	}
	double t[3];
	for (int i = 0; i < 3; ++i) {
		t[i] = 0 - O[i];
	}
	cameraTransform.A[3][0] = DotProduct(u,t);
	cameraTransform.A[3][1] = DotProduct(v,t);
	cameraTransform.A[3][2] = DotProduct(w,t);

	return cameraTransform;
}

Matrix Camera::ViewTransform() {

	Matrix viewTransform;
	double cot = cos(angle/2)/sin(angle/2);
	for (int i = 0; i < 4; ++i) {

		for (int j = 0; j < 4; ++j) {
			viewTransform.A[i][j] = 0;
		}
	}

	viewTransform.A[0][0] = cot;	
	viewTransform.A[1][1] = cot;
	viewTransform.A[2][2] = (far + near) / (far-near);
	viewTransform.A[2][3] = -1;
	viewTransform.A[3][2] = (2*far*near) / (far - near);

	return viewTransform;
}

Matrix Camera::DeviceTransform() {
	Matrix deviceTransform;
	double n = 1000;
	double m = 1000;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j)
		{
			deviceTransform.A[i][j] = 0;
		}
	}
	deviceTransform.A[0][0] = n / 2;
	deviceTransform.A[1][1] = m / 2;
	deviceTransform.A[2][2] = 1;
	deviceTransform.A[3][0] = n / 2;
	deviceTransform.A[3][1] = m / 2;
	deviceTransform.A[3][3] = 1;

	return deviceTransform;
}







double SineParameterize(int curFrame, int nFrames, int ramp)
{
    int nNonRamp = nFrames-2*ramp;
    double height = 1./(nNonRamp + 4*ramp/M_PI);
    if (curFrame < ramp)
    {
        double factor = 2*height*ramp/M_PI;
        double eval = cos(M_PI/2*((double)curFrame)/ramp);
        return (1.-eval)*factor;
    }
    else if (curFrame > nFrames-ramp)
    {
        int amount_left = nFrames-curFrame;
        double factor = 2*height*ramp/M_PI;
        double eval =cos(M_PI/2*((double)amount_left/ramp));
        return 1. - (1-eval)*factor;
    }
    double amount_in_quad = ((double)curFrame-ramp);
    double quad_part = amount_in_quad*height;
    double curve_part = height*(2*ramp)/M_PI;
    return quad_part+curve_part;
}

Camera
GetCamera(int frame, int nframes)
{
    double t = SineParameterize(frame, nframes, nframes/10);
    Camera c;
    c.near = 5;
    c.far = 200;
    c.angle = M_PI/6;
    c.position[0] = 40*sin(2*M_PI*t);
    c.position[1] = 40*cos(2*M_PI*t);
    c.position[2] = 40;
    c.focus[0] = 0;
    c.focus[1] = 0;
    c.focus[2] = 0;
    c.up[0] = 0;
    c.up[1] = 1;
    c.up[2] = 0;
    return c;
}


class Triangle
{
  public:
      double         X[3];
      double         Y[3];
      double	     Z[3];
      double colors[3][3];
      double normals[3][3];
      double shading[3];

  // would some methods for the triangle be helpful?
};

class Screen
{
  public:
      unsigned char   *buffer;
      int width, height;
  // would some methods for accessing and setting pixels be helpful?
};


struct LightingParameters
{
    LightingParameters(void)
    {
         lightDir[0] = -0.6;
         lightDir[1] = 0;
         lightDir[2] = -0.8;
         Ka = 0.3;
         Kd = 0.7;
         Ks = 2.8;
         alpha = 50.5;
    };
  

    double lightDir[3]; // The direction of the light source
    double Ka;          // The coefficient for ambient lighting
    double Kd;          // The coefficient for diffuse lighting
    double Ks;          // The coefficient for specular lighting
    double alpha;       // The exponent term for specular lighting
};


LightingParameters
GetLighting(Camera c)
{
    LightingParameters lp;
    lp.lightDir[0] = c.position[0]-c.focus[0];
    lp.lightDir[1] = c.position[1]-c.focus[1];
    lp.lightDir[2] = c.position[2]-c.focus[2];
    double mag = sqrt(lp.lightDir[0]*lp.lightDir[0]
                    + lp.lightDir[1]*lp.lightDir[1]
                    + lp.lightDir[2]*lp.lightDir[2]);
    if (mag > 0)
    {
        lp.lightDir[0] /= mag;
        lp.lightDir[1] /= mag;
        lp.lightDir[2] /= mag;
    }

    return lp;
}


int i = 0;

std::vector<Triangle>
GetTriangles(void)
{
    vtkPolyDataReader *rdr = vtkPolyDataReader::New();
    rdr->SetFileName("proj1f_geometry.vtk");
    //cerr << "Reading" << endl;
    i++;
    printf("Frame %d\n", i);
    rdr->Update();
    //cerr << "Done reading" << endl;
    if (rdr->GetOutput()->GetNumberOfCells() == 0)
    {
        cerr << "Unable to open file!!" << endl;
        exit(EXIT_FAILURE);
    }
    vtkPolyData *pd = rdr->GetOutput();

    int numTris = pd->GetNumberOfCells();
    vtkPoints *pts = pd->GetPoints();
    vtkCellArray *cells = pd->GetPolys();
    vtkDoubleArray *var = (vtkDoubleArray *) pd->GetPointData()->GetArray("hardyglobal");
    double *color_ptr = var->GetPointer(0);
    //vtkFloatArray *var = (vtkFloatArray *) pd->GetPointData()->GetArray("hardyglobal");
    //float *color_ptr = var->GetPointer(0);
    vtkFloatArray *n = (vtkFloatArray *) pd->GetPointData()->GetNormals();
    float *normals = n->GetPointer(0);
    std::vector<Triangle> tris(numTris);
    vtkIdType npts;
    vtkIdType *ptIds;
    int idx;
    for (idx = 0, cells->InitTraversal() ; cells->GetNextCell(npts, ptIds) ; idx++)
   {
        if (npts != 3)
        {
            cerr << "Non-triangles!! ???" << endl;
            exit(EXIT_FAILURE);
        }
        double *pt = NULL;
        pt = pts->GetPoint(ptIds[0]);
        tris[idx].X[0] = pt[0];
        tris[idx].Y[0] = pt[1];
        tris[idx].Z[0] = pt[2];
#ifdef NORMALS
        tris[idx].normals[0][0] = normals[3*ptIds[0]+0];
        tris[idx].normals[0][1] = normals[3*ptIds[0]+1];
        tris[idx].normals[0][2] = normals[3*ptIds[0]+2];
#endif
        pt = pts->GetPoint(ptIds[1]);
        tris[idx].X[1] = pt[0];
        tris[idx].Y[1] = pt[1];
        tris[idx].Z[1] = pt[2];
#ifdef NORMALS
        tris[idx].normals[1][0] = normals[3*ptIds[1]+0];
        tris[idx].normals[1][1] = normals[3*ptIds[1]+1];
        tris[idx].normals[1][2] = normals[3*ptIds[1]+2];
#endif
        pt = pts->GetPoint(ptIds[2]);
        tris[idx].X[2] = pt[0];
        tris[idx].Y[2] = pt[1];
        tris[idx].Z[2] = pt[2];
#ifdef NORMALS
        tris[idx].normals[2][0] = normals[3*ptIds[2]+0];
        tris[idx].normals[2][1] = normals[3*ptIds[2]+1];
        tris[idx].normals[2][2] = normals[3*ptIds[2]+2];
#endif

        // 1->2 interpolate between light blue, dark blue
        // 2->2.5 interpolate between dark blue, cyan
        // 2.5->3 interpolate between cyan, green
        // 3->3.5 interpolate between green, yellow
        // 3.5->4 interpolate between yellow, orange
        // 4->5 interpolate between orange, brick
        // 5->6 interpolate between brick, salmon
        double mins[7] = { 1, 2, 2.5, 3, 3.5, 4, 5 };
        double maxs[7] = { 2, 2.5, 3, 3.5, 4, 5, 6 };
        unsigned char RGB[8][3] = { { 71, 71, 219 },
                                    { 0, 0, 91 },
                                    { 0, 255, 255 },
                                    { 0, 128, 0 },
                                    { 255, 255, 0 },
                                    { 255, 96, 0 },
                                    { 107, 0, 0 },
                                    { 224, 76, 76 }
                                  };
        for (int j = 0 ; j < 3 ; j++)
        {
            float val = color_ptr[ptIds[j]];
            int r;
            for (r = 0 ; r < 7 ; r++)
            {
                if (mins[r] <= val && val < maxs[r])
                    break;
            }
            if (r == 7)
            {
                cerr << "Could not interpolate color for " << val << endl;
                exit(EXIT_FAILURE);
            }
            double proportion = (val-mins[r]) / (maxs[r]-mins[r]);
            tris[idx].colors[j][0] = (RGB[r][0]+proportion*(RGB[r+1][0]-RGB[r][0]))/255.0;
            tris[idx].colors[j][1] = (RGB[r][1]+proportion*(RGB[r+1][1]-RGB[r][1]))/255.0;
            tris[idx].colors[j][2] = (RGB[r][2]+proportion*(RGB[r+1][2]-RGB[r][2]))/255.0;
        }
    }

    return tris;
}


                                                

void RasterizeRightTriangle(double RightTriangle[][7], Screen *screen, double Triangles[], Triangle *triangles, int i) {
	 int bounds = 1000 * 1000 * 3;
	 double swap;

//	  cout << "Triangle 1: " << RightTriangle[0][0] << " , " << RightTriangle[0][1] << " , "<< RightTriangle[0][2] << " , Colors = [" << RightTriangle[0][3] << " , " << RightTriangle[0][4] << " , " << RightTriangle[0][5]<< "]" << endl; 
//	  cout << "Triangle 2: " << RightTriangle[1][0] << " , " << RightTriangle[1][1] << " ,"<< RightTriangle[1][2] << " , Colors = [" << RightTriangle[1][3] << " , " << RightTriangle[1][4] << " , " << RightTriangle[1][5]<< "]" << endl; 
//	  cout << "Triangle 3: " << RightTriangle[2][0] << " , " << RightTriangle[2][1] << " , "<< RightTriangle[2][2] << " , Colors = [" << RightTriangle[2][3] << " , " << RightTriangle[2][4] << " , " << RightTriangle[2][5]<< "]" << endl; 

//	 cout << "working on a going right triangle" << endl;
	 //FIX HERE* RIGHT TRIANGLE FROM C ASSUMED THAT [0][0] IS HIGHEST AND [2][0] IS LOWEST BUT IN THIS PROJ ITS CHANGED
//	 cout << "Scanlines are " << int(ceil__441(RightTriangle[0][0])) << " to " << int(floor__441(RightTriangle[2][0])) << endl;
        for (int c = ceil__441(RightTriangle[0][0]); c <= floor__441(RightTriangle[2][0]); c++) {
	//	cout <<"Working on scanline " << c << endl;
                double m = (RightTriangle[0][1] - RightTriangle[2][1]) / (RightTriangle[0][0] - RightTriangle[2][0]);
                double b = RightTriangle[2][1] - RightTriangle[2][0] * m;
                double topEnd = m * double(c) + b;
                double m2 = (RightTriangle[2][1] - RightTriangle[1][1]) / (RightTriangle[2][0] - RightTriangle[1][0]);
                double b2 = RightTriangle[1][1] - RightTriangle[1][0] * m2;
                double bottomEnd = m2 * double(c) + b2;
		//cout <<"Y-Intercepts are "<< bottomEnd << " , " << topEnd << endl;
		//cout << "Floor: " << ceil__441(bottomEnd) << " , " << floor__441(topEnd) << endl;
		if (topEnd < bottomEnd) {
			swap = bottomEnd;
			bottomEnd = topEnd;
			topEnd = swap;
		}

		double t = (c - RightTriangle[2][0]) / (RightTriangle[0][0] - RightTriangle[2][0]);
		double bottomzrgb[4];
		double topzrgb[4];
		for (int i = 0; i < 4; i++) {
			bottomzrgb[i] = RightTriangle[2][i + 2] + t * (RightTriangle[1][i + 2] - RightTriangle[2][i + 2]);
			topzrgb[i] = RightTriangle[2][i + 2] + t * (RightTriangle[0][i + 2] - RightTriangle[2][i + 2]);
		}
		double bshadepoint = RightTriangle[2][6] + t * (RightTriangle[1][6] - RightTriangle[2][6]);
                double tshadepoint = RightTriangle[2][6] + t * (RightTriangle[0][6] - RightTriangle[2][6]);


		if (RightTriangle[0][1] < RightTriangle[1][1]) {
			for (int i = 0; i < 4; i++) {
				swap = topzrgb[i];
				topzrgb[i] = bottomzrgb[i];
				bottomzrgb[i] = swap;
			}
			swap = tshadepoint;
                        tshadepoint = bshadepoint;
                        bshadepoint = swap;

		}

	//	cout << "One end is at Y=" << bottomEnd << ", Z=" << bottomzrgb[0] << " and color " << bottomzrgb[1] << " , " << bottomzrgb[2] << " , " <<bottomzrgb[3] << endl;
          //      cout << "Other end is at Y=" << topEnd <<", Z="<< topzrgb[0] << " and color " << topzrgb[1] << " , " <<topzrgb[2] << " , " << topzrgb[3] << endl;


                for (int r = ceil__441(bottomEnd); r <= floor__441(topEnd); r++) {
			int lowerbound = (3 * (r * screen->width + c));
			//cout << "rows are " << r << " to " << floor__441(topEnd) << endl;
			if ((3 * (r*screen->width + c)) >= 0 && (3 *(r*screen->width + c)) <= bounds && c < 1000 && c >= 0) {
			double zrgb[4];
			double shading;
			t = (r - topEnd) / (bottomEnd - topEnd);
			for (int i = 0; i < 4; i++) {
				zrgb[i] = (topzrgb[i]) + t * (bottomzrgb[i] - topzrgb[i]);
			}

			shading = tshadepoint + t * (bshadepoint - tshadepoint);
			if (zrgb[0] > RC[c][r]) {
//			cout << "Depositing color from Triangle " << i << " into column " << c << ", row " << r <<" With depth=" << zrgb[0] << ", and color " << zrgb[1] << " , " << zrgb[2] << " , " << zrgb[3] << " , " << shading << endl;
	                screen->buffer[(lowerbound) + 0] = ceil__441(255.0 * min(1.0,shading * zrgb[1]));
                        screen->buffer[(lowerbound) + 1] = ceil__441(255.0 * min(1.0,shading * zrgb[2]));
                        screen->buffer[(lowerbound) + 2] = ceil__441(255.0 * min(1.0,shading * zrgb[3]));
			RC[c][r] = zrgb[0];
			}
		}
		}
        }
}

void RasterizeLeftTriangle(double LeftTriangle[][7], Screen *screen, double Triangles[], Triangle *triangles, int i) {
	// cout << "Rasterirzing a left tri" << endl;

	 // cout << "Triangle 1: " << LeftTriangle[0][0] << " , " << LeftTriangle[0][1] << " Colors = ["<< LeftTriangle[0][2] << " , " << LeftTriangle[0][3] << " , " << LeftTriangle[0][4] << " , " << LeftTriangle[0][5]<< "]" << endl; 
	//  cout << "Triangle 2: " << LeftTriangle[1][0] << " , " << LeftTriangle[1][1] << " Colors = ["<< LeftTriangle[1][2] << " , " << LeftTriangle[1][3] << " , " << LeftTriangle[1][4] << " , "<< LeftTriangle[1][5] <<"]" << endl;
	//  cout << "Triangle 3: " << LeftTriangle[2][0] << " , " << LeftTriangle[2][1] << " Colors = ["<< LeftTriangle[2][2] << " , " << LeftTriangle[2][3] << " , " << LeftTriangle[2][4] << " , " << LeftTriangle[2][5]<< "]" << endl;
	  int bounds = 1000 * 1000 * 3;
	 double swap;
	// cout << "Scanlines are " << int(ceil__441(LeftTriangle[0][0])) << " to " << int(floor__441(LeftTriangle[2][0])) << endl;
	 for (int c = ceil__441(LeftTriangle[0][0]); c <= floor__441(LeftTriangle[2][0]); c++) {
		//cout <<"Working on scanline " << c << endl;
	 	double m = (LeftTriangle[0][1] - LeftTriangle[2][1]) / (LeftTriangle[0][0] - LeftTriangle[2][0]);
		double b = LeftTriangle[2][1] - LeftTriangle[2][0] * m;
		double topEnd = m * double(c) + b;
		double m2 = (LeftTriangle[0][1] - LeftTriangle[1][1]) / (LeftTriangle[0][0] - LeftTriangle[1][0]);
		double b2 = LeftTriangle[1][1] - LeftTriangle[1][0] * m2;
		double bottomEnd = m2 * double(c) + b2;
		//cout << "Floor: " << bottomEnd << " , " << topEnd << endl;
		if (bottomEnd < topEnd) {
                        swap = topEnd;
                        topEnd = bottomEnd;
                        bottomEnd = swap;
                }

		double t = (c - LeftTriangle[0][0]) / (LeftTriangle[1][0] - LeftTriangle[0][0]);
		double bottomzrgb[4];
		double topzrgb[4];
		for (int i = 0; i < 4; i++) {
			bottomzrgb[i] = LeftTriangle[0][i + 2] + t * (LeftTriangle[1][i + 2] - LeftTriangle[0][i + 2]);
			topzrgb[i] = LeftTriangle[0][i + 2] + t * (LeftTriangle[2][i + 2] - LeftTriangle[0][i + 2]);
		}
		double bshadepoint = LeftTriangle[0][6] + t * (LeftTriangle[1][6] - LeftTriangle[0][6]);
		double tshadepoint = LeftTriangle[0][6] + t * (LeftTriangle[2][6] - LeftTriangle[0][6]);

		if (LeftTriangle[1][1] < LeftTriangle[2][1]) {
			for (int i = 0; i < 4; i++) {
				swap = topzrgb[i];
				topzrgb[i] = bottomzrgb[i];
				bottomzrgb[i] = swap;
		}
			swap = tshadepoint;
			tshadepoint = bshadepoint;
			bshadepoint = swap;
	}



//		cout << "One end is at Y=" << bottomEnd << ", Z=" << bottomzrgb[0] << " and color " << bottomzrgb[1] << " , " << bottomzrgb[2] << " , " <<bottomzrgb[3] << endl;
//		cout << "Other end is at Y=" << topEnd <<", Z="<< topzrgb[0] << " and color " << topzrgb[1] << " , " <<topzrgb[2] << " , " << topzrgb[3] << endl;

		for (int r = ceil__441(topEnd); r <= floor__441(bottomEnd); r++) {
			//cout << "rows are " << r << " to " << floor__441(bottomEnd) << endl;
			int lowerbound = (3 * (r * screen->width + c));
			if ((3 * (r * screen->width + c)) >= 0 && (3 * (r*screen->width + c)) <= bounds && c < 1000 && c >= 0) {


			double shading;
			double zrgb[4];	
			t = (r - topEnd) / (bottomEnd - topEnd);
			for (int i = 0; i < 4; i++) {
				zrgb[i] = (topzrgb[i]) + t * (bottomzrgb[i] - topzrgb[i]);
			}

			shading = tshadepoint + t * (bshadepoint - tshadepoint);
                        if (zrgb[0] > RC[c][r]) {
  //                      cout << "Depositing color from Triangle " << i << " into column " << c << ", row " << r <<" With depth=" << zrgb[0] << ", and color " << zrgb[1] << " , " << zrgb[2] << " , " << zrgb[3] << " , " << shading << endl;
                        
			screen->buffer[(lowerbound) + 0] = ceil__441(255.0 * min(1.0,shading * zrgb[1]));
                        screen->buffer[(lowerbound) + 1] = ceil__441(255.0 * min(1.0,shading * zrgb[2]));
                        screen->buffer[(lowerbound) + 2] = ceil__441(255.0 * min(1.0,shading * zrgb[3]));
                        RC[c][r] = zrgb[0];

		}
		}
	 }
	 }

}
void RasterizeArbitraryTriangle(double Vertex[][7] , double Triangles[], Screen *screen, Triangle *triangles, int i)
{
//	   cout << "splitting this Triangle: " << endl; 
//	   cout << "(" << Vertex[0][0] << "," << Vertex[0][1] << "," << Vertex[0][2] << "), color = ("<< Vertex[0][3] << "," << Vertex[0][4] << ","<< Vertex[0][5] << ")" << endl;    
//	   cout << "(" << Vertex[1][0] << "," << Vertex[1][1] << "," << Vertex[1][2] << "), color = ("<< Vertex[1][3] << "," << Vertex[1][4] << ","<< Vertex[1][5] << ")" << endl;
//	   cout << "(" << Vertex[2][0] << "," << Vertex[2][1] << "," << Vertex[2][2] << "), color = ("<< Vertex[2][3] << "," << Vertex[2][4] << ","<< Vertex[2][5] << ")" << endl;

	  int middle;
	  int right;
	  int left;
	  //This for loop is to find out where the left,right, and middle vertices of the triangle are in the 2D vertex array
	  for (int i = 0; i < 3; i++) {
		  if (Triangles[1] == Vertex[i][0]) {

			  middle = i;
		  }
		  if (Triangles[0] == Vertex[i][0]) {

			  left = i;
		  }
		  if (Triangles[2] == Vertex[i][0]) {

			  right = i;
		  }
	  }
	  //split the triangle down the middle and find the new y coordinate after the split
	  double m = (Vertex[left][1] - Vertex[right][1]) / (Vertex[left][0] - Vertex[right][0]);
	  double b = Vertex[right][1] - Vertex[right][0] * m;
	  double y = m * Vertex[middle][0] + b;
	  double middle_zrgb[4];
	  double t = (Vertex[middle][0] - Vertex[left][0]) / (Vertex[right][0] - Vertex[left][0]);
//	  cout << "Checking t=" << t << ", Vertex[left][0] =" << Vertex[left][0] << ", Vertex[midde][0] =" << Vertex[middle][0] << "Vertex[right][0] =" << Vertex[right][0]<< endl;
	  for (int i = 0; i < 4; i++) {
		  middle_zrgb[i] = (Vertex[left][i + 2]) + t * (Vertex[right][i + 2] - Vertex[left][i + 2]);
	  }
	  double newshade = (Vertex[left][6]) + t * (Vertex[right][6] - Vertex[left][6]);
		 
	  //Create right and left triangle based off the split wit the new vertex with the old x and new y coordinate
	  double RightTriangle[3][7] = {{Vertex[middle][0], Vertex[middle][1], Vertex[middle][2], Vertex[middle][3], Vertex[middle][4], Vertex[middle][5],Vertex[middle][6]} ,{ Vertex[middle][0], y , middle_zrgb[0], middle_zrgb[1], middle_zrgb[2], middle_zrgb[3],newshade}, {Vertex[right][0] , Vertex[right][1],Vertex[right][2] , Vertex[right][3] , Vertex[right][4], Vertex[right][5],Vertex[right][6]}};
	  double LeftTriangle[3][7] = {{Vertex[left][0] , Vertex[left][1],Vertex[left][2] , Vertex[left][3] , Vertex[left][4], Vertex[left][5],Vertex[middle][6]} , {Vertex[middle][0], Vertex[middle][1], Vertex[middle][2], Vertex[middle][3], Vertex[middle][4], Vertex[middle][5],Vertex[middle][6]} ,{ Vertex[middle][0], y , middle_zrgb[0], middle_zrgb[1], middle_zrgb[2], middle_zrgb[3],newshade}};
//	  cout << "Into left:" << endl;
	  for (int i = 0; i < 3; i++) {
//	  	cout << "(" << LeftTriangle[i][0] << "," << LeftTriangle[i][1] << ","<< LeftTriangle[i][2] << "), color = (" << LeftTriangle[i][3] << " , "<< LeftTriangle[i][4] << "," << LeftTriangle[i][5] << ")" << endl;
	  }
//	  cout << "Into Right:" << endl;
	  for (int i = 0; i < 3; i++) {
//		  cout << "(" << RightTriangle[i][0] << "," << RightTriangle[i][1] << ","<< RightTriangle[i][2] << "), color = (" << RightTriangle[i][3] << " , "<< RightTriangle[i][4] << "," << RightTriangle[i][5] << ")" << endl;
	  }
	  
	   RasterizeLeftTriangle(LeftTriangle,screen,Triangles,triangles,i);
	   RasterizeRightTriangle(RightTriangle,screen,Triangles,triangles,i);
}

void CalculateShading(Triangle &triangle, LightingParameters &lp, Camera &cam) {
	for (int i =0 ; i < 3; i++) {
		double shadingvalue = 0;
		shadingvalue += lp.Ka;
		double *vecN = Normalize(triangle.normals[i][0], triangle.normals[i][1], triangle.normals[i][2]);
		double vecL[3];
		vecL[0] = lp.lightDir[0];
		vecL[1] = lp.lightDir[1];
		vecL[2] = lp.lightDir[2];

		shadingvalue += lp.Kd * max(0.0, DotProduct(vecL, vecN));

		double R[3], camVec[3], temp;
		temp = 2.0 * DotProduct(vecL, vecN);

		for (int p = 0; p < 3; p++)
		{
			vecN[p] *= temp;
		}
		for (int p=0; p < 3; p++)
		{
			R[p] = vecN[p] - vecL[p];
		}
		camVec[0] = cam.position[0] - triangle.X[i];
		camVec[1] = cam.position[1] - triangle.Y[i];
		camVec[2] = cam.position[2] - triangle.Z[i];

		Normalize(R);
		Normalize(camVec);

		shadingvalue += lp.Ks * pow(max(0.0, DotProduct(R, camVec)), lp.alpha);

		delete vecN;
		triangle.shading[i] = shadingvalue;
	}
}



int main()
{
   vtkImageData *image = NewImage(1000, 1000);
   unsigned char *buffer = 
     (unsigned char *) image->GetScalarPointer(0,0,0);
   int npixels = 1000*1000;
   for (int c = 0; c < 1000; c++) {
	   char imageName[128];
	   sprintf(imageName, "frame%03d", c);
	   Camera cam = GetCamera(c,1000);
	   LightingParameters lp = GetLighting(cam);


	   for (int d = 0; d < npixels * 3; d++) {
		   buffer[d] = 0;
	   }
  	   std::vector<Triangle> triangles = GetTriangles();
   	   Screen screen;
   	   screen.buffer = buffer;
   	   screen.width = 1000;
   	   screen.height = 1000;

   Matrix temp = Matrix::ComposeMatrices(cam.CameraTransform(), cam.ViewTransform());
   Matrix m = Matrix::ComposeMatrices(temp, cam.DeviceTransform());
   for (int i = 0; i < 1000; i++) {
     for (int j = 0; j < 1000; j++) {
            RC[i][j] = -1;
      }
}
//////////////////////////////////////////////////////////////////////////////////
   for (int i = 0; i < triangles.size(); i++) {

	   double Vertex[3][7];
	   double Points[3][4];
	   double tmpPnt[4];
	   CalculateShading(triangles[i], lp, cam);
	   for (int b = 0; b < 3; b++) {
		   Points[b][0] = triangles[i].X[b];
		   Points[b][1] = triangles[i].Y[b];
		   Points[b][2] = triangles[i].Z[b];
		   Points[b][3] = 1;
	   }


	   for (int b = 0; b < 3; b++) {
		   m.TransformPoint(Points[b], tmpPnt);
		   triangles[i].X[b] = tmpPnt[0]/tmpPnt[3];
		   triangles[i].Y[b] = tmpPnt[1]/tmpPnt[3];
		   triangles[i].Z[b] = tmpPnt[2]/tmpPnt[3];
		  
	   }

	   for (int j = 0; j < 3; j++) {
		   Vertex[j][0] = triangles[i].X[j];
		   Vertex[j][1] = triangles[i].Y[j];
		   Vertex[j][2] = triangles[i].Z[j];
		   Vertex[j][3] = triangles[i].colors[j][0];
		   Vertex[j][4] = triangles[i].colors[j][1];
		   Vertex[j][5] = triangles[i].colors[j][2];
		   Vertex[j][6] = triangles[i].shading[j];
	   } 

	   double Triangles[3] = {triangles[i].X[0] , triangles[i].X[1], triangles[i].X[2]};
	   for (int j = 0; j < 3; j++) {
		   for (int p = 0; p < 3; p++) {
			   if (Triangles[j] == Vertex[p][0] && j != p) {
				   //If an x coordinate is the same as another x coordinate in the triangle then this is not arbitrary but its a left/right triangle
				   int index[] = {0,1,2};
				   //Sort triangle by the x's and attach the y with them
				   sort(index, index + 3, [&](int n1, int n2) { return Vertex[n1][0] < Vertex[n2][0];});
				   //cout << "Triangles: " << Vertex[index[0]][0] << " , " << Vertex[index[0]][1] << " , " << Vertex[index[0]][2] << " , " << Vertex[index[0]][3] << endl;;
				   if (Vertex[index[1]][0] != Vertex[index[2]][0] ) {
					   //if x coordinate 1 and 2 are different then it will be a right triangle since index 2 is the biggest x coordinate
					   double RightTriangle[3][7];
					   for (int rt = 2; rt >= 0; rt--) {
						   for (int rv = 0; rv < 7; rv++) {
							   RightTriangle[rt][rv] = Vertex[index[rt]][rv];
						   }
					   }
					   RasterizeRightTriangle(RightTriangle,&screen,Triangles,&triangles[i],i);
				   }
				   else {
					   double LeftTriangle[3][7];

					   //else this will be a left triangle since index 0 is the smallest

					   for (int lt = 0; lt < 3; lt++) {
						   for (int lv = 0; lv < 7; lv++) {
							   LeftTriangle[lt][lv] = Vertex[index[lt]][lv];
						   }
					   }

					   RasterizeLeftTriangle(LeftTriangle,&screen,Triangles,&triangles[i], i);
				   }
				   break;
			   }
		   }
	   }
	   int asize = sizeof(Triangles) / sizeof(Triangles[0]);
	   sort(std::begin(Triangles), std::end(Triangles));
	   RasterizeArbitraryTriangle(Vertex, Triangles, &screen, &triangles[i],i);
	   //cout << endl;
	   //cout << endl;
   }

   // YOUR CODE GOES HERE TO DEPOSIT TRIANGLES INTO PIXELS USING THE SCANLINE ALGORITHM

   WriteImage(image, imageName);
   }
}
