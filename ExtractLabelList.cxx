#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkDataReader.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vtkPointData.h>

int main ( int argc, char *argv[] )
{
    // Ensure a filename was specified
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " InputFilename: vtk surface with color " << endl;
        return EXIT_FAILURE;
    }
    std::cout<<"hello"<<std::endl;
    // Get the filename from the command line
    std::string fileName = argv[1];

    // ReadFile
    vtkSmartPointer< vtkPolyDataReader > reader = vtkSmartPointer< vtkPolyDataReader >::New() ;
    vtkSmartPointer< vtkPolyData > polyData = vtkSmartPointer< vtkPolyData >::New() ;
    reader->SetFileName( fileName.c_str() ) ;
    reader->Update() ;
    polyData = reader->GetOutput() ;

    //Checked if surface file with color no containing errors
    if (reader->GetErrorCode() !=0 )
    {
        std::cerr << "Unable to open input file: " << fileName.c_str() << std::endl ;
        return EXIT_FAILURE ;
    }

    vtkPointData* pointdata =  polyData->GetPointData();
    //Search all array in File
    for(unsigned i = 0; i < pointdata->GetNumberOfArrays(); i++){
        std::cout<<pointdata->GetArrayName(i)<<std::endl; //VectorId = 1
    }

    //OutputFile
    std::ofstream outputFile;
    outputFile.open("listLabel.txt",std::ofstream::out); //Name has to be change
    if (outputFile.good())
    {
        outputFile << "#!ascii file from ExtractLabelList project \n";
        //outputFile << polyData->GetNumberOfPoints() << " " << polyData->GetNumberOfPolys() << "\n";

        //Write in the file allLabels corresponding to each points - in the same order
        for(vtkIdType i = 0; i < polyData->GetNumberOfPoints(); i++)
        {
            //double p[3];
            //polyData->GetPoint(i,p); //This is identical to: output->GetPoints()->GetPoint(i,p);
            double vec[3];
            pointdata->GetArray(1)->GetTuple(i,vec);

            //std::cout << "Point " << i << " : (" << p[0] << " " << p[1] << " " << p[2]<<")" << std::endl;
            //std::cout << "RGB Value (Point "<<i << ") : " << vec[0] << " " << vec[1] << " " << vec[2]  << std::endl;
            //outputFile << p[0] <<" " << p[1]<<" "<< p[2] << "\n";
            outputFile << vec[0] <<" " << vec[1]<<" "<< vec[2] << "\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Unable to open file"<<std::endl;
    }
    outputFile.close();

//    //WriteFile - convert inputFile to ASCII format
//    std::string outputFileName = fileName + ".ASCII.vtk";
//    vtkSmartPointer< vtkPolyDataWriter > writer = vtkSmartPointer< vtkPolyDataWriter >::New() ;
//    writer->SetFileName(outputFileName.c_str() ) ;
//    writer->SetInputData( polyData ) ;
//    writer->SetFileTypeToASCII() ;
//    writer->Update() ;
//    return EXIT_SUCCESS ;
}
