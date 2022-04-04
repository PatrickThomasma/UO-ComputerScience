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

  /* vtkContourFilter *renco = vtkContourFilter::New();
   renco->SetNumberOfContours(2);
   renco->SetValue(0,2.4);
   renco->SetValue(1,4);
   renco->SetInputConnection(reader->GetOutputPort());
*/


   vtkPlane *plane = vtkPlane::New();
   plane->SetNormal(0,0,1);

   vtkCutter *rencut = vtkCutter::New();
   rencut->SetCutFunction(plane);
   rencut->SetInputConnection(reader->GetOutputPort());
   rencut->Update();

   vtkDataSetMapper *mapper = vtkDataSetMapper::New();
   mapper->SetInputConnection(rencut->GetOutputPort());
   
   vtkLookupTable *lut = vtkLookupTable::New();
   mapper->SetLookupTable(lut);
   mapper->SetScalarRange(1,6);
   lut->Build();

   vtkActor *actor = vtkActor::New();
   actor->SetMapper(mapper);

   vtkRenderer *ren = vtkRenderer::New();
   ren->AddActor(actor);

   vtkRenderWindow *renwin = vtkRenderWindow::New();
   renwin->AddRenderer(ren);

   vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
   iren->SetRenderWindow(renwin);
   renwin->SetSize(768,768);
   renwin->Render();
   iren->Start();
}


