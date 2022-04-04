#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkContourFilter.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkCamera.h>


int main(int argc, char *argv[])
{
   vtkDataSetReader *reader = vtkDataSetReader::New();
   reader->SetFileName("noise.vtk");
   reader->Update();
   //Contour Filter
   vtkContourFilter *renco = vtkContourFilter::New();
   renco->SetNumberOfContours(1);
   renco->SetValue(0,1.0);
   renco->SetInputConnection(reader->GetOutputPort());

   // Plane
   vtkPlane *plane = vtkPlane::New();
   plane->SetNormal(0,0,1);

   //Cutter
   vtkCutter *rencut = vtkCutter::New();
   rencut->SetCutFunction(plane);
   rencut->SetInputConnection(reader->GetOutputPort());
   rencut->Update();
   
   //mapper for cutter
   vtkDataSetMapper *mapper = vtkDataSetMapper::New();
   mapper->SetInputConnection(rencut->GetOutputPort());
   
   //mapper for contour
   vtkDataSetMapper *slicemap = vtkDataSetMapper::New();
   slicemap->SetInputConnection(renco->GetOutputPort());
   
   //lookup for cutter interpolate blue to red
   vtkLookupTable *lut = vtkLookupTable::New();
   mapper->SetLookupTable(lut);
   mapper->SetScalarRange(1,6);
   lut->Build();

   for (int i = 0; i < 256; i++) {
	   lut->SetTableValue(i,i,0.0,256.0 - i , 1.0);
   }
   //lookup for contour interpolate blue to red
   vtkLookupTable *slice = vtkLookupTable::New();
   slicemap->SetLookupTable(slice);
   slicemap->SetScalarRange(1,6);
   slice->Build();

   for (int i = 0; i < 256; i++) {
	   slice->SetTableValue(i,i,0.0,256.0 - i, 1.0);
   }

   //actor for cutter
   vtkActor *actor = vtkActor::New();
   actor->SetMapper(mapper);

   //actor for contour
   vtkActor *Sliceactor = vtkActor::New();
   Sliceactor->SetMapper(slicemap);

   //renderer for cutter
   vtkRenderer *ren = vtkRenderer::New();
   ren->AddActor(actor);


   //renderer for contour
   vtkRenderer *sren = vtkRenderer::New();
   sren->AddActor(Sliceactor);
   
   vtkRenderWindow *renwin = vtkRenderWindow::New();
   renwin->AddRenderer(ren);
   renwin->AddRenderer(sren);

   ren->SetViewport(0.0,0.0,0.5,1.0);
   sren->SetViewport(0.5,0.0,1.0,1.0);

   vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
   iren->SetRenderWindow(renwin);
   renwin->SetSize(768,768);
   renwin->Render();


   double isovalue = 1.0;
   for (int i = 0; i < 500; i++) {
	   renco->Update();
	   renco->SetValue(0,isovalue);
	   renco->Update();

	   isovalue += 0.01;

	   sren->GetActiveCamera()->ShallowCopy(ren->GetActiveCamera());

           renwin->Render();
   }
   //iren->Start();
}


