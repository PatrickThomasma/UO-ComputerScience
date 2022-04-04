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




int main(int argc, char *argv[])
{
   vtkDataSetReader *reader = vtkDataSetReader::New();
   reader->SetFileName("noise.vtk");
   reader->Update();

   vtkContourFilter *renco = vtkContourFilter::New();
   renco->SetNumberOfContours(2);
   renco->SetValue(0,2.4);
   renco->SetValue(1,4);
   renco->SetInputConnection(reader->GetOutputPort());

   vtkPlane *plane = vtkPlane::New();
   plane->SetNormal(0,0,1);

   vtkCutter *rencut = vtkCutter::New();
   rencut->SetCutFunction(plane);
   rencut->SetInputConnection(reader->GetOutputPort());
   rencut->Update();

   vtkDataSetMapper *mapper = vtkDataSetMapper::New();
   mapper->SetInputConnection(rencut->GetOutputPort());

   vtkDataSetMapper *slicemap = vtkDataSetMapper::New();
   slicemap->SetInputConnection(renco->GetOutputPort());
   
   vtkLookupTable *lut = vtkLookupTable::New();
   mapper->SetLookupTable(lut);
   mapper->SetScalarRange(1,6);
   lut->Build();

   for (int i = 0; i < 256; i++) {
	   lut->SetTableValue(i,i,0.0,256.0 - i , 1.0);
   }
   vtkLookupTable *slut = vtkLookupTable::New();
   slicemap->SetLookupTable(slut);
   slicemap->SetScalarRange(1,6);

   for (int i = 0; i < 256; i++) {
	   slut->SetTableValue(i,i,0.0,256.0 - i, 1.0);
   }

   vtkActor *actor = vtkActor::New();
   actor->SetMapper(mapper);

   vtkActor *Sliceactor = vtkActor::New();
   Sliceactor->SetMapper(slicemap);

   vtkRenderer *ren = vtkRenderer::New();
   ren->AddActor(actor);

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
   iren->Start();
}


